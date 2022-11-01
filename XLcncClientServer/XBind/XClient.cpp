#include <XClient.h>

#include <chrono>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h> //! Problem for PyBind.
#include <unistd.h>
#include <iostream>
#include <thread>

#include <lodepng.h>

//! Transfer raw pixels into a png in memory, then make packages myChunks.
void XClient::encodeRawToPng(unsigned char *thePixels, int theWidth, int theHeight){

    //! Encode from raw pixels to in-memory PNG file.
    std::vector<unsigned char> thePng;
    unsigned error = lodepng::encode(thePng, thePixels, theWidth, theHeight);
    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;

    //! Will be saved to : ~linuxcnc/configs/sim/axis/
    //! lodepng::save_file(thePng,"pngtest.png");

    //! Save to fixed packages. The last package size is set to fit the data size.
    size_t packagesize=10240;
    std::vector<unsigned char> theChunk;
    uint k=0;
    for(uint i=0; i<thePng.size(); i++){
        theChunk.push_back(thePng[i]);
        if(k==packagesize){
            myChunks.push_back(theChunk);
            theChunk.clear();
            k=0;
        }
        if(i==thePng.size()-1){
            myChunks.push_back(theChunk);
        }
        k++;
    }
}
//! Return the size of myChunks.
size_t XClient::getChunksByteSize(){
    //! Get size of all packages.
    size_t size=0;
    for(uint i=0; i<myChunks.size(); i++){
        for(uint j=0; j<myChunks.at(i).size(); j++){
            size++;
        }
    }
    return size;
}
//! Return the size of one chunk.
size_t XClient::getChunkByteSize(std::vector<unsigned char> theChunk){
    //! Get size of all packages.
    size_t size=0;
    for(uint i=0; i<theChunk.size(); i++){
            size++;

    }
    return size;
}
//! Run the client.
void XClient::run()
{
    if(!init){
        socket_desc_main = socket_init_client();
        if (socket_desc_main == 1){
            std::cout<<"Could not init socket client!"<<std::endl;
            return;
        }
        init=1;
    }

    //! Client is in endless loop sending images.
    //! while(1){

    //! receive_text(socket_desc_main);
    //! receive_text(socket_desc_main);
    //! send_text(socket_desc_main);

    //! Send texture data.
    send_memory(socket_desc_main);
    //! Wait for message.
    receive_text(socket_desc_main);
    //! }

    //! This part is left for info.
    /*
    delay(100);

    socket_desc_main = socket_init_client();
    if (socket_desc_main == 1)
    {
        printf("Could not init socket client!\n");
        return 1;
    }
    receive_image(socket_desc_main);
    close(socket_desc_main);
    printf("Client Socket Closed!!!\n");
    */
}
//! Close.
void XClient::closeClient(){
    close(socket_desc_main);
    std::cout<<"Client Socket Closed!!!"<<std::endl;
}
//! Send memory.
void XClient::send_memory(int socket){
    int size=0 , read_size =0, total_size = 0, stat=0;
    uint packet_index=0;
    unsigned char send_buffer[10240];
    char read_buffer[256];
    packet_index = 0;

    size=getChunksByteSize();
    //! std::cout<<"Chunks to send:"<<myChunks.size()<<std::endl;
    //! std::cout<<"Chunks total bytes:"<<size<<std::endl;
    //! Send Picture Size
    //! std::cout<<("Sending Picture Size\n");
    send(socket, (void *)&size, sizeof(int), 0);

    //! Send Picture as Byte Array
    //! std::cout<<("Sending Picture as Byte Array\n");

    do { //! Read while we get errors that are due to signals.
        stat = recv(socket, &read_buffer , 255, 0);
        //! std::cout<<"Bytes read:"<<stat<<std::endl;
    } while (stat < 0);

    //! std::cout<<"Received data in socket"<<std::endl;
    //! std::cout<<"Socket data:"<<read_buffer<<std::endl;

    while(packet_index!=myChunks.size())
    {
        //! Read from the file into our send buffer
        std::vector<unsigned char> theChunk=myChunks.at(packet_index);
        read_size = getChunkByteSize(theChunk);
        total_size+=read_size;
        //! Vector to array..
        //! std::vector<double> v;
        //! double* a = &v[0];
        memcpy(send_buffer,&theChunk[0],read_size);

        //! Send data through our socket until nothing to send.
        do {
            stat = send(socket, send_buffer, read_size, 0);
        } while (stat < 0);

        //! std::cout<<"Packet Number:"<<packet_index<<std::endl;
        //! std::cout<<"Packet Size Sent"<<read_size<<std::endl;
        //! std::cout<<"Total bytes send"<<total_size<<std::endl;
        //! std::cout<<std::endl;
        //! std::cout<<std::endl;

        packet_index++;

        //! Zero out our send buffer
        bzero(send_buffer, sizeof(send_buffer));
    }
    myChunks.clear();
}
//! Send text.
int XClient::send_text(int socket, std::string theText)
{
    int n;
    char buffer[TEXTBUFFERSIZE];
    strcpy(buffer,theText.c_str());
    n = send(socket, buffer, sizeof(buffer), 0);
    if (n <= 0){
        perror("[-]Error in sending text.");
        return -1;
    }

    bzero(buffer, sizeof(buffer));
    return 0;
}
//! Recieve text.
int XClient::receive_text(int socket)
{
    int n;
    char buffer[TEXTBUFFERSIZE];

    n = recv(socket, buffer, TEXTBUFFERSIZE, 0);
    if (n <= 0)
    {
        return -1;
    }
    //! std::cout<<"Received Text:"<<buffer<<std::endl;

    bzero(buffer, TEXTBUFFERSIZE);
    return 0;
}
//! Send image.
void XClient::send_image(int socket)
{
    FILE *picture;
    int size, read_size, stat, packet_index;
    char send_buffer[10240], read_buffer[256];
    packet_index = 1;

    picture = fopen("picture.jpeg", "r");
    std::cout<<"Getting Picture Size"<<std::endl;

    if(picture == NULL)
    {
        std::cout<<"Error Opening Image File"<<std::endl;
    }

    fseek(picture, 0, SEEK_END);
    size = ftell(picture);
    fseek(picture, 0, SEEK_SET);
    std::cout<<"Total Picture size:"<<size<<std::endl;

    //! Send Picture Size
    std::cout<<("Sending Picture Size\n");
    send(socket, (void *)&size, sizeof(int), 0);

    //! Send Picture as Byte Array
    std::cout<<("Sending Picture as Byte Array\n");

    do { //! Read while we get errors that are due to signals.
        stat = recv(socket, &read_buffer , 255, 0);
        std::cout<<"Bytes read:"<<stat<<std::endl;
    } while (stat < 0);

    std::cout<<"Received data in socket"<<std::endl;
    std::cout<<"Socket data:"<<read_buffer<<std::endl;

    while(!feof(picture))
    {
        //! while(packet_index = 1){
        //! Read from the file into our send buffer
        read_size = fread(send_buffer, 1, sizeof(send_buffer)-1, picture);

        //! Send data through our socket
        do{
            stat = send(socket, send_buffer, read_size, 0);
        }while (stat < 0);

        std::cout<<"Packet Number:"<<packet_index<<std::endl;
        std::cout<<"Packet Size Sent"<<read_size<<std::endl;
        std::cout<<std::endl;
        std::cout<<std::endl;

        packet_index++;

        //! Zero out our send buffer
        bzero(send_buffer, sizeof(send_buffer));
    }
    fclose(picture);
}
//! Recieve image.
int XClient::receive_image(int socket){
    int recv_size = 0,size = 0, read_size, write_size, packet_index =1,stat;

    char imagearray[10241];
    FILE *image;

    //! Find the size of the image
    do{ stat = recv(socket, &size, sizeof(int), 0);
    } while(stat<0);

    std::cout<<"Packet received."<<std::endl;
    std::cout<<"Packet size:"<<stat<<std::endl;
    std::cout<<"Image size:"<<size<<std::endl;
    std::cout<<std::endl;

    char buffer[] = "Got it";

    //! Send our verification signal
    do{ stat = write(socket, &buffer, sizeof(int));
    } while(stat<0);

    std::cout<<"Reply sent"<<std::endl;
    std::cout<<std::endl;

    image = fopen("recieved.jpeg", "w");

    if(image == NULL) {
        printf("Error has occurred. Image file could not be opened\n");
        return -1; }

    //! Loop while we have not received the entire file yet

    struct timeval timeout = {10,0};

    fd_set fds;
    int buffer_fd;

    while(recv_size < size) {
        //! while(packet_index < 2){

        FD_ZERO(&fds);
        FD_SET(socket, &fds);

        buffer_fd = select(FD_SETSIZE,&fds,NULL,NULL,&timeout);

        if(buffer_fd < 0){
            std::cout<<"error: bad file descriptor set."<<std::endl;
        }

        if(buffer_fd == 0){
            std::cout<<"error: buffer read timeout expired."<<std::endl;
        }

        if(buffer_fd > 0){
            do{ read_size = recv(socket,imagearray, 10241, 0);
            } while(read_size <0);

            std::cout<<"Packet number received:"<<packet_index<<std::endl;
            std::cout<<"Packet size:"<<read_size<<std::endl;

            //! Write the currently read data into our image file
            write_size = fwrite(imagearray,1,read_size, image);
            std::cout<<"Written image size:"<<write_size<<std::endl;

            if(read_size !=write_size)
            {
                printf("error in read write\n");
            }

            //! Increment the total number of bytes read
            recv_size += read_size;
            packet_index++;
            std::cout<<"Total received image size:"<<recv_size<<std::endl;
            std::cout<<std::endl;
            std::cout<<std::endl;
        }
    }

    fclose(image);
    std::cout<<"Image successfully Received!"<<std::endl;
    return 1;
}
//! Init client.
int XClient::socket_init_client()
{
    int socket_desc;
    sockaddr_in server;

    //! Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);

    if (socket_desc == -1){
        std::cout<<"Could not create socket"<<std::endl;
    }

    memset(&server, 0,sizeof(server));
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8889 );

    //! Connect to remote server
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //! cout<<strerror(errno);
        close(socket_desc);
        puts("Connect Error");
        return 1;
    }

    puts("Connected\n");

    std::cout<<"Debug: socket_desc:"<<socket_desc<<std::endl;
    return socket_desc;
}
//! Delay
void XClient::delay(int number_of_seconds){
    //! Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
    //! Storing start time
    clock_t start_time = clock();
    //! looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}

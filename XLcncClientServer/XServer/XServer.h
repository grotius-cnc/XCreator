#ifndef XCServer_H
#define XCServer_H

#include <iostream>
#include <thread>
#include <tcp_acceptor.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <mutex>

#include <glad/glad.h>
#include <glfw3.h>

#include <XPixmap.h>
#include <lodepng.h>

#define SIZE 1024

//! Class to enchange myData over sockets.
class XServer {
public:
    //! Empty constructor using port : 12345
    XServer(){
        std::thread thr(&XServer::run,this);
        thr.detach();
    }
    //! Close, close socket descriptor.
    ~XServer(){}
    //! Return pixmap data, texture data.
    XPixmap Pixmap(){
        XPixmap thePixmap;
        //! Lock other trhead from accessing the same var.
        myMutex.lock();
        thePixmap=myPixmap;
        myMutex.unlock();
        return thePixmap;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    XPixmap myPixmap;
    std::mutex myMutex;
public:
    //! Run the server.
    int run(){
        int socket_desc_main , new_socket_main;

        socket_desc_main = socket_init_server();
        if (socket_desc_main == 1)
        {
            std::cout<<"Could not init socket Server!"<<std::endl;
            return 1;
        }
        new_socket_main = socket_handshake_server(socket_desc_main);

        while(1){

            //! start = std::chrono::high_resolution_clock::now();
            //! receive_image(new_socket_main);

            //! Recieve texture data.
            myPixmap=receive_memory(new_socket_main);
            //! Send ok back.
            send_text(new_socket_main);
            //! end = std::chrono::high_resolution_clock::now();
            //!
            //! std::cout << "Elapsed time in milliseconds: "<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
        }
        close(socket_desc_main);
        fflush(stdout);
        //! std::cout<<"Server Socket Closed!!!"<<std::endl;

        //! This part is left for info.
        /*
        socket_desc_main = socket_init_server();
        if (socket_desc_main == 1)
        {
            printf("Could not init socket Server!\n");
            return 1;
        }
        new_socket_main = socket_handshake_server(socket_desc_main);
        send_image(new_socket_main);
        close(socket_desc_main);
        fflush(stdout);
        std::cout<<"Server Socket Closed!!!"<<std::endl;
        */
        return 0;
    }
    //! Recieve memory, recieve data like textures.
    XPixmap receive_memory(int socket){

        int recv_size = 0,size = 0, read_size, write_size, packet_index =1,stat;

        unsigned char imagearray[10241];

        //! Find the size of the image
        do{ stat = recv(socket, &size, sizeof(int), 0);
        } while(stat<0);

        //! std::cout<<"Image size:"<<size<<std::endl;
        //! std::cout<<std::endl;

        char buffer[] = "Got it";

        //! Send our verification signal
        do { stat = write(socket, &buffer, sizeof(int));
        } while(stat<0);

        //! std::cout<<"Reply sent"<<std::endl;
        //! std::cout<<std::endl;

        //! Loop while we have not received the entire file yet

        struct timeval timeout = {10,0};

        fd_set fds;
        int buffer_fd;
        std::vector<std::vector<unsigned char>> theChunks;
        while(recv_size < size) {
            //! while(packet_index < 2){

            FD_ZERO(&fds);
            FD_SET(socket, &fds);

            buffer_fd = select(FD_SETSIZE,&fds,NULL,NULL,&timeout);

            if (buffer_fd < 0)
                std::cout<<"error: bad file descriptor set."<<std::endl;

            if (buffer_fd == 0)
                std::cout<<"error: buffer read timeout expired."<<std::endl;

            if (buffer_fd > 0)
            {
                do {
                    //! In this section we build the chunk vector.
                    read_size = recv(socket,imagearray, 10241, 0);

                    std::vector<unsigned char> theChunk;
                    for(int i=0; i<read_size; i++){
                        theChunk.push_back(imagearray[i]);
                    }
                    theChunks.push_back(theChunk);

                } while(read_size <0);

                //! std::cout<<"Packet number received:"<<packet_index<<std::endl;
                //! std::cout<<"Packet size:"<<read_size<<std::endl;

                write_size = read_size;
                //! std::cout<<"Written image size:"<<write_size<<std::endl;

                if(read_size !=write_size)
                {
                    //! std::cout<<"error in read write"<<std::endl;
                }

                //! Increment the total number of bytes read
                recv_size += read_size;
                packet_index++;
                //! std::cout<<"Total received image size:"<<recv_size<<std::endl;
                //! std::cout<<std::endl;
                //! std::cout<<std::endl;
            }
        }
        return decodePngToRaw(theChunks);
    }
    //! Decode the png in memory data to raw pixel data.
    XPixmap decodePngToRaw(std::vector<std::vector<unsigned char>> theChunks){
        //! Get size of all packages.
        size_t size=0;
        for(uint i=0; i<theChunks.size(); i++){
            for(uint j=0; j<theChunks.at(i).size(); j++){
                size++;
            }
        }
        //! Restore back multiple packages into the original png.
        std::vector<unsigned char> thePng;
        for(uint i=0; i<theChunks.size(); i++){
            for(uint j=0; j<theChunks.at(i).size(); j++){
                thePng.push_back(theChunks.at(i).at(j));
            }
        }
        //! Save to file for test.
        lodepng::save_file(thePng,"lodepngtest.png");
        //! Decode the png into raw pixels.
        XPixmap thePixmap;
        uint error = lodepng::decode(thePixmap.pixels, thePixmap.width, thePixmap.height, thePng);
        if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
        return thePixmap;
    }
    //! Send text.
    int send_text(int socket)
    {
        int n;
        char buffer[SIZE] = "Test sending from Server!\n";

        n = send(socket, buffer, sizeof(buffer), 0);
        if (n <= 0){
            perror("[-]Error in sending text.");
            return -1;
        }

        bzero(buffer, sizeof(buffer));
        return 0;
    }
    //! Recieve text.
    std::string receive_text(int socket)
    {
        std::string str;
        int n;
        char buffer[SIZE];

        n = recv(socket, buffer, SIZE, 0);
        if (n <= 0)
        {
            return "";
        }
        // std::cout<<"Received Text:"<<buffer<<std::endl;
        str=buffer;
        //! Empty buffer.
        bzero(buffer, SIZE);
        return str;
    }
    //! Send image.
    void send_image(int socket){

        FILE *picture;
        int size, read_size, stat, packet_index;
        char send_buffer[10240], read_buffer[256];
        packet_index = 1;

        picture = fopen("picture.jpeg", "r");
        std::cout<<"Getting Picture Size"<<std::endl;

        if(picture == NULL)
        {
            std::cout<<"Error Opening Image File."<<std::endl;
        }

        fseek(picture, 0, SEEK_END);
        size = ftell(picture);
        fseek(picture, 0, SEEK_SET);
        printf("Total Picture size: %i\n",size);

        //Send Picture Size
        std::cout<<"Sending Picture Size."<<std::endl;
        send(socket, (void *)&size, sizeof(int), 0);

        //Send Picture as Byte Array
        std::cout<<"Sending Picture as Byte Array."<<std::endl;

        do { //Read while we get errors that are due to signals.
            stat = recv(socket, &read_buffer , 255, 0);
            printf("Bytes read: %i\n",stat);
        } while (stat < 0);

        std::cout<<"Received data in socket."<<std::endl;
        //! printf("Socket data: %c\n", read_buffer);

        while(!feof(picture))
        {
            //! while(packet_index = 1){
            //! Read from the file into our send buffer
            read_size = fread(send_buffer, 1, sizeof(send_buffer)-1, picture);

            //! Send data through our socket
            do{
                stat = send(socket, send_buffer, read_size, 0);
            }while (stat < 0);

            //! std::cout<<"Packet Number:"<<packet_index<<std::endl;
            //! std::cout<<"Packet Size Sent:"<<read_size<<std::endl;
            //! std::cout<<std::endl;
            //! std::cout<<std::endl;

            packet_index++;

            //! Zero out our send buffer
            bzero(send_buffer, sizeof(send_buffer));
        }
        fclose(picture);
    }
    //! Recieve image.
    int receive_image(int socket){

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
        do { stat = write(socket, &buffer, sizeof(int));
        } while(stat<0);

        std::cout<<"Reply sent"<<std::endl;
        std::cout<<std::endl;

        image = fopen("recieved.jpeg", "w");

        if( image == NULL) {
            std::cout<<"Error has occurred. Image file could not be opened."<<std::endl;
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

            if (buffer_fd < 0)
                std::cout<<"error: bad file descriptor set."<<std::endl;

            if (buffer_fd == 0)
                std::cout<<"error: buffer read timeout expired."<<std::endl;

            if (buffer_fd > 0)
            {
                do{
                    read_size = recv(socket,imagearray, 10241, 0);
                }while(read_size <0);

                std::cout<<"Packet number received:"<<packet_index<<std::endl;
                std::cout<<"Packet size:"<<read_size<<std::endl;


                //! Write the currently read data into our image file
                write_size = fwrite(imagearray,1,read_size, image);
                std::cout<<"Written image size:"<<write_size<<std::endl;

                if(read_size !=write_size)
                {
                    std::cout<<"error in read write"<<std::endl;
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
    //! Init server.
    int socket_init_server()
    {
        int socket_desc;
        struct sockaddr_in server;
        //! Create socket
        socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_desc == -1)
        {
            std::cout<<"Could not create socket"<<std::endl;
        }

        //! Prepare the sockaddr_in structure
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons( 8889 );

        //! Bind
        if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
        {
            puts("bind failed");
            return 1;
        }

        puts("bind done");

        //! Listen
        listen(socket_desc , 3);

        //! Accept and incoming connection
        puts("Waiting for incoming connections...");

        std::cout<<"Debug: socket_desc:"<<socket_desc<<std::endl;
        return socket_desc;
    }
    //! Socket handshake server.
    int socket_handshake_server(int socket_desc)
    {
        int new_socket, c;
        struct sockaddr_in client;

        c = sizeof(struct sockaddr_in);

        if((new_socket = accept(socket_desc, (struct sockaddr *)&client,(socklen_t*)&c)))
        {
            puts("Connection accepted");
        }

        fflush(stdout);

        if (new_socket<0)
        {
            std::cerr<<"Accept Failed"<<std::endl;
            return 1;
        }

        return new_socket;
    }
};
#endif


























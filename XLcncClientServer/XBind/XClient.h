#ifndef XCLIENT_H
#define XCLIENT_H

#include <thread>
#include <iostream>
#include <vector>

#define TEXTBUFFERSIZE 1024

//! This class has a source file to avoid pyBind11 complaining.
class XClient {
public:
    //! Empty constructor.
    XClient(){
        //! Python does the tread, otherwise:
        //! std::thread myThread(&XClient::run,this);
        //! myThread.detach();
    }
    //! Empty destructor.
    ~XClient(){}
    //! Set data from the python XBind class.
    void encodeRawToPng(unsigned char *thePixels, int theWidth, int theHeight);
    //! Run the client.
    void run();
    //! Close.
    void closeClient();
private:
    int socket_desc_main;
    //! Used to init socket.
    bool init=0;
    //! Png into packages of fixed size.
    std::vector<std::vector<unsigned char>> myChunks;
    //! Get the size of chunks, myChunks.
    size_t getChunksByteSize();
    //! Get the size of one chunk.
    size_t getChunkByteSize(std::vector<unsigned char> theChunk);
    //! Send data like textures to the server.
    void send_memory(int socket);
    //! Send text to the server.
    int send_text(int socket, std::string theText);
    //! Recieve text from server.
    int receive_text(int socket);
    //! Send image to server.
    void send_image(int socket);
    //! Recieve image from server.
    int receive_image(int socket);
    //! Delay function can be used in loop.
    void delay(int number_of_seconds);
    //! Init client.
    int socket_init_client();
};
#endif












#ifndef XCServer_H
#define XCServer_H

/*
        Copyright (c) 2022 Skynet Cyberdyne

        This software is provided 'as-is', without any express or implied
        warranty. In no event will the authors be held liable for any damages
        arising from the use of this software.

        Permission is granted to anyone to use this software for any purpose,
        excluding commercial applications, and to alter it and redistribute it
        freely, subject to the following restrictions:

        1. The origin of this software must not be misrepresented; you must not
           claim that you wrote the original software. If you use this software
           in a product, an acknowledgment in the product documentation would
           be appreciated but is not required.

        2. Altered source versions must be plainly marked as such, and must not
           be misrepresented as being the original software.

        3. This notice may not be removed or altered from any source
           distribution.
*/

#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include <thread>
#include <vector>
#include <SOIL/SOIL.h>
#include <lodepng.h>
#include <glad/glad.h>
#include <glfw3.h>
//! Class to enchange myData over sockets.
//! This is the server, like duckduck is the server.
//! https://github.com/bozkurthan/Simple-TCP-Server-Client-CPP-Example
class XServer {
public:
    //! Empty constructor using default port adres : 5000
    XServer(){}
    //! Server port number, for example : 5010
    XServer(int thePortNumber):myPortNumber(thePortNumber){}
    //! Close, close socket descriptor.
    ~XServer(){
        delete myThread;
        myThread=NULL;
    }
    //! Start a thread, the thread function :
    //! Initialize a new connection. This fuction can be expanded to add more clients.
    void run(){
        myThread = new std::thread(&XServer::thread,this);
        myThread->detach(); //! Execute the thread independent from other programs.
    }
    void sendMessage(){
        mySend=true;
    }
    //! Close connection.
    void terminate(){
        closeServer();
    }

private:
    int myPortNumber=8011;
    //! Buffer to send and receive messages with
    char myBuffer[1500]; //! Values possible in range of 0-255.
    //! Server adres.
    sockaddr_in myServerAddress;
    //! Socket descriptor
    int myNewSd=0;
    int myServerSd=0;
    int myBindStatus=0;
    //! Logging.
    int myBytes=0, myBytesRead=0, myBytesWritten=0;
    //! The data to send.
    std::string myData;
    //! Session time.
    std::string myExitMessage = "exit";
    //! Logging session time.
    struct timeval myStartTime, myEndTime;
    //! Run this app in thread so it does not lock our program.
    std::thread *myThread;
    //! Status.
    uint myClientUp=0;
    //! Status.
    uint myServerUp=0;
    //! Send message.
    bool mySend=0;

    //! Run a seperate thread to avoid locking our main program loop.
    void thread(){
        if(!myServerUp){
            myServerUp=initServer();
        }
        if(myServerUp && ! myClientUp){
            myClientUp=initCLient();
        }
        if(myServerUp && myClientUp){
            if(!runServer()){
                delete myThread;
                myThread=NULL;
            }
            if(myThread==NULL){
                std::cout<<"Server thread destroyed."<<std::endl;
            }
        }
    }
    //! Init the server socket.
    int initServer(){
        //! Setup a socket and connection tools
        bzero((char*)&myServerAddress, sizeof(myServerAddress));
        myServerAddress.sin_family = AF_INET;
        myServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
        myServerAddress.sin_port = htons(myPortNumber);
        //! Open stream oriented socket with internet address
        //! Also keep track of the socket descriptor
        myServerSd = socket(AF_INET, SOCK_STREAM, 0);
        if(myServerSd < 0){
            std::cerr << "Server: Error establishing the server socket" << std::endl;
            return 0;
        }
        //! Bind the socket to its local address
        myBindStatus = bind(myServerSd, (struct sockaddr*) &myServerAddress,
                            sizeof(myServerAddress));
        if(myBindStatus < 0){
            std::cerr << "Server: Error binding socket to local address" << std::endl;
            return 0;
        }
        return 1;
    }
    //! Wait for client connection.
    int initCLient(){
        std::cout << "Server: Waiting for a client to connect..." << std::endl;
        //! Listen for up to 5 requests at a time
        listen(myServerSd, 5);
        //! Receive a request from client using accept
        //! We need a new address to connect with the client
        sockaddr_in newSockAddr;
        socklen_t newSockAddrSize = sizeof(newSockAddr);
        //! Accept, create a new socket descriptor to
        //! Handle the new connection with client
        myNewSd = accept(myServerSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
        if(myNewSd < 0){
            std::cerr << "Server: Error accepting request from client!" << std::endl;
            return 0;
        }
        std::cout << "Server: Connected with client!" << std::endl;
        //! lets keep track of the session time
        gettimeofday(&myStartTime, NULL);

        return 1;
    }
    //! Update server thread.
    int runServer(){
        while(1){
            //! Receive a message from the client (listen)
            std::cout << "Server: Awaiting client response..." << std::endl;
            //! Use myBuffer to recieve.
            memset(&myBuffer, 0, sizeof(myBuffer)); //! Clear the buffer
            myBytes = recv(myNewSd, (char*)&myBuffer, sizeof(myBuffer), 0);
            //! Log the session.
            myBytesRead+=myBytes;

            if(!strcmp(myBuffer, "exit")){
                std::cout << "Server: Client has quit the session" << std::endl;
                break;
            }

            //! Do something with the myBuffer content, and responce with message to client.
            std::cout << "Server << " << myBuffer << std::endl;
            std::cout << "> ";
            getline(std::cin, myData);

            //! Use myBuffer to send.
            memset(&myBuffer, 0, sizeof(myBuffer)); //! Clear the buffer
            strcpy(myBuffer, myData.c_str());
            if(myData == myExitMessage){
                //! Send to the client that server has closed the connection
                send(myNewSd, (char*)&myBuffer, strlen(myBuffer), 0);
                break;
            }
            //! Send the message to client, log the bytes of the session.
            myBytesWritten+=send(myNewSd, (char*)&myBuffer, strlen(myBuffer), 0);
        }
        closeServer();
        return 0;
    }
    //! Close the server.
    void closeServer(){
        //! We need to close the socket descriptors after we're all done
        gettimeofday(&myEndTime, NULL);
        close(myNewSd);
        close(myServerSd);
        myServerUp=0;
        std::cout << "********Session********" << std::endl;
        std::cout << "Bytes written: " << myBytesWritten << " Bytes read: " << myBytesRead << std::endl;
        std::cout << "Elapsed time: " << (myEndTime.tv_sec - myStartTime.tv_sec)
                  << " secs" << std::endl;
        std::cout << "Connection closed..." << std::endl;
    }
};
#endif








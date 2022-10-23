#ifndef XCLIENT_H
#define XCLIENT_H

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
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include <thread>

class XClient {
public:
    //! Empty constructor using default port adres : 5000
    XClient(){}
    //! Server port number, for example : 5010
    XClient(int thePortNumber):myPortNumber(thePortNumber){}
    //! Close, close socket descriptor.
    ~XClient(){
        delete myThread;
        myThread=NULL;
    }
    //! Start a thread, the thread function :
    //! Initialize a new connection. This fuction can be expanded to add more clients.
    void run(){
        myThread = new std::thread(&XClient::thread,this);
        myThread->detach(); //! Execute the thread independent from other programs.
    }
    //! Send message
    void sendMessage(){
        mySend=true;
    }
    //! Close connection.
    void terminate(){
        closeClient();
    }
private:
    //! Run this app in thread so it does not lock our program.
    std::thread *myThread;
    //! Localhost.
    std::string myServerIp="127.0.0.1";
    //! Port number.
    int myPortNumber=8011;
    //! message buffer
    char msg[1500];
    //! Logger.
    int myBytesRead=0, myBytesWritten=0;
    //! Host.
    struct hostent* myHost;
    //! Log session time.
    struct timeval myStartTime, myEndTime;
    //! Client socket descriptor.
    int clientSd=0;
    //! Data.
    std::string myData;
    //! Client status.
    bool myClientUp=0;
    //! Send message.
    bool mySend=0;

    void thread(){
        if(!myClientUp){
            myClientUp=initClient();
        }
        if(myClientUp){
            runClient();
        }
    }
    //! Init client.
    int initClient(){
        //! setup a socket and connection tools
        myHost = gethostbyname(myServerIp.c_str());
        sockaddr_in sendSockAddr;
        bzero((char*)&sendSockAddr, sizeof(sendSockAddr));
        sendSockAddr.sin_family = AF_INET;
        sendSockAddr.sin_addr.s_addr =
                inet_addr(inet_ntoa(*(struct in_addr*)*myHost->h_addr_list));
        sendSockAddr.sin_port = htons(myPortNumber);
        clientSd = socket(AF_INET, SOCK_STREAM, 0);
        //try to connect...
        int status = connect(clientSd,(sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
        if(status < 0){
            std::cout<<"CLient: Error connecting to socket!"<<std::endl;
            return 0;
        }
        std::cout << "CLient: Connected to the server!" << std::endl;
        gettimeofday(&myStartTime, NULL);
        return 1;
    }
    //! Run client.
    int runClient(){
        while(1)
        {
            std::cout << ">";
            getline(std::cin, myData);

            memset(&msg, 0, sizeof(msg)); //! clear the buffer
            strcpy(msg, myData.c_str());
            if(myData == "exit"){
                send(clientSd, (char*)&msg, strlen(msg), 0);
                break;
            }
            myBytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
            std::cout << "CLient: Awaiting server response..." << std::endl;
            memset(&msg, 0, sizeof(msg)); //! clear the buffer
            myBytesRead += recv(clientSd, (char*)&msg, sizeof(msg), 0);
            if(!strcmp(msg, "exit")){
                std::cout << "Client: Server has quit the session." << std::endl;
                break;
            }
            std::cout << "Client << " << msg << std::endl;
        }
        closeClient();
        return 0;
    }
    void closeClient(){
        //! Close connection.
        gettimeofday(&myEndTime, NULL);
        close(clientSd);
        myClientUp=0;
        std::cout << "********Session********" << std::endl;
        std::cout << "Bytes written: " << myBytesWritten <<
                     " Bytes read: " << myBytesRead << std::endl;
        std::cout << "Elapsed time: " << (myEndTime.tv_sec- myStartTime.tv_sec)
                  << " secs" << std::endl;
        std::cout << "Connection closed." << std::endl;
    }
};
#endif














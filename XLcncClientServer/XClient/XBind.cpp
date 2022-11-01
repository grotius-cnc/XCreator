#ifndef XBIND_H
#define XBIND_H

#include <iostream>
#include <XClient.h>

//! Python c++ bindings.
int main()
{
    XClient myClient;
    return 0;
}

extern "C" {
    XClient* XClient_new(){ return new XClient(); }
    //! Recieve the openGl raw picture data.
    void XClient_encodeRawToPng(XClient* client, unsigned char *thePixels, int theWidth, int theHeight){
        client->encodeRawToPng(thePixels,theWidth,theHeight);
    }
    //! Run the client.
    void XClient_run(XClient* client){
        client->run();
    }
    /* Example:
    int isNExist (char* sequence) {
        std::cout << sequence << std::endl;
        return 0;
    }*/
}

#endif // XBIND_H

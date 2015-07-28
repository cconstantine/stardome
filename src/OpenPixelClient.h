#ifndef OPENPIXELCLIENT_H
#define OPENPIXELCLIENT_H

#include "ofMain.h"
#include "ofxNetwork.h"

namespace OpenPixel
{
typedef struct OPCPacket_Header {
    // Standard OPC-packet header
    uint8_t channel;
    uint8_t command;
    uint16_t data_length;
} OPCPacket_Header_t;

typedef struct OPCPacket_SPCData {
    // OPC "Set Pixel Colours" data structure
    unsigned char r;
    unsigned char g;
    unsigned char b;
} *OPCPacket_SPCData_t;
class Client
{
public:
    Client(string address, int port);
    virtual ~Client() {}

    void connect();

    void writeColors(vector<ofColor>&pix);
private:
    string _address;
    int _port;
    ofxTCPClient client;

};



};

#endif // OPENPIXELCLIENT_H

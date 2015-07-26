#include "OpenPixelClient.h"

namespace OpenPixel {
  Client::Client(string address, int port)
  {
      // Copy the Address and port to the variables
      _port = port;
      _address = address;

      // Connect to the Server
      connect();
  }

  void Client::connect()
  {
    if (client.isConnected()) {
      return;
    }

    client.setup(_address, _port);
    ofLog(OF_LOG_NOTICE, "Opening Connection to Server @"+ofToString(_address)+ ":" + ofToString(_port));
    if (client.isConnected()) {
        ofLog(OF_LOG_NOTICE, "Connected to Server @"+ofToString(_address)+ ":" + ofToString(_port));
    }
  }

    void Client::writeColors(vector<ofColor>pix)
    {
        OPCPacket_Header_t header;

          // Determine the length of the data section, as a multiple of the SPCData type
        uint16_t data_length = pix.size() * sizeof(struct OPCPacket_SPCData);

        // Fill out the header
        header.channel = 0x00;
        header.command = 0x00;
        header.data_length = htons(data_length);

        client.sendRawBytes((char *)(&header), sizeof(header));

        for(std::vector<ofColor>::iterator i = pix.begin(); i != pix.end(); ++i) {
          struct OPCPacket_SPCData message;
          ofColor color = *i;
          message.r = color.r;
          message.g = color.g;
          message.b = color.b;

          client.sendRawBytes((char *)(&message), sizeof(message));
        }

    }

}

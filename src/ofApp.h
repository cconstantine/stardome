#pragma once

#include "ofMain.h"
#include "LedMatrix.h"
#include "OpenPixelClient.h"
#include "ofxHTTP.h"

class ofApp : public ofBaseApp
{

public:
    ofApp();
    void setup();
    void update();
    void draw();
    void exit();

    float getBrightness();
    void setBrightness(float);

    void onHTTPPostEvent(ofx::HTTP::PostEventArgs& evt);
    void onHTTPFormEvent(ofx::HTTP::PostFormEventArgs& evt);
    void onHTTPUploadEvent(ofx::HTTP::PostUploadEventArgs& args);
private:
    OpenPixel::Client* opcClient;
    LedMatrix strips;
    ofVideoPlayer myPlayer;
    float _brightness;

    //ofx::HTTP::BasicPostServer::SharedPtr server;
};


class ActiveRoute: public ofx::HTTP::BaseRoute_<ofx::HTTP::BaseRouteSettings>
{
public:
    ActiveRoute(ofApp* app, const ofx::HTTP::BaseRouteSettings& settings = ofx::HTTP::BaseRouteSettings());
    virtual ~ActiveRoute();

    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);

    virtual bool canHandleRequest(const Poco::Net::HTTPServerRequest& request, bool isSecurePort) const;

private:
    ofApp* _app;
};

class ActiveRouteHandler: public ofx::HTTP::AbstractRouteHandler
{
public:
    ActiveRouteHandler(ofApp* app);

    void handleRequest(Poco::Net::HTTPServerRequest& request,  Poco::Net::HTTPServerResponse& response);
private:
    ofApp* _app;
};

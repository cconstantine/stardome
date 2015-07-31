#include "ofApp.h"
#include <string>

//--------------------------------------------------------------
ofApp::ofApp() : _brightness(1) { }

void ofApp::setup()
{
    ofLog(OF_LOG_NOTICE, "ofApp::setup()");
//    ofSetVerticalSync(false);
    opcClient = new OpenPixel::Client("stardome.local", 7890);
    ofx::HTTP::BasicServerSettings settings;
    settings.setPort(8080);
    ofx::HTTP::BasicServer* server = new ofx::HTTP::BasicServer(settings);
    ofx::HTTP::FileSystemRouteSettings fsRouteSettings;
    server->addRoute(std::shared_ptr<ofx::HTTP::FileSystemRoute>(new ofx::HTTP::FileSystemRoute(fsRouteSettings)));
    server->addRoute(std::shared_ptr<ActiveRoute>(new ActiveRoute(this)));
    server->start();

    int x = 40;
    int y = 20;
    strips.addStrip(ofPoint(x, y), ofPoint(x+=5, y+2*70), 70);
    strips.addStrip(ofPoint(x, y), ofPoint(x+=5, y+2*82), 82);
    strips.addStrip(ofPoint(x, y), ofPoint(x+=5, y+2*84), 84);
    strips.addStrip(ofPoint(x, y), ofPoint(x+=5, y+2*84), 84);

    strips.addStrip(ofPoint(x, y), ofPoint(x+=5, y+2*70), 70);
    strips.addStrip(ofPoint(x, y), ofPoint(x+=5, y+2*82), 82);
    strips.addStrip(ofPoint(x, y), ofPoint(x+=5, y+2*84), 84);
    strips.addStrip(ofPoint(x, y), ofPoint(x+=5, y+2*84), 84);

    strips.addStrip(ofPoint(x, y), ofPoint(x+=5, y+2*70), 70);
    strips.addStrip(ofPoint(x, y), ofPoint( x+=5, y+2*82), 82);
    strips.addStrip(ofPoint(x, y), ofPoint(x+=5, y+2*84), 84);
    strips.addStrip(ofPoint(x, y), ofPoint(x+=5, y+2*84), 84);

    strips.addStrip(ofPoint(x, y), ofPoint(x+=5, y+2*70), 70);
    strips.addStrip(ofPoint(x, y), ofPoint(x+=5, y+2*82), 82);
    strips.addStrip(ofPoint(x, y), ofPoint(x+=5, y+2*84), 84);
    strips.addStrip(ofPoint(x, y), ofPoint(x+=5, y+2*84), 84);


    strips.addStrip(ofPoint(x, y), ofPoint(x+=5, y+2*70), 70);
    strips.addStrip(ofPoint(x, y), ofPoint(x+=5, y+2*82), 82);
    strips.addStrip(ofPoint(x, y), ofPoint(x+=5, y+2*84), 84);
    strips.addStrip(ofPoint(x, y), ofPoint(x+=5, y+2*84), 84);

    myPlayer.loadMovie("movies/fractals_quiet_small.mp4");

    myPlayer.setSpeed(1);
    myPlayer.setLoopState(OF_LOOP_NORMAL);
    //myPlayer.setUseTexture(false);

    myPlayer.play();
}

void ofApp::update()
{
    static float lastTick = ofGetElapsedTimef();
    myPlayer.update(); // get all the new frames
    if(lastTick + 10 < ofGetElapsedTimef())
    {
        ofLog(OF_LOG_NOTICE, "Framerate:  %3.1f", ofGetFrameRate());
        ofLog(OF_LOG_NOTICE, "Brightness: %1.3f", getBrightness());
        lastTick = ofGetElapsedTimef();
    }

}

void ofApp::exit()
{
    ofLog(OF_LOG_NOTICE, "ofApp::exit(%d)", strips.colorData().size());

    vector<ofColor> blank;
    for(unsigned int i = 0; i < strips.colorData().size(); i++)
    {
        blank.push_back(ofColor(0));
    }
    opcClient->writeColors(blank, 0);
    ofLog(OF_LOG_NOTICE, "strips should be off");
}
//--------------------------------------------------------------
void ofApp::draw()
{
    myPlayer.draw(0,0);
    strips.drawGrabRegion();
    if(!myPlayer.isFrameNew())
    {
        return;
    }

    strips.grabImageData(myPlayer.getPixelsRef());
    opcClient->writeColors(strips.colorData(), getBrightness());
}


void ofApp::onHTTPPostEvent(ofx::HTTP::PostEventArgs& evt)
{
    ofLogNotice("ofApp::onHTTPPostEvent") << "Data: " << evt.getBuffer().getText();

}

void ofApp::onHTTPFormEvent(ofx::HTTP::PostFormEventArgs& evt)
{
    ofLogNotice("ofApp::onHTTPFormEvent") << "";
    ofx::HTTP::HTTPUtils::dumpNameValueCollection(evt.getForm(), ofGetLogLevel());
}

void ofApp::onHTTPUploadEvent(ofx::HTTP::PostUploadEventArgs& evt)
{

}

float ofApp::getBrightness()
{
    return _brightness;
}

void ofApp::setBrightness(float brightness)
{
    _brightness = brightness;
}

ActiveRouteHandler::ActiveRouteHandler(ofApp* app) : _app(app) {}

void ActiveRouteHandler::handleRequest(Poco::Net::HTTPServerRequest& request,
                                       Poco::Net::HTTPServerResponse& response)
{
    std::string body;
    Poco::StreamCopier::copyToString(request.stream(), body);


    response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_OK);
    if (request.getMethod() == "GET")
    {
        char buff[256];
        int bufSize = snprintf(buff, sizeof(buff), "%1.3f", _app->getBrightness());

        response.sendBuffer(buff, bufSize);
    }
    else
    {
        float bodyNum = ::atof(body.c_str());

        _app->setBrightness(bodyNum);

        response.setContentLength(0);
        response.send();
    }
}

ActiveRoute::ActiveRoute(ofApp* app, const ofx::HTTP::BaseRouteSettings& settings) : ofx::HTTP::BaseRoute_<ofx::HTTP::BaseRouteSettings>(settings), _app(app) {}

ActiveRoute::~ActiveRoute() {}

Poco::Net::HTTPRequestHandler* ActiveRoute::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
    return new ActiveRouteHandler(_app);
}
bool ActiveRoute::canHandleRequest(const Poco::Net::HTTPServerRequest& request, bool isSecurePort) const
{
    ofLog(OF_LOG_NOTICE) << "canHandleRequest: '" << request.getMethod() << "' '" << request.getURI();
    return request.getURI() == std::string("/brightness");
}

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofLog(OF_LOG_NOTICE, "ofApp::setup()");
//    ofSetVerticalSync(false);
    opcClient = new OpenPixel::Client("localhost", 7890);


    brightness = 1;
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
    strips.addStrip(ofPoint(x, y), ofPoint(x+=5, y+2*82), 82);
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
    strips.drawGrabRegion(ledOverlay);
}

void ofApp::update()
{
    static float lastTick = ofGetElapsedTimef();
    myPlayer.update(); // get all the new frames
    if(lastTick + 1 < ofGetElapsedTimef()) {
        ofLog(OF_LOG_NOTICE, "Framerate: %3.1f", ofGetFrameRate());
        ofLog(OF_LOG_NOTICE, "Brightness: %1.3f", brightness);
       lastTick = ofGetElapsedTimef();
    }

}

void ofApp::exit()
{
    ofLog(OF_LOG_NOTICE, "ofApp::exit(%d)", strips.colorData().size());

    vector<ofColor> blank;
    for(unsigned int i = 0; i < strips.colorData().size();i++) {
        blank.push_back(ofColor(0));
    }
    opcClient->writeColors(blank, 0);
    ofLog(OF_LOG_NOTICE, "strips should be off");
}
//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);

    myPlayer.draw(0,0);

    ledOverlay.draw(0,0);


    if(!myPlayer.isFrameNew()) {
        return;
    }
    strips.grabImageData(myPlayer.getPixelsRef());
    opcClient->writeColors(strips.colorData(), brightness);


}



//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    //ofLog(OF_LOG_NOTICE, "Got key: %c", key);
    if(key == OF_KEY_ESC) {
        exit();
    } else if(key == OF_KEY_UP) {
      brightness += 0.01;
    } else if(key == OF_KEY_DOWN) {
      brightness -= 0.01;
    }
    if (brightness < 0) {
      brightness = 0;
    }
    if (brightness > 1) {
      brightness = 1;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    ofLog(OF_LOG_NOTICE, "ofApp::keyReleased(%d)", key);


}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
    ofLog(OF_LOG_NOTICE, "ofApp::mouseMoved(%d, %d)", x, y);


}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    ofLog(OF_LOG_NOTICE, "ofApp::mouseDragged(%d, %d, %d)", x, y, button);


}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    ofLog(OF_LOG_NOTICE, "ofApp::mousePressed(%d, %d, %d)", x, y, button);


}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    ofLog(OF_LOG_NOTICE, "ofApp::mouseReleased(%d, %d, %d)", x, y, button);


}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    ofLog(OF_LOG_NOTICE, "ofApp::windowResized(%d, %d)", w, h);


}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
    ofLog(OF_LOG_NOTICE, "ofApp::gotMessage");

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
    ofLog(OF_LOG_NOTICE, "ofApp::dragEvent");

}

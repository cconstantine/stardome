#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofLog(OF_LOG_NOTICE, "ofApp::setup()");

    opcClient = new OpenPixel::Client("localhost", 7890);

    strips.addStrip(ofPoint(30, 30), ofPoint(30, 5*70), 70);
    strips.addStrip(ofPoint(35, 30), ofPoint(35, 5*82), 82);
    strips.addStrip(ofPoint(40, 30), ofPoint(40, 5*84), 84);
    strips.addStrip(ofPoint(45, 30), ofPoint(45, 5*84), 84);

    myPlayer.loadMovie("movies/fractals_quiet.mp4");

    myPlayer.setLoopState(OF_LOOP_NORMAL);
    //myPlayer.setUseTexture(false);

    myPlayer.play();
}

void ofApp::update()
{
    myPlayer.update(); // get all the new frames

}

void ofApp::exit()
{
    ofLog(OF_LOG_NOTICE, "ofApp::exit(%d)", strips.colorData().size());

    vector<ofColor> blank;
    for(unsigned int i = 0; i < strips.colorData().size();i++) {
        blank.push_back(ofColor(0));
    }
    opcClient->writeColors(blank);
    ofLog(OF_LOG_NOTICE, "strips should be off");
}
//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);

    myPlayer.draw(0,0);

    strips.grabImageData(myPlayer.getPixelsRef());
    opcClient->writeColors(strips.colorData());

    strips.drawGrabRegion();

}



//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    ofLog(OF_LOG_NOTICE, "Got key: %c", key);
    if(key == OF_KEY_ESC) {
        exit();
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}

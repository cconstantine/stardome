#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofLog(OF_LOG_NOTICE, "ofApp::setup()");
    opcClient = new OpenPixel::Client("localhost", 7890);
    myPlayer.loadMovie("movies/fractals_quiet_small.mp4");
    while(!myPlayer.isLoaded());

    brightness = 1;
    speed = 1;
    int x = myPlayer.getWidth() / 2;
    int y = myPlayer.getHeight() / 2;

    float scale = y / 7.8;
    ofPoint pos_0 = ofPoint(x      , y      );

    ofPoint pos_1 = ofPoint(x + scale *  3.917, y + scale *  1.272);
    ofPoint pos_2 = ofPoint(x + scale *  0    , y + scale *  4.118);
    ofPoint pos_3 = ofPoint(x + scale * -3.917, y + scale *  1.272);
    ofPoint pos_4 = ofPoint(x + scale * -2.421, y + scale * -3.332);
    ofPoint pos_5 = ofPoint(x + scale *  2.421, y + scale * -3.332);

    ofPoint pos_6 = ofPoint(x + scale *  4.423, y + scale *  6.088);
    ofPoint pos_7 = ofPoint(x + scale * -4.423, y + scale *  6.088);
    ofPoint pos_8 = ofPoint(x + scale * -7.157, y + scale * -2.325);
    ofPoint pos_9 = ofPoint(x + scale *  0    , y + scale * -7.526);
    ofPoint pos_A = ofPoint(x + scale *  7.157, y + scale * -2.325);


    strips.addStrip(pos_1, pos_0, 70);
    strips.addStrip(pos_1, pos_2, 82);
    strips.addStrip(pos_1, pos_6, 84);
    strips.addStrip(pos_1, pos_A, 84);


    strips.addStrip(pos_2, pos_0, 70);
    strips.addStrip(pos_2, pos_3, 82);
    strips.addStrip(pos_2, pos_6, 84);
    strips.addStrip(pos_2, pos_7, 84);


    strips.addStrip(pos_3, pos_0, 70);
    strips.addStrip(pos_3, pos_4, 82);
    strips.addStrip(pos_3, pos_7, 84);
    strips.addStrip(pos_3, pos_8, 84);


    strips.addStrip(pos_4, pos_0, 70);
    strips.addStrip(pos_4, pos_5, 82);
    strips.addStrip(pos_4, pos_8, 84);
    strips.addStrip(pos_4, pos_9, 84);


    strips.addStrip(pos_5, pos_0, 70);
    strips.addStrip(pos_5, pos_1, 82);
    strips.addStrip(pos_5, pos_9, 84);
    strips.addStrip(pos_5, pos_A, 84);

    myPlayer.setSpeed(speed);
    myPlayer.setLoopState(OF_LOOP_NORMAL);
    myPlayer.play();
}

void ofApp::update()
{
    static float lastTick = ofGetElapsedTimef();
    myPlayer.update(); // get all the new frames
    if(lastTick + 1 < ofGetElapsedTimef()) {
        ofLog(OF_LOG_NOTICE, "Framerate: %3.1f", ofGetFrameRate());
        ofLog(OF_LOG_NOTICE, "Brightness: %1.3f", brightness);
        ofLog(OF_LOG_NOTICE, "Speed: %1.3f", speed);
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
    ofSetColor(255, 255);

    myPlayer.draw(0,0, ofGetWidth(), ofGetHeight());

    strips.drawGrabRegion(myPlayer.getWidth(), myPlayer.getHeight());


    if(!myPlayer.isFrameNew()) {
        return;
    }
    static int currentFrame = myPlayer.getCurrentFrame();
    if(currentFrame < myPlayer.getCurrentFrame() - 1) {
        ofLog(OF_LOG_NOTICE, "Skipped: %d frames", myPlayer.getCurrentFrame() - currentFrame - 1);
    }
    currentFrame = myPlayer.getCurrentFrame();
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
    } else if(key == OF_KEY_LEFT) {
      speed -= 0.1;
    } else if(key == OF_KEY_RIGHT) {
      speed += 0.1;
    }
    if (brightness < 0) {
      brightness = 0;
    }
    if (brightness > 1) {
      brightness = 1;
    }
    if (speed < 0) {
      speed = 0;
    }
    if (speed > 2) {
      speed = 2;
    }
    myPlayer.setSpeed(speed);
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

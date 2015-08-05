#ifndef LEDMATRIX_H
#define LEDMATRIX_H
#include <iostream>
#include "ofMain.h"

class LedMatrix
{
public:
    LedMatrix() : overlayDrawn(false) {}
    virtual ~LedMatrix()  {}

    void addStrip(ofVec2f start, ofVec2f end, unsigned int length);
    void grabImageData(ofPixelsRef pixels);
    void drawGrabRegion();

    // Return Data Method
    vector <ofColor>& colorData();

private:
    // Hold the Captured Colors
    vector <ofColor> colors;
    // Hold the Position of our Capture points
    vector <ofVec2f> pos;

    // Variables
    unsigned int size;
    ofVec2f _start;
    ofVec2f _end;

    // Capture Objects
    ofImage img;
    bool overlayDrawn;
    ofPixels pixels;
};


#endif // LEDMATRIX_H

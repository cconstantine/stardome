#include "LedMatrix.h"

void LedMatrix::addStrip(ofVec2f start, ofVec2f end, unsigned int length)
{
    // Setup Positioning
    _start = start;
    _end = end;

    float width = abs(end.x - start.x);
    float height = abs(end.y - start.y);

    img.allocate(width,height,OF_IMAGE_COLOR);

    float deltaX = width / length;
    float deltaY = height / length;

    for (unsigned int i = 0; i < length; i++)
    {
        pos.push_back(ofVec2f(start.x + i*deltaX,start.y + i*deltaY));
        colors.push_back(ofColor(0));
    }

}
//--------------------------------------------------------------
vector <ofColor>& LedMatrix::colorData()
{
    // Transmit Data
    return colors;
}
//--------------------------------------------------------------
void LedMatrix::grabImageData(ofPixelsRef pixels)
{
    //img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());

    for (unsigned int i = 0; i < pos.size(); i++)
    {
        colors[i] = pixels.getColor(pos[i].x, pos[i].y);
    }

}
//--------------------------------------------------------------
void LedMatrix::drawGrabRegion(ofPath& canvas)
{
    canvas.setColor(128);
    canvas.setStrokeColor(128);
    canvas.setStrokeWidth(1);


    for (unsigned int i = 0; i < pos.size(); i++)
    {
        canvas.circle(pos[i], 2);
    }
}


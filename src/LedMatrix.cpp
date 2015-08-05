#include "LedMatrix.h"

void LedMatrix::addStrip(ofVec2f start, ofVec2f end, unsigned int length)
{
    // Setup Positioning
    _start = start;
    _end = end;

    float width = abs(end.x - start.x);
    float height = abs(end.y - start.y);

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

    for (unsigned int i = 0; i < pos.size(); i++)
    {
        colors[i] = pixels.getColor(pos[i].x, pos[i].y);
    }

}
//--------------------------------------------------------------
void LedMatrix::drawGrabRegion()
{

    if (!overlayDrawn)
    {
        ofBackground(0);
        ofFill();

        for (unsigned int i = 0; i < pos.size(); i++)
        {
            ofCircle(pos[i],3);
        }

        img.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
        img.grabScreen(0,0,ofGetWidth(), ofGetHeight());

        ofPixels alphaPixels;
        alphaPixels.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);

        for(int y = 0;y < ofGetHeight();y++)
        {
            for(int x = 0;x < ofGetWidth();x++)
            {
                ofColor color = img.getColor(x, y);
                if (color == ofColor(0) )
                {
                    alphaPixels.setColor(x, y, ofColor(0,0,0, 127));
                }
                else
                {
                    alphaPixels.setColor(x, y, ofColor(0,0,0, 0));
                }
            }
        }
        img.setFromPixels(alphaPixels);

        overlayDrawn = true;
    }
    else
    {
        img.draw(0,0);
    }

}


// =============================================================================
//
// Copyright (c) 2014 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup()
{
    ofSetVerticalSync(false);
    
	camWidth = 320;
	camHeight = 240;
    camFrameRate = 120;
    
    //we can now get back a list of devices.
    std::vector<ofVideoDevice> devices = vidGrabber.listDevices();
    
    for(std::size_t i = 0; i < devices.size(); ++i)
    {
        std::stringstream ss;
        
        ss << devices[i].id << ": " << devices[i].deviceName;
        
        if(!devices[i].bAvailable)
        {
            ss << " - unavailable ";
        }
        
        ofLogNotice("ofApp::setup") << ss.str();
	}
    
	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(camFrameRate);
	vidGrabber.setup(camWidth, camHeight);
    
    vidGrabber.setAutogain(true);
    vidGrabber.setAutoWhiteBalance(false);
    
    
    // setup GUI (panel with controls)
    gui.setup();
    gui.add(thresh.set("thresh", 150, 0, 255));


    
}


void ofApp::update() // processing called every frame before draw step
{
	vidGrabber.update();
    
	if (vidGrabber.isFrameNew())
    {
//        diff.update();
//        threshold(diff,0);
		videoTexture.loadData(vidGrabber.getPixels());
        thresholdedIm = vidGrabber.getPixels();
        // thresholdedIm.setImageType(OF_IMAGE_GRAYSCALE);

        thresholdedIm.threshold(thresh); // automatically sets the input to the thresholded imput
        // thresholdedIm.update();
        
	}
}


void ofApp::draw()
{
    
    ofBackground(0);
    ofSetColor(255);
    
    gui.draw();

    
    videoTexture.draw(0, 400); // draw @ 0,0
    thresholdedIm.draw(camWidth,0);
    
    std::stringstream ss;
    
    ss << "App FPS: " << ofGetFrameRate() << std::endl;
    ss << "Cam FPS: " << vidGrabber.getFPS();
    
    ofDrawBitmapStringHighlight(ss.str(), ofPoint(10, 15));
    
}

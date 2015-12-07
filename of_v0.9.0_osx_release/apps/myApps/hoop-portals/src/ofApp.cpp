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
    
	contourFinder.setMinAreaRadius(10);
	contourFinder.setMaxAreaRadius(200);
    
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
    
    vidGrabber.setAutogain(false);
    vidGrabber.setAutoWhiteBalance(true);
    
    if (doBackgroundSub) {
    // background subtraction start
	background.setLearningTime(900);
	background.setThresholdValue(10);
    // background.setDifferenceMode(??); // ABSDIFF
    }

    // setup GUI (panel with controls)
    // CAMERA
    gui.setup("camera settings");
    gui.setPosition(camWidth*2+10,10);
    gui.add(thresh.set("thresh", 150, 0, 500)); // set camera thresh
    gui.add(exposure.set("exposure", 24, 0, 255)); // expsoreu
    gui.add(channel.set("channel (RGBA)", 1, 1, 4)); // which channel to grab from
    gui.add(minRadius.set("minRadius", 50, 1, 500)); // which channel to grab from
    // HOUGH SETTINGS
    //setup gui
    gui2.setup("hough settings"); //
    gui2.setPosition(camWidth*2+10, 100);
    gui2.add(dp_param.setup("dp param", 1, 0, 10));
    gui2.add(mindist_param.setup("min dist param", 200, 1, 1000));
    gui2.add(param1_param.setup("param1 param", 130, 1, 500));
    gui2.add(param2_param.setup("param2 param", 30, 1, 100));
    gui2.add(minradius_param.setup("min. radius param", 0, 0, 500));
    gui2.add(maxradius_param.setup("max. radius param", 400, 0, 500));
    gui2.add(threshold_param.setup("threshold", 120, 0, 255));
    gui2.add(blurparam.set("blurparam", 6, 1, 25));

    gui2.add(numCircles.setup("# of circles size", ofToString((int)circles.size())));

    contourFinder.setTargetColor(ofColor(255,255,255));

    // allocation for
    ofxCv::allocate(cvMat, camWidth, camHeight, OF_IMAGE_GRAYSCALE);


} // setup


void ofApp::update() // processing called every frame before draw step
{
    // update params
    contourFinder.setMinArea(minRadius);

    vidGrabber.setExposure(exposure); //
	vidGrabber.update();
    
	if (vidGrabber.isFrameNew())
    {
        
        
		videoTexture.loadData(vidGrabber.getPixels()); // loads from cam
        // vidgrabber should return RGBA
        pixelFrame = vidGrabber.getPixels();
        
        if (doBackgroundSub) {
            background.setThresholdValue(thresh); // threshold controlled here
            background.update(vidGrabber, plainImage);
            pixelFrame = plainImage.getPixels();
            thresholdedIm.setFromPixels(pixelFrame.getChannel(channel)); // converts to grayscale


        }
        else {
            thresholdedIm.setFromPixels(pixelFrame.getChannel(channel)); // converts to grayscale
            thresholdedIm.threshold(thresh); // automatically sets the input to the thresholded imput
        }

        contourFinder.findContours(thresholdedIm);
        
        //displayImage = dealWithContours(contourFinder);
        
        //thresholdedIm.resize(outputWidth, outputHeight);
        // thresholdedIm.update();
        cvMat = ofxCv::toCv(thresholdedIm); // hough transform preprocessing
        //cv::GaussianBlur( cvMat, cvMat, cv::Size(5, 5), 2, 2 );
        cv::HoughCircles( cvMat,
                         circles,
                         CV_HOUGH_GRADIENT,
                         dp_param,
                         mindist_param,
                         param1_param,
                         param2_param,
                         minradius_param,
                         maxradius_param);
        std::cout << "num circles " << circles.size() << endl;
        
        //deal with color image... as a mask?
        
        //displayImage = thresholdedIm;
        

        
        

	}
}


//ofxCvColorImage ofApp::dealWithContours(ContourFinder contourFinder)/
//{
    
//        return
//}

void ofApp::draw()
{
    
    ofBackground(0);
    ofSetColor(255);
    
    gui.draw();
    gui2.draw();
    
    videoTexture.draw(0,camHeight); // draw @ 0,0
    thresholdedIm.draw(camWidth,0);
    plainImage.draw(camWidth,camHeight);
    contourFinder.draw();
    
    // hough stuff
    ofSetColor(0, 255, 0);
    ofNoFill();


    for (int i=0; i<circles.size(); i++) {
        ofDrawCircle(circles[i][0], circles[i][1], circles[i][2]);
    }
    
    // for each blob found
    for (int i =0; i<contourFinder.size(); i++) {
        
        testRect = contourFinder.getFitEllipse(i); // get the largest ellipse which would fit in the bounding box
        
        ofPushMatrix();
        ofPushStyle();
        
        ofSetColor(255,0,255); // draw in red

        // ofRotate(testRect.angle);
        
        Point2f vertices[4];
        Point2f corner;
        testRect.points(vertices);
        
        cout << vertices[0];

    
        // here we're trying to draw the ellipses captured
        for (int j=0; j<4; j++){ // draw each point
            corner = vertices[j];
            ofCircle(corner.x, corner.y, 5);
        }
        
        ofEllipse(testRect.center.x, testRect.center.y, testRect.size.width, testRect.size.height);
        
        ofPopMatrix();
        ofPopStyle();
        
    }
    
    std::stringstream ss;
    
    ss << "App FPS: " << ofGetFrameRate() << std::endl;
    ss << "Cam FPS: " << vidGrabber.getFPS() << std::endl;
    ss << "Pixel Format: " << vidGrabber.getPixelFormat() << std::endl;
    ss << "Exposure: " << to_string(vidGrabber.getExposure()) << std::endl;
    ss << "Num circles: " << circles.size() << std::endl;
    
    ofDrawBitmapStringHighlight(ss.str(), ofPoint(10, 15));
}


void ofApp::keyPressed(int key) {
	if(key == ' ') {
        
        
		if (doBackgroundSub) {
            background.reset();
        }
	}
}

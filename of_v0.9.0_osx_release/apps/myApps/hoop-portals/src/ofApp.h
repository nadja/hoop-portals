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


#pragma once


#include "ofMain.h"
#include "ofxPS3EyeGrabber.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"
#include <iostream>

class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    ofxCvColorImage dealWithContours(ofxCv::ContourFinder contourFinder);
    void keyPressed(int key);
    
    ofxPS3EyeGrabber vidGrabber; // the IR camera
    ofTexture videoTexture;
    
    int camWidth;
    int camHeight;
    int camFrameRate;
    
    int outputWidth=900;
    int outputHeight=600;
    
    ofPixels pixelFrame;
    ofImage plainImage;
    ofxCvColorImage displayImage;
    ofxCvGrayscaleImage thresholdedIm;
    
    // guis
    ofxPanel gui, gui2;
    ofParameter<int> thresh, exposure, channel, minRadius, blurparam;
    ofxIntSlider dp_param;
    ofxIntSlider mindist_param;
    ofxIntSlider param1_param;
    ofxIntSlider param2_param;
    ofxIntSlider minradius_param;
    ofxIntSlider maxradius_param;
    ofxIntSlider threshold_param;

    ofxLabel numCircles;

    
    
    bool doBackgroundSub = false;
    ofxCv::RunningBackground background;
    
    // contours?
    ofxCv::ContourFinder contourFinder;
    ofColor targetColor;
    
    // flow?
    ofxCv::Flow* curFlow;
    ofxCv::FlowFarneback fb; // flwtype
    
    cv::RotatedRect testRect;
 //


    // hough stuff
    cv::Mat cvMat;
    vector<cv::Vec3f> circles;


    
    
};

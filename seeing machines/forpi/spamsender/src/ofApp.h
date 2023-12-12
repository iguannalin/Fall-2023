#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxKinect.h"

class ofApp : public ofBaseApp{
    
public:
    void setup() override;
    void update() override;
    void draw() override;
    void mouseMoved(int x, int y) override;
    void exit() override;
    
    std::string sendAddr;
    int sendPort;
    
    ofxOscSender sender;
    
    ofxKinect kinect;
    
    ofxCvColorImage colorImg;
    ofxCvGrayscaleImage thresholdImg;
    
    ofxCvContourFinder contourFinder;
    
    ofParameter<float> nearThreshold;
    ofParameter<float> farThreshold;
    ofParameter<float> minArea;
    ofParameter<float> maxArea;
    
    ofxPanel gui;
    std::vector<ofVec2f> positions;
    bool test;
};

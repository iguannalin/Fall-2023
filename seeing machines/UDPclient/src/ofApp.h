// ofApp.h
#pragma once

#include "ofMain.h"

#include "ofxOsc.h"

class ofApp : public ofBaseApp
{
public:
  void setup() override;
  void draw() override;

  void keyPressed(int key) override;
  void mouseMoved(int x, int y ) override;
  void mousePressed(int x, int y, int button) override;
  void mouseReleased(int x, int y, int button) override;
    
  bool mouseDrag = false;

  std::string sendAddr;
  int sendPort;

  ofxOscSender sender;
};

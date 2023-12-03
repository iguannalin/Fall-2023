// ofApp.cpp
#include "ofApp.h"

void ofApp::setup()
{
  ofSetWindowShape(1280, 2400);

  // Make the circle smoother by increasing the resolution.
  ofSetCircleResolution(128);

  // Set up the OSC sender.
  sendAddr = "localhost";
  sendPort = 3030;
  sender.setup(sendAddr, sendPort);
//  ofSetFrameRate(2);
}

void ofApp::draw()
{
  ofBackground(0);

  // Draw a circle at the mouse position.
  if (ofGetMousePressed())
  {
      ofFill();
  }
  else
  {
      ofNoFill();
  }
  ofSetColor(255);
  ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 50);
  ofFill();
}

void ofApp::keyPressed(int key)
{
  if (key == ' ')
  {
    ofxOscMessage msg;
    msg.setAddress("/cursor/color");

    sender.sendMessage(msg);
  }
}

void ofApp::mouseMoved(int x, int y )
{
    ofxOscMessage msg;
    msg.setAddress("/cursor/move");
    msg.addIntArg(ofGetMouseX());
    msg.addIntArg(ofGetMouseY());
    sender.sendMessage(msg);
}

void ofApp::mousePressed(int x, int y, int button)
{
//    mouseDrag = true;
//    cout << mouseDrag << endl;
}

void ofApp::mouseReleased(int x, int y, int button)
{
//  mouseDrag = false;
}

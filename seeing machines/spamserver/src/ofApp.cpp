#include "ofApp.h"

//window help: https://forum.openframeworks.cc/t/multi-windows-open-close-it-programatically-is-there-a-way/25268/2

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(15);
    
    // Set up the OSC receiver.
    recvPort = 3030;
    receiver.setup(recvPort);
    windowLimit = 5; // no more than this many windows open at a time
}

//--------------------------------------------------------------
void ofApp::update(){
    while (receiver.hasWaitingMessages())
    {
      // Get the next message.
      ofxOscMessage msg;
      receiver.getNextMessage(msg);
      if (msg.getAddress() == "/cursor/move")
      {
//          check if at least 25px offset from previous window
          if (abs(msg.getArgAsInt(0) - getX) > 50 ||
              abs(msg.getArgAsInt(1) - getY) > 50)
          {
              getX = ofLerp(getX, msg.getArgAsInt(0), 0.5);
              getY = ofLerp(getY, msg.getArgAsInt(1), 0.5);
              drawWindow();
          }
      } else
      {
        ofLogWarning(__FUNCTION__) << "Unrecognized message " << msg.getAddress();
      }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
}

//--------------------------------------------------------------
void ofApp::exit(){

}

void ofApp::drawRandomInWindow(ofEventArgs & args){
    ofPushStyle();
    ofSetColor(ofColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255)));
    ofFill();
    ofDrawRectangle(ofRandomuf()*20.f, ofRandomuf()*20.f, ofRandomuf()*80.f, ofRandomuf()*80.f);
    ofPopStyle();
}

void ofApp::drawWindow() {
    if (windowIndex == windowLimit) {
        windowIndex = 0;
    }
    if (windows.size() < windowLimit) {
        ofGLFWWindowSettings settings;
        settings.setSize(100,100);
        settings.setPosition(ofVec2f(getX,getY));
        windows.push_back( ofCreateWindow(settings));
        
        // when this is front() rectangles stop drawing after 1st popup
        ofAddListener(windows.back()->events().draw, this, &ofApp::drawRandomInWindow);
    } else {
        shared_ptr<ofAppBaseWindow> recycle = windows[windowIndex];
        recycle->setWindowPosition(getX,getY);
    }
    windowIndex+=1;
}

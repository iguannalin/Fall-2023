#include "ofApp.h"

//window help: https://forum.openframeworks.cc/t/multi-windows-open-close-it-programatically-is-there-a-way/25268/2

//--------------------------------------------------------------
void ofApp::setup(){
//    ofBackground(255);
//    ofSetCircleResolution(200);

    ofSetFrameRate(8);
    
    // Set up the OSC receiver.
    recvPort = 3030;
    receiver.setup(recvPort);
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
          if (abs(msg.getArgAsInt(0) - getX) > 25 ||
              abs(msg.getArgAsInt(1) - getY) > 25)
          {
              getX = msg.getArgAsInt(0);
              getY = msg.getArgAsInt(1);
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
    ofGLFWWindowSettings settings;
    settings.setSize(100,100);
    settings.setPosition(ofVec2f(getX,getY));
    settings.resizable = false;
    if ()
    windows.push_back( ofCreateWindow(settings) );
    cout << windows.size() << endl;
    
    // when this is front() rectangles stop drawing after 1st popup
    ofAddListener(windows.back()->events().draw, this, &ofApp::drawRandomInWindow);
}

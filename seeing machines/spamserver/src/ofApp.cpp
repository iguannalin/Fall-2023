#include "ofApp.h"

//window help: https://forum.openframeworks.cc/t/multi-windows-open-close-it-programatically-is-there-a-way/25268/2

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(15);
    
    // Set up the OSC receiver.
    recvPort = 3030;
//    receiver.setup("172.20.10.15", recvPort);
    receiver.setup(recvPort);
    windowLimit = 5; // no more than this many windows open at a time

    font.load("Comic Sans MS.ttf", 12);
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
//          cout<<msg.getArgAsInt(0)<<endl;
//          check if at least 25px offset from previous window
          if (abs(msg.getArgAsInt(0) - getX) > 75 ||
              abs(msg.getArgAsInt(1) - getY) > 75)
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

//TODO: display ad content from json file
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

void ofApp::drawRandomInWindow(ofEventArgs & args){
    ofPushStyle();
    ofSetColor(ofColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255)));
//    ofDrawRectangle(ofRandomuf()*20.f, ofRandomuf()*20.f, ofRandomuf()*80.f, ofRandomuf()*80.f);
    ofBackground(ofColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255)));
//    font.drawString("⛔️ you are at risk", 10, 10);
//    ofDrawBitmapString("a test of \nmultiline \ntext", 10,10);
    ofDrawBitmapStringHighlight("⛔️ you are \n at risk!!", 5, 25, ofColor(255,255,0), ofColor(255,0,0));
    ofPopStyle();
}

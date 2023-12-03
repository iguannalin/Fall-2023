#include "ofApp.h"

//window help: https://forum.openframeworks.cc/t/multi-windows-open-close-it-programatically-is-there-a-way/25268/2

//--------------------------------------------------------------
void ofApp::setup(){
    // add to ofApp::setup() to manipulate created windows
    for(auto it=windows.begin(); it!=windows.end(); it++){
        ofDefaultVec2 pos(150+cos(fmod(ofGetElapsedTimef(),TWO_PI)) * 100.f, 150+sin(fmod(ofGetElapsedTimef(),TWO_PI)) * 100.f);
        (*it)->setWindowPosition(pos.x, pos.y);
    }
    
    ofBackground(255);
    ofSetCircleResolution(200);

//    ofSetFrameRate(0.2);
    
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
      cout << msg << endl;

      if (msg.getAddress() == "/cursor/move")
      {
//        cursorX = msg.getArgAsInt(0);
//      cursorY = msg.getArgAsInt(1);
          if (abs(msg.getArgAsInt(0) - getX) > 25 ||
              abs(msg.getArgAsInt(1) - getY) > 25)
          {
              getX = msg.getArgAsInt(0);
              getY = msg.getArgAsInt(1);
              drawWindow();
          }
      }
      else if (msg.getAddress() == "/cursor/color")
      {
        // Generate a new random color.
        cursorColor = ofColor(ofRandom(127, 255), ofRandom(127, 255), ofRandom(127, 255));
      }
      else
      {
        ofLogWarning(__FUNCTION__) << "Unrecognized message " << msg.getAddress();
      }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofBackground(0);

    // Draw a circle at the cursor position.
//    ofSetColor(cursorColor);
//    ofDrawCircle(cursorX, cursorY, 50);
    
//    if (ofGetFrameNum() % 240)
//    {
//        ofApp::makeCall();
//    }
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

void ofApp::drawRandomInWindow(ofEventArgs & args){
    ofPushStyle();
    ofSetColor(ofColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255)));
    ofFill();
    ofDrawRectangle(ofRandomuf()*20.f, ofRandomuf()*20.f, ofRandomuf()*80.f, ofRandomuf()*80.f);
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

void ofApp::drawWindow() {
    ofGLFWWindowSettings settings;
    settings.setSize(300,300);
//    settings.setPosition(ofVec2f(ofRandom(0,400),ofRandom(0,600)));
    settings.setPosition(ofVec2f(getX,getY));
    settings.resizable = false;
    windows.push_back( ofCreateWindow(settings) );
    windows.back()->setVerticalSync(false);
    
    // when this is front() rectangles stop drawing after 1st popup
    ofAddListener(windows.back()->events().draw, this, &ofApp::drawRandomInWindow);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

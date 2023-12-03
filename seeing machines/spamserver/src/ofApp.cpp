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
    
    ofSetFrameRate(0.2);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(100);
    ofDrawCircle(ofGetWidth()*0.5,ofGetHeight()*0.5,50);
    ofSetColor(0);
    ofDrawBitmapString(ofGetFrameRate(),20,20);
    
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
    drawWindow();
}

void ofApp::drawRandomInWindow(ofEventArgs & args){
    ofPushStyle();
    ofSetColor(ofRandom(128,255));
    ofFill();
    ofDrawBitmapStringHighlight(element, ofPoint(30, 30));
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
    settings.setPosition(ofVec2f(ofRandom(0,400),ofRandom(0,600)));
//    settings.setPosition(ofVec2f(getX,getY));
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

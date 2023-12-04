#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // add to ofApp::setup() to manipulate created windows
    for(auto it=windows.begin(); it!=windows.end(); it++){
        ofDefaultVec2 pos(150+cos(fmod(ofGetElapsedTimef(),TWO_PI)) * 100.f, 150+sin(fmod(ofGetElapsedTimef(),TWO_PI)) * 100.f);
        (*it)->setWindowPosition(pos.x, pos.y);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    ofGLFWWindowSettings settings;
    settings.setSize(300,300);
    settings.setPosition(ofVec2f(ofRandom(0,600),ofRandom(0,400)));
    settings.resizable = false;
//    push to back of vector
    windows.push_back( ofCreateWindow(settings) );
    windows.back()->setVerticalSync(false);
// when last window is drawn, call drawrandom in window
    ofAddListener(windows.back()->events().draw, this,&ofApp::drawRandomInWindow);
}

void ofApp::drawRandomInWindow(ofEventArgs &args){
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

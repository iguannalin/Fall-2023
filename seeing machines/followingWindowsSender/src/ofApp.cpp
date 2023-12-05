#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // depth thresholds
    nearThreshold.set("Near Threshold", 0.01f, 0.0f, 0.1f);
    farThreshold.set("Far Threshold", 0.02f, 0.0f, 0.1f);
    
    // gui setup
    gui.setup();
    gui.add(nearThreshold);
    gui.add(farThreshold);

    // kinect setup
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
    
    // color img initialization
    colorImg.allocate(kinect.getWidth(), kinect.getHeight());
    
    // Set up the OSC sender.
    sendAddr = "localhost";
    sendPort = 3030;
    sender.setup(sendAddr, sendPort);
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();

    if (kinect.isFrameNew()){
        // update color img
        colorImg.setFromPixels(kinect.getPixels());
        
        // get pixel data from kinect
        const ofFloatPixels& rawDepthPix = kinect.getRawDepthPixels();
        
        // filter depth using thresholds
        ofFloatPixels thresholdNear, thresholdFar, thresholdResult;
        
        ofxCv::threshold(rawDepthPix, thresholdNear, nearThreshold);
        ofxCv::threshold(rawDepthPix, thresholdFar, farThreshold, true);
        ofxCv::bitwise_and(thresholdNear, thresholdFar, thresholdResult);
        
        thresholdImg.setFromPixels(thresholdResult);

        // contour size range
        int minimum = thresholdImg.getWidth() * thresholdImg.getHeight() * 0.05;
        int maximum = thresholdImg.getWidth() * thresholdImg.getHeight() * 0.8;
        
        // look for contours
        contourFinder.findContours(thresholdImg, minimum, maximum, 3, false);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    colorImg.draw(0, 0);
    
    contourFinder.draw();
    
    // draw centroids of the contour blobs
    if (contourFinder.nBlobs > 0) {
        for (int i=0; i<contourFinder.nBlobs; i++) {
            ofVec3f centroid = contourFinder.blobs[i].centroid;
            cout << centroid << endl;
            ofDrawCircle(centroid, 20);
            
            ofxOscMessage msg;
            msg.setAddress("/cursor/move");
            msg.addIntArg(centroid[0]);
            msg.addIntArg(centroid[1]);
            sender.sendMessage(msg);
        }
    }
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

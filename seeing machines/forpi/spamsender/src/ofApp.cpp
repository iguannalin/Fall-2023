#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // depth thresholds
    nearThreshold.set("Near Threshold", 0.01f, 0.0f, 0.1f);
    farThreshold.set("Far Threshold", 0.02f, 0.0f, 0.1f);
    scale = 1.7;
    
    // gui setup
    gui.setup();
    gui.add(nearThreshold);
    gui.add(farThreshold);

    // kinect setup
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
    
    // Set up the OSC sender.
    sendAddr = "localhost";
    sendPort = 3030;
    sender.setup(sendAddr, sendPort);
    test =  true;
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();

    if (kinect.isFrameNew()){
        test = false;
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
    ofClear(0.0f, 0.0f, 0.0f, 0.0f);
    
    
    if (!test) {
        ofPushMatrix();
        ofScale(scale,scale);
        // draw something
        contourFinder.draw();
        ofPopMatrix();
        
        // draw centroids of the contour blobs
        if (contourFinder.nBlobs > 0) {
            ofxOscMessage blobmsg;
            blobmsg.setAddress("/cursor/blobSize");
            blobmsg.addIntArg(contourFinder.nBlobs);
            sender.sendMessage(blobmsg);
            for (int i=0; i<contourFinder.nBlobs; i++) {
                ofVec3f centroid = contourFinder.blobs[i].centroid;
                ofxOscMessage msg;
                msg.setAddress("/cursor/move");
                msg.addIntArg(centroid[0]);
                msg.addIntArg(centroid[1]);
//                cout << centroid[0] << centroid[1] << endl;;
                sender.sendMessage(msg);
            }
        }
        gui.draw();
    }
}

void ofApp::mouseMoved(int x, int y) {
    if (test) {
        ofxOscMessage msg;
        msg.setAddress("/cursor/move");
        msg.addIntArg(x);
        msg.addIntArg(y);
//        cout << x << y << endl;
        sender.sendMessage(msg);
    }
}

//--------------------------------------------------------------
void ofApp::exit(){

}

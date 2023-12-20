#include "ofApp.h"
using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(100);
    finder.setup("haarcascade_frontalface_default.xml");
    finder.setPreset(ObjectFinder::Fast);
    finder.getTracker().setSmoothingRate(.3);
    cam.setup(ofGetWidth(), ofGetHeight());
    ofEnableAlphaBlending();
    
    windowLimit = 15; // no more than this many windows open at a time per person/blob
    
    adLinks = {
//        "https://iguannalin.github.io/spam/assets/howtocookspam.gif",
       "https://iguannalin.github.io/spam/assets/musubi.png",
//        "https://iguannalin.github.io/spam/assets/spamfactory.gif",
       "https://iguannalin.github.io/spam/assets/SpamLiteLogo.png",
       "https://iguannalin.github.io/spam/assets/SpamClassicLogo.png",
        "https://iguannalin.github.io/spam/assets/holeton-figurski-spam.png",
       "https://iguannalin.github.io/spam/assets/spam.png",
       "https://iguannalin.github.io/spam/assets/spamonaplate.png"
    };
    
    for (int i = 0; i < adLinks.size(); i++) {
        ofImage ad;
        ad.load(adLinks[i]);
        ads.push_back(ad);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    if(cam.isFrameNew()) {
        finder.update(cam);
    }

    if (abs(centroid[0] - getX) > 50 ||
        abs(centroid[1] - getY) > 50)
    {
        getX = ofLerp(getX, centroid[0], 0.5);
        getY = ofLerp(getY, centroid[1], 0.5);
        drawWindow();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    translateX = (ofGetWidth()/2 - cam.getWidth()/2);
    translateY = (ofGetHeight()/2 - cam.getHeight()/2);
    cam.draw(translateX, translateY);
    ofSetBackgroundColor(0);
    for(int i = 0; i < finder.size(); i++) {
        blobs = 1;finder.size();
        ofRectangle object = finder.getObjectSmoothed(i);
        centroid = object.getCenter();
    }
}

//--------------------------------------------------------------
void ofApp::exit(){

}

void ofApp::drawWindow() {
    if (windowIndex >= windowLimit) {
        windowIndex = 0;
    }
    ofPushMatrix();
    ofTranslate(translateX, translateY);
    for (int i = 0; i < blobs; i++) {
        if (windows.size() < (blobs*windowLimit)) {
            ofGLFWWindowSettings settings;
            settings.setSize(100,100);
            settings.setPosition(ofVec2f(getX,getY));
            settings.doubleBuffering = false;
            auto window = ofCreateWindow(settings);
            window->setVerticalSync(false);
            windows.push_back( window);
            // when this is front() rectangles stop drawing after 1st popup
            ofAddListener(windows.back()->events().draw, this, &ofApp::drawRandomInWindow);
        } else {
            shared_ptr<ofAppBaseWindow> recycle = windows[(i*windowLimit)+windowIndex];
            recycle->setWindowPosition(getX,getY);
        }
    }
    ofPopMatrix();
    windowIndex+=1;
}

void ofApp::drawRandomInWindow(ofEventArgs & args){
    ofGetCurrentRenderer() -> setBackgroundAuto(false);
    if (ofGetFrameNum() % 20 == 0) {
        ofPushStyle();
            ofBackground(ofColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255)));
            ofImage randomAd = ads[ofRandom(0, ads.size())];
            randomAd.draw(-5,15,110, 75);
        ofPopStyle();
   }
}

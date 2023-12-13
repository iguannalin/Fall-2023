#include "ofApp.h"

//window help: https://forum.openframeworks.cc/t/multi-windows-open-close-it-programatically-is-there-a-way/25268/2

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundAuto(false);
    ofSetFrameRate(25);
    blobs = 1;
    
    // Set up the OSC receiver.
    recvPort = 3030;
    receiver.setup(recvPort);
    windowLimit = 5; // no more than this many windows open at a time per person/blob
    
    adLinks = {
        "https://iguannalin.github.io/spam/assets/howtocookspam.gif",
       "https://iguannalin.github.io/spam/assets/musubi.png",
        "https://iguannalin.github.io/spam/assets/spamfactory.gif",
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
    while (receiver.hasWaitingMessages())
    {
      // Get the next message.
      ofxOscMessage msg;
      receiver.getNextMessage(msg);
      if (msg.getAddress() == "/cursor/move")
      {
//          cout<<msg.getArgAsInt(0)<<msg.getArgAsInt(1) <<endl;
//          check if at least 100px offset from previous window
          if (abs(msg.getArgAsInt(0) - getX) > 75 ||
              abs(msg.getArgAsInt(1) - getY) > 75)
          {
              getX = ofLerp(getX, msg.getArgAsInt(0), 0.5);
              getY = ofLerp(getY, msg.getArgAsInt(1), 0.5);
//              ofScale(2,2);
              drawWindow();
          }
      } else if (msg.getAddress() == "/cursor/blobSize")
      {
          blobs = msg.getArgAsInt(0);
          cout << "blobs: " << blobs<<endl;
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

void ofApp::drawWindow() {
    if (windowIndex >= windowLimit) {
        windowIndex = 0;
    }
    for (int i = 0; i < blobs; i++) {
        if (windows.size() < (blobs*windowLimit)) {
            ofGLFWWindowSettings settings;
            settings.setSize(150,150);
            settings.setPosition(ofVec2f(getX*2,getY*2));
            settings.doubleBuffering = false;
            auto window = ofCreateWindow(settings);
            window->setVerticalSync(false);
            windows.push_back( window);
            // when this is front() rectangles stop drawing after 1st popup
            ofAddListener(windows.back()->events().draw, this, &ofApp::drawRandomInWindow);
        } else {
            shared_ptr<ofAppBaseWindow> recycle = windows[(i*windowLimit)+windowIndex];
            recycle->setWindowPosition(getX*2,getY*2);
        }
    }
    windowIndex+=1;
}

void ofApp::drawRandomInWindow(ofEventArgs & args){
    ofGetCurrentRenderer() -> setBackgroundAuto(false);
   if (ofGetFrameNum() % 4 == 0) {
        ofPushStyle();
            
            ofBackground(ofColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255)));
            ofImage randomAd = ads[ofRandom(0, ads.size())];
            randomAd.draw(-10,25,175, 100);
        ofPopStyle();
   }
}

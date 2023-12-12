#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp{

    public:
        void setup() override;
        void update() override;
        void draw() override;
        void exit() override;
        void drawWindow();
    
        std::vector<shared_ptr<ofAppBaseWindow> > windows;
        void drawRandomInWindow(ofEventArgs & args);
        int blobs;
        float getX;
        float getY;
    
        int recvPort;
        ofxOscReceiver receiver;
    
        int windowIndex;
        int windowLimit;
    
        ofTrueTypeFont font;
        std::vector<string> ads;
};

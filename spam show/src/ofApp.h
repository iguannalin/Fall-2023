#pragma once

#include "ofMain.h"
#include "ofxCv.h"

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;
        void drawWindow();
        void drawRandomInWindow(ofEventArgs & args);
    
        std::vector<shared_ptr<ofAppBaseWindow> > windows;
        
        int blobs;
        float getX;
        float getY;
        int windowIndex;
        int windowLimit;
        ofTrueTypeFont font;
        std::vector<string> adLinks;
        std::vector<ofImage> ads;
    
        ofVideoGrabber cam;
        ofxCv::ObjectFinder finder;
        glm::vec3 centroid;
    
        float translateX;
        float translateY;
};

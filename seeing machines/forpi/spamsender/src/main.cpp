#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){

	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
    ofGLFWWindowSettings settings;
	settings.setSize(1024, 768);
//    settings.glVersionMajor = 3.0;
//    settings.glVersionMinor = 3.0;
//    settings.transparent = true;
    settings.windowMode = OF_FULLSCREEN; //OF_WINDOW; //can also be OF_FULLSCREEN

	auto window = ofCreateWindow(settings);
	ofRunApp(window, make_shared<ofApp>());
	ofRunMainLoop();
    
}

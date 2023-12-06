
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
    //Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
    ofGLFWWindowSettings settings;
    settings.visible = false;
    auto mainWindow = ofCreateWindow(settings);
    auto mainApp = make_shared<ofApp>();
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
}

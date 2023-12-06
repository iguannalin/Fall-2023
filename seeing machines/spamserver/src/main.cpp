
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
    //Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
    ofGLFWWindowSettings settings;
    settings.setSize(100, 100);
    settings.setPosition(glm::vec2(-100,-100));
    settings.resizable = true;
    auto mainWindow = ofCreateWindow(settings);
    auto mainApp = make_shared<ofApp>();
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
}

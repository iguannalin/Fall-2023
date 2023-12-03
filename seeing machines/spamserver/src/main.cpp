
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){

    //Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
    ofGLFWWindowSettings settings;
    settings.setSize(400, 400);
    settings.setPosition(glm::vec2(300,0));
    settings.resizable = true;
    auto mainWindow = ofCreateWindow(settings);
    auto mainApp = make_shared<ofApp>();
    
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
}

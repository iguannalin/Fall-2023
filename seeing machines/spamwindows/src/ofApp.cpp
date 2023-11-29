#include "ofApp.h"

//window help: https://forum.openframeworks.cc/t/multi-windows-open-close-it-programatically-is-there-a-way/25268/2

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    ofSetCircleResolution(200);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    // add to ofApp::setup() to manipulate created windows
    for(auto it=windows.begin(); it!=windows.end(); it++){
        ofDefaultVec2 pos(150+cos(fmod(ofGetElapsedTimef(),TWO_PI)) * 100.f, 150+sin(fmod(ofGetElapsedTimef(),TWO_PI)) * 100.f);
        (*it)->setWindowPosition(pos.x, pos.y);
    }
    
    ofSetColor(100);
    ofDrawCircle(ofGetWidth()*0.5,ofGetHeight()*0.5,50);
    ofSetColor(0);
    ofDrawBitmapString(ofGetFrameRate(),20,20);
    ofSetFrameRate(1);
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

void ofApp::drawRandomInWindow(ofEventArgs & args){
    ofPushStyle();
    ofSetColor(ofRandom(128,255));
    ofFill();
    ofDrawBitmapStringHighlight(element, ofPoint(30, 30));
    ofPopStyle();
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
    ofApp::makeCall();
    ofGLFWWindowSettings settings;
    settings.setSize(300,300);
    settings.setPosition(ofVec2f(getX,getY));
    settings.resizable = false;
    windows.push_back( ofCreateWindow(settings) );
    windows.back()->setVerticalSync(false);
    
    // when this is front() rectangles stop drawing after 1st popup
    ofAddListener(windows.back()->events().draw, this, &ofApp::drawRandomInWindow);
}

void ofApp::makeCall() {
    // Testing redirects and https.
    // This server will echo back everything that you send to it.
    std::string url = "https://dweet.io:443/get/latest/dweet/for/307b329b-67ef-4b9d-bf68-7096a62bf6bd";

    // Create a client.
    ofxHTTP::Client client;

    // Create a request.
    ofxHTTP::GetRequest request(url);

    // Create a context.
    ofxHTTP::Context context;

    // Set custom session settings.
    //
    // See the class documentation for many additional settings.
    ofxHTTP::ClientSessionSettings sessionSettings;

    // Use an iPhone X user agent string.
    sessionSettings.setUserAgent("Mozilla/5.0 (iPhone; CPU iPhone OS 11_0 like Mac OS X) AppleWebKit/604.1.38 (KHTML, like Gecko) Version/11.0 Mobile/15A372 Safari/604.1");

    // Set a 60 second keep-alive timeout (default is 8 seconds).
    sessionSettings.setKeepAliveTimeout(Poco::Timespan::SECONDS * 60);

    // Save the session settings with the context.
    context.setClientSessionSettings(sessionSettings);
    
    // Do the query!
    try
    {
        // Execute the request within the given context.
        auto response = client.execute(context, request);

        // Check the response.
        if (response->getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
        {
            // A successful response.
            ofLogNotice("ofApp::setup") << "Response success, expecting " << response->estimatedContentLength() << " bytes.";

            // Buffer the response, or otherwise consume the stream.
            ofJson json(response->json());

            ofLogNotice("ofApp::setup") << "Content Begin";
            
            element = json.begin().value();
            ofJson with = json.at("with");
            std::cout << json.dump(4) << std::endl;
            std::cout << json["with"] << std::endl;
            getX = json["with"][0]["content"]["x"];
            getY = json["with"][0]["content"]["y"];
            std::cout << json["with"][0]["content"]["x"] << std::endl;
            std::cout << json["with"][0]["content"]["y"] << std::endl;
//            std::cout << with.at("content") << std::endl;
            
            ofLogNotice("ofApp::setup") << "Content End";
        }
        else
        {
            ofLogError("ofApp::setup") << response->getStatus() << " " << response->getReason();
        }
    }
    catch (const Poco::Exception& exc)
    {
        ofLogError("ofApp::setup") << exc.displayText();
    }
    catch (const std::exception& exc)
    {
        ofLogError("ofApp::setup") << exc.what();
    }
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

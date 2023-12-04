//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"

// code from https://stackoverflow.com/a/71096161
struct Writer
{
    std::string name{};
};
void from_json(const nlohmann::json& j, Writer& writer)
{
    j.get_to(writer.name);
}

struct Writers
{
    std::vector<Writer> data{};
};
void from_json(const nlohmann::json& j, Writers& writers)
{
    writers.data = j.get<std::vector<Writer>>();
}

//[writer:[name:"VALUE"]]

void ofApp::setup()
{
    // This server will echo back everything that you send to it.
    std::string uri = "http://httpbin.org/post";

    ofJson json = {
        "hello", "jello"
    };

    // Create a client.
    ofxHTTP::Client client;

    // Create a request.
    ofxHTTP::JSONRequest request(uri);
    
    // Set the json request data.
    request.setJSON(json);
    
    try
    {
        // Execute the request.
        auto response = client.execute(request);
        
        // Check the response.
        if (response->getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
        {
            // A successful response.
            ofLogNotice("ofApp::setup") << "Response success, expecting " << response->estimatedContentLength() << " bytes.";
            
            // Buffer the response, or otherwise consume the stream.
            ofJson responseJson = response->json();
            
            ofLogNotice("ofApp::setup") << "Content Begin";
//            responseJson.dump(4);
            Writers writers{};
            responseJson.at("json").get_to(writers);

            for (const auto& writer : writers.data)
            {
                std::cout << writer.name << ", ";
            }
            std::cout << responseJson.value("json", "nonexistent") << std::endl;
            
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


void ofApp::draw()
{
    ofBackgroundGradient(ofColor::white, ofColor::black);

    ofDrawBitmapStringHighlight("See console for output.", ofPoint(30, 30));
}

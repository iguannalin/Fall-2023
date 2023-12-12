#include "ofApp.h"

//window help: https://forum.openframeworks.cc/t/multi-windows-open-close-it-programatically-is-there-a-way/25268/2

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(15);
    blobs = 1;
    
    // Set up the OSC receiver.
    recvPort = 3030;
    receiver.setup(recvPort);
    windowLimit = 10; // no more than this many windows open at a time per person/blob
    
    ads = {
        "🚀 Boost Your Productivity Instantly!\n Click Now for the Ultimate Time Management Solution! 🕒",
        "🌟 Unlock Success! Limited-Time Offer\n on Life-Changing Success Strategies! 💼",
        "🎉 Attention Gamers! Level Up Your \nSkills with the Latest Gaming Gear - Exclusive Discounts Inside! 🎮",
        "💰 Double Your Income! Discover the\n Secret to Financial Freedom - Act Fast for a Special Bonus! 💸",
        "🔥 Hot Deals Alert! Don't Miss Out on \nthe Hottest Trends - Shop Now and Save Big! 🛍️",
        "👩‍💻 Work Smarter, Not Harder! Transform\n Your Workday with Our Revolutionary Productivity App! 📱",
        "🍀 Feeling Lucky? Click to Spin the Wheel\nand Win Exciting Prizes! 🎰",
        "🌈 Brighten Your Day! Dive into a World\n of Happiness with Our Exclusive Feel-Good Content! 😄",
        "🔒 Secure Your Online Presence! Get the\n Ultimate Cybersecurity Solution - Limited Slots Available! 🛡️",
        "🚗 Rev Up Your Ride! Exclusive Discounts \non the Coolest Car Accessories - Shop Now! 🚗",
        "🎁 Freebies Galore! Click Now to Claim\n Your Free Sample - Limited Stock, Act Fast! 🆓",
        "🚨 Emergency Sale! Unbelievable Discounts\n on Must-Have Products - Hurry, While Stocks Last! ⏳",
        "👯‍♂️ Join the Fun! Exclusive Access to VIP\n Events - Click to RSVP Now! 🎉",
        "🧠 Unlock Your Brain's Potential! Boost\n Memory and Focus with Our Revolutionary Brain-Boosting Supplement! 💡",
        "🌐 Explore the World! Unbeatable Travel \nDeals Await - Your Dream Vacation is Just a Click Away! ✈️",
        "📚 Upgrade Your Skills! Limited-Time Offer \non Online Courses - Click for Instant Access! 🎓",
        "🔮 Discover Your Future! Get a Personalized\n Tarot Reading - Click for Insight and Guidance! 🔍",
        "🍕 Pizza Lovers Rejoice! Exclusive Offer on \nYour Favorite Pizzas - Order Now and Save! 🍕",
        "🎤 Sing Your Heart Out! Karaoke Night Special \n- Click to Reserve Your Spot and Shine on Stage! 🎶",
        "🏋️‍♂️ Fitness Freaks, Unite! Special Offer on\n Premium Gym Memberships - Click for a Healthier You! 💪"
    };
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
          if (abs(msg.getArgAsInt(0) - getX) > 100 ||
              abs(msg.getArgAsInt(1) - getY) > 100)
          {
              getX = ofLerp(getX, msg.getArgAsInt(0), 0.5);
              getY = ofLerp(getY, msg.getArgAsInt(1), 0.5);
//              ofScale(0.7,0.7);
              drawWindow();
          }
      } else if (msg.getAddress() == "/cursor/blobSize")
      {
          blobs = msg.getArgAsInt(0);
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
            settings.setPosition(ofVec2f(getX,getY));
            windows.push_back( ofCreateWindow(settings));
            // when this is front() rectangles stop drawing after 1st popup
            ofAddListener(windows.back()->events().draw, this, &ofApp::drawRandomInWindow);
        } else {
            shared_ptr<ofAppBaseWindow> recycle = windows[(i*windowLimit)+windowIndex];
            recycle->setWindowPosition(getX,getY);
        }
    }
    windowIndex+=1;
}

void ofApp::drawRandomInWindow(ofEventArgs & args){
//    cout<<windowIndex<<endl;
    ofPushStyle();
        ofSetColor(ofColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255)));
        //    ofDrawRectangle(ofRandomuf()*20.f, ofRandomuf()*20.f, ofRandomuf()*80.f, ofRandomuf()*80.f);
        ofBackground(ofColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255)));
        ofDrawBitmapStringHighlight(ads[windowIndex%ads.size()], 15, 50, ofColor(255,255,0), ofColor(255,0,0));
    ofPopStyle();
}

#include "ofMain.h"

#include "ofxSmartOscSender.h"
#include "ofxMultiOscSender.h"

using namespace bbb::ofxOscMessageStrictStreamOperators;

#include "ofxOscMessageOstreamExtension.h"
#include "ofxOscMessageInputStream.h"

class ofxSmartOscSenderExampleApp : public ofBaseApp {
    ofxMultiOscSender sender;
    ofxOscReceiver receiver;
    
public:
    void setup() {
        sender.addTarget("localhost", 9006);
        sender.addTarget("localhost", 9005);
        receiver.setup(9006);
    }
    
    void update() {
        ofxOscMessage m;
        
        if(ofGetFrameNum() % 60 == 0) {
            
            // simple format example
            sender.sendAsSimpleFormat("/framerate", ofGetFrameNum(), "aaa");
            
            // strict format example
            char c = rand();
            sender.sendAsStrictFormat("/random", c, c < 0);
            
            m.setAddress("/stream");
            m << '0' << 1 << 2l << 3.0f << 4.0 << "5";
            sender.sendMessage(m);
            
            // simple format stream operator, and set address with sender's call operator example
            sender.setUsingStrictFormat(false);
            sender("/sender_stream") << '0' << 1 << 2l << 3.0f << 4.0 << "5" << bbb::send;
            
            // strict format stream operator, and set address with bbb::send's call operator example
            sender.setUsingStrictFormat(true);
            sender << '0' << 1 << 2l << 3.0f << 4.0 << "5" << bbb::send("/sender_stream2");
            sender("/oscin_test") << 1 << 2 << "foo" << bbb::send;
        }
        
        while(receiver.hasWaitingMessages()) {
            receiver.getNextMessage(m);
            if(m.getAddress() == "/oscin_test") {
                int x, y;
                std::string str;
                oscin(m) >> x >> y >> str;
                ofLogNotice("/oscin_test") << x << ", " << y << ", " << str;
            } else {
                ofLogNotice() << m;
            }
        }
    }
};

int main() {
    ofSetupOpenGL(100, 100, OF_WINDOW);
    ofRunApp(new ofxSmartOscSenderExampleApp);
}

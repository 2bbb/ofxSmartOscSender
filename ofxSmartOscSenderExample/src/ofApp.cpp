#include "ofMain.h"
#include "ofxSmartOscSender.h"
#include "ofxMultiOscSender.h"

using namespace bbb::ofxOscMessageStreamOperators;

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
            sender.sendAsSimpleFormat("/framerate", ofGetFrameNum(), "aaa");
            
            char c = rand();
            sender.sendAsStrictFormat("/random", c);
            
            m.setAddress("/stream");
            m << '0' << 1 << 2l << 3.0f << 4.0 << "5";
            sender.sendMessage(m);
        }
        
        while(receiver.hasWaitingMessages()) {
            receiver.getNextMessage(m);
            const string &address = m.getAddress();
            if(address == "/framerate") {
                std::cout << m.getArgTypeName(0) << ":" << m.getArgAsInt32(0) << ", "
                          << m.getArgTypeName(1) << ":" << m.getArgAsString(1)
                          << std::endl;
            }
            
            else if(address == "/random") {
                std::cout << m.getArgTypeName(0) << ":" << (int)m.getArgAsChar(0)
                          << std::endl;
            }
            
            else if(address == "/stream") {
                std::cout << m.getArgTypeName(0) << ":" << (int)m.getArgAsChar(0)
                          << m.getArgTypeName(1) << ":" << m.getArgAsInt32(1)
                          << m.getArgTypeName(2) << ":" << m.getArgAsInt64(2)
                          << m.getArgTypeName(3) << ":" << m.getArgAsFloat(3)
                          << m.getArgTypeName(4) << ":" << m.getArgAsDouble(4)
                          << m.getArgTypeName(5) << ":" << m.getArgAsString(5);
            }
        }
    }
};

int main() {
    ofSetupOpenGL(1280, 720, OF_WINDOW);
    ofRunApp(new ofxSmartOscSenderExampleApp);
}

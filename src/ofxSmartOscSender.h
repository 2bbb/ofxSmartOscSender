//
//  ofxSmartOscSender.h
//  ofxSmartOscSender
//
//  Created by ISHII 2bit on 2015/11/12.
//
//

#ifndef ofxSmartOscSender_h
#define ofxSmartOscSender_h

#include "ofxOsc.h"
#include "ofxOscMessageStreamOperator.h"
#include <type_traits>

namespace bbb {
    using namespace ofxOscMessageStrictStreamOperators;

    template <typename Arg>
    void createMessageImpl(ofxOscMessage &m, const Arg &arg) {
        m << arg;
    }
    
    template <typename Arg, typename ... Args>
    void createMessageImpl(ofxOscMessage &m, const Arg &arg, const Args & ... args) {
        createMessageImpl(m << arg, args ...);
    }
    
    template <typename ... Args>
    ofxOscMessage createMessage(const std::string &address, const Args & ... args) {
        static_assert(sizeof...(args) != 0, "args is null at createMessage");
        
        ofxOscMessage m;
        m.setAddress(address);
        createMessageImpl(m, args ...);
        return m;
    }
    
    class ofxSmartOscSender;
    class ofxMultiOscSender;
    
    class Terminator {
        friend ofxSmartOscSender;
        friend ofxMultiOscSender;
        std::string address;
    public:
        Terminator &operator()(const std::string &address) {
            this->address = address;
            return *this;
        }
    };
    
    Terminator send;
    
    class ofxSmartOscSender : public ofxOscSender {
        bool bStrict;
        bool wrapInBundle;
        ofxOscMessage buf;
    public:
        ofxSmartOscSender(bool bStrict = false, bool wrapInBundle = true)
        : bStrict(bStrict)
        , wrapInBundle(wrapInBundle) {};
        
        ofxSmartOscSender(std::string host, int port, bool bStrict = false, bool wrapInBundle = true)
        : ofxSmartOscSender(bStrict, wrapInBundle) { setup(host, port); }
        
        void setUsingStrictFormat(bool bStrict) {
            this->bStrict = bStrict;
        }
        
        bool getUsingStrictFormat() const {
            return bStrict;
        }
        
        void setSendingWithWrapInBundle(bool wrapInBundle) {
            this->wrapInBundle = wrapInBundle;
        }
        
        bool getSendingWithWrapInBundle() const {
            return wrapInBundle;
        }

        void sendMessage(ofxOscMessage &m) {
            ofxOscSender::sendMessage(m, wrapInBundle);
        }
        
        template <typename ... Args>
        inline void send(const std::string &address, const Args & ... args) {
            static_assert(sizeof...(args) != 0, "args is null at send");
            
            ofxOscMessage m = createMessage(address, args ...);
            if(bStrict) sendAsStrictFormat(address, args ...);
            else        sendAsSimpleFormat(address, args ...);
        }
        
        template <typename ... Args>
        void sendAsStrictFormat(const std::string &address, const Args & ... args) {
            static_assert(sizeof...(args) != 0, "args is null at send as Smart format");
            
            ofxOscMessage m = createMessage(address, args ...);
            ofxOscSender::sendMessage(m, wrapInBundle);
        }

        template <typename ... Args>
        void sendAsSimpleFormat(const std::string &address, const Args & ... args) {
            static_assert(sizeof...(args) != 0, "args is null at send as Smart format");
            
            ofxOscMessage m = createMessage(address, simplize_cast<Args>(args) ...);
            ofxOscSender::sendMessage(m, wrapInBundle);
        }
        
#pragma mark stream
        
        ofxSmartOscSender &operator()(const std::string &address) {
            buf.setAddress(address);
            return *this;
        }
        
        template <typename T>
        get_type<std::enable_if<
            std::is_arithmetic<T>::value,
            ofxSmartOscSender
        >> &operator<<(T t) {
            if(bStrict) buf << t;
            else        buf << simplize_cast<T>(t);
            return *this;
        }
        
        ofxSmartOscSender &operator<<(const std::string &str) {
            buf << str;
            return *this;
        }
        
        ofxSmartOscSender &operator<<(const ofBuffer &buffer) {
            buf << buffer;
            return *this;
        }

        ofxSmartOscSender &operator<<(Terminator &t) {
            if(t.address != "") {
                operator()(t.address);
                t.address = "";
            }
            sendMessage(buf);
            buf.clear();
            
            return *this;
        }
    };
};

using ofxSmartOscSender = bbb::ofxSmartOscSender;

#endif /* ofxSmartOscSender_h */

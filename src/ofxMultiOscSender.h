//
//  ofxMultiOscSender.h
//  ofxSmartOscSender
//
//  Created by ISHII 2bit on 2015/11/12.
//
//

#ifndef ofxMultiOscSender_h
#define ofxMultiOscSender_h

#include "ofxSmartOscSender.h"

namespace bbb {
    class ofxMultiOscSender {
        struct Target {
            std::string host;
            int port;
            Target(std::string host, int port)
            : host(host)
            , port(port) {}
            bool operator<(const Target &key) const {
                if(host == key.host) return port < key.port;
                return strcmp(host.c_str(), key.host.c_str()) < 0;
            }
        };
        std::map<Target, ofxSmartOscSender> senders;
        
        bool bStrict;
        bool wrapInBundle;
    public:
        ofxMultiOscSender(bool bStrict = false, bool wrapInBundle = true)
        : bStrict(bStrict)
        , wrapInBundle(wrapInBundle) {}
        
        inline void addTarget(const std::string &host, int port) {
            senders.insert(std::make_pair(Target(host, port), ofxSmartOscSender(host, port, bStrict, wrapInBundle)));
        }
        
        void removeTarget(const std::string &host, int port) {
            auto result = senders.find(Target(host, port));
            if(result != senders.end()) {
                senders.erase(result);
            } else {
                ofLogWarning("ofxMultiOscSender") << host << ":" << port << " not found";
            }
        }
        
        void setUsingStrictFormat(bool bStrict) {
            this->bStrict = bStrict;
            for(auto &sender : senders) {
                sender.second.setUsingStrictFormat(bStrict);
            }
        }
        
        bool getUsingStrictFormat() const {
            return bStrict;
        }

        void setSendingWithWrapInBundle(bool wrapInBundle) {
            this->wrapInBundle = wrapInBundle;
            for(auto &sender : senders) {
                sender.second.setSendingWithWrapInBundle(wrapInBundle);
            }
        }
        
        bool getSendingWithWrapInBundle() const {
            return wrapInBundle;
        }

        template <typename ... Args>
        inline void send(const std::string &address, const Args & ... args) {
            if(bStrict) sendAsStrictFormat(address, args ...);
            else        sendAsSimpleFormat(address, args ...);
        }
        
        template <typename ... Args>
        void sendAsStrictFormat(const std::string &address, const Args & ... args) {
            for(auto &sender : senders) {
                sender.second.sendAsStrictFormat(address, args ...);
            }
        }

        template <typename ... Args>
        void sendAsSimpleFormat(const std::string &address, const Args & ... args) {
            for(auto &sender : senders) {
                sender.second.sendAsSimpleFormat(address, args ...);
            }
        }
        
        inline void sendMessage(ofxOscMessage &message) {
            for(auto &sender : senders) {
                sender.second.ofxOscSender::sendMessage(message, wrapInBundle);
            }
        }

        inline void sendMessage(ofxOscMessage &message, bool wrapInBundle = true) {
            for(auto &sender : senders) {
                sender.second.ofxOscSender::sendMessage(message, wrapInBundle);
            }
        }
        
        inline void sendBundle(ofxOscBundle &bundle) {
            for(auto &sender : senders) {
                sender.second.sendBundle(bundle);
            }
        }
        
        inline void sendParameter(const ofAbstractParameter &parameter) {
            for(auto &sender : senders) {
                sender.second.sendParameter(parameter);
            }
        }
        
        inline void disableBroadcast() {
            for(auto &sender : senders) {
                sender.second.disableBroadcast();
            }
        }
        
        inline void enableBroadcast() {
            for(auto &sender : senders) {
                sender.second.enableBroadcast();
            }
        }
    };
};

using ofxMultiOscSender = bbb::ofxMultiOscSender;

#endif /* ofxMultiOscSender_h */

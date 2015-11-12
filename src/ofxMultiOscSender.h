//
//  ofxMultiOscSender.h
//  ofxSimpleOscSender
//
//  Created by ISHII 2bit on 2015/11/12.
//
//

#ifndef ofxMultiOscSender_h
#define ofxMultiOscSender_h

#include "ofxSimpleOscSender.h"

namespace bbb {
    class ofxMultiOscSender {
        struct Key {
            std::string host;
            int port;
            Key(std::string host, int port)
            : host(host)
            , port(port) {}
            bool operator<(const Key &key) const {
                if(host == key.host) return port < key.port;
                return strcmp(host.c_str(), key.host.c_str()) < 0;
            }
        };
        std::map<Key, ofxSimpleOscSender> senders;
    public:
        inline void addTarget(const std::string &host, int port) {
            senders.insert(std::make_pair(Key(host, port), ofxSimpleOscSender(host, port)));
        }
        
        void removeTarget(const std::string &host, int port) {
            auto result = senders.find(Key(host, port));
            if(result != senders.end()) {
                senders.erase(result);
            } else {
                ofLogWarning("ofxMultiOscSender") << host << ":" << port << " not found";
            }
        }
        
        template <typename ... Args>
        void send(const std::string &address, const Args & ... args) {
            for(auto &sender : senders) {
                sender.second.send(address, args ...);
            }
        }
        
        template <typename ... Args>
        void sendAsSimpleFormat(const std::string &address, const Args & ... args) {
            for(auto &sender : senders) {
                sender.second.sendAsSimpleFormat(address, args ...);
            }
        }
        
        inline void sendMessage(ofxOscMessage &message, bool wrapInBundle = true) {
            for(auto &sender : senders) {
                sender.second.sendMessage(message, wrapInBundle);
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

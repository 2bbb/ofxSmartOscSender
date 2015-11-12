//
//  ofxSimpleOscSender.h
//  ofxSimpleOscSender
//
//  Created by ISHII 2bit on 2015/11/12.
//
//

#ifndef ofxSimpleOscSender_h
#define ofxSimpleOscSender_h

#include "ofxOsc.h"
#include <type_traits>

namespace bbb {
    ofxOscMessage &operator+=(ofxOscMessage &m, const char * const str) {
        m.addStringArg(std::string(str));
        return m;
    }
    
    ofxOscMessage &operator+=(ofxOscMessage &m, const std::string &str) {
        m.addStringArg(str);
        return m;
    }
    
    ofxOscMessage &operator+=(ofxOscMessage &m, bool b) {
        m.addBoolArg(b);
        return m;
    }
    
    ofxOscMessage &operator+=(ofxOscMessage &m, char c) {
        m.addCharArg(c);
        return m;
    }
    
    ofxOscMessage &operator+=(ofxOscMessage &m, unsigned char c) {
        m.addInt32Arg(c);
        return m;
    }
    
    ofxOscMessage &operator+=(ofxOscMessage &m, int n) {
        m.addInt32Arg(n);
        return m;
    }
    
    ofxOscMessage &operator+=(ofxOscMessage &m, unsigned int n) {
        m.addInt64Arg(n);
        return m;
    }
    
    ofxOscMessage &operator+=(ofxOscMessage &m, long n) {
        m.addInt64Arg(n);
        return m;
    }
    
    ofxOscMessage &operator+=(ofxOscMessage &m, unsigned long n) {
        m.addInt64Arg(n);
        return m;
    }
    
    ofxOscMessage &operator+=(ofxOscMessage &m, long long n) {
        m.addInt64Arg(n);
        return m;
    }
    
    ofxOscMessage &operator+=(ofxOscMessage &m, unsigned long long n) {
        m.addInt64Arg(n);
        return m;
    }
    
    ofxOscMessage &operator+=(ofxOscMessage &m, float f) {
        m.addFloatArg(f);
        return m;
    }
    
    ofxOscMessage &operator+=(ofxOscMessage &m, double f) {
        m.addDoubleArg(f);
        return m;
    }
    
    ofxOscMessage &operator+=(ofxOscMessage &m, const ofBuffer &buf) {
        m.addBlobArg(buf);
        return m;
    }
    
    template <typename Arg>
    void createMessageImpl(ofxOscMessage &m, const Arg &arg) {
        m += arg;
    }
    
    template <typename Arg, typename ... Args>
    void createMessageImpl(ofxOscMessage &m, const Arg &arg, const Args & ... args) {
        m += arg;
        createMessageImpl(m, args ...);
    }
    
    template <typename ... Args>
    ofxOscMessage createMessage(const std::string &address, const Args & ... args) {
        ofxOscMessage m;
        m.setAddress(address);
        static_assert(sizeof...(args) != 0, "args is null at createMessage");
        createMessageImpl(m, args ...);
        return m;
    }
    
    template <typename T>
    using get_type = typename T::type;

    template <typename T>
    using simplize_cast = get_type<std::conditional<
        std::is_same<get_type<std::remove_const<T>>, char *>::value
        || (std::is_array<T>::value && std::is_same<get_type<std::remove_extent<T>>, char>::value),
        char *,
        get_type<std::conditional<
            std::is_integral<T>::value,
            int,
            get_type<std::conditional<
                std::is_floating_point<T>::value,
                float,
                T
            >>
        >>
    >>;

    class ofxSimpleOscSender : public ofxOscSender {
    public:
        ofxSimpleOscSender(std::string host, int port) {
            setup(host, port);
        }
        
        template <typename ... Args>
        void send(const std::string &address, const Args & ... args) {
            static_assert(sizeof...(args) != 0, "args is null at send");
            ofxOscMessage m = createMessage(address, args ...);
            sendMessage(m);
        }
        
        template <typename ... Args>
        void sendAsSimpleFormat(const std::string &address, const Args & ... args) {
            static_assert(sizeof...(args) != 0, "args is null at send as simple format");
            ofxOscMessage m = createMessage(address, simplize_cast<Args>(args) ...);
            sendMessage(m);
        }
    };
};

using ofxSimpleOscSender = bbb::ofxSimpleOscSender;

#endif /* ofxSimpleOscSender_h */

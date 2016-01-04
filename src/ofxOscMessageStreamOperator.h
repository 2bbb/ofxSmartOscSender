//
//  ofxOscMessageStreamOperator.h
//  ofxSmartOscSender
//
//  Created by ISHII 2bit on 2015/11/14.
//
//

#ifndef ofxOscMessageStreamOperator_h
#define ofxOscMessageStreamOperator_h

#include "ofxOscMessage.h"

namespace bbb {
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
    
    namespace ofxOscMessageBasicStreamOperators {
        inline ofxOscMessage &operator<<(ofxOscMessage &m, const char * const str) {
            m.addStringArg(std::string(str));
            return m;
        }
        
        inline ofxOscMessage &operator<<(ofxOscMessage &m, const std::string &str) {
            m.addStringArg(str);
            return m;
        }
        
        inline ofxOscMessage &operator<<(ofxOscMessage &m, const ofBuffer &buf) {
            m.addBlobArg(buf);
            return m;
        }
        
        inline ofxOscMessage &operator<<(ofxOscMessage &m, const ofColor &c) {
            m.addInt32Arg(c.r);
            m.addInt32Arg(c.g);
            m.addInt32Arg(c.b);
            m.addInt32Arg(c.a);
            return m;
        }
        
        inline ofxOscMessage &operator<<(ofxOscMessage &m, const ofShortColor &c) {
            m.addInt32Arg(c.r);
            m.addInt32Arg(c.g);
            m.addInt32Arg(c.b);
            m.addInt32Arg(c.a);
            return m;
        }
        
        inline ofxOscMessage &operator<<(ofxOscMessage &m, const ofFloatColor &c) {
            m.addFloatArg(c.r);
            m.addFloatArg(c.g);
            m.addFloatArg(c.b);
            m.addFloatArg(c.a);
            return m;
        }
        
        inline ofxOscMessage &operator<<(ofxOscMessage &m, const ofVec2f &p) {
            m.addFloatArg(p.x);
            m.addFloatArg(p.y);
            return m;
        }
        
        inline ofxOscMessage &operator<<(ofxOscMessage &m, const ofVec3f &p) {
            m.addFloatArg(p.x);
            m.addFloatArg(p.y);
            m.addFloatArg(p.z);
            return m;
        }
        
        inline ofxOscMessage &operator<<(ofxOscMessage &m, const ofVec4f &p) {
            m.addFloatArg(p.x);
            m.addFloatArg(p.y);
            m.addFloatArg(p.z);
            m.addFloatArg(p.w);
            return m;
        }
        
        inline ofxOscMessage &operator<<(ofxOscMessage &m, const ofRectangle &rect) {
            m.addFloatArg(rect.x);
            m.addFloatArg(rect.y);
            m.addFloatArg(rect.width);
            m.addFloatArg(rect.height);
            return m;
        }
    }
    
    namespace ofxOscMessageSimpleStreamOperators {
        using namespace ofxOscMessageBasicStreamOperators;
        
        template <typename T>
        get_type<std::enable_if<std::is_integral<T>::value, ofxOscMessage>> &operator<<(ofxOscMessage &m, T n) {
            m.addInt32Arg(n);
            return m;
        }
        
        template <typename T>
        get_type<std::enable_if<std::is_floating_point<T>::value, ofxOscMessage>> &operator<<(ofxOscMessage &m, T f) {
            m.addFloatArg(f);
            return m;
        }
    }
    
    namespace ofxOscMessageStrictStreamOperators {
        using namespace ofxOscMessageBasicStreamOperators;
        
        inline ofxOscMessage &operator<<(ofxOscMessage &m, bool b) {
            m.addBoolArg(b);
            return m;
        }

        ofxOscMessage &operator<<(ofxOscMessage &m, char c) {
            m.addCharArg(c);
            return m;
        }
        
        template <typename T>
        get_type<std::enable_if<
            !std::is_same<T, char>::value && (
                sizeof(T) < 4 ||
                (sizeof(T) == 4 && std::is_signed<T>::value)
            ),
            ofxOscMessage
        >> &operator<<(ofxOscMessage &m, T c) {
            m.addInt32Arg(c);
            return m;
        }

        template <typename T>
        get_type<std::enable_if<
            !std::is_same<T, int>::value && (
                4 <= sizeof(T) &&
                std::is_integral<T>::value
            ),
            ofxOscMessage
        >> &operator<<(ofxOscMessage &m, T n) {
            m.addInt64Arg(n);
            return m;
        }

        inline ofxOscMessage &operator<<(ofxOscMessage &m, float f) {
            m.addFloatArg(f);
            return m;
        }

        inline ofxOscMessage &operator<<(ofxOscMessage &m, double f) {
            m.addDoubleArg(f);
            return m;
        }
    }
    namespace ofxOscMessageStreamOperators = ofxOscMessageSimpleStreamOperators;
};

#endif /* ofxOscMessageStreamOperator_h */

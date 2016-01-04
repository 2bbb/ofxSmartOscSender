//
//  ofxOscMessageInputStream.h
//  ofxSmartOscSender
//
//  Created by ISHII 2bit on 2016/01/04.
//
//

#ifndef ofxOscMessageInputStream_h
#define ofxOscMessageInputStream_h

#include "ofxOscMessage.h"

class ofxOscMessageInputStream {
    const ofxOscMessage &m;
    std::size_t offset;
    ofxOscMessageInputStream &self;
public:
    ofxOscMessageInputStream(const ofxOscMessage &m, std::size_t offset = 0)
    : m(m)
    , offset(offset)
    , self(*this) {}
    
    ofxOscMessageInputStream &operator>>(std::string &str) {
        str = m.getArgAsString(offset++);
        return self;
    }
    
    ofxOscMessageInputStream &operator>>(bool &b) {
        b = m.getArgAsBool(offset++);
        return self;
    }
    
    ofxOscMessageInputStream &operator>>(float &num) {
        num = m.getArgAsFloat(offset++);
        return self;
    }
    
    ofxOscMessageInputStream &operator>>(double &num) {
        num = m.getArgAsFloat(offset++);
        return self;
    }
    
    ofxOscMessageInputStream &operator>>(ofRectangle &rect) {
        rect.x = m.getArgAsFloat(offset++);
        rect.y = m.getArgAsFloat(offset++);
        rect.width = m.getArgAsFloat(offset++);
        rect.height = m.getArgAsFloat(offset++);
        
        return self;
    }
    
    ofxOscMessageInputStream &operator>>(ofColor &c) {
        c.r = m.getArgAsInt32(offset++);
        c.g = m.getArgAsInt32(offset++);
        c.b = m.getArgAsInt32(offset++);
        if(offset < m.getNumArgs()) c.a = m.getArgAsInt32(offset++);
        
        return self;
    }
    
    ofxOscMessageInputStream &operator>>(ofShortColor &c) {
        c.r = m.getArgAsInt32(offset++);
        c.g = m.getArgAsInt32(offset++);
        c.b = m.getArgAsInt32(offset++);
        if(offset < m.getNumArgs()) c.a = m.getArgAsInt32(offset++);
        
        return self;
    }
    
    ofxOscMessageInputStream &operator>>(ofFloatColor &c) {
        c.r = m.getArgAsFloat(offset++);
        c.g = m.getArgAsFloat(offset++);
        c.b = m.getArgAsFloat(offset++);
        if(offset < m.getNumArgs()) c.a = m.getArgAsFloat(offset++);
        
        return self;
    }
    
    ofxOscMessageInputStream &operator>>(ofVec2f &p) {
        p.x = m.getArgAsFloat(offset++);
        p.y = m.getArgAsFloat(offset++);
        
        return self;
    }
    
    ofxOscMessageInputStream &operator>>(ofVec3f &p) {
        p.x = m.getArgAsFloat(offset++);
        p.y = m.getArgAsFloat(offset++);
        if(offset < m.getNumArgs()) p.z = m.getArgAsFloat(offset++);
        
        return self;
    }
    
    ofxOscMessageInputStream &operator>>(ofVec4f &p) {
        p.x = m.getArgAsFloat(offset++);
        p.y = m.getArgAsFloat(offset++);
        p.z = m.getArgAsFloat(offset++);
        p.w = m.getArgAsFloat(offset++);
        
        return self;
    }
    
    ofxOscMessageInputStream &operator>>(ofBuffer &buf) {
        buf = m.getArgAsBlob(offset++);
        
        return self;
    }
    
    template <typename T>
    auto operator>>(T &num)
    -> typename std::enable_if<(std::is_integral<T>::value && sizeof(T) < 4) || (std::is_integral<T>::value && std::is_signed<T>::value && sizeof(T) == 4), ofxOscMessageInputStream &>::type
    {
        num = m.getArgAsInt32(offset++);
        return self;
    }
    
    template <typename T>
    auto operator>>(T &num)
    -> typename std::enable_if<(std::is_integral<T>::value && std::is_unsigned<T>::value && sizeof(T) == 4) || (std::is_integral<T>::value && 4 < sizeof(T)), ofxOscMessageInputStream &>::type
    {
        num = m.getArgAsInt64(offset);
        offset++;
        return self;
    }
};

using oscin = ofxOscMessageInputStream;

#endif /* ofxOscMessageInputStream_h */

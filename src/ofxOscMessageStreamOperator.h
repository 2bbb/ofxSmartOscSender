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

inline ofxOscMessage &operator<<(ofxOscMessage &m, const char * const str) {
    m.addStringArg(std::string(str));
    return m;
}

inline ofxOscMessage &operator<<(ofxOscMessage &m, const std::string &str) {
    m.addStringArg(str);
    return m;
}

inline ofxOscMessage &operator<<(ofxOscMessage &m, bool b) {
    m.addBoolArg(b);
    return m;
}

inline ofxOscMessage &operator<<(ofxOscMessage &m, char c) {
    m.addCharArg(c);
    return m;
}

inline ofxOscMessage &operator<<(ofxOscMessage &m, unsigned char c) {
    m.addInt32Arg(c);
    return m;
}

inline ofxOscMessage &operator<<(ofxOscMessage &m, short n) {
    m.addInt32Arg(n);
    return m;
}

inline ofxOscMessage &operator<<(ofxOscMessage &m, unsigned short c) {
    m.addInt32Arg(c);
    return m;
}

inline ofxOscMessage &operator<<(ofxOscMessage &m, int n) {
    m.addInt32Arg(n);
    return m;
}

inline ofxOscMessage &operator<<(ofxOscMessage &m, unsigned int n) {
    m.addInt64Arg(n);
    return m;
}

inline ofxOscMessage &operator<<(ofxOscMessage &m, long n) {
    m.addInt64Arg(n);
    return m;
}

inline ofxOscMessage &operator<<(ofxOscMessage &m, unsigned long n) {
    m.addInt64Arg(n);
    return m;
}

inline ofxOscMessage &operator<<(ofxOscMessage &m, long long n) {
    m.addInt64Arg(n);
    return m;
}

inline ofxOscMessage &operator<<(ofxOscMessage &m, unsigned long long n) {
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

inline ofxOscMessage &operator<<(ofxOscMessage &m, const ofBuffer &buf) {
    m.addBlobArg(buf);
    return m;
}

#endif /* ofxOscMessageStreamOperator_h */

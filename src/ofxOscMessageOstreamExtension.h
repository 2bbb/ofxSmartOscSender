//
//  ofxOscMessageOstreamExtension.h
//  ofxSmartOscSender
//
//  Created by ISHII 2bit on 2015/11/16.
//
//

#ifndef ofxOscMessageOstream_h
#define ofxOscMessageOstream_h

#include "ofxOscMessage.h"

std::ostream &operator<<(std::ostream &os, const ofxOscMessage &m);

#endif /* ofxOscMessageOstream_h */

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

#if (OF_VERSION_MAJOR == 0) && (OF_VERSION_MINOR < 10)

std::ostream &operator<<(std::ostream &os, const ofxOscMessage &m);

#endif

#endif /* ofxOscMessageOstream_h */

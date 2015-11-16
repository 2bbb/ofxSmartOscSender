//
//  ofxOscMessageOstreamExtension.h
//  ofxSmartOscSender
//
//  Created by ISHII 2bit on 2015/11/16.
//
//

#ifndef ofxOscMessageOstream_h
#define ofxOscMessageOstream_h

std::ostream &operator<<(std::ostream &os, const ofxOscMessage &m) {
    os << "from " << m.getRemoteIp() << ":" << m.getRemotePort() << " [" << m.getAddress() << "]:\n  {";
    for(size_t i = 0; i < m.getNumArgs(); i++) {
        switch(m.getArgType(i)) {
            case OFXOSC_TYPE_INT32:
                os << i << " : " << m.getArgAsInt32(i) << " [int32], ";
                break;
            case OFXOSC_TYPE_INT64:
                os << i << " : " << m.getArgAsInt64(i) << " [int64], ";
                break;
            case OFXOSC_TYPE_FLOAT:
                os << i << " : " << m.getArgAsFloat(i) << " [float], ";
                break;
            case OFXOSC_TYPE_DOUBLE:
                os << i << " : " << m.getArgAsDouble(i) << " [double], ";
                break;
            case OFXOSC_TYPE_STRING:
                os << i << " : \"" << m.getArgAsString(i) << "\" [string], ";
                break;
            case OFXOSC_TYPE_SYMBOL:
                os << i << " : \"" << m.getArgAsSymbol(i) << "\" [symbol], ";
                break;
            case OFXOSC_TYPE_CHAR: {
                os << i << " : ";
                if(std::isprint(m.getArgAsChar(i))) {
                    os << "'" << m.getArgAsChar(i) << "' == ";
                }
                int8_t val = m.getArgAsChar(i);
                uint8_t c;
                memcpy(&c, &val, 1);
                os << (int)c << " [char], ";
                break;
            }
            case OFXOSC_TYPE_MIDI_MESSAGE: {
                int32_t val = m.getArgAsMidiMessage(i);
                uint8_t midi[4];
                memcpy(midi, &val, 4);
                os << i << " : {" << midi[0] << ", "
                                  << midi[1] << ", "
                                  << midi[2] << ", "
                                  << midi[3] << "} [midi], ";
                break;
            }
            case OFXOSC_TYPE_TRUE:
                os << i << " : [true], ";
                break;
            case OFXOSC_TYPE_FALSE:
                os << i << " : [false], ";
                break;
            case OFXOSC_TYPE_NONE:
                os << i << " : [none], ";
                break;
            case OFXOSC_TYPE_TRIGGER:
                os << i << " : " << (m.getArgAsTrigger(i) ? "true" : "false") << " [trigger], ";
                break;
            case OFXOSC_TYPE_TIMETAG:
                os << i << " : " << m.getArgAsInt64(i) << " [time], ";
                break;
            case OFXOSC_TYPE_BLOB:
                os << i << " : " << m.getArgAsInt64(i) << " [blob], ";
                break;
            case OFXOSC_TYPE_BUNDLE:
                os << i << " : [bundle], ";
                break;
            case OFXOSC_TYPE_RGBA_COLOR: {
#if true || OF_VERSION_MINOR < 9 || (OF_VERSION_MINOR == 9 && OF_VERSION_PATCH == 0)
                os << i << " : [color], ";
#else
                int32_t val = m.getArgAsRgbaColor(i);
                uint8_t color[4];
                memcpy(color, &val, 4);
                os << i << " : {" << color[0] << ", "
                                  << color[1] << ", "
                                  << color[2] << ", "
                                  << color[3] << "} [color], ";
#endif
                break;
            }
            case OFXOSC_TYPE_INDEXOUTOFBOUNDS:
                os  << i << " : [out of bounds], ";
                break;
        }
    }
    return os << "}";
}


#endif /* ofxOscMessageOstream_h */

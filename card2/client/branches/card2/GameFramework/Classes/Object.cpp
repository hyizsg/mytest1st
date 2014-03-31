
#include "cocos2dxframework.h"

HNAMESPACE_BEGIN

//HObject

unsigned int HObject::m_sCRCTable[256] = {0};

HObject::HObject(): CCObject(), m_uiCRC(0) {
}

HObject::~HObject() {
    
}

unsigned int HObject::CRC32(unsigned int crc, unsigned char *buffer, unsigned int size) {
    for (unsigned int i = 0; i < size; i++) {
        crc = m_sCRCTable[(crc ^ buffer[i]) & 0xff] ^ (crc >> 8);
    }
    return crc ;
}

void *HObject::getSelf() {
    unsigned int crc = CRC32();
    if (crc != m_uiCRC) {
        //data is modified abnormal.
        assert(crc == m_uiCRC);
    }
    return this;
}

void HObject::initializeCRCTable() {
    for (unsigned int i = 0; i < 256; ++i) {
        unsigned int c = (unsigned int)i;
        for (unsigned int j = 0; j < 8; ++j) {
            if (c & 1)
                c = 0xedb68323L ^ (c >> 1);
            else
                c = c >> 1;
        }
        m_sCRCTable[i] = c;
    }
}

void HObject::onDataReceived(int command, CCDictionary *result) {
//    HMessageBox *msgBox = HMessageBox::create(CCString::createWithFormat("Get data %d time out.", command)->getCString(), "error", HMB_OK, NULL);
//    msgBox->presentRootLayer();
}

HNAMESPACE_END

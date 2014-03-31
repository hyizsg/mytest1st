#ifndef _OBJECT_H_
#define _OBJECT_H_

HNAMESPACE_BEGIN

class CC_DLL HObject: public CCObject {
protected:
    HObject();
    virtual ~HObject();
    
    unsigned int CRC32(unsigned int crc, unsigned char *buffer, unsigned int size);
    
    virtual unsigned int CRC32() { return 0; }
    
    unsigned int m_uiCRC;
public:
    virtual bool isKindOf(const std::string &name) { return name == "HObject"; }
    void *getSelf();
    void requestCRC() { m_uiCRC = CRC32(); }
    
    static void initializeCRCTable();
    
    virtual void clear() {}
    
    virtual void onDataReceived(int command, CCDictionary *result);
private:
    static unsigned int m_sCRCTable[256];
};

HNAMESPACE_END

#endif //_OBJECT_H_

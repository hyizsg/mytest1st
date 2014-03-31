//
//  HReadText.h
//  testReadtxt
//
//  Created by 周 刚 on 13-4-24.
//
//

#ifndef __testReadtxt__HReadText__
#define __testReadtxt__HReadText__

class HTextReader : public cocos2d::CCObject
{
    
public:
    HTextReader(const char* file);
    HTextReader(unsigned char* data, unsigned long size);
    ~HTextReader();
    
    
    bool haveNext();
    bool getNext(char* str);
    
private:
    unsigned char* m_pData;
    unsigned char* m_pIndex;
    
    unsigned int m_nLen;
    bool m_bDelete;
    
    bool _isBlank(char p);
};

extern void decodeConfig(unsigned char *data, int len);

#endif /* defined(__testReadtxt__HReadText__) */

#ifndef _HSTRING_H_
#define _HSTRING_H_

HNAMESPACE_BEGIN

CC_DLL enum HSTRING_VALUETYPE {
    HSVT_STRING,
    HSVT_BOOLEAN,
    HSVT_INTEGER,
    HSVT_UINTEGER,
    HSVT_FLOAT,
    HSVT_DOUBLE
};

class CC_DLL HString: public CCString {
    CC_SYNTHESIZE(int, m_iValueType, ValueType);
public:
    HString(): m_iValueType(HSVT_STRING) {}
    HString(const char* str): CCString(str), m_iValueType(HSVT_STRING) {}
    HString(const std::string& str): CCString(str), m_iValueType(HSVT_STRING) {}
    HString(const CCString& str): CCString(str), m_iValueType(HSVT_STRING) {}
    
    static HString* create(const std::string& str);
    static HString* createWithFormat(const char* format, ...);
    static HString* createWithData(const unsigned char* pData, unsigned long nLen);
    static HString* createWithContentsOfFile(const char* pszFileName);
    
    static HString* createWithBoolean(bool value);
    static HString* createWithInteger(int value);
    static HString* createWithUInteger(unsigned int value);
    static HString* createWithFloat(float value);
    static HString* createWithDouble(double value);
private:
    bool initWithFormatAndValist(const char* format, va_list ap);
};

HNAMESPACE_END

#endif //_HSTRING_H_

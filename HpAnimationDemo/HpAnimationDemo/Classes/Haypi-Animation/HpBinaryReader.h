//
//  HpBinaryReader.h
//  HpAnimTest
//
//  Created by zhou gang on 13-2-20.
//  Copyright (c) 2013年 Haypi. All rights reserved.
//

#ifndef __HpAnimTest__HpBinaryReader__
#define __HpAnimTest__HpBinaryReader__

#include <stdio.h>

namespace haypi_animation{

class HpBinaryReader {
    FILE* m_fp;
    char m_buffer[128];
    
    const char* m_pData;
    unsigned int m_dataLength;
    const char* m_ptr;
    
    size_t	 fread(void * __restrict, size_t, size_t);
    
public:
    HpBinaryReader(const char* p_file);
    HpBinaryReader(const char* p_data, unsigned int length);
    void Close();
    int Read(char* buffer, int count);
    bool ReadBoolean();
    char ReadChar();
    int ReadChars(char* buffer, int count);
    unsigned char ReadByte();
    double ReadDouble();
    short ReadInt16();
    int ReadInt32();
    long ReadInt64();
    float ReadSingle();
    int ReadString(char* buffer);
    unsigned short ReadUInt16();
    unsigned int ReadUInt32();
    unsigned long ReadUInt64();
};
}


#endif /* defined(__HpAnimTest__HpBinaryReader__) */

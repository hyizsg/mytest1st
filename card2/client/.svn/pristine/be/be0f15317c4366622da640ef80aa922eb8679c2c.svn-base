//
//  HpBinaryReader.cpp
//  HpAnimTest
//
//  Created by zhou gang on 13-2-20.
//  Copyright (c) 2013年 Haypi. All rights reserved.
//

#include "HpBinaryReader.h"
#include <memory.h>
#include <string.h>

namespace haypi_animation{
    
HpBinaryReader::HpBinaryReader(const char* p_file)
{
    m_fp = fopen(p_file, "rb");
    m_pData = NULL;
    m_dataLength = 0;
    m_ptr = NULL;

}
    
HpBinaryReader::HpBinaryReader(const char* p_data, unsigned int length)
{
    m_fp = NULL;
    m_pData = p_data;
    m_dataLength = length;
    m_ptr = m_pData;
}

void HpBinaryReader::Close()
{
    if (m_fp != NULL) {
        fclose(m_fp);
    }
}
    
size_t HpBinaryReader::fread(void * __restrict buff, size_t size, size_t count)
{
    if (m_fp != NULL) {
        return ::fread(buff, size, count, m_fp);
    }else if (m_pData != NULL){
        memcpy(buff, m_ptr, size * count);
        m_ptr += size * count;
        return size * count;
    }
    return 0;
}

int HpBinaryReader::Read(char* buffer, int count)
{
    memset(buffer, 0, count);
    return fread(buffer, sizeof(char), count);
}

bool HpBinaryReader::ReadBoolean()
{
    fread(m_buffer, sizeof(char), 1);
    return m_buffer[0] != 0;
}

char HpBinaryReader::ReadChar()
{
    fread(m_buffer, sizeof(char), 1);
    return m_buffer[0];
}

int HpBinaryReader::ReadChars(char* buffer, int count)
{
    return fread(buffer, sizeof(char), count);
}

unsigned char HpBinaryReader::ReadByte()
{
    fread(m_buffer, sizeof(unsigned char), 1);
    return *((unsigned char*)m_buffer);
    
}

double HpBinaryReader::ReadDouble()
{
    fread(m_buffer, sizeof(double), 1);
    return *((double*)m_buffer);
}

short HpBinaryReader::ReadInt16()
{
    fread(m_buffer, sizeof(short), 1);
    return *((short*)m_buffer);
}

int HpBinaryReader::ReadInt32()
{
    fread(m_buffer, sizeof(int), 1);
    return *((int*)m_buffer);
}

long HpBinaryReader::ReadInt64()
{
    fread(m_buffer, sizeof(long), 1);
    return *((long*)m_buffer);
}

float HpBinaryReader::ReadSingle()
{
    fread(m_buffer, sizeof(float), 1);
    return *((float*)m_buffer);
}

int HpBinaryReader::ReadString(char* buffer)
{
    unsigned char len = ReadByte();
    memset(buffer, 0, len+1);
    return  ReadChars(buffer, len);
}

unsigned short HpBinaryReader::ReadUInt16()
{
    fread(m_buffer, sizeof(unsigned short), 1);
    return *((unsigned short*)m_buffer);
}

unsigned int HpBinaryReader::ReadUInt32()
{
    fread(m_buffer, sizeof(unsigned int), 1);
    return *((unsigned int*)m_buffer);
}

unsigned long HpBinaryReader::ReadUInt64()
{
    fread(m_buffer, sizeof(unsigned long), 1);
    return *((unsigned long*)m_buffer);
}
}

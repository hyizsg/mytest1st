//
//  crypt.h
//  from HaypiNet
//
//  Created by jim kaden on 11-12-21.
//  Copyright (c) 2013年 Haypi Co.,Ltd. All rights reserved.
//
#ifndef __CYRPT_H__
#define __CYRPT_H__
#include <vector>
#include <string>

namespace haypi
{
    class CryptFunctions
    {
    public:
        typedef enum
        {
            CM_Plain = 0,   // 尚未实现
            CM_DES,         // 默认CM_DES_SBOX
            CM_RC4,         // 尚未实现
            CM_Base64,
            CM_RC5,
            CM_RC6,
            CM_DES_SBOX,
            CM_DES_CBC,
            CM_DES_ECB,
        }
        CRYPT_METHOD;
    public:
        // output 为空，outputLen将返回需要的长度
        // 否则，outputLen中初始值必须为output的长度
        virtual bool encrypt(unsigned char* input, int inputLen, unsigned char* output, int* outputLen) = 0;
        virtual bool decrypt(unsigned char* input, int inputLen, unsigned char* output, int* outputLen) = 0;
        
        // num_round非必须
        virtual bool init(unsigned char* key, int keylen, int num_rounds = 0) = 0;
        
        static CryptFunctions* createCrypt(CRYPT_METHOD method);
        
        // 避免gcc的warning
        virtual ~CryptFunctions(){}
    };


}
#endif

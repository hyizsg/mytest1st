//
//  crypt.h
//  from HaypiNet
//
//  Created by jim kaden on 11-12-21.
//  Copyright (c) 2013年 Haypi Co.,Ltd. All rights reserved.
//

#ifndef __CYRPT_IMP_H__
#define __CYRPT_IMP_H__
#include "Crypt.h"

typedef std::vector<char> CryptData;

namespace haypi
{
    typedef enum
    {
        ENCRYPT = 0,
        DECRYPT,
    }
    CRYPT_TYPE;
    
    typedef bool    (*PSubKey)[16][48];
    
    class Des : public CryptFunctions
    {
    private:
        bool SubKey[2][16][48];// 16»¶◊”√‹‘ø
        bool Is3DES;// 3¥ŒDES±Í÷æ
        //char Tmp[256];
        char deskey[16];
        char key[16];
        int  keyLen;
    protected:
        CRYPT_METHOD cm;
    private:
        bool Des_Go(char *Out,char *In,long datalen,const char *Key,int keylen,bool Type);
        void SetKey(const char* Key, int len);
        void DES(char Out[8], char In[8], const PSubKey pSubKey, bool Type);
        void SetSubKey(PSubKey pSubKey, const char Key[8]);
        void F_func(bool In[32], const bool Ki[48]);
        void S_func(bool Out[32], const bool In[48]);
        void Transform(bool *Out, bool *In, const char *Table, int len);
        void Xor(bool *InA, const bool *InB, int len);
        void RotateL(bool *In, int len, int loop);
        void ByteToBit(bool *Out, const char *In, int bits);
        void BitToByte(char *Out, const bool *In, int bits);
    public:
        Des();
        bool init(unsigned char* key, int keylen, int num_rounds);
        bool encrypt(unsigned char* input, int inputLen, unsigned char* output, int* outputLen) ;
        bool decrypt(unsigned char* input, int inputLen, unsigned char* output, int* outputLen) ;
    };

    class Des_CBC : public Des
    {
    public:
        Des_CBC(){cm = CM_DES_CBC;}
    };
    
    class Des_ECB : public CryptFunctions
    {
    private:
        char iv[8];
        char key[8];
    public:
        Des_ECB();
        bool init(unsigned char* key, int keylen, int num_rounds);
        bool encrypt(unsigned char* input, int inputLen, unsigned char* output, int* outputLen) ;
        bool decrypt(unsigned char* input, int inputLen, unsigned char* output, int* outputLen) ;
    };
    
    class Des_SBOX : public Des
    {
    public:
        Des_SBOX(){cm = CM_DES_SBOX;}
    };
    
    
    class RC5 : public CryptFunctions
    {
    private:
        unsigned long K[50], rounds;
    public:
        RC5();
        bool init(unsigned char* key, int keylen, int num_rounds);
        bool encrypt(unsigned char* input, int inputLen, unsigned char* output, int* outputLen) ;
        bool decrypt(unsigned char* input, int inputLen, unsigned char* output, int* outputLen) ;
    };

    class RC6 : public CryptFunctions
    {
    private:
        unsigned long K[44];
    public:
        RC6();
        bool init(unsigned char* key, int keylen, int num_rounds);
        bool encrypt(unsigned char* input, int inputLen, unsigned char* output, int* outputLen) ;
        bool decrypt(unsigned char* input, int inputLen, unsigned char* output, int* outputLen) ;
    };
    
    class Base64 : public CryptFunctions
    {
    public:
        Base64(){}
        bool init(unsigned char* key, int keylen, int num_rounds){return true;}
        bool encrypt(unsigned char* input, int inputLen, unsigned char* output, int* outputLen) ;
        bool decrypt(unsigned char* input, int inputLen, unsigned char* output, int* outputLen) ;
    };
}

#endif

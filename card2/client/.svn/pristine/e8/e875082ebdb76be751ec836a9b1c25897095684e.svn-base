//
//  crypt.cpp
//  from HaypiNet
//
//  Created by jim kaden on 11-12-21.
//  Copyright (c) 2013年 Haypi Co.,Ltd. All rights reserved.
//
#import "Crypt_imp.h"
#include "cocos2dxframework.h"
#include "Base.h"

#ifdef HOS_APPLE
extern "C" int base64_decode_(void * dst, const void * src, unsigned long len);
extern "C" int base64_encode_(void * dst, const void * src, unsigned long len);
#import <CommonCrypto/CommonCryptor.h>
#endif

using namespace haypi;
#define STORE32L(x, y) { (y)[3] = ((x)>>24)&255; (y)[2] = ((x)>>16)&255; (y)[1] = ((x)>>8)&255; (y)[0] = (x)&255; }
#define LOAD32L(x, y)  { x = (((unsigned long)(y)[3])<<24)|(((unsigned long)(y)[2])<<16)|(((unsigned long)(y)[1])<<8)|(((unsigned long)(y)[0])); }
#define STORE64L(x, y) { (y)[7] = ((x)>>56)&255; (y)[6] = ((x)>>48)&255; (y)[5] = ((x)>>40)&255; (y)[4] = ((x)>>32)&255; (y)[3] = ((x)>>24)&255; (y)[2] = ((x)>>16)&255; (y)[1] = ((x)>>8)&255; (y)[0] = (x)&255; }
#define LOAD64L(x, y)  { x = (((unsigned long long)((y)[7]))<<56)|(((unsigned long long)((y)[6]))<<48)|(((unsigned long long)((y)[5]))<<40)|(((unsigned long long)((y)[4]))<<32)|(((unsigned long long)((y)[3]))<<24)|(((unsigned long long)((y)[2]))<<16)|(((unsigned long long)((y)[1]))<<8)|(((unsigned long long)((y)[0]))); }
#define BSWAP(x)       ( ((x>>24)&0x000000FF)|((x<<24)&0xFF000000)|((x>>8)&0x0000FF00)|((x<<8)&0x00FF0000) )

#define ROL(x, y) ( ((x)<<((y)&31)) | ((x)>>(32-((y)&31))) )
#define ROR(x, y) ( ((x)>>((y)&31)) | ((x)<<(32-((y)&31))) )

#define MAX(x, y) ( ((x)>(y))?(x):(y) )
#define MIN(x, y) ( ((x)<(y))?(x):(y) )



// initial permutation IP
const static char IP_Table[64] = {
	58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17,  9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
};
// final permutation IP^-1 
const static char IPR_Table[64] = {
	40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41,  9, 49, 17, 57, 25
};
// expansion operation matrix
static const char E_Table[48] = {
	32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
    8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1
};
// 32-bit permutation function P used on the output of the S-boxes 
const static char P_Table[32] = {
	16, 7, 20, 21, 29, 12, 28, 17, 1,  15, 23, 26, 5,  18, 31, 10,
	2,  8, 24, 14, 32, 27, 3,  9,  19, 13, 30, 6,  22, 11, 4,  25
};
// permuted choice table (key) 
const static char PC1_Table[56] = {
	57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
	10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
	14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4
};
// permuted choice key (table) 
const static char PC2_Table[48] = {
	14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
	23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};
// number left rotations of pc1 
const static char LOOP_Table[16] = {
	1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};
// The (in)famous S-boxes 
const static char S_Box[8][4][16] = {
	// S1 
	14,	 4,	13,	 1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
    0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
    4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
    15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13,
	// S2 
    15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
    3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
    0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
    13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9,
	// S3 
    10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
	13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
	13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
    1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12,
	// S4 
    7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
	13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
	10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
    3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14,
	// S5 
    2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
	14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
    4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
    11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3,
	// S6 
    12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
	10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
    9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
    4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13,
	// S7 
    4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
	13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
    1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
    6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12,
	// S8 
    13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
    1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
    7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
    2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
};


Des::Des()
{
	memset(SubKey, 0, sizeof(SubKey));
	memset(deskey, 0, sizeof(deskey));
    char tmp[] = {1,9,7,5,0,3,0,9};
    memset(key, 0, 16);
	memcpy(key, tmp, 8);
    keyLen = 8;
}

bool Des::init(unsigned char * key_, int keylen_, int num_rounds)
{
	memset(SubKey, 0, sizeof(SubKey));
	memset(deskey, 0, sizeof(deskey));
    memset(key, 0, 16);
	memcpy(key, key_, MIN(16, keylen_));
    keyLen = keylen_;
    return true;
}

bool Des::encrypt(unsigned char* input, int inputLen, unsigned char* output, int* outputLen)
{
    memset(SubKey, 0, sizeof(SubKey));
    memset(deskey, 0, sizeof(deskey));

    int len = (inputLen + 7) / 8 * 8;
    if ( output == NULL )
    {
        *outputLen = len;
        return true;
    }
    if ( *outputLen < len )
        return false;
    
    *outputLen = len;
    return Des_Go((char*)output, (char*)input, inputLen, key, keyLen, ENCRYPT);
}

bool Des::decrypt(unsigned char* input, int inputLen, unsigned char* output, int* outputLen)
{
    memset(SubKey, 0, sizeof(SubKey));// 16»¶◊”√‹‘ø
    memset(deskey, 0, sizeof(deskey));
    int len = inputLen;
    if ( output == NULL )
    {
        *outputLen = len;
        return true;
    }
    if ( *outputLen < len )
        return false;
    return Des_Go((char*)output, (char*)input, inputLen, key, keyLen, DECRYPT);
}


bool Des::Des_Go(char * Out, char* In, long datalen, const char* Key, int keylen, bool Type)
{
    if( !( Out && In && Key && (datalen=(datalen+7)&0xfffffff8) ) ) 
		return false;
	SetKey(Key,keylen);
	if( !Is3DES ) 
    {
        if ( cm == CM_DES_SBOX || cm == CM_DES || cm == CM_DES_ECB )
        {
            for(long i=0,j=datalen>>3; i<j; ++i,Out+=8,In+=8)
                DES(Out,In,(const PSubKey)&SubKey[0],Type);
        }
        else if ( cm == CM_DES_CBC )
        {
            unsigned char cvec[8] = {2,0,0,2,0,5,2,3}; //初始化向量
            unsigned char cvin[8] = ""; //中间变量
            

            for(long i=0,j=datalen>>3; i<j; ++i,Out+=8,In+=8)
            {
                if(Type == ENCRYPT)
                {
                    for(int k=0;k<8;++k)     //将输入与扭转变量异或
                    {
                        cvin[k] = In[k] ^ cvec[k];
                    }
                }
                else
                {
                    memcpy(cvin,In,8);
                }
                
                DES(Out, (char*)cvin,(const PSubKey)&SubKey[0],Type);
                
                if(Type == ENCRYPT)
                {
                    memcpy(cvec,Out,8);         //将输出设定为扭转变量
                }
                else
                {
                    for(int k=0;k<8;++k)        //将输出与扭转变量异或
                    {
                        Out[k]  =   Out[k] ^ cvec[k];
                    }
                    memcpy(cvec,cvin,8);        //将输入设定为扭转变量
                }
            }
        }
	}
    else
    {
        if ( cm == CM_DES_SBOX || cm == CM_DES || cm == CM_DES_ECB )
        {
            for(long i=0,j=datalen>>3; i<j; ++i,Out+=8,In+=8)
            {
                DES(Out,In,(const PSubKey)&SubKey[0],Type);
                DES(Out,Out,(const PSubKey)&SubKey[1],!Type);
                DES(Out,Out,(const PSubKey)&SubKey[0],Type);
            }
        }
        else if ( cm == CM_DES_CBC )
        {
            unsigned char cvec[8] = ""; //扭转向量
            unsigned char cvin[8] = ""; //中间变量
            
            for(long i=0,j=datalen>>3; i<j; ++i,Out+=8,In+=8)
            {
                if(Type == ENCRYPT)
                {
                    for(int k=0;k<8;++k)     //将输入与扭转变量异或
                    {
                        cvin[k] = In[k] ^ cvec[k];
                    }
                }
                else
                {
                    memcpy(cvin,In,8);
                }
                
                DES(Out,(char*)cvin,(const PSubKey)&SubKey[0],Type);
                DES(Out,Out,(const PSubKey)&SubKey[1],!Type);
                DES(Out,Out,(const PSubKey)&SubKey[0],Type);
                if(Type == ENCRYPT)
                {
                    memcpy(cvec,Out,8);         //将输出设定为扭转变量
                }
                else
                {
                    for(int k=0;k<8;++k)     //将输出与扭转变量异或
                    {
                        Out[k] = Out[k] ^ cvec[k];
                    }
                    memcpy(cvec,cvin,8);            //将输入设定为扭转变量
                }
            }
        }
	}
	return true;
}

void Des::SetKey(const char* Key, int len)
{
	memset(deskey, 0, 16);
	memcpy(deskey, Key, len>16?16:len);
	SetSubKey((PSubKey)&SubKey[0], (const char*)&deskey[0]);
	Is3DES = len>8 ? (SetSubKey((PSubKey)&SubKey[1],&deskey[8]), true) : false;
}

void Des::DES(char* Out, char* In, const PSubKey pSubKey, bool Type)
{
    bool M[64], tmp[32], *Li=&M[0], *Ri=&M[32];
    ByteToBit(M, In, 64);
    Transform(M, M, IP_Table, 64);
    if( Type == ENCRYPT )
    {
        for(int i=0; i<16; ++i)
        {
            memcpy(tmp, Ri, 32);
            F_func(Ri, (*pSubKey)[i]);
            Xor(Ri, Li, 32);
            memcpy(Li, tmp, 32);
        }
    }
    else
    {
        for(int i=15; i>=0; --i)
        {
            memcpy(tmp, Li, 32);
            F_func(Li, (*pSubKey)[i]);
            Xor(Li, Ri, 32);
            memcpy(Ri, tmp, 32);
        }
	}
    RotateL(M,64,32);
    Transform(M, M, IPR_Table, 64);
    BitToByte(Out, M, 64);
}

void Des::SetSubKey(PSubKey pSubKey, const char* Key)
{
    bool K[64], *KL=&K[0], *KR=&K[28];
    ByteToBit(K, Key, 64);
    Transform(K, K, PC1_Table, 56);
    for(int i=0; i<16; ++i) {
        RotateL(KL, 28, LOOP_Table[i]);
        RotateL(KR, 28, LOOP_Table[i]);
        Transform((*pSubKey)[i], K, PC2_Table, 48);
    }
}

void Des::ByteToBit(bool *Out, const char *In, int bits)
{
    for(int i=0; i<bits; ++i)
        Out[i] = (In[i>>3]>>(i&7)) & 1;
}

void Des::S_func(bool Out[32], const bool In[48])
{
    for(char i=0,j,k; i<8; ++i,In+=6,Out+=4) {
        j = (In[0]<<1) + In[5];
        k = (In[1]<<3) + (In[2]<<2) + (In[3]<<1) + In[4];
		ByteToBit(Out, &S_Box[i][j][k], 4);
    }
}
void Des::Transform(bool *Out, bool *In, const char *Table, int len)
{
    char Tmp[256];
	memset(Tmp, 0, sizeof(Tmp));
    for(int i=0; i<len; ++i)
        Tmp[i] = In[ Table[i]-1 ];
    memcpy(Out, Tmp, len);
}
void Des::Xor(bool *InA, const bool *InB, int len)
{
    for(int i=0; i<len; ++i)
        InA[i] ^= InB[i];
}
void Des::RotateL(bool *In, int len, int loop)
{
    char Tmp[256];
	memset(Tmp, 0, sizeof(Tmp));
    
    memcpy(Tmp, In, loop);
    memcpy(In, In+loop, len-loop);
    memcpy(In+len-loop, Tmp, loop);
}

void Des::BitToByte(char *Out, const bool *In, int bits)
{
    memset(Out, 0, bits>>3);
    for(int i=0; i<bits; ++i)
        Out[i>>3] |= In[i]<<(i&7);
}

void Des::F_func(bool In[32], const bool Ki[48])
{
    bool MR[48];
    Transform(MR, In, E_Table, 48);
    Xor(MR, Ki, 48);
    S_func(In, MR);
    Transform(In, In, P_Table, 32);
}

RC5::RC5()
{
    std::string commonKey = "com.haypi.crypto.19750309.rc5";
    init((unsigned char*)commonKey.c_str(), commonKey.length(), 24);
}

bool RC5::init(unsigned char * key, int keylen, int num_rounds)
{
    unsigned long L[64], S[50], A, B, i, j, v, s, t, l;
    
    /* test parameters */
    if (num_rounds == 0) num_rounds = 12;
    if (num_rounds < 12 || num_rounds > 24) 
    {
        
        return false;
    }
    
    if (keylen < 8 || keylen > 128)
    {
        return false;
    }
    
    /* copy the key into the L array */
    for (A = i = j = 0; i < keylen; )
    {
        A = (A << 8) | ((unsigned long)key[i++]);
        if (!(i & 3)) {
            L[j++] = BSWAP(A);
            A = 0;
        }
    }
    if (keylen & 3) { A <<= (8 * (3 - (keylen&3))); L[j++] = BSWAP(A); }
    
    /* setup the S array */
    t = 2 * (num_rounds + 1);
    S[0] = 0xB7E15163;
    for (i = 1; i < t; i++) S[i] = S[i - 1] + 0x9E3779B9;
    
    /* mix buffer */
    s = 3 * MAX(t, j);
    l = j;
    for (A = B = i = j = v = 0; v < s; v++) { 
        A = S[i] = ROL(S[i] + A + B, 3);
        B = L[j] = ROL(L[j] + A + B, (A+B));
        i = (i + 1) % t;
        j = (j + 1) % l;
    }
    
    /* copy to key */
    for (i = 0; i < t; i++) K[i] = S[i];
    rounds = num_rounds;
    
    memset(L, 0, sizeof(L));
    memset(S, 0, sizeof(S));
    A = B = 0;
    return true;
}

bool RC5::encrypt(unsigned char* input, int inputLen, unsigned char* output, int* outputLen)
{
    int length = ((inputLen+7)/8)*8;
    int seg_num = length/8;
    
    if ( output == NULL )
    {
        *outputLen = length;
        return true;
    }
    if ( *outputLen < length )
        return false;
    
    *outputLen = length;
    
    memset( output, 0, length * sizeof(char));
    
    unsigned char* pt = input;
    unsigned char* ct = output;
    for( int i = 0; i < seg_num; i ++, pt += 8, ct += 8 )
    {
        unsigned long A, B;
        int r;
        
        LOAD32L(A, &pt[0]);
        LOAD32L(B, &pt[4]);
        A += K[0];
        B += K[1];
        for (r = 0; r < rounds; r++) 
        {
            A = ROL(A ^ B, B) + K[r+r+2];
            B = ROL(B ^ A, A) + K[r+r+3];
        }
        STORE32L(A, &ct[0]);
        STORE32L(B, &ct[4]);
        A = B = 0;
    }

    return true;
}

bool RC5::decrypt(unsigned char* input, int inputLen, unsigned char* output, int* outputLen)
{
    int length = ((inputLen+7)/8)*8;
    int seg_num = length/8;
    
    if ( output == NULL )
    {
        *outputLen = length;
        return true;
    }
    if ( *outputLen < length )
        return false;
    
    *outputLen = length;
    
    memset( output, 0, length * sizeof(char));
    
    unsigned char* pt = output;
    unsigned char* ct = input;
    
    for( int i = 0; i < seg_num; i ++, pt += 8, ct += 8 )
    {
        unsigned long A, B;
        int r;
        
        LOAD32L(A, &ct[0]);
        LOAD32L(B, &ct[4]);
        for (r = rounds - 1; r >= 0; r--)
        {
            B = ROR(B - K[r+r+3], A) ^ A;
            A = ROR(A - K[r+r+2], B) ^ B;
        }
        A -= K[0];
        B -= K[1];
        STORE32L(A, &pt[0]);
        STORE32L(B, &pt[4]);
        A = B = 0;
    }
    return true;
}

RC6::RC6()
{
    std::string commonKey = "com.haypi.crypto.19750309.rc6";
    init((unsigned char*)commonKey.c_str(), commonKey.length(), 20);
}



bool RC6::init(unsigned char * key, int keylen, int num_rounds)
{
    unsigned long L[64], S[50], A, B, i, j, v, s, t, l;
    
    /* test parameters */
    if (num_rounds != 0 && num_rounds != 20)
    {
        return false;
    }
    
    if (keylen < 8 || keylen > 128)
    {
        return false;
    }
    
    /* copy the key into the L array */
    for (A = i = j = 0; i < keylen; )
    {
        A = (A << 8) | ((unsigned long)key[i++]);
        if (!(i & 3))
        {
            L[j++] = BSWAP(A);
            A = 0;
        }
    }
    
    if (keylen & 3)
    {
        A <<= (8 * (3 - (keylen&3)));
        L[j++] = BSWAP(A);
    }
    
    /* setup the S array */
    t = 44;				/* fixed at 20 rounds */
    S[0] = 0xB7E15163;
    for (i = 1; i < t; i++) S[i] = S[i - 1] + 0x9E3779B9;
    
    /* mix buffer */
    s = 3 * MAX(t, j);
    l = j;
    for (A = B = i = j = v = 0; v < s; v++)
    {
        A = S[i] = ROL(S[i] + A + B, 3);
        B = L[j] = ROL(L[j] + A + B, (A+B));
        i = (i + 1) % t;
        j = (j + 1) % l;
    }
    
    /* copy to key */
    for (i = 0; i < t; i++)
        K[i] = S[i];
    
    memset(L, 0, sizeof(L));
    memset(S, 0, sizeof(S));
    A = B = 0;
    return true;
}

bool RC6::encrypt(unsigned char* input, int inputLen, unsigned char* output, int* outputLen)
{
    int length = ((inputLen+15)/16)*16;
    int seg_num = length/16;
    
    if ( output == NULL )
    {
        *outputLen = length;
        return true;
    }
    if ( *outputLen < length )
        return false;
    
    *outputLen = length;
    
    memset( input, 0, length * sizeof(char));
    
    unsigned char* pt = input;
    unsigned char* ct = output;
    for( int i = 0; i < seg_num; i ++, pt += 16, ct += 16 )
    {
        unsigned long a,b,c,d,t,u;
        int r;
        
        LOAD32L(a,&pt[0]);LOAD32L(b,&pt[4]);LOAD32L(c,&pt[8]);LOAD32L(d,&pt[12]);
        b += K[0];
        d += K[1];
        for (r = 0; r < 20; r++) {
            t = (b * (b + b + 1)); t = ROL(t, 5);
            u = (d * (d + d + 1)); u = ROL(u, 5);
            a = ROL(a^t,u) + K[r+r+2];
            c = ROL(c^u,t) + K[r+r+3];
            t = a; a = b; b = c; c = d; d = t;
        }
        a += K[42];
        c += K[43];
        STORE32L(a,&ct[0]);STORE32L(b,&ct[4]);STORE32L(c,&ct[8]);STORE32L(d,&ct[12]);
        a = b = c = d = t = 0;
    }

    return true;
}

bool RC6::decrypt(unsigned char* input, int inputLen, unsigned char* output, int* outputLen)
{
    int length = ((inputLen+15)/16)*16;
    int seg_num = length/16;
    if ( output == NULL )
    {
        *outputLen = length;
        return true;
    }
    if ( *outputLen < length )
        return false;
    
    *outputLen = length;
    
    memset( output, 0, length * sizeof(char));
    
    unsigned char* pt = output;
    unsigned char* ct = input;
    for( int i = 0; i < seg_num; i ++, pt += 16, ct += 16 )
    {
        unsigned long a,b,c,d,t,u;
        int r;
        
        LOAD32L(a,&ct[0]);LOAD32L(b,&ct[4]);LOAD32L(c,&ct[8]);LOAD32L(d,&ct[12]);
        a -= K[42];
        c -= K[43];
        for (r = 19; r >= 0; r--) {
            t = d; d = c; c = b; b = a; a = t;
            t = (b * (b + b + 1)); t = ROL(t, 5);
            u = (d * (d + d + 1)); u = ROL(u, 5);
            c = ROR(c - K[r+r+3], t) ^ u;
            a = ROR(a - K[r+r+2], u) ^ t;
        }
        b -= K[0];
        d -= K[1];
        STORE32L(a,&pt[0]);STORE32L(b,&pt[4]);STORE32L(c,&pt[8]);STORE32L(d,&pt[12]);   
    }

    return true;
}

bool Base64::encrypt(unsigned char* input, int inputLen, unsigned char* output, int* outputLen)
{
    
    int length = (inputLen*4/3)+1;
    if ( output == NULL )
    {
        *outputLen = length;
        return true;
    }
    if ( *outputLen < length )
        return false;
    
    *outputLen = length;
    
    memset( output, 0, length * sizeof(char));
    
#ifdef HOS_APPLE
    *outputLen = base64_encode_(output, input, inputLen);
    output[*outputLen] = 0;
#else
    *outputLen = haypi::encodeBase64(output, input, inputLen);
    output[*outputLen] = 0;
#endif
    return true;
}

bool Base64::decrypt(unsigned char* input, int inputLen, unsigned char* output, int* outputLen)
{
    
    int length = (inputLen*3/4)+1;
    if ( output == NULL )
    {
        *outputLen = length;
        return true;
    }
    if ( *outputLen < length )
        return false;
    
    *outputLen = length;
    
    memset( output, 0, length * sizeof(char));

#ifdef HOS_APPLE
    *outputLen = base64_decode_(output, input, inputLen);
    output[*outputLen] = 0;
#else
    *outputLen = haypi::decodeBase64(output, input, inputLen);
    output[*outputLen] = 0;
#endif
    return true;
}

Des_ECB::Des_ECB()
{
    const char iv_[8] = {2,0,0,2,0,5,2,3};
    const char key_[8] = {1,9,7,5,0,3,0,9};
    memcpy(iv, iv_, 8);
    memcpy(key, key_, 8);
}

bool Des_ECB::init(unsigned char* key_, int keylen, int num_rounds)
{
    memset(key, 0, 8);
	memcpy(key, key_, MIN(8, keylen));
    return true;
}

bool Des_ECB::encrypt(unsigned char* input, int inputLen, unsigned char* output, int* outputLen)
{
    int len = (inputLen + 7) / 8 * 8;
    if ( output == NULL )
    {
        *outputLen = len;
        return true;
    }
    if ( *outputLen < len )
        return false;
    
    *outputLen = len;
#ifdef HOS_APPLE
    CCCryptorStatus cryptStatus = CCCrypt(kCCEncrypt, kCCAlgorithmDES,
                                          kCCOptionECBMode,
                                          (const void *)key, 8,
                                          (const void *)iv,
                                          (const void *)input, inputLen,
                                          (void *)output, (size_t)*outputLen,
                                          (size_t*)outputLen);
    if (cryptStatus == kCCSuccess)
    {
        return true;
    }
#else
#endif
    return false;
}

bool Des_ECB::decrypt(unsigned char* input, int inputLen, unsigned char* output, int* outputLen)
{
    int len = inputLen;
    if ( output == NULL )
    {
        *outputLen = len;
        return true;
    }
    if ( *outputLen < len )
        return false;
    
    *outputLen = len;
#ifdef HOS_APPLE    
    CCCryptorStatus cryptStatus = CCCrypt(kCCDecrypt, kCCAlgorithmDES,
                                          kCCOptionECBMode,
                                          (const void *)key, 8,
                                          (const void *)iv,
                                          (const void *)input, inputLen,
                                          (void *)output, (size_t)*outputLen,
                                          (size_t*)outputLen);
    if (cryptStatus == kCCSuccess)
    {
        return true;
    }
#else
#endif
    return false;
}

CryptFunctions* CryptFunctions::createCrypt(CRYPT_METHOD method)
{
    CryptFunctions* func = NULL;
    switch (method)
    {
        case CryptFunctions::CM_DES:
        case CryptFunctions::CM_DES_SBOX:
            func = new Des_SBOX();
            break;
        case CryptFunctions::CM_DES_CBC:
            func = new Des_CBC();
            break;
        case CryptFunctions::CM_DES_ECB:
            func = new Des_ECB();
            break;
        case CryptFunctions::CM_RC5:
            func = new RC5();
            break;
        case CryptFunctions::CM_RC6:
            func = new RC6();
            break;
        case CryptFunctions::CM_Base64:
            func = new Base64();
            break;
        default:
            break;
    }
    return func;
}


#include "cocos2dxframework.h"
#include "Base.h"
#include "json/json.h"
#include "support/zip_support/unzip.h"

#ifdef HOS_WIN32
#include <direct.h>
#include <io.h>
#define PATH_SPLIT  '\\'
#define ACCESS _access
#define MKDIR(a) _mkdir((a))
#else
#include <stdarg.h>
#include <sys/stat.h>
#define PATH_SPLIT  '/'
#define ACCESS access
#define MKDIR(a) mkdir((a),0755)
#endif

HNAMESPACE_BEGIN

int createDir(const char *path) {
    int iRet = ACCESS(path, 0);
    if (0 != iRet) {
        iRet = MKDIR(path);
        if (0 != iRet) return -1;
    }
    return 0;
}

static int createDirInRecursive(char *path, int headLen = 0) {
    int iLen = strlen(path);
//    if ((path[iLen - 1] != '/') && (path[iLen - 1] != '\\')) {
//        path[iLen] = PATH_SPLIT;
//        path[++iLen] = '\0';
//    }
    for (int i = headLen; i < iLen; i++) {
        if ((path[i] == '/') || (path[i] == '\\')) {
            path[i] = '\0';
            int iRet = createDir(path);
            if (0 != iRet) return -1;
            path[i] = PATH_SPLIT;
        }
    }
    return 0;
}

//common
//static long gRandomSeed = 0;
void setRandomSeed(long seed) {
    //    gRandomSeed = seed;
    srandom(seed);
}

long getRandom() {
    //    gRandomSeed = random();
    //    srandom(gRandomSeed);
    //    return gRandomSeed;
    return random();
}

bool stringEndsWith(const char *filename, const char *ends) {
    int filenameLen = strlen(filename);
    int endsLen = strlen(ends);
    if (filenameLen >= endsLen) {
        return 0 == strcmp(filename + filenameLen - endsLen, ends);
    }
    return false;
}

//base 64
// an implementation of base64 encoding & decoding
static const char base64_tbl[64] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'
};
static __inline void base64_encode_unit(void * dst, const void * src) {
	unsigned long data = (((unsigned char *)src)[0] << 16) | (((unsigned char *)src)[1] << 8) | ((unsigned char *)src)[2];
	((unsigned char *)dst)[3] = base64_tbl[(data & 0x3f)]; data >>= 6;
	((unsigned char *)dst)[2] = base64_tbl[(data & 0x3f)]; data >>= 6;
	((unsigned char *)dst)[1] = base64_tbl[(data & 0x3f)]; data >>= 6;
	((unsigned char *)dst)[0] = base64_tbl[(data & 0x3f)];
}
static __inline void base64_encode_part(void * dst, const void * src, size_t len) {
	unsigned long data = (((unsigned char *)src)[0] << 10);
	if (len == 2)
		data |= (((unsigned char *)src)[1] << 2);
	((unsigned char *)dst)[3] = '=';
	((unsigned char *)dst)[2] = len == 1 ? '=' : base64_tbl[(data & 0x3f)]; data >>= 6;
	((unsigned char *)dst)[1] = base64_tbl[(data & 0x3f)]; data >>= 6;
	((unsigned char *)dst)[0] = base64_tbl[(data & 0x3f)];
}

int encodeBase64(void *result, const void *data, int len) {
    if(!result || !data || len <= 0) return -1;
	
	unsigned long trip = len / 3;
	unsigned long rem = len % 3;
	unsigned char * pd = (unsigned char *)result;
	const unsigned char * ps = (const unsigned char *)data;
	
	while(trip-- > 0) {
		base64_encode_unit(pd, ps);
		pd += 4;
		ps += 3;
	}
	if(rem) {
		base64_encode_part(pd, ps, rem);
		pd += 4;
	}
	return pd - (unsigned char *)result;
}

static const char b64_tab[256] = {
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*000-007*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*010-017*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*020-027*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*030-037*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*040-047*/
    '\177', '\177', '\177', '\76',  '\177', '\177', '\177', '\77',  /*050-057*/
    '\64',  '\65',  '\66',  '\67',  '\70',  '\71',  '\72',  '\73',  /*060-067*/
    '\74',  '\75',  '\177', '\177', '\177', '\100', '\177', '\177', /*070-077*/
    '\177', '\0',   '\1',   '\2',   '\3',   '\4',   '\5',   '\6',   /*100-107*/
    '\7',   '\10',  '\11',  '\12',  '\13',  '\14',  '\15',  '\16',  /*110-117*/
    '\17',  '\20',  '\21',  '\22',  '\23',  '\24',  '\25',  '\26',  /*120-127*/
    '\27',  '\30',  '\31',  '\177', '\177', '\177', '\177', '\177', /*130-137*/
    '\177', '\32',  '\33',  '\34',  '\35',  '\36',  '\37',  '\40',  /*140-147*/
    '\41',  '\42',  '\43',  '\44',  '\45',  '\46',  '\47',  '\50',  /*150-157*/
    '\51',  '\52',  '\53',  '\54',  '\55',  '\56',  '\57',  '\60',  /*160-167*/
    '\61',  '\62',  '\63',  '\177', '\177', '\177', '\177', '\177', /*170-177*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*200-207*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*210-217*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*220-227*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*230-237*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*240-247*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*250-257*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*260-267*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*270-277*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*300-307*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*310-317*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*320-327*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*330-337*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*340-347*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*350-357*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*360-367*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*370-377*/
};

static __inline int convert(unsigned char * pd, const unsigned char * ps) {
	unsigned int data = 0;
	unsigned int d;
	int equ = 0;
	
	d = b64_tab[ps[0]];
	if(d & '\100') return -1; data <<= 6; data |= d;
	
	d = b64_tab[ps[1]];
	if(d & '\100') return -1; data <<= 6; data |= d;
	
	d = b64_tab[ps[2]];
	if(d & '\100') {
		if(ps[2] == '=') {
			data <<= 6;
			equ++;
		} else return -1;
	} else data <<= 6; data |= d;
	
	d = b64_tab[ps[3]];
	if(d & '\100') {
		if(ps[3] == '=') {
			data <<= 6;
			equ++;
		} else return -1;
	} else {
		if(equ) 	return -1;
		data <<= 6; data |= d;
	}
	
	pd[0] = data >> 16;
	if(equ < 2) pd[1] = (data >> 8) & 0xff;
	if(equ < 1) pd[2] = (data) & 0xff;
	
	return 3 - equ;
}

int decodeBase64(void *result, const void *data, int len) {
    const unsigned char * ps = (const unsigned char *)data;
	unsigned char * pd = (unsigned char *)result;
	int err;
	
	if(len % 4 != 0) return -1;
	
	while(len > 0) {
		err = convert(pd, ps);
		if(err < 0) return err;
		
		ps += 4;
		pd += err;
		len -= 4;
	}
	return pd - (unsigned char *)result;
}

//md5
typedef unsigned char * POINTER;

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

static unsigned char PADDING[64] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* F, G, H and I are basic MD5 functions.
 */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits.
 */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
 Rotation is separate from addition to prevent recomputation.
 */
#define FF(a, b, c, d, x, s, ac) { \
(a) += F ((b), (c), (d)) + (x) + (UINT4)(ac); \
(a) = ROTATE_LEFT ((a), (s)); \
(a) += (b); \
}
#define GG(a, b, c, d, x, s, ac) { \
(a) += G ((b), (c), (d)) + (x) + (UINT4)(ac); \
(a) = ROTATE_LEFT ((a), (s)); \
(a) += (b); \
}
#define HH(a, b, c, d, x, s, ac) { \
(a) += H ((b), (c), (d)) + (x) + (UINT4)(ac); \
(a) = ROTATE_LEFT ((a), (s)); \
(a) += (b); \
}
#define II(a, b, c, d, x, s, ac) { \
(a) += I ((b), (c), (d)) + (x) + (UINT4)(ac); \
(a) = ROTATE_LEFT ((a), (s)); \
(a) += (b); \
}

/* Note: Replace "for loop" with standard memset if possible.
 */
static void MD5_memset (POINTER output, int value, unsigned int len) {
    for (int i = 0; i < len; i++) ((char *)output)[i] = (char)value;
}

/* Decodes input (unsigned char) into output (UINT4). Assumes len is
 a multiple of 4.
 */
static void Decode (UINT4 *output, unsigned char *input, unsigned int len) {
    for (int i = 0, j = 0; j < len; i++, j += 4)
        output[i] = ((UINT4)input[j]) | (((UINT4)input[j+1]) << 8) | (((UINT4)input[j+2]) << 16) | (((UINT4)input[j+3]) << 24);
}

/* MD5 basic transformation. Transforms state based on block.
 */
static void MD5Transform (UINT4 state[4], unsigned char block[64]) {
    UINT4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];
    
    Decode (x, block, 64);
    
    /* Round 1 */
    FF (a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
    FF (d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
    FF (c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
    FF (b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
    FF (a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
    FF (d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
    FF (c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
    FF (b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
    FF (a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
    FF (d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
    FF (c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
    FF (b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
    FF (a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
    FF (d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
    FF (c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
    FF (b, c, d, a, x[15], S14, 0x49b40821); /* 16 */
    
    /* Round 2 */
    GG (a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
    GG (d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
    GG (c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
    GG (b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
    GG (a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
    GG (d, a, b, c, x[10], S22,  0x2441453); /* 22 */
    GG (c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
    GG (b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
    GG (a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
    GG (d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
    GG (c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
    GG (b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
    GG (a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
    GG (d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
    GG (c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
    GG (b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */
    
    /* Round 3 */
    HH (a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
    HH (d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
    HH (c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
    HH (b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
    HH (a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
    HH (d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
    HH (c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
    HH (b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
    HH (a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
    HH (d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
    HH (c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
    HH (b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
    HH (a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
    HH (d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
    HH (c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
    HH (b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */
    
    /* Round 4 */
    II (a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
    II (d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
    II (c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
    II (b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
    II (a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
    II (d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
    II (c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
    II (b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
    II (a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
    II (d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
    II (c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
    II (b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
    II (a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
    II (d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
    II (c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
    II (b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */
    
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    
    /* Zeroize sensitive information.
     */
    MD5_memset ((POINTER)x, 0, sizeof (x));
}

/* Encodes input (UINT4) into output (unsigned char). Assumes len is
 a multiple of 4.
 */
static void Encode (unsigned char *output, UINT4 *input, unsigned int len) {
    for (int i = 0, j = 0; j < len; i++, j += 4) {
        output[j] = (unsigned char)(input[i] & 0xff);
        output[j+1] = (unsigned char)((input[i] >> 8) & 0xff);
        output[j+2] = (unsigned char)((input[i] >> 16) & 0xff);
        output[j+3] = (unsigned char)((input[i] >> 24) & 0xff);
    }
}

/* Note: Replace "for loop" with standard memcpy if possible.
 */

static void MD5_memcpy (POINTER output, POINTER input, unsigned int len) {
    for (int i = 0; i < len; i++) output[i] = input[i];
}

/* MD5 initialization. Begins an MD5 operation, writing a new context.
 */
void MD5Init (MD5_CTX *context) {
    context->count[0] = context->count[1] = 0;
    //Load magic initialization constants.
    context->state[0] = 0x67452301;
    context->state[1] = 0xefcdab89;
    context->state[2] = 0x98badcfe;
    context->state[3] = 0x10325476;
}

/* MD5 block update operation. Continues an MD5 message-digest
 operation, processing another message block, and updating the
 context.
 */
void MD5Update (MD5_CTX *context, unsigned char *input, unsigned int inputLen) {
    unsigned int i, index, partLen;
    
    /* Compute number of bytes mod 64 */
    index = (unsigned int)((context->count[0] >> 3) & 0x3F);
    
    /* Update number of bits */
    if ((context->count[0] += ((UINT4)inputLen << 3))
        < ((UINT4)inputLen << 3))
        context->count[1]++;
    context->count[1] += ((UINT4)inputLen >> 29);
    
    partLen = 64 - index;
    
    /* Transform as many times as possible.
     */
    if (inputLen >= partLen) {
        MD5_memcpy((POINTER)&context->buffer[index], (POINTER)input, partLen);
        MD5Transform (context->state, context->buffer);
        
        for (i = partLen; i + 63 < inputLen; i += 64)
            MD5Transform (context->state, &input[i]);
        
        index = 0;
    }
    else
        i = 0;
    
    /* Buffer remaining input */
    MD5_memcpy((POINTER)&context->buffer[index], (POINTER)&input[i],inputLen-i);
}

/* MD5 finalization. Ends an MD5 message-digest operation, writing the
 the message digest and zeroizing the context.
 */
void MD5Final (unsigned char digest[16], MD5_CTX *context) {
    unsigned char bits[8];
    unsigned int index, padLen;
    
    /* Save number of bits */
    Encode (bits, context->count, 8);
    
    /* Pad out to 56 mod 64.
     */
    index = (unsigned int)((context->count[0] >> 3) & 0x3f);
    padLen = (index < 56) ? (56 - index) : (120 - index);
    MD5Update (context, PADDING, padLen);
    
    /* Append length (before padding) */
    MD5Update (context, bits, 8);
    
    /* Store state in digest */
    Encode (digest, context->state, 16);
    
    /* Zeroize sensitive information.
     */
    MD5_memset ((POINTER)context, 0, sizeof (*context));
}

void MD5Data(const void *data, int len, unsigned char digest[16]) {
    MD5_CTX context;
    MD5Init (&context);
    MD5Update (&context, (unsigned char *)data, len);
    MD5Final (digest, &context);
}

void convertPVR2PNG(const char *pvr, const char *png) {
//    CCImage *image = new CCImage;
//    CCTexturePVR *texPVR = new CCTexturePVR;
//    texPVR->initWithContentsOfFile(pvr, image);
//    image->saveToFile(png, false);
//    delete image;
}

//zip
int zip(unsigned char *data, int len, unsigned char *result, int size) {
    z_stream stream;
    stream.opaque = 0;
    stream.zalloc = 0;
    stream.zfree = 0;
    int ret = deflateInit(&stream, Z_BEST_COMPRESSION);
    if (ret != Z_OK) return -1;
    stream.avail_in = len;
    stream.next_in = data;
    stream.avail_out = size;
    stream.next_out = result;
    ret = deflate(&stream, Z_SYNC_FLUSH);
    if ((ret != Z_OK) && (ret != Z_STREAM_END)) return -1;
    ret = stream.total_out;
    deflateEnd(&stream);
    return ret;
}

int unzip(unsigned char *data, int len, unsigned char *result, int size) {
    z_stream stream;
    stream.opaque = 0;
    stream.zalloc = 0;
    stream.zfree = 0;
    int ret = inflateInit(&stream);
    if (ret != Z_OK) return -1;
    stream.avail_in = len;
    stream.next_in = data;
    stream.avail_out = size;
    stream.next_out = result;
    ret = inflate(&stream, Z_SYNC_FLUSH);
    if ((ret != Z_OK) && (ret != Z_STREAM_END)) return -1;
    ret = stream.total_out;
    inflateEnd(&stream);
    return ret;
}

void unzipFile(const char *zipFile, const char *dir, const char *resultPath, CCArray *excludeList, CCArray *includeList, FuncOnPercent onPercent, bool pvr2Png) {
    if (!zipFile || !resultPath) return;
    if (strlen(zipFile) == 0) return;
    
    unzFile pFile = unzOpen(zipFile);
    if (!pFile) return;
    
    unz_global_info pglobal_info;
    unzGetGlobalInfo(pFile, &pglobal_info);
    float totalCount = (float)pglobal_info.number_entry;
    
    int dirLen = strlen(dir);
    
    char path[260];
    strcpy(path, resultPath);
    createDirInRecursive(path, 1);
    int headLen = strlen(path);
    
    unsigned char * pBuffer = NULL;
    int bufSize = 0;
    
    int step = pglobal_info.number_entry / 100;
    int stepAdder = 0;
    int index = 0;
    if (onPercent) onPercent(index / totalCount);
    int nRet = unzGoToFirstFile(pFile);
    while (UNZ_OK == nRet) {
        char filename[260];
        unz_file_info FileInfo;
        nRet = unzGetCurrentFileInfo(pFile, &FileInfo, filename, sizeof(filename), NULL, 0, NULL, 0);
        if( UNZ_OK == nRet) {
            bool needUnzip = true;
            if (excludeList) {
                for (int i = excludeList->count() - 1; i >= 0; --i) {
                    CCString *str = (CCString *)excludeList->objectAtIndex(i);
                    if (strcasestr(filename, str->getCString())) {
                        needUnzip = false;
                        break;
                    }
                }
            }
            if (includeList) {
                for (int i = includeList->count() - 1; i >= 0; --i) {
                    CCString *str = (CCString *)includeList->objectAtIndex(i);
                    if (strcasestr(filename, str->getCString())) {
                        needUnzip = true;
                        break;
                    }
                }
            }
            if (needUnzip) {
                nRet = unzOpenCurrentFile(pFile);
                if (UNZ_OK == nRet) {
                    if (bufSize < FileInfo.uncompressed_size) {
                        bufSize = FileInfo.uncompressed_size;
                        if (pBuffer) delete [] pBuffer;
                        pBuffer = new unsigned char[bufSize];
                    }
                    int nSize = unzReadCurrentFile(pFile, pBuffer, FileInfo.uncompressed_size);
                    CCAssert(nSize == 0 || nSize == (int)FileInfo.uncompressed_size, "the file size is wrong");
                    
                    bool isOK = true;
                    if (dirLen > 0) {
                        if (0 != memcmp(filename, dir, dirLen)) isOK = false;
                        else strcpy(path + headLen, filename + dirLen);
                    } else {
                        strcpy(path + headLen, filename);
                    }
                    if (isOK) {
                        createDirInRecursive(path, headLen);
                        FILE *file = fopen(path, "wb");
                        if (file) {
                            fwrite(pBuffer, 1, nSize, file);
                            fclose(file);
                            if (pvr2Png) {
                                char *pos = strstr(path, ".pvr");
                                if (pos) {
                                    char p[260];
                                    strcpy(p, path);
                                    strcpy(pos, ".png");
                                    convertPVR2PNG(p, path);
                                    // delete by zg
//                                    HFileUtils::deleteFile(p);
                                }
                            }
                            HLOGI("unzip to:%s", path);
                        }
                    }
                    unzCloseCurrentFile(pFile);
                }
            }
        }
        
        nRet = unzGoToNextFile(pFile);
        
        ++index;
        if (onPercent) {
            ++stepAdder;
            if (stepAdder >= step) {
                onPercent(index / totalCount);
                stepAdder = 0;
            }
        }
    }
    
    unzClose(pFile);
    
    if (pBuffer) delete [] pBuffer;
}

bool pathExists(const char *path) {
    return 0 == ACCESS(path, 0);
}

//dictionary
class CC_DLL HDictionaryGenerator: public CCObject, public CCSAXDelegator {
    CC_SYNTHESIZE_READONLY(CCDictionary *, m_pDictResult, DictionayResult);
    CC_SYNTHESIZE(bool, m_bStoringCharacters, StoringCharacters);
public:
    HDictionaryGenerator();
    virtual ~HDictionaryGenerator();
    
    static CCDictionary *dictionaryFromPlist(const char *data, unsigned int size);
    static CCDictionary *dictionaryFromPlist(const char *filename);
    static CCDictionary *dictionaryFromJSON(const char *data, unsigned int size);
    static CCDictionary *dictionaryFromJSON(const char *filename);
    static std::string dictionaryToJSON(CCDictionary *dict);
    
    void startElement(void *ctx, const char *name, const char **atts);
    void endElement(void *ctx, const char *name);
    void textHandler(void *ctx, const char *ch, int len);
  
protected:
    void traverseJsonValue(const std::string &name, Json::Value &value, void *data, bool isDict);
    
private:
    bool parseFromPlist(const char *data, unsigned int size);
    bool parseFromJSON(const char *data, unsigned int size);
    
    static bool parseToJSON(Json::Value &value, void *data, bool isDict);
    
    std::string m_strCurrentTag;
    
    std::string m_strCurrentKey;
    CCArray *m_pDictStack;
    //    CCDictionary* m_pCurrentArray;
    
    std::string m_strCurrentString;
    inline const char* getCurrentString(){ return m_strCurrentString.c_str(); }
    inline void setCurrentString(const char *currentString){ m_strCurrentString = currentString; }
};

HDictionaryGenerator::HDictionaryGenerator(): CCObject(),  m_pDictStack(NULL) {
    
}

HDictionaryGenerator::~HDictionaryGenerator() {
    
}

CCDictionary *HDictionaryGenerator::dictionaryFromPlist(const char *data, unsigned int size) {
    if (size < 1) size = strlen(data);
    HDictionaryGenerator generator;
    if (!generator.parseFromPlist(data, size)) return NULL;
    return generator.getDictionayResult();
}

CCDictionary *HDictionaryGenerator::dictionaryFromPlist(const char *filename) {
    
    return CCDictionary::createWithContentsOfFileThreadSafe(filename);
    
    // delete by zg
//    filename = HFileUtils::getInstance()->getResourceName(filename);
//    if (HFileUtils::fileInApp(filename)) return CCDictionary::createWithContentsOfFileThreadSafe(filename);
//    
//    unsigned long size = 0;
//    unsigned char *data = CCFileUtils::sharedFileUtils()->getFileData(filename, "rb", &size);
//    if (data && size > 0) {
//        CCDictionary *pRet = HDictionaryGenerator::dictionaryFromPlist((char *)data, size);
//        delete [] data;
//        return pRet;
//    }
//    return NULL;
}

CCDictionary *HDictionaryGenerator::dictionaryFromJSON(const char *data, unsigned int size) {
    if (size < 1) size = strlen(data);
    HDictionaryGenerator generator;
    if (!generator.parseFromJSON(data, size)) return NULL;
    return generator.getDictionayResult();
}

CCDictionary *HDictionaryGenerator::dictionaryFromJSON(const char *filename) {
    unsigned long size = 0;
    unsigned char *data = CCFileUtils::sharedFileUtils()->getFileData(filename, "rb", &size);
    if (data && size > 0) {
        CCDictionary *pRet = HDictionaryGenerator::dictionaryFromJSON((char *)data, size);
        delete [] data;
        return pRet;
    }
    return NULL;
}

bool HDictionaryGenerator::parseToJSON(Json::Value &value, void *data, bool isDict) {
    if (isDict) {
        CCDictionary *dict = (CCDictionary *)data;
        CCArray *keys = dict->allKeys();
        int count = dict->count();
        if (count < 1) return false;
        bool keyIsString = dynamic_cast<CCString *>(keys->objectAtIndex(0)) != NULL;
        for (int i = 0; i < count; ++i) {
            CCString *key = keyIsString ? (CCString *)keys->objectAtIndex(i) : HString::createWithInteger(((CCInteger *)keys->objectAtIndex(i))->getValue());
			if(!key) continue;
            CCObject *content = keyIsString ? (CCObject *)dict->objectForKey(key->m_sString) : (CCObject *)dict->objectForKey(((CCInteger *)keys->objectAtIndex(i))->getValue());
            if (dynamic_cast<CCDictionary *>(content)) {
                Json::Value obj(Json::objectValue);
                parseToJSON(obj, content, true);
                value[key->m_sString] = obj;
            } else if (dynamic_cast<CCArray *>(content)) {
                Json::Value obj(Json::arrayValue);
                parseToJSON(obj, content, false);
                value[key->m_sString] = obj;
            } else if (dynamic_cast<HString *>(content)) {
                HString *str = (HString *)content;
                switch (str->getValueType()) {
                    case HSVT_BOOLEAN:
                        value[key->m_sString] = str->boolValue();
                        break;
                    case HSVT_INTEGER:
                        value[key->m_sString] = str->intValue();
                        break;
                    case HSVT_UINTEGER:
                        value[key->m_sString] = str->uintValue();
                        break;
                    case HSVT_FLOAT:
                        value[key->m_sString] = str->floatValue();
                        break;
                    case HSVT_DOUBLE:
                        value[key->m_sString] = str->doubleValue();
                        break;
                    default:
                        value[key->m_sString] = str->m_sString;
                        break;
                }
            }
        }
    } else {
        CCArray *array = (CCArray *)data;
        int count = array->count();
        if (count < 1) return false;
        int index = 0;
        for (int i = 0; i < count; ++i) {
            CCObject *content = (CCObject *)array->objectAtIndex(i);
            if (dynamic_cast<CCDictionary *>(content)) {
                Json::Value obj(Json::objectValue);
                parseToJSON(obj, content, true);
                value[index++] = obj;
            } else if (dynamic_cast<CCArray *>(content)) {
                Json::Value obj(Json::arrayValue);
                parseToJSON(obj, content, false);
                value[index++] = obj;
            } else if (dynamic_cast<HString *>(content)) {
                HString *str = (HString *)content;
                switch (str->getValueType()) {
                    case HSVT_BOOLEAN:
                        value[index++] = str->boolValue();
                        break;
                    case HSVT_INTEGER:
                        value[index++] = str->intValue();
                        break;
                    case HSVT_UINTEGER:
                        value[index++] = str->uintValue();
                        break;
                    case HSVT_FLOAT:
                        value[index++] = str->floatValue();
                        break;
                    case HSVT_DOUBLE:
                        value[index++] = str->doubleValue();
                        break;
                    default:
                        value[index++] = str->m_sString;
                        break;
                }
            }
        }
    }
    return true;
}

std::string HDictionaryGenerator::dictionaryToJSON(CCDictionary *dict) {
    Json::Value root(Json::objectValue);
    if (!parseToJSON(root, dict, true)) return "";
    return root.toStyledString();
}

void HDictionaryGenerator::startElement(void *ctx, const char *name, const char **atts) {
    m_strCurrentTag = name;
    //    HLOGI("start:%s", m_strCurrentTag.c_str());
    //    std::map<std::string, std::string> *attributeDict = new std::map<std::string, std::string>();
    //    if (atts && atts[0]) {
    //        for(int i = 0; atts[i]; i += 2) {
    //            std::string key = (char*)atts[i];
    //            std::string value = (char*)atts[i+1];
    //            attributeDict->insert(std::pair<std::string, std::string>(key, value));
    //        }
    //    }
    
    if (m_strCurrentTag == "dict") {
        if (m_strCurrentKey != "") {
            CCDictionary *dict = CCDictionary::create();
            CCObject *lastObject = (CCObject *)m_pDictStack->lastObject();
            if (dynamic_cast<CCDictionary *>(lastObject)) {
                ((CCDictionary *)lastObject)->setObject(dict, m_strCurrentKey);
            } else {
                ((CCArray *)lastObject)->addObject(dict);
            }
            m_pDictStack->addObject(dict);
        }
    } else if (m_strCurrentTag == "array") {
        if (m_strCurrentKey != "") {
            CCArray *array = CCArray::create();
            CCObject *lastObject = (CCObject *)m_pDictStack->lastObject();
            if (dynamic_cast<CCDictionary *>(lastObject)) {
                ((CCDictionary *)lastObject)->setObject(array, m_strCurrentKey);
            } else {
                ((CCArray *)lastObject)->addObject(array);
            }
            m_pDictStack->addObject(array);
        }
    } else {
        if (m_strCurrentTag != "plist") {
            setStoringCharacters(true);
        }
    }
}

void HDictionaryGenerator::endElement(void *ctx, const char *name) {
    std::string elementName = name;
    
    if ((elementName == "dict") || (elementName == "array")) {
        m_pDictStack->removeLastObject();
    } else if (elementName == "key") {
        m_strCurrentKey = m_strCurrentString;
    } else if (elementName != "plist") {
        if (m_strCurrentKey != "") {
            HString *obj = HString::create(m_strCurrentString);
            CCObject *lastObject = (CCObject *)m_pDictStack->lastObject();
            if (dynamic_cast<CCDictionary *>(lastObject)) {
                ((CCDictionary *)lastObject)->setObject(obj, m_strCurrentKey);
            } else {
                ((CCArray *)lastObject)->addObject(obj);
            }
            if (elementName == "integer") {
                obj->setValueType(HSVT_INTEGER);
            } else if (elementName == "true") {
                obj->setValueType(HSVT_BOOLEAN);
            } else if (elementName == "false") {
                obj->setValueType(HSVT_BOOLEAN);
            }
        }
    }
    
    setCurrentString("");
    setStoringCharacters(false);
}

void HDictionaryGenerator::textHandler(void *ctx, const char *ch, int len) {
    if (getStoringCharacters()) {
        m_strCurrentString = std::string((char*)ch, 0, len);
    }
}

//private
bool HDictionaryGenerator::parseFromPlist(const char *data, unsigned int size) {
    m_pDictResult = NULL;
    
    CCSAXParser parser;
    if (false == parser.init("UTF-8")) {
        return false;
    }
    parser.setDelegator(this);
    
    m_pDictResult = CCDictionary::create();
    m_pDictStack = CCArray::createWithCapacity(4);
    m_pDictStack->addObject(m_pDictResult);
    
    m_strCurrentString = "";
    m_bStoringCharacters = false;
    
    //    m_pDictFrames = CCDictionary::create();
    //    m_pDictMetadata = CCDictionary::create();
    //    m_pDictResult->setObject(m_pDictFrames, "frames");
    //    m_pDictResult->setObject(m_pDictMetadata, "metadata");
    
    return parser.parse(data, size);
}

//#define HPRINT_JSON_PROGRESS
bool HDictionaryGenerator::parseFromJSON(const char *data, unsigned int size) {
#ifdef HPRINT_JSON_PROGRESS
    HLOGI("---parseFromJSON: size(%d)", size);
#endif
    m_pDictResult = NULL;
    Json::Reader reader;
    Json::Value value;
    
    std::string pText((char*)data, 0, size);
    if (reader.parse(pText, value)) {
        if  (value.type() == Json::objectValue) {
            m_pDictResult = CCDictionary::create();
            //            m_pDictStack = CCArray::createWithCapacity(16);
            //            m_pDictStack->addObject(m_pDictResult);
            
            //            traverseJsonValue("", value, m_pDictResult, true);
            Json::Value::Members members(value.getMemberNames());
            for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it) {
                const std::string &name = *it;
                traverseJsonValue(name, value[name], m_pDictResult, true);
            }
        }
    }
#ifdef HPRINT_JSON_PROGRESS
    HLOGI("---parseFromJSON: end");
#endif
    return true;
}

void HDictionaryGenerator::traverseJsonValue(const std::string &name, Json::Value &value, void *data, bool isDict) {
#ifdef HPRINT_JSON_PROGRESS
    HLOGI("JSON: key(%s) --parent(%s)- data(0x%x)", name.c_str(), isDict ? "dict" : "array", data);
#endif
    switch (value.type()) {
        case Json::objectValue: {
#ifdef HPRINT_JSON_PROGRESS
            HLOGI("JSON: object...");
#endif
            CCDictionary *dict = CCDictionary::create();
            if (isDict) {
                CCDictionary *lastDict = (CCDictionary *)data;
#ifdef HPRINT_JSON_PROGRESS
                HLOGI("JSON: parent dict count(%d)..retain count(%d).", lastDict->count(), lastDict->retainCount());
#endif
                lastDict->setObject(dict, name);
            } else {
                CCArray *lastArray = (CCArray *)data;
#ifdef HPRINT_JSON_PROGRESS
                HLOGI("JSON: parent array count(%d)..retain count(%d).", lastArray->count(), lastArray->retainCount());
#endif
                lastArray->addObject(dict);
            }
            
            Json::Value::Members members(value.getMemberNames());
#ifdef HPRINT_JSON_PROGRESS
            HLOGI("JSON: traverseJsonValue dict size(%d)...", members.size());
#endif
            for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it) {
                const std::string &name = *it;
                traverseJsonValue(name, value[name], dict, true);
            }
        }
            break;
        case Json::arrayValue: {
#ifdef HPRINT_JSON_PROGRESS
            HLOGI("JSON: array...");
#endif
            CCArray *array = CCArray::create();
            if (isDict) {
                CCDictionary *lastDict = (CCDictionary *)data;
#ifdef HPRINT_JSON_PROGRESS
                HLOGI("JSON: parent dict count(%d)..retain count(%d).", lastDict->count(), lastDict->retainCount());
#endif
                lastDict->setObject(array, name);
            } else {
                CCArray *lastArray = (CCArray *)data;
#ifdef HPRINT_JSON_PROGRESS
                HLOGI("JSON: parent array count(%d)..retain count(%d).", lastArray->count(), lastArray->retainCount());
#endif
                lastArray->addObject(array);
            }
            
            int size = value.size();
#ifdef HPRINT_JSON_PROGRESS
            HLOGI("JSON: traverseJsonValue array size(%d)...", size);
#endif
            for (int i = 0; i < size; ++i) {
                traverseJsonValue("", value[i], array, false);
            }
        }
            break;
        default: {
#ifdef HPRINT_JSON_PROGRESS
            HLOGI("JSON: value...");
#endif
            HString *obj = NULL;//HString::create(value.asString());
            switch (value.type()) {
                case Json::intValue:
#ifdef HPRINT_JSON_PROGRESS
                    HLOGI("JSON: int(%d)...", value.asInt());
#endif
                    obj = HString::createWithInteger(value.asInt());
                    break;
                case Json::uintValue:
#ifdef HPRINT_JSON_PROGRESS
                    HLOGI("JSON: uint(%d)...", value.asUInt());
#endif
                    obj = HString::createWithUInteger(value.asUInt());
                    break;
                case Json::realValue:
#ifdef HPRINT_JSON_PROGRESS
                    HLOGI("JSON: real(%f)...", value.asDouble());
#endif
                    obj = HString::createWithFloat(value.asDouble());
                    break;
                case Json::booleanValue:
#ifdef HPRINT_JSON_PROGRESS
                    HLOGI("JSON: boolean(%d)...", value.asBool());
#endif
                    obj = HString::createWithBoolean(value.asBool());
                    break;
                case Json::stringValue:
#ifdef HPRINT_JSON_PROGRESS
                    HLOGI("JSON: string(%s)...", value.asString().c_str());
#endif
                    obj = HString::create(value.asString());
                    break;
                    //break;
                default:
#ifdef HPRINT_JSON_PROGRESS
                    HLOGI("JSON: null...");
#endif
                    break;
            }
            if (obj) {
                if (isDict) {
                    CCDictionary *dict = (CCDictionary *)data;
#ifdef HPRINT_JSON_PROGRESS
                    HLOGI("JSON: parent dict count(%d)..retain count(%d).", dict->count(), dict->retainCount());
#endif
                    dict->setObject(obj, name);
                } else {
                    CCArray *array = (CCArray *)data;
#ifdef HPRINT_JSON_PROGRESS
                    HLOGI("JSON: parent array count(%d)..retain count(%d).", array->count(), array->retainCount());
#endif
                    array->addObject(obj);
                }
            }
        }
            break;
    }
}

CCDictionary *dictionaryFromPlist(const char *data, unsigned int size) {
    return HDictionaryGenerator::dictionaryFromPlist(data, size);
}

CCDictionary *dictionaryFromPlist(const char *filename) {
    return HDictionaryGenerator::dictionaryFromPlist(filename);
}

CCDictionary *dictionaryFromJSON(const char *data, unsigned int size) {
    return HDictionaryGenerator::dictionaryFromJSON(data, size);
}

CCDictionary *dictionaryFromJSON(const char *filename) {
    return HDictionaryGenerator::dictionaryFromJSON(filename);
}

std::string dictionaryToJSON(CCDictionary *dict) {
    return HDictionaryGenerator::dictionaryToJSON(dict);
}

class CC_DLL HArrayGenerator:public HDictionaryGenerator
{
public:
    static CCArray *arrayFromJSON(const char *data, unsigned int size);
    
protected:
    HArrayGenerator();
    ~HArrayGenerator();
private:
    bool parseFromJSON(const char *data, unsigned int size);
private:
    CCArray *m_pArrayResult;
};

HArrayGenerator::HArrayGenerator()
:m_pArrayResult(NULL)
{

}

HArrayGenerator::~HArrayGenerator()
{    
}

CCArray *arrayFromJSON(const char *data, unsigned int size)
{
    return HArrayGenerator::arrayFromJSON(data, size);
}

bool HArrayGenerator::parseFromJSON(const char *data, unsigned int size)
{
#ifdef HPRINT_JSON_PROGRESS
    HLOGI("---parseFromJSON: size(%d)", size);
#endif
    m_pDictResult = NULL;
    Json::Reader reader;
    Json::Value value;
    
    std::string pText((char*)data, 0, size);
    if (reader.parse(pText, value)) {
        if  (value.type() == Json::arrayValue) {
            m_pArrayResult = CCArray::create();            
            int size = value.size();
            for (int i = 0; i < size; ++i) {
                traverseJsonValue("", value[i], m_pArrayResult, false);
            }
        }
    }
#ifdef HPRINT_JSON_PROGRESS
    HLOGI("---parseFromJSON: end");
#endif
    return true;
}

CCArray *HArrayGenerator::arrayFromJSON(const char *data, unsigned int size)
{
    HArrayGenerator generator;
    if (generator.parseFromJSON(data, size))
        return generator.m_pArrayResult;
    return NULL;
}

HNAMESPACE_END

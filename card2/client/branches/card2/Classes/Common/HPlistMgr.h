//
//  HPlistMgr.h
//  card
//
//  Created by zhou gang on 13-4-2.
//
//

#ifndef __card__HPlistMgr__
#define __card__HPlistMgr__

#include <string>
#include <map>
using namespace std;

class HPlistManager : public CCObject {
    
public:
    HSINGLETON_OBJECT(HPlistManager);
    
public:
    void addPlist(const char* plist);
    void removePlist(const char* plist);
    CCSpriteFrame* spriteFrameWithName(const char* fileName);
    
public:
    CCDictionary* m_plist_cache;
};

class HFontManager : public CCObject {
    HSINGLETON_OBJECT(HFontManager);
    
public:
    
    const char* getFontName(const char* ttfFile);
    
    void replaceFont(CCNode* node);
    
protected:
    map<string, const char*> m_fontMap;
};

#define HFontArialBold      "Arial-BoldMT"
#define HFontLiSu           "Stliti"
#define HFontHelvetica      "Helvetica"


#endif /* defined(__card__HPlistMgr__) */

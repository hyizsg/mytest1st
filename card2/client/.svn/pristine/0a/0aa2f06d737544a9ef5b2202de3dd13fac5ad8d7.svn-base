//
//  TriVersion.cpp
//
//  Created by jim kaden on 13-6-4.
//

#include "TriVersion.h"
#include <algorithm>
using namespace haypi;

TriVersion::TriVersion()
{
    _num[0] = 0;
    _num[1] = 0;
    _num[2] = 0;
    _ver = "0.0.0";
}

TriVersion::TriVersion(std::string ver)
{
    _num[0] = 0;
    _num[1] = 0;
    _num[2] = 0;
    _ver = "0.0.0";
    parse(ver);
}

bool TriVersion::parse(std::string ver)
{
    int pos = 0, last_pos = 0;
    int verIndex = 0;
    long num[3];
    num[0] = num[1] = num[2] = 0;
    
    do
    {
        pos = ver.find(".", last_pos);
        std::string subver;
        if ( pos != std::string::npos)
        {
            subver = ver.substr(last_pos, pos - last_pos);
            last_pos = pos + 1;
        }
        else
        {
            subver = ver.substr(last_pos, ver.length() - last_pos);
        }
        
        if ( std::find_if(subver.begin(), subver.end(), std::not1(std::ptr_fun<int, int>(std::isdigit))) != subver.end() )
            return false;
        
        if ( verIndex > 3 )
        {
            // modified by jim
            // 2013-08-14
            // 为了兼容服务器传回的版本字符串，允许多余三段的版本存在
            //return false;
            break;
        }
        num[verIndex++] = atol(subver.c_str());
    }
    while ( pos != std::string::npos);

    // uncomment these lines when release
//    if ( verIndex < 3 )
//        return false;
    
    _num[0] = num[0];
    _num[1] = num[1];
    _num[2] = num[2];
    _ver = ver;
    return true;
}

TriVersion::VERSION_COMPARE_RESULT TriVersion::compare(TriVersion& ver)
{
    if ( ver.big() != big() )
        return VCR_BigChange;
    
    if ( ver.mid() < mid() )
        return VCR_LessThan;
    if ( ver.mid() > mid() )
        return VCR_BigThan;
    if ( ver.small() < small() )
        return VCR_LessThan;
    if ( ver.small() > small() )
        return VCR_BigThan;
    
    return VCR_Equal;
}

TriVersion::VERSION_COMPARE_RESULT TriVersion::compareMiddle(TriVersion& ver)
{
    if ( ver.big() < big() )
        return VCR_LessThan;
    if ( ver.big() > big() )
        return VCR_BigThan;
    
    if ( ver.mid() < mid() )
        return VCR_LessThan;
    if ( ver.mid() > mid() )
        return VCR_BigThan;
    
    return VCR_Equal;
}


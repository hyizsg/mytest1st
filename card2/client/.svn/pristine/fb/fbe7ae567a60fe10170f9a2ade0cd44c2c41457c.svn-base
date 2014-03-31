
//
//  TrimVersion.h
//
//  Created by jim kaden on 13-6-4.
//

#ifndef __TRIVERSION_H__
#define __TRIVERSION_H__
#include <stdlib.h>
#include <string>

namespace haypi
{
    class TriVersion
    {
    public:
        typedef enum
        {
            VCR_Equal = 0,
            VCR_LessThan ,
            VCR_BigThan ,
            VCR_BigChange ,
        }
        VERSION_COMPARE_RESULT;
        
    private:
        long _num[3];
        std::string _ver;
    public:
        TriVersion();
        TriVersion(std::string ver);
        bool parse(std::string ver);
        /*
          比较所有版本号, 结果为传入参数与我的比较结果
         */
        VERSION_COMPARE_RESULT compare(TriVersion& ver);
        /*
         仅比较到中级版本号, 结果为传入参数与我的比较结果
         */
        VERSION_COMPARE_RESULT compareMiddle(TriVersion& ver);
    public:
        long big(){return _num[0];}
        long mid(){return _num[1];}
        long small(){return _num[2];}
        std::string ver(){return _ver;}
    };
};
#endif /* defined(__GameFramework__UpdateManager__) */

//
//  UpdateManager.h
//
//  Created by jim kaden on 13-5-7.
//

#ifndef __UPDATEMANAGER_H__
#define __UPDATEMANAGER_H__
#include <string>

namespace haypi
{
    class UpdateManager
    {
    public:
        typedef enum
        {
            /* 有错误，下载过程已停止, 错误号调用error()获得 */
            UMS_Error = -1,
            UMS_OK = 0,
            /* 正在准备下载 */
            UMS_PreProcessing,
            /* 正在下载 */
            UMS_Downloading,
            /* 正在分析内容*/
            UMS_Analyzing,
            /* 开始处理下载的文件 */
            UMS_PostProcessing,
            /* 尚未开始进行检查版本 */
            UMS_NoChecking,
        }
        UM_STATE;
        
        typedef enum
        {
            UME_NoError,
            UME_BadLocalList,
            UME_BadRemoteList,
            UME_BadRemoteFile,
            UME_ConnectionLost,
            /* 有大版本号更新 */
            UME_BigVersionChanged,
            UME_GeneralError,
        }
        UM_ERROR;
        
    public:
        /**
         @brief 检查版本，传入url.php所在的地址 
         @param[in] url http://haypi.mobi/passport/url.php
         @warning 目前platform保留为0， gcType取值自PASSPORT_PLATFORM, market取值自PASSPORT_MARKET, deviceType取值自DEVICE_TYPE
         @return 成功开始检查返回true，如果正在检查版本或其他出错则返回false
         */
        virtual bool checkVersion(const char* url, int deviceType = 0, int gcType = 0, int platform = 0, int market = 0) = 0;
        
        /**
         @brief 获取当前进度,100即结束
         @return 1~100
         */
        virtual int progress() = 0;
        
        /**
         @brief 获取当前状态
         @return UM_STATE类型
         */
        virtual UM_STATE state() = 0;
        
        /**
         @brief 获取当前错误号
         @return UM_ERROR类型
         */
        virtual UM_ERROR error() = 0;
        
        /**
         @breif 获取path对应的全路径，如果不在此列表内，则返回空
         @param[in] path 请求检查的文件名例如 ccbResources/fileTest.png
         @return 返回path对应的全路径
         */
        virtual std::string pathForName(char* path) = 0;
        
        /**
         @brief 获取动态升级管理程序所用的目录
         */
        virtual std::string rootPath() = 0;
        
        /**
         @brief 当目前状态为UMS_Error， 错误号为UME_BigVersionChanged时，返回对应的升级连接
         @return 当此版本不存在下载连接时，返回"",否则返回对应的升级连接
         */
        virtual std::string upgradeUrl() = 0;
        
        /**
         @brief 清除目前的下载管理器的状态，回复到checkVersion之前的状态，从后台回到前台的时候，建议调用
         */
        virtual void clean() = 0;
        
        /**
         @brief 获取当前本地版本号
         @return 获得当前本地版本号，三段式版本号, 如果本地不存在任何数据，返回“”
         */
        virtual std::string currentVersion() = 0;        
        virtual std::string getInuseVersion() = 0;
        
        /**
         @brief 与当前本地版本号比较，是否有大版本更新
         @param[in] version 传入的版本号。必须按照 xxx.xxx.xxx.xxx 类似的方式传递，每一段版本号，将尽量解码
         @return 返回true则表示有大版本更新，否则返回false
         */
        virtual bool hasBigChange(std::string version) = 0;
        
        /**
         @brief 获得一个UpdateManager实例, 此实例不可以delete
         */
        static UpdateManager* sharedInstance();        
    };
};
#endif /* defined(__GameFramework__UpdateManager__) */

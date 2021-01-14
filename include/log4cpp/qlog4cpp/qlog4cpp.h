/********************************************************************/
/** cpp4log快速配置头文件
*  使用步骤：
* 声明根日志： log4cpp::Category& root = log4cpp::Category::getRoot();
* 初始化： 	   cpp4log_init("./log4cpp.conf");
* 使用后关闭： cpp4log_close();
*   
* 
*********************************************************************/

#pragma once

#include "log4cpp/Category.hh"
#include "log4cpp/PropertyConfigurator.hh"
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh> 
#include "simplelog.h"
 
#include <time.h>
#include <iostream>

using namespace std;

/*** 禁用cpp4log **/
//#define UENABLE_LOG4CPP  

/**************************************************************************************************************/
/*                                              可配置的cpp4log                                               */
/**************************************************************************************************************/

#ifdef UENABLE_LOG4CPP  // 禁用cpp4log

#define DeclarationLog4cpp
#define cpp4log_init(logconfig)
#define cpp4log_close()
#define LOG_MODEL(model_name, grade, format, ...) 

#define LOG_DEBUG(format, ...)   Q_LOG_DEBUG(format,   ##__VA_ARGS__)
#define LOG_INFO(format, ...)    Q_LOG_INFO(format,    ##__VA_ARGS__)  
#define LOG_NOTICE(format, ...)  Q_LOG_NOTICE(format,  ##__VA_ARGS__)
#define LOG_WARN(format, ...)    Q_LOG_WARN(format,    ##__VA_ARGS__)  
#define LOG_ERROR(format, ...)   Q_LOG_ERROR(format,   ##__VA_ARGS__) 
#define LOG_CRIT(format, ...)    Q_LOG_CRIT(format,    ##__VA_ARGS__)  
#define LOG_ALERT(format, ...)   Q_LOG_ALERT(format,   ##__VA_ARGS__) 
#define LOG_FATAL(format, ...)   Q_LOG_FATAL(format,   ##__VA_ARGS__) 
#define LOG_EMERG(format, ...)   Q_LOG_EMERG(format,   ##__VA_ARGS__) 

#else 
 
#pragma comment(lib, "ws2_32.lib") 

#define DeclarationLog4cpp log4cpp::Category& root = log4cpp::Category::getRoot();

#define Qlog4DefaultTimeFromat "%d{%Y-%m-%d %H:%M:%S,%l} %c-> [%6p] %x: %m%n"

extern log4cpp::Category& root;

// 日志初始化 cpp4log_init("./log4cpp.conf");
#define cpp4log_init(logconfig) { \
        log4cpp::PropertyConfigurator::configure(logconfig); \
        log4cpp::OstreamAppender* osAppender = new log4cpp::OstreamAppender("console", &cout); \
        log4cpp::PatternLayout* pLayout = new log4cpp::PatternLayout(); \
        pLayout->setConversionPattern(Qlog4DefaultTimeFromat);  \
        osAppender->setLayout(pLayout); \
        root.addAppender(osAppender);  \
}

// 日志 释放 关闭 
#define cpp4log_close(){ \
    log4cpp::Category::shutdown(); \
}

/** 获取模块日志, appname 是模块名称 **/
#define LOG_CREAT(appname)       root.getInstance(appname); 
 
// 输出模块日志 
#define LOG_MODEL(model_name, grade, format, ...) { \
	    log4cpp::Category& model = LOG_CREAT(model_name); \
        model.grade(format, ##__VA_ARGS__); \
}
 

/** 提供的默认日志宏 **/
#define LOG_DEBUG(format, ...)   root.debug( "[%s:%-6d] " format "", __FUNCTION__ , __LINE__, ##__VA_ARGS__)
#define LOG_INFO(format, ...)    root.info(  "[%s:%-6d] " format "", __FUNCTION__ , __LINE__, ##__VA_ARGS__)
#define LOG_NOTICE(format, ...)  root.notice("[%s:%-6d] " format "", __FUNCTION__ , __LINE__, ##__VA_ARGS__)
#define LOG_WARN(format, ...)    root.warn(  "[%s:%-6d] " format "", __FUNCTION__ , __LINE__, ##__VA_ARGS__)
#define LOG_ERROR(format, ...)   root.error( "[%s:%-6d] " format "", __FUNCTION__ , __LINE__, ##__VA_ARGS__)
#define LOG_CRIT(format, ...)    root.crit(  "[%s:%-6d] " format "", __FUNCTION__ , __LINE__, ##__VA_ARGS__)
#define LOG_ALERT(format, ...)   root.alert( "[%s:%-6d] " format "", __FUNCTION__ , __LINE__, ##__VA_ARGS__)
#define LOG_FATAL(format, ...)   root.fatal( "[%s:%-6d] " format "", __FUNCTION__ , __LINE__, ##__VA_ARGS__)
#define LOG_EMERG(format, ...)   root.emerg( "[%s:%-6d] " format "", __FUNCTION__ , __LINE__, ##__VA_ARGS__)
 
#endif
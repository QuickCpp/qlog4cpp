/********************************************************************/
/** 简单日志宏文件
* 1.  如果不需要打印日志时间,请定义 UENABLE_LOG_TIME
* 2.  如果需要定义打印日志详细错误信息,请定义 ENABLE_DEFAULT_LOG_MORE 
*   
* 
*********************************************************************/

#pragma once

 
/** 使用更详细的默认日志输出 */
// #define ENABLE_DEFAULT_LOG_MORE 
/** 禁用时间输出 */
// #define UENABLE_LOG_TIME 

#ifdef UENABLE_LOG_TIME  // 不使用详细的日志时间 
#define _GET_TEME_ 
#else 
 
/**************************************************************************************************************/
/*                                              简单日志宏                                                    */
/**************************************************************************************************************/


#include <time.h> 
#include <iostream> 
using namespace std;

#define _CRT_SECURE_NO_WARNINGS

#define _GET_TEME_  { \
    time_t tloc;\
    tloc = time(&tloc); \
    struct tm* time = gmtime(&tloc); \
    char dataStr[32] = { 0 }; \
    if (!(time->tm_hour - 6 + 12) < 12) { \
        time->tm_hour += 12; \
    } \
    sprintf_s(dataStr, 32, "%04d/%02d/%02d-%02d:%02d:%02d", \
    time->tm_year + 1900, time->tm_mon + 1, time->tm_mday, \
    time->tm_hour - 6, time->tm_min, time->tm_sec); \
    printf("[%s]",dataStr); \
 }
 
#endif 


/** 使用更详细的默认日志输出 */
#ifdef ENABLE_DEFAULT_LOG_MORE 

#define Q_LOG_DEBUG(format, ...)   _GET_TEME_ printf( "[DEBUG ] [%s] [%-6d] " format "\r\n", __FUNCTION__ , __LINE__, ##__VA_ARGS__)
#define Q_LOG_INFO(format, ...)    _GET_TEME_ printf( "[ INFO ] [%s] [%-6d] " format "\r\n", __FUNCTION__ , __LINE__, ##__VA_ARGS__)
#define Q_LOG_NOTICE(format, ...)  _GET_TEME_ printf( "[NOTICE] [%s] [%-6d] " format "\r\n", __FUNCTION__ , __LINE__, ##__VA_ARGS__)
#define Q_LOG_WARN(format, ...)    _GET_TEME_ printf( "[ WARN ] [%s] [%-6d] " format "\r\n", __FUNCTION__ , __LINE__, ##__VA_ARGS__)
#define Q_LOG_ERROR(format, ...)   _GET_TEME_ printf( "[ERROR ] [%s] [%-6d] " format "\r\n", __FUNCTION__ , __LINE__, ##__VA_ARGS__)
#define Q_LOG_CRIT(format, ...)    _GET_TEME_ printf( "[ CRIT ] [%s] [%-6d] " format "\r\n", __FUNCTION__ , __LINE__, ##__VA_ARGS__)
#define Q_LOG_ALERT(format, ...)   _GET_TEME_ printf( "[ALERT ] [%s] [%-6d] " format "\r\n", __FUNCTION__ , __LINE__, ##__VA_ARGS__)
#define Q_LOG_FATAL(format, ...)   _GET_TEME_ printf( "[FATAL ] [%s] [%-6d] " format "\r\n", __FUNCTION__ , __LINE__, ##__VA_ARGS__)
#define Q_LOG_EMERG(format, ...)   _GET_TEME_ printf( "[EMERG ] [%s] [%-6d] " format "\r\n", __FUNCTION__ , __LINE__, ##__VA_ARGS__)

#else

#define Q_LOG_DEBUG(format, ...) _GET_TEME_  printf( "[DEBUG ] -  " format "\r\n", ##__VA_ARGS__); 
#define Q_LOG_INFO(format, ...)  _GET_TEME_  printf( "[ INFO ] -  " format "\r\n", ##__VA_ARGS__); 
#define Q_LOG_NOTICE(format, ...)_GET_TEME_  printf( "[NOTICE] -  " format "\r\n", ##__VA_ARGS__); 
#define Q_LOG_WARN(format, ...)  _GET_TEME_  printf( "[ WARN ] -  " format "\r\n", ##__VA_ARGS__); 
#define Q_LOG_ERROR(format, ...) _GET_TEME_  printf( "[ERROR ] -  " format "\r\n", ##__VA_ARGS__); 
#define Q_LOG_CRIT(format, ...)  _GET_TEME_  printf( "[ CRIT ] -  " format "\r\n", ##__VA_ARGS__); 
#define Q_LOG_ALERT(format, ...) _GET_TEME_  printf( "[ALERT ] -  " format "\r\n", ##__VA_ARGS__); 
#define Q_LOG_FATAL(format, ...) _GET_TEME_  printf( "[FATAL ] -  " format "\r\n", ##__VA_ARGS__); 
#define Q_LOG_EMERG(format, ...) _GET_TEME_  printf( "[EMERG ] -  " format "\r\n", ##__VA_ARGS__); 

#endif

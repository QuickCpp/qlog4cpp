#include <stdio.h>
#include "log4cpp/Portability.hh"
#ifdef LOG4CPP_HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <iostream>
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#ifdef LOG4CPP_HAVE_SYSLOG
#include "log4cpp/SyslogAppender.hh"
#endif
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/NDC.hh"

#include "log4cpp/Category.hh"
#include "log4cpp/PropertyConfigurator.hh"
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh> 

#pragma comment(lib, "ws2_32.lib")

#include <iostream> 

using namespace std;
 

#define Qlog4DefaultTimeFromat "%d{%Y-%m-%d %H:%M:%S,%l} %c-> [%6p] %x: %m%n"

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

/** 获取模块日志, appname 是模块名称 **/
#define LOG_CREAT(appname)       root.getInstance(appname); 


int main(int argc, char** argv) {
	
	log4cpp::PropertyConfigurator::configure("./log4cpp.conf");
	log4cpp::Category& root = log4cpp::Category::getRoot();


	log4cpp::OstreamAppender* osAppender = new log4cpp::OstreamAppender("console", &cout);
	log4cpp::PatternLayout* pLayout = new log4cpp::PatternLayout();
	pLayout->setConversionPattern(Qlog4DefaultTimeFromat); // 时间 TAG [等级] : 消息
	osAppender->setLayout(pLayout);
	root.addAppender(osAppender); // 最好只设置一次,否则执行 shutdown 时可能出错

	LOG_DEBUG("测试:%s", "测试");

	// 模块1的Log
	log4cpp::Category& info = LOG_CREAT("app1");
	info.debug("system is running %s", "日志");
	info.info("system is running %s", "日志trst");
	info.warn("system has a warning");
	info.error("system has a error, can't find a file");
	info.fatal("system has a fatal error,must be shutdown");



	// 释放 关闭 
	log4cpp::Category::shutdown();
//
//
//	log4cpp::Appender* appender;
//#ifdef LOG4CPP_HAVE_SYSLOG
//	log4cpp::SyslogAppender* syslogAppender;
//
//	syslogAppender = new log4cpp::SyslogAppender("syslog", "log4cpp");
//#else
//	log4cpp::Appender* syslogAppender;
//
//	syslogAppender = new log4cpp::OstreamAppender("syslogdummy", &std::cout);
//#endif
//
//	if (argc < 2) {
//		appender = new log4cpp::OstreamAppender("default", &std::cout);
//	} else {
//		appender = new log4cpp::FileAppender("default", argv[1]);
//	}
//
//	syslogAppender->setLayout(new log4cpp::BasicLayout());
//	appender->setLayout(new log4cpp::BasicLayout());
//
//	//log4cpp::Category& root = log4cpp::Category::getRoot();
//	root.addAppender(syslogAppender);
//	root.setPriority(log4cpp::Priority::ERROR);
//
//	log4cpp::Category& sub1 = log4cpp::Category::getInstance(std::string("sub1"));
//	sub1.addAppender(appender);
//
//	log4cpp::Category& sub2 = log4cpp::Category::getInstance(std::string("sub1.sub2"));
//
//	log4cpp::NDC::push(std::string("ndc1"));
//
//	std::cout << " root prio = " << root.getPriority() << std::endl;
//	std::cout << " sub1 prio = " << sub1.getPriority() << std::endl;
//	std::cout << " sub2 prio = " << sub2.getPriority() << std::endl;
//
//	root.error("root error");
//	root.warn("root warn");
//	sub1.error("sub1 error");
//	sub1.warn("sub1 warn");
//	sub2.error("sub2 error");
//	sub2.warn("sub2 warn");
//
//	sub1.setPriority(log4cpp::Priority::INFO);
//	std::cout << " root prio = " << root.getPriority() << std::endl;
//	std::cout << " sub1 prio = " << sub1.getPriority() << std::endl;
//	std::cout << " sub2 prio = " << sub2.getPriority() << std::endl;
//
//	std::cout << "priority info" << std::endl;
//	root.error("root error");
//	root.warn("root warn");
//	sub1.error("sub1 error");
//	sub1.warn("sub1 warn");
//	sub2.error("sub2 error");
//	sub2.warn("sub2 warn");
//
//	sub2.warnStream() << "streamed warn";
//
//	sub2 << log4cpp::Priority::WARN << "warn2" << " warn3" 
//             << log4cpp::eol << " warn4";
//
//	{
//		for(int i = 0; i < 10000; i++) {
//			char ndc2[20];
//			sprintf(ndc2, "i=%d", i);
//			log4cpp::NDC::push(ndc2);
//			sub1.info("%s%d", "i = ", i);
//			if ((i % 10) == 0) {
//				sub1.log(log4cpp::Priority::NOTICE, "reopen log");
//				if (log4cpp::Appender::reopenAll()) {
//					sub1.info("log reopened");
//				} else {
//					sub1.warn("could not reopen log");
//				}
//			}
//#ifndef WIN32
//			sleep(1);
//#endif
//			log4cpp::NDC::pop();
//		}
//	}

	return 0;
}

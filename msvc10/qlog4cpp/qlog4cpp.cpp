// mlog.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <log4cpp/qlog4cpp/qlog4cpp.h>

#include <iostream>

using namespace std;
  
log4cpp::Category& root = log4cpp::Category::getRoot();

int main()
{
	cpp4log_init("./log4cpp.conf");
	LOG_DEBUG("测试");
	cpp4log_close();
}

 
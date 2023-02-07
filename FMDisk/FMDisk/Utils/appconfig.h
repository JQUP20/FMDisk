#ifndef APPCONFIG_H
#define APPCONFIG_H

//#ifdef _MSC_VER
//#  ifdef BUILDING_MYDLL
//#    define MYCLASS_DECLSPEC __declspec(dllexport)
//#  else
//#    define MYCLASS_DECLSPEC __declspec(dllimport)
//#  endif
//#endif


#ifdef P_API_
  #define P_API___declspec(dllexport)
#else
   #define P_API___declspec(dllimport)
#endif


#define P_API_

#define _MS
#include <iostream>
#include <memory>
#include "spdlog/spdlog.h"

using namespace std;

// 使用宏替代单例实例
#define AppConfigHandler AppConfig::GetInstance()

class AppConfig
{
public:
    static AppConfig& GetInstance(void);		/// 实例(工厂方法)

    //初始化日志工具
    void InitialiseLog(const string &path);
    void DropSpdLog();
    void Info(const string &msg);
private:
    AppConfig();
    ~AppConfig(void);
private:
    std::shared_ptr<spdlog::logger> m_daily_logger;
    std::shared_ptr<spdlog::logger> m_console_logger;
    friend class auto_ptr<AppConfig>;				/// 使用智能指针
    /// 即使从未被调用也会被构造(析构);如果对象使用static 修饰，意思是只有一个对象会被产生出来。
    /// 构造函数属性为 private ，可以防止对象的产生。(auto_ptr need #include <memory>)
    static auto_ptr<AppConfig> auto_ptr_instance;	/// 惟一实例
};

#endif // APPCONFIG_H

#include "appconfig.h"

#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/daily_file_sink.h"

// 单例声明
// 类内 class static 除了在class 之内声明，还需要在class 之外定义.
auto_ptr<AppConfig> AppConfig::auto_ptr_instance;

AppConfig& AppConfig::GetInstance(void)
{
    if (auto_ptr_instance.get() == 0) {
        auto_ptr_instance.reset(new AppConfig());
    }
    return *(auto_ptr_instance.get());
}

void AppConfig::InitialiseLog(const string &path)
{
    //spdlog::set_async_mode(4096, spdlog::async_overflow_policy::discard_log_msg);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [thread %t] [%n] [%l] %v");
    m_daily_logger = spdlog::daily_logger_mt("daily_logger", path.c_str(), 2, 30);
    m_daily_logger->flush_on(spdlog::level::err);

    m_console_logger = spdlog::stdout_logger_mt("console");
    m_console_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
    m_console_logger->info("CONSOLE LOG INITIALISED");
}

void AppConfig::DropSpdLog()
{
    spdlog::drop_all();
}

void AppConfig::Info(const string &msg)
{
    try{
        m_daily_logger->info(msg.c_str());
        m_console_logger->info(msg.c_str());
    }
    catch (const spdlog::spdlog_ex& ex){
       // std::cout << "Log failed: " << ex.what() << std::endl;
    }
}

AppConfig::AppConfig()
{

}

AppConfig::~AppConfig()
{

}

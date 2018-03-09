#ifndef NOMA_LOG_HELPER_HPP_
#define NOMA_LOG_HELPER_HPP_
#include <iostream>
#include <vector>
#include <fstream>


namespace noma {
    enum class LogType {
        Info,
        Warning,
        Error,
        Fatal
    };

    class LogHelper
    {
    public:
        /*static void Init()
        {
            Init("log.txt");
        }

        static void Init(const std::string& logFile)
        {
            stream_ = std::ofstream("logs/" + logFile);

            is_init_ = true;
        }

        static void Uninit()
        {
            stream_.close();
        }*/

        static void Log(const std::string& msg)
        {
            Log(msg, LogType::Info);
        }

        static void Log(const std::string& msg, LogType logType)
        {
            //if (!is_init_) throw std::runtime_error("Init first");

            std::string prefix = "";
            switch (logType)
            {
                case LogType::Info:
                    prefix = "INFO";
                break;
                case LogType::Warning:
                    prefix = "WARNING";
                break;
                case LogType::Error:
                    prefix = "ERROR";
                break;
                case LogType::Fatal:
                    prefix = "FATAL";
                break;
                default: break;
            }  

            std::string fullStr = "[" + prefix + "]" + "\t" + msg;
            std::cerr << fullStr << std::endl;

            //stream_ << fullStr << std::endl;
        }

    private:
        /*static bool is_init_;
        static std::ofstream stream_;*/
    };

    /*bool LogHelper::is_init_ = false;
    std::ofstream LogHelper::stream_ = std::ofstream("logs/log.txt");*/
    
    #define L(x) { LogHelper::Log(x); }
}

#endif // NOMA_LOG_HELPER_HPP_
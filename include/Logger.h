#pragma once

#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/core.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <cstring>
#include <string>

namespace logging = boost::log;
namespace keywords = boost::log::keywords;

// Compile-time filename trimming macro
#define PROJECT_ROOT_STR "satpi/"
#define __FILENAME__ (strstr(__FILE__, PROJECT_ROOT_STR) ? strstr(__FILE__, PROJECT_ROOT_STR) + sizeof(PROJECT_ROOT_STR) - 1 : __FILE__)

class Logger {
public:
    static void init(bool debug = false) {
        logging::add_console_log(
            std::clog,
            keywords::format = (
                "[%TimeStamp%] [%Severity%] [%SourceFile%:%SourceLine%] %Message%"
            )
        );

        // Optional: File sink
        /*
        logging::add_file_log (
            keywords::file_name = "dreampi_%N.log",
            keywords::rotation_size = 10 * 1024 * 1024,
            keywords::format = "[%TimeStamp%] [%Severity%] [%SourceFile%:%SourceLine%] %Message%",
            keywords::auto_flush = true
        );
        */

        logging::add_common_attributes();

        // Set severity level
        logging::core::get()->set_filter(
            logging::trivial::severity >= (debug ? logging::trivial::debug : logging::trivial::info)
        );
    }

    static void info(const std::string& msg, const char* file, int line) {
        BOOST_LOG_SCOPED_THREAD_TAG("SourceFile", file);
        BOOST_LOG_SCOPED_THREAD_TAG("SourceLine", line);
        BOOST_LOG_TRIVIAL(info) << msg;
    }

    static void warn(const std::string& msg, const char* file, int line) {
        BOOST_LOG_SCOPED_THREAD_TAG("SourceFile", file);
        BOOST_LOG_SCOPED_THREAD_TAG("SourceLine", line);
        BOOST_LOG_TRIVIAL(warning) << msg;
    }

    static void error(const std::string& msg, const char* file, int line) {
        BOOST_LOG_SCOPED_THREAD_TAG("SourceFile", file);
        BOOST_LOG_SCOPED_THREAD_TAG("SourceLine", line);
        BOOST_LOG_TRIVIAL(error) << msg;
    }

    static void debug(const std::string& msg, const char* file, int line) {
        BOOST_LOG_SCOPED_THREAD_TAG("SourceFile", file);
        BOOST_LOG_SCOPED_THREAD_TAG("SourceLine", line);
        BOOST_LOG_TRIVIAL(debug) << msg;
    }
};

// Logging macros to capture the call site file/line with trimmed filename
#define LOG_INFO(msg)  Logger::info((msg), __FILENAME__, __LINE__)
#define LOG_WARN(msg)  Logger::warn((msg), __FILENAME__, __LINE__)
#define LOG_ERROR(msg) Logger::error((msg), __FILENAME__, __LINE__)
#define LOG_DEBUG(msg) Logger::debug((msg), __FILENAME__, __LINE__)


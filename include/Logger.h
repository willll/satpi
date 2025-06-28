#ifndef LOGGER_H
#define LOGGER_H

#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/core.hpp>

namespace logging = boost::log;
namespace keywords = boost::log::keywords;

class Logger {
public:
    static void init(bool debug = false) {
        // Console sink
        logging::add_console_log(
            std::clog,
            keywords::format = "[%TimeStamp%] [%Severity%] %Message%"
        );

        // Optional: File sink
        /*
        logging::add_file_log (
            keywords::file_name = "dreampi_%N.log",
            keywords::rotation_size = 10 * 1024 * 1024,
            keywords::format = "[%TimeStamp%] [%Severity%] %Message%",
            keywords::auto_flush = true
        );
        */

        logging::add_common_attributes();

        // Set severity level
        logging::core::get()->set_filter(
            logging::trivial::severity >= (debug ? logging::trivial::debug : logging::trivial::info)
        );
    }

    // Severity shortcut macros (for consistency with old Logger API)
    static void info(const std::string& msg) {
        BOOST_LOG_TRIVIAL(info) << msg;
    }

    static void warn(const std::string& msg) {
        BOOST_LOG_TRIVIAL(warning) << msg;
    }

    static void error(const std::string& msg) {
        BOOST_LOG_TRIVIAL(error) << msg;
    }

    static void debug(const std::string& msg) {
        BOOST_LOG_TRIVIAL(debug) << msg;
    }
};

#endif // LOGGER_H

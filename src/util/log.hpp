#pragma once
#include <iostream>

#define LOG
#define WARN
#define ERR

namespace log {
    inline void _warn(std::ostream& os, const std::string& msg) {
        os << "WARNING: " << msg << std::endl;
    }
    inline void _log(std::ostream& os, const std::string& msg) {
        os << "INFO: " << msg << std::endl;
    }
    inline void _err(std::ostream& os, const std::string& msg) {
        os << "ERROR: " << msg << std::endl;
    }
}

#ifdef WARN
#define warn(m) log::_warn(std::cout, m)
#else
#define warn(m)
#endif

#ifdef LOG
#define log(m) log::_log(std::cout, m)
#else
#define log(m)
#endif

#ifdef ERR
#define err(m) log::_err(std::cerr, m)
#else
#define err(m)
#endif
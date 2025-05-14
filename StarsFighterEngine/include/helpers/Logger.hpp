#pragma once

#include <memory>
#include <sstream>
#include <string>

namespace Helpers {

    enum class LogLevel : int {
        Off = 0,
        Error,
        Warning,
        Info,
        DefaultLevel = Info,
        Debug,
        _Last
    };

    class Logger {
    public:
        //! Get the logger singleton, initialized on first call
        static Logger GetLogger();

        // Copying the logger is cheap, thanks to shared implementation
        Logger(const Logger&) = default;
        Logger& operator=(const Logger&) = default;

        ~Logger() = default;

        // Move leaves the object in a 'default' state,
        // which does not make sense for a logger
        Logger(Logger&&) = delete;
        Logger& operator=(Logger&&) = delete;

        //! Get current log level
        LogLevel GetLevel() const;
        //! Messages with higher level will be ignored by the logger
        void SetLevel(LogLevel Level);

        //! Write a message to the log, unless the current log level is lower
        void Write(LogLevel Level, const std::string& Message) const;

    private:
        // Use get_logger instead
        Logger() = default;

        // All loggers use the same implementation
        struct Logger_impl;
        std::shared_ptr<Logger_impl> Impl;
    };

    namespace detail {
        template<typename MessagePart>
        inline void StreamParts(std::stringstream& Stream, const MessagePart& Part) {
            Stream << Part;
        }

        template<typename MessagePart, typename... MessageParts>
        inline void StreamParts(std::stringstream& Stream, const MessagePart& Part, const MessageParts& ...MoreParts) {
            Stream << Part;
            StreamParts(Stream, MoreParts...);
        }
    }

    /*! Write any amount of elements of various types into a single log entry
        Every part type must support stream operator <<
    */
    template<typename... MessageParts>
    inline void WriteLog(Logger& Logger, LogLevel Level, const MessageParts& ...Parts) {
        // Optimization: check level before doing expensive conversions
        if (Level > Logger.GetLevel())
            return;

        // Use string stream to convert
        std::stringstream s;
        detail::StreamParts(s, Parts...);
        Logger.Write(Level, s.str());
    }
}

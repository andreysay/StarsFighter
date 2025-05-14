#include "helpers/Logger.hpp"

#include <fstream>
#include <cassert>
#include <qdebug.h>
#include <qlogging.h>
#include <thread>
#include <queue>
#include <iostream>
#include <chrono>
#include <mutex>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

constexpr std::string_view LogFile = "Gamelog.txt";

namespace Helpers {
//! Convert log level into string
static std::string StringLogLevel(LogLevel Level) {
    const char* Names[] = {
        "OFF", "ERROR", "WARNING", "INFO", "DEBUG"
    };
    auto iLevel = static_cast<int>(Level);
    if (iLevel < 0 || Level >= LogLevel::_Last)
        iLevel = 0; // avoid overrun
    return Names[iLevel];
}

//! Get current time, for printing into the log
static std::string GetNowTimeString(bool IsShort = false) {
    using system_clock = std::chrono::system_clock;
    auto Now = system_clock::now();
    auto Cnow = system_clock::to_time_t(Now);
    if (IsShort) {
        auto Time = std::localtime(&Cnow);
        std::stringstream Stream;
        Stream << std::put_time(Time, "%Y-%m-%d-%H-%M");
        return Stream.str();
    }
    auto Result = std::string{ std::ctime(&Cnow) };
    // ctime result always ends with '\n', we don't want it in our logs
    if (!Result.empty())
        Result.pop_back();
    return Result;
}
}

using namespace Helpers;

//! Logger implementation
struct Logger::Logger_impl {
    LogLevel Level = LogLevel::DefaultLevel;
    std::ofstream Stream;

    std::mutex Mutex;
    std::queue<std::string> Messages;

    std::thread WriterThread;
    std::atomic<bool> bActive = true;
    /*
    * The condition variable is used to notify the writer thread
    */
    std::condition_variable MessagePending;

    Logger_impl()
        : WriterThread([this]() {
            while (bActive.load(std::memory_order_relaxed)) {
                write_pending_message();
            }
        })
    {}

    ~Logger_impl() {
        bActive.store(false, std::memory_order_relaxed);
        std::scoped_lock Lock{ Mutex };
        MessagePending.notify_all();

        WriterThread.detach();
    }

    void write_pending_message() {

        std::unique_lock Lock{ Mutex };
        // Wait until there is a message to process
        MessagePending.wait(Lock); // releases the mutex
        // mutex is acquired

        if (Messages.empty())
            return;

        std::queue<std::string> TakenMessages{ std::move(Messages) };
        Lock.unlock();

        qInfo() << "Taken " << TakenMessages.size() << " messages";

        while (!TakenMessages.empty()) {

            std::string Message{ std::move(TakenMessages.front()) };
            TakenMessages.pop();

            Stream << Message << std::endl;
            qInfo() << Message;
        }
    }

    void push_message(LogLevel level, const std::string& message) {
        std::stringstream Stream;
        Stream
            << "["
            << GetNowTimeString()
            << "]\t"
            << StringLogLevel(level)
            << '\t'
            << message;

        {
            // Keep the mutex locked as short as possible
            std::scoped_lock Lock{ Mutex };
            Messages.push(Stream.str());
        }
        // Notify a single thread wake up and process the message
        MessagePending.notify_one();
    }
};

//! Get logger singleton. Throws if log cannot be accessed
Logger Logger::GetLogger() {
    static Logger Singleton;
    if (!Singleton.Impl) {
        auto Impl = std::make_shared<Logger::Logger_impl>();
        //std::string LogFileName = GetNowTimeString(true) + std::string{"log.txt"};
        qInfo() << "Log file name is " << std::string{LogFile};
        Impl->Stream.open(std::string{LogFile}, std::ios_base::app);
        if (!Impl->Stream.is_open()) {
            throw std::runtime_error{ "Cannot open a log" };
        }
        Singleton.Impl = Impl;
    }
    return Singleton;
}

// Function is const:
//      Writing to log does not change logger state
// Message is const&:
//      Caller gets a guarantee that the string won't change

void Logger::Write(LogLevel Level, const std::string& Message) const {

    assert(Impl);

    if (Level > Impl->Level)
        return;

    Impl->push_message(Level, Message);
}

LogLevel Logger::GetLevel() const {
    assert(Impl);
    return Impl->Level;
}

void Logger::SetLevel(LogLevel level) {
    assert(Impl);
    Impl->Level = level;
}


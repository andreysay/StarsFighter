#include "GameEntry.hpp"

#include <QCoreApplication>
#include "framework/GameBaseApp.hpp"
#include "framework/Core.hpp"

using namespace Helpers;

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.
    LogLevel Loglevel = LogLevel::Debug;
    //auto Log = CreateLogger(Loglevel);

    GLog.SetLevel(Loglevel);
    WriteLog(GLog, Loglevel, "Game is starting up");
    std::unique_ptr<StarsFigher::GameBaseApp> Game = GetGame();
    Game->RunGame();
    WriteLog(GLog, Loglevel, "Game finished");
    //return a.exec();
}

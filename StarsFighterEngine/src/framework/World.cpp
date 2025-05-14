#include "framework/World.hpp"
#include "framework/Core.hpp"
#include "framework/GameBaseApp.hpp"
#include <QString>

namespace StarsFigher
{
    World::World(GameBaseApp *OwningApp)
    : WorldOwningApp{OwningApp}
    {

    }

    void World::BeginPlayInternal()
    {
        if(!bBeginPlay)
        {
            bBeginPlay = true;
            BeginPlay();
        }
    }

    void World::TickInternal(float DeltaTime)
    {
        Tick(DeltaTime);
    }

    void World::BeginPlay()
    {

    }

    void World::Tick(float DeltaTime)
    {
        Helpers::WriteLog(GLog, Helpers::LogLevel::Info, QString("Tick at frame rate %1").arg(QString::number(1.f/DeltaTime)).toStdString());
    }
}

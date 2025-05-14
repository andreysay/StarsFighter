#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "framework/World.hpp"

using namespace sf;;

namespace StarsFigher
{

    class GameBaseApp
    {
    public:
        GameBaseApp();
        void RunGame();

    template<typename WorldType>
    std::weak_ptr<WorldType> LoadWorld();

    protected:
        virtual void Render();
        virtual void Tick(float DeltaTime);

    private:
        void TickInternal(float DeltaTime);
        void RenderInternal();

    private:
        std::unique_ptr<RenderWindow> GameWindow = nullptr;
        std::shared_ptr<World> CurrentWorld = nullptr;
        float TargetFrameRate{60.f};
        Clock TickClock{};
    };

    template<typename WorldType>
    inline std::weak_ptr<WorldType> GameBaseApp::LoadWorld()
    {
        std::shared_ptr<WorldType> NewWorld = std::make_shared<WorldType>(this);
        CurrentWorld = NewWorld;
        CurrentWorld->BeginPlayInternal();
        return NewWorld;
    }
}

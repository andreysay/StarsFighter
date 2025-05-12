#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

using namespace sf;;

namespace StarsFigher
{
    class GameBaseApp
    {
    public:
        GameBaseApp();
        void RunGame();

    protected:
        virtual void Render();
        virtual void Tick(float DeltaTime);

    private:
        void TickInternal(float DeltaTime);
        void RenderInternal();

    private:
        std::unique_ptr<RenderWindow> GameWindow;
        float TargetFrameRate{60.f};
        Clock TickClock{};
    };
}

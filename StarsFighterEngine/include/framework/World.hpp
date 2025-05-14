#pragma once

namespace StarsFigher
{
    class GameBaseApp;
    class World
    {
    public:
        explicit World(GameBaseApp* OwningApp);
        virtual ~World() = default;

        void BeginPlayInternal();
        void TickInternal(float DeltaTime);
    protected:
        void BeginPlay();
        void Tick(float DeltaTime);

    private:
        GameBaseApp* WorldOwningApp{nullptr};
        bool bBeginPlay{false};
    };
}

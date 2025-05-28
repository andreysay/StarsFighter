/*
*  GameBaseApp.hpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "framework/World.hpp"

using namespace sf;;

namespace SF
{
	static const float FrameRate{ 60.f };
	static const float CleanInterval{ 2.f }; // Interval for cleaning up the world
    /*
	* Base class for the game application.
    */
    class GameBaseApp
    {
    public:
		GameBaseApp() = delete;
        GameBaseApp(Vector2u WinSize, const std::string& Title, std::uint32_t Style);
		GameBaseApp(const GameBaseApp&) = delete;
		GameBaseApp(GameBaseApp&&) = delete;
		GameBaseApp& operator=(const GameBaseApp&) = delete;
		GameBaseApp& operator=(GameBaseApp&&) = delete;
		virtual ~GameBaseApp() = default;
		// Starts the game loop
        void RunGame();
		// Returns the size of the game window
		[[nodiscard]]
		Vector2u GetWindowSize() const;
    
		// Loads a new world of the specified type and returns a weak pointer to it.
        template<typename WorldType>
        std::weak_ptr<WorldType> LoadWorld();

    protected:
		// Called to render the game frame
        virtual void Render();
		// Called every frame to update the game state
        virtual void Tick(float DeltaTime);

    private:
		// Called internally to handle the internal tick logic
        void TickInternal(float DeltaTime);
		// Called internally to handle the internal rendering logic
        void RenderInternal();

    private:
        std::unique_ptr<RenderWindow> GameWindow{ nullptr };
		// Current world being played
        std::shared_ptr<World> CurrentWorld{ nullptr };
		// Target frame rate for the game loop
        float TargetFrameRate{ FrameRate };
		// Clock for the game loop
        Clock TickClock{};
		// Clock for cleaning up the world
        sf::Clock CleanCycleClock;
		// Interval for cleaning up the world
		float CleanCycleInterval{ CleanInterval };
    };

    template<typename WorldType>
    inline std::weak_ptr<WorldType> GameBaseApp::LoadWorld()
    {
        std::shared_ptr<WorldType> NewWorld{ new WorldType{*this} };
        CurrentWorld = NewWorld;
        CurrentWorld->BeginPlayInternal();
        return NewWorld;
    }
}

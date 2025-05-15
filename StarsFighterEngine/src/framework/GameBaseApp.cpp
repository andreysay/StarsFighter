#include "framework/GameBaseApp.hpp"
#include "framework/AssetManager.hpp"

namespace SF
{

const Vector2u WindowSize{1024, 1440};
const std::string_view GameTitle{"StarsFigher"};

GameBaseApp::GameBaseApp(Vector2u WinSize, const std::string& Title, std::uint32_t Style)
{
    GameWindow = std::make_unique<RenderWindow>(VideoMode{ WinSize }, std::string{ Title }, Style);
}

void GameBaseApp::RunGame()
{
    TickClock.restart();
    float AccumulatedTime = 0.f;
    float TargetDeltaTime = 1.f/TargetFrameRate;

    while (GameWindow->isOpen())
    {
        while (const std::optional Event = GameWindow->pollEvent())
        {
            if(Event->is<sf::Event::Closed>())
            {
                GameWindow->close();
            }
        }
        AccumulatedTime +=TickClock.restart().asSeconds();
        while (AccumulatedTime > TargetDeltaTime)
        {
            AccumulatedTime -= TargetDeltaTime;
            TickInternal(TargetDeltaTime);
            RenderInternal();
        }
    }
}

void GameBaseApp::Render()
{
    //RectangleShape Rect{{200, 200}};
    //Rect.setFillColor(Color::Green);
    //Rect.setPosition({GameWindow->getSize().x*0.5f, GameWindow->getSize().y*0.5f});
    //Rect.setOrigin({50.f,50.f});
    //GameWindow->draw(Rect);
	if (CurrentWorld)
	{
		CurrentWorld->Render(*GameWindow);
	}
}

void GameBaseApp::Tick(float DeltaTime)
{

}

void GameBaseApp::TickInternal(float DeltaTime)
{
    //qInfo() << "Ticking at framerate: " << 1.f/DeltaTime;
    Tick(DeltaTime);

    if(CurrentWorld)
    {
        CurrentWorld->TickInternal(DeltaTime);
    }

	// Cleanup unused assets
	if (CleanCycleClock.getElapsedTime().asSeconds() > CleanCycleInterval)
	{
		CleanCycleClock.restart();
		AssetManager::Get().CleanCycle();
	}
}

void GameBaseApp::RenderInternal()
{
    GameWindow->clear();
    Render();
    GameWindow->display();
}

} // End namespace StarsFigher

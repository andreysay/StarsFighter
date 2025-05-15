#include "framework/AssetManager.hpp"
#include "framework/Core.hpp"

namespace SF
{
	std::unique_ptr<AssetManager> AssetManager::AssetManagerPtr{ nullptr };

	AssetManager& AssetManager::Get()
	{
		if (!AssetManagerPtr)
		{
			AssetManagerPtr = std::unique_ptr<AssetManager>{new AssetManager};
		}
		return *AssetManagerPtr;
	}
	std::shared_ptr<sf::Texture> AssetManager::LoadTexture(const std::filesystem::path& FilePath)
	{
		auto Texture = LoadedTextures.find(FilePath.string());
		if (Texture != LoadedTextures.end())
		{
			return Texture->second;
		}

		auto NewTexture = std::make_shared<sf::Texture>();
		if (NewTexture->loadFromFile(FilePath))
		{
			LoadedTextures[FilePath.string()] = NewTexture;
			return NewTexture;
		}

		return nullptr;
	}
	void AssetManager::CleanCycle()
	{
		for (auto it = LoadedTextures.begin(); it != LoadedTextures.end();)
		{
			if (it->second.use_count() == 1)
			{
				std::string Message = "Texture " + it->first + " is no longer used, removing from memory.";
				WriteLog(GLog, GLoglevel, Message);
				//it = LoadedTextures.erase(it);
				++it;
			}
			else
			{
				++it;
			}
		}
	}
	AssetManager::AssetManager()
	{
	}
	
}

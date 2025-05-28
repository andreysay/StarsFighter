#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <filesystem>
#include <memory>

namespace SF
{
	class AssetManager
	{
	public:
		// Get the singleton instance of AssetManager
		static AssetManager& Get();

	public:
		std::shared_ptr<sf::Texture> LoadTexture(const std::filesystem::path& FilePath);
		void CleanCycle();
		void SetAssetRootDirectory(const std::filesystem::path& AssetRootDirectory);

		AssetManager(const AssetManager&) = delete;
		AssetManager& operator=(const AssetManager&) = delete;
		~AssetManager() = default;
	protected:
		AssetManager();
		
		//void LoadFont(const std::string& FontName, const std::filesystem::path& FilePath);
		//void LoadSound(const std::string& SoundName, const std::filesystem::path& FilePath);
		//sf::Texture& GetTexture(const std::string& TextureName);
		//sf::Font& GetFont(const std::string& FontName);
		//sf::SoundBuffer& GetSound(const std::string& SoundName);
	private:
		static std::unique_ptr<AssetManager> AssetManagerPtr;
		std::unordered_map<std::string, std::shared_ptr<sf::Texture> > LoadedTextures;
		//std::unordered_map<std::string, sf::Font> Fonts;
		//std::unordered_map<std::string, sf::SoundBuffer> Sounds;
		std::filesystem::path RootDirectory;
	};
}
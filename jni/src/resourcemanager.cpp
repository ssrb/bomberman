#include "resourcemanager.hpp"

namespace bomberman {
namespace resources {

	ResourceManager *ResourceManager::_Singleton;

	std::shared_ptr<SDL_Texture> ResourceManager::GetTexture(const std::string &filename) const
	{
		return std::shared_ptr<SDL_Texture>(IMG_LoadTexture(_renderer, filename.c_str()), SDL_DestroyTexture);
		
		// std::shared_ptr<SDL_Texture> LoadTexture(SDL_Renderer* renderer, std::string filename)
		// {
		// 	auto surface = IMG_Load(filename.c_str());
		// 	auto result = LoadTexture(renderer, surface);
		// 	SDL_FreeSurface(surface);
		// 	return result;
		// }
	}

	std::shared_ptr<TTF_Font> ResourceManager::GetFont(const std::string &fontName, int ptSize) const
	{
		return std::shared_ptr<TTF_Font>(TTF_OpenFont(fontName.c_str(), ptSize), TTF_CloseFont);
	}

	std::shared_ptr<Mix_Chunk> ResourceManager::GetMixChunk(const std::string &audioFile) const
	{
	 	return std::shared_ptr<Mix_Chunk>(Mix_LoadWAV("sound/explosion.wav"), Mix_FreeChunk);
	}
}
}
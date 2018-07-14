#include "resourcemanager.hpp"

namespace bomberman {
namespace resources {

	ResourceManager *ResourceManager::_Singleton;

	std::shared_ptr<SDL_Texture> ResourceManager::GetTexture(const std::string &filename) const
	{		
		return std::shared_ptr<SDL_Texture>(IMG_LoadTexture(_renderer, filename.c_str()), SDL_DestroyTexture);		
	}

	std::shared_ptr<SDL_Texture> ResourceManager::GetTexture(const std::string &filename, uint32_t colorKey) const
	{
	 	auto surface = IMG_Load(filename.c_str());
	 	SDL_SetColorKey(surface, SDL_TRUE, colorKey);
	 	auto texture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(_renderer, surface), SDL_DestroyTexture);
	 	SDL_FreeSurface(surface);
	 	return texture;
	}

	std::shared_ptr<TTF_Font> ResourceManager::GetFont(const std::string &fontName, int ptSize) const
	{
		return std::shared_ptr<TTF_Font>(TTF_OpenFont(fontName.c_str(), ptSize), TTF_CloseFont);
	}

	std::shared_ptr<Mix_Chunk> ResourceManager::GetMixChunk(const std::string &audioFile) const
	{
	 	return std::shared_ptr<Mix_Chunk>(Mix_LoadWAV(audioFile.c_str()), Mix_FreeChunk);

	 	// if (!_bombPlaceSound)
		// {
		//  printlog("Mix_LoadWAV: %s\n", Mix_GetError());
		// }
	}
}
}
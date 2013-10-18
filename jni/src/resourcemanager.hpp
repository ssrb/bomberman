#pragma once

#include <memory>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

namespace bomberman {
namespace resources {

	class ResourceManager
	{
		public:
			static void Initialize(SDL_Renderer *iRenderer)
			{
				_Singleton = new ResourceManager(iRenderer);
			} 
			static ResourceManager *GetSingleton() 
			{
				return _Singleton;
			}
			std::shared_ptr<SDL_Texture> GetTexture(const std::string &filename) const;
			std::shared_ptr<TTF_Font> GetFont(const std::string &fontName, int ptSize) const;
			std::shared_ptr<Mix_Chunk> GetMixChunk(const std::string &audioFile) const;
		private:
			ResourceManager(SDL_Renderer *iRenderer)
				: _renderer(iRenderer)
			{
			}
			SDL_Renderer *_renderer;
			static ResourceManager *_Singleton;
	};
}
}
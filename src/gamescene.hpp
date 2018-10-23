#pragma once

#include "scene_interface.hpp"
#include "map.hpp"
#include "player.hpp"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <string>
#include <memory>
#include <list>
#include <array>
#include <map>

#include "player.hpp"

namespace bomberman {

struct PlayerConfig
{
	bool present;
	bool isComputer;
	std::string spriteName;
	std::string name;
	std::string aiScript;
};

typedef std::array<PlayerConfig, 4> PlayerConfigArray;

class GameScene : public SceneInterface
{
	public:
		GameScene(const PlayerConfigArray &playerConfig);
		virtual ~GameScene() {}
		virtual void Init(SDL_Window* window, SDL_Renderer* renderer);
		virtual void Update(const std::vector<InputState>& inputs, uint32_t timestamp);
		virtual void Render(SDL_Renderer *renderer);
		virtual bool Running();
		
		int GetVictor() const { return _victor; }

	protected:
		std::shared_ptr<Mix_Music> _music;
		std::shared_ptr<SDL_Texture> _background;	
		MapPtr _presentMap;

		template<typename T>
		class CircularBuffer {
		public:
			explicit CircularBuffer(size_t capacity)
				: _buffer(capacity + 1),
				_next(0),
				_first(0)
			{
			}

			void push(const T &x)
			{
				_buffer[_next] = x;
				if (++_next == (int)_buffer.size())
				{
					_next = 0;
				}

				if (_next == _first)
				{
					_buffer[_first] = T();
					if (++_first == (int)_buffer.size())
					{
						_first = 0;
					}
				}
			}

			T pop()
			{
				T x;

				if (!empty())
				{
					if (--_next == -1)
					{
						_next = _buffer.size() - 1;
					}
					std::swap(_buffer[_next], x);
				}
				
				return x;
			}

			bool empty() const
			{
				return _next == _first;
			}

		private:
			std::vector<T> _buffer;
			int _next, _first;
		};

		PlayerConfigArray _playerConfig;
		CircularBuffer<std::pair<uint32_t, MapPtr>> _pastMaps;

		bool _running;
		int _victor;

		PlayerId _playerIds[4];

		void InitPlayers(SDL_Renderer* renderer);
		void InitBlocks(SDL_Renderer* renderer);

		void RenderPlayerDashBoard(const bestiary::PlayerPtr &iPlayer, int pos, SDL_Renderer* renderer);

		void BackThroughTime();
};

}

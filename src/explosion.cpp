#include "explosion.hpp"
#include "block.hpp"
#include "softblock.hpp"
#include "bomb.hpp"
#include "propbomb.hpp"
#include "player.hpp"
#include "computer.hpp"
#include "constants_resolution.hpp"
#include "constants_game.hpp"
#include "resourcemanager.hpp"

// SDL
#include <SDL_image.h>

using bomberman::architecture::Block;
using bomberman::architecture::SoftBlock;
using bomberman::resources::ResourceManager;

namespace bomberman {
namespace arsenal {

	namespace {
		const int kExplosionTimer = 200;
	}

	ExplosionPtr Explosion::Create(int iCreationTime, Orientation orientation) {
		auto explosion = std::make_shared<Explosion>();
        explosion->id = constants::EXPLOSIONID;
		explosion->_timeout = iCreationTime + kExplosionTimer;
		explosion->_stage = 0;
		explosion->zlevel = constants::EXPLOSION_ZLEVEL;
		explosion->_orientation = orientation;
		explosion->_explosion = ResourceManager::GetSingleton()->GetTexture("drawable/flare.png");
		return explosion;
	}

	void Explosion::Evolve(const std::vector<InputState>& /*iInputs*/, Uint32 iTimestamp, const MapConstPtr &iPresentMap, const MapPtr &iFutureMap) const
	{
		auto explosion = std::make_shared<Explosion>(*this);
		if (iTimestamp > _timeout) 
		{
			explosion->_stage++;
			explosion->_timeout = iTimestamp + kExplosionTimer;
		}

		if (_stage < 4)
		{
			explosion->active = true;
			iFutureMap->SetEntity(explosion);
		}
	}

	void Explosion::Interact(const std::vector<InputState>& iInputs, Uint32 iTimestamp, const EntitySet &iOthers)
	{
		using bomberman::arsenal::Bomb;
		using bomberman::arsenal::PropBomb;
		using bomberman::architecture::SoftBlock;
		using bomberman::bestiary::Player;
		using bomberman::bestiary::Computer;

		for (auto other : iOthers)
		{
			if(typeid(*other) == typeid(PropBomb))
			{
				auto bomb = std::dynamic_pointer_cast<PropBomb>(other);
				bomb->Detonate();
			}
			else if(typeid(*other) == typeid(Bomb))
			{
				auto bomb = std::dynamic_pointer_cast<Bomb>(other);
				bomb->Detonate();
			}
			else if(typeid(*other) == typeid(Explosion))
			{
				auto explosion = std::dynamic_pointer_cast<Explosion>(other);
				if (explosion->_stage > _stage)
				{
					explosion->active = false;
				}
			}
			else if(typeid(*other) == typeid(Player))
			{
				auto player = std::dynamic_pointer_cast<Player>(other);
				player->Kill();
			}
			else if(typeid(*other) == typeid(Computer))
			{
				auto player = std::dynamic_pointer_cast<Computer>(other);
				player->Kill();
			}
			else if (typeid(*other) == typeid(SoftBlock))
			{
				auto softblock = std::dynamic_pointer_cast<SoftBlock>(other);
				softblock->Kill();
			}
		}
	}

	void Explosion::Render(SDL_Renderer *iRenderer) const 
	{
		using namespace bomberman::constants;

		SDL_Rect srcRect;
		srcRect.w = 16;
		srcRect.h = 32;
		srcRect.x = _stage * srcRect.w;
		srcRect.y = (int)_orientation * srcRect.h;
		
		SDL_Rect r;
		r.w = TILE_WIDTH;
		r.h = TILE_HEIGHT;
		r.x = GetX() * TILE_WIDTH + MAP_X;
		r.y = GetY() * TILE_WIDTH + MAP_Y;
		
		SDL_RenderCopy(iRenderer, _explosion.get(), &srcRect, &r);
	}

}
}

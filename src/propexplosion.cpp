#include "propexplosion.hpp"
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

		bool CanPropagate(const MapConstPtr &iMap, int x, int y)
		{
			if (iMap->CheckPosition(x, y) == Map::BOUNDARY)
			{
				return false;
			}

			for (auto entity : iMap->GetEntities(x, y)) 
			{
				if (typeid(*entity) == typeid(Block))
				{
					return false;
				}
			}

			return true;
		}
	}

	PropExplosionPtr PropExplosion::Create(int iCreationTime) {
		auto explosion = std::make_shared<PropExplosion>();
        explosion->id = constants::EXPLOSIONID;
		explosion->_timeout = iCreationTime + kExplosionTimer;
		explosion->_stage = 0;
		explosion->zlevel = constants::EXPLOSION_ZLEVEL;
		explosion->_propagation = IsoTropic;
		explosion->_willPropagate = true;

		explosion->_explosion[0] = ResourceManager::GetSingleton()->GetTexture("drawable/explosion1.png");
		explosion->_explosion[1] = ResourceManager::GetSingleton()->GetTexture("drawable/explosion2.png");
		explosion->_explosion[2] = ResourceManager::GetSingleton()->GetTexture("drawable/explosion3.png");
		explosion->_explosion[3] = ResourceManager::GetSingleton()->GetTexture("drawable/explosion4.png");

		return explosion;
	}

	void PropExplosion::Evolve(const std::vector<InputState>& /*iInputs*/, Uint32 iTimestamp, const MapConstPtr &iPresentMap, const MapPtr &iFutureMap) const
	{
		if (iTimestamp < _timeout) 
		{
			auto explosion = std::make_shared<PropExplosion>(*this);
			explosion->active = true;
		  	iFutureMap->SetEntity(explosion);
		}
		else
		{
			if (_stage == 0)
			{
				if (_willPropagate)
				{
					Propagate(iTimestamp, iPresentMap, iFutureMap);
				}
			}
			
			if (_stage < 4)
			{
				auto explosion = std::make_shared<PropExplosion>(*this);
				explosion->active = true;
				explosion->_timeout = iTimestamp + kExplosionTimer;
				explosion->_stage = explosion->_stage + 1;
				iFutureMap->SetEntity(explosion);
			}
		}
	}

	void PropExplosion::Interact(const std::vector<InputState>& iInputs, Uint32 iTimestamp, const EntitySet &iOthers)
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
			else if(typeid(*other) == typeid(PropExplosion))
			{
				auto explosion = std::dynamic_pointer_cast<PropExplosion>(other);
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
				_willPropagate = false;
				softblock->Kill();
			}
		}
	}

	void PropExplosion::Render(SDL_Renderer *iRenderer) const 
	{
		if (_stage >= 4)
		{
			return;
		}

		using namespace bomberman::constants;
		
		SDL_Rect r;
		r.w = TILE_WIDTH;
		r.h = TILE_HEIGHT;
		r.x = GetX() * TILE_WIDTH + MAP_X;
		r.y = GetY() * TILE_WIDTH + MAP_Y;
		
		SDL_RenderCopy(iRenderer, _explosion[_stage].get(), nullptr, &r);
	}

	 void PropExplosion::Propagate(Uint32 iTimestamp, const MapConstPtr &iPresentMap, const MapPtr &iFutureMap) const
	 {
	 	switch(_propagation)
	 	{
	 		case IsoTropic:

 				if (CanPropagate(iPresentMap, GetX() + 1, GetY()))
 				{
 					auto explosion = std::make_shared<PropExplosion>(*this);
 					explosion->active = true;
				    explosion->_timeout = iTimestamp + kExplosionTimer;
				    explosion->SetX(GetX() + 1);
				    explosion->_propagation = Right;
				    iFutureMap->SetEntity(explosion);	  
 				}

 				if (CanPropagate(iPresentMap, GetX() - 1, GetY()))
 				{
 					auto explosion = std::make_shared<PropExplosion>(*this);
 					explosion->active = true;
				    explosion->_timeout = iTimestamp + kExplosionTimer;
				    explosion->SetX(GetX() - 1);
				    explosion->_propagation = Left;
				    iFutureMap->SetEntity(explosion);	  
 				}

				if (CanPropagate(iPresentMap, GetX(), GetY() + 1))
 				{
 					auto explosion = std::make_shared<PropExplosion>(*this);
 					explosion->active = true;
				    explosion->_timeout = iTimestamp + kExplosionTimer;
				    explosion->SetY(GetY() + 1);
				    explosion->_propagation = Down;
				    iFutureMap->SetEntity(explosion);	  
 				}

 				if (CanPropagate(iPresentMap, GetX(), GetY() - 1))
 				{
 					auto explosion = std::make_shared<PropExplosion>(*this);
 					explosion->active = true;
				    explosion->_timeout = iTimestamp + kExplosionTimer;
				    explosion->SetY(GetY() - 1);
				    explosion->_propagation = Up;
				    iFutureMap->SetEntity(explosion);	  
 				}

	 			return;

	 		case Up:

	 			if (CanPropagate(iPresentMap, GetX(), GetY() - 1))
 				{
 					auto explosion = std::make_shared<PropExplosion>(*this);
 					explosion->active = true;
				    explosion->_timeout = iTimestamp + kExplosionTimer;
				    explosion->SetY(GetY() - 1);
				    explosion->_propagation = Up;
				    iFutureMap->SetEntity(explosion);	  
 				}

 				return;

	 		case Down:

	 			if (CanPropagate(iPresentMap, GetX(), GetY() + 1))
 				{
 					auto explosion = std::make_shared<PropExplosion>(*this);
 					explosion->active = true;
				    explosion->_timeout = iTimestamp + kExplosionTimer;
				    explosion->SetY(GetY() + 1);
				    explosion->_propagation = Down;
				    iFutureMap->SetEntity(explosion);	  
 				}

 				return;

	 		case Left:

				if (CanPropagate(iPresentMap, GetX() - 1, GetY()))
 				{
 					auto explosion = std::make_shared<PropExplosion>(*this);
 					explosion->active = true;
				    explosion->_timeout = iTimestamp + kExplosionTimer;
				    explosion->SetX(GetX() - 1);
				    explosion->_propagation = Left;
				    iFutureMap->SetEntity(explosion);	  
 				}

				return;

	 		case Right:

	 			if (CanPropagate(iPresentMap, GetX() + 1, GetY()))
 				{
 					auto explosion = std::make_shared<PropExplosion>(*this);
 					explosion->active = true;
				    explosion->_timeout = iTimestamp + kExplosionTimer;
				    explosion->SetX(GetX() + 1);
				    explosion->_propagation = Right;
				    iFutureMap->SetEntity(explosion);	  
 				}

 				return;
	 	}
	 }
}
}

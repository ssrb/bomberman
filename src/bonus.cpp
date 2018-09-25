#include "bonus.hpp"
#include "constants_game.hpp"
#include "constants_resolution.hpp"
#include "printlog.hpp"
#include "resourcemanager.hpp"

// STL, libstdc++
#include <array>

// SDL
#include <SDL_image.h>

using bomberman::resources::ResourceManager;

namespace bomberman {
namespace bonus {

	BonusPtr Bonus::Create() 
	{
		auto bonus = std::make_shared<Bonus>();
        bonus->id = constants::BONUSID;
		bonus->zlevel = constants::BONUS_ZLEVEL;
		bonus->elevel = -1;
		bonus->_state = Available;

		std::array<double, 3> probabilities;
		probabilities[PROPBOMB] = 0.10;
		probabilities[BOMBCOUNT] = 0.45;
		probabilities[BOMBSTRENGTH] = 0.45;
		
		double number = (double)rand() / (double)RAND_MAX;
		double soFar = 0;
		for (int i = 0;i < probabilities.size(); i++)
		{
			soFar += probabilities[i];
			printlog("number = %lf, soFar = %lf\n", number, soFar);
			if (number < soFar)
			{
				bonus->_bonusType = (BonusType)i;
				break;
			}
		}

		 bonus->_bonusTexture.insert(std::make_pair(Bonus::PROPBOMB, ResourceManager::GetSingleton()->GetTexture("drawable/propbombbonus.png")));
		 bonus->_bonusTexture.insert(std::make_pair(Bonus::BOMBCOUNT, ResourceManager::GetSingleton()->GetTexture("drawable/bombbonus.png")));
		 bonus->_bonusTexture.insert(std::make_pair(Bonus::BOMBSTRENGTH, ResourceManager::GetSingleton()->GetTexture("drawable/firebonus.png")));

		return bonus;
	}

	void Bonus::Evolve(const std::vector<InputState>& /*iInputs*/, uint32_t /*iTimestamp*/, const MapConstPtr &/*iPresentMap*/, const MapPtr &iFutureMap) const
	{
		if (_state == Available) 
		{
			iFutureMap->SetEntity(std::make_shared<Bonus>(*this));
		}
	}

	void Bonus::Render(SDL_Renderer *iRenderer) const 
	{
		using namespace bomberman::constants;
		
		SDL_Rect r;
		r.w = TILE_WIDTH;
		r.h = TILE_HEIGHT;
		r.x = GetX() * TILE_WIDTH + MAP_X;
		r.y = GetY() * TILE_WIDTH + MAP_Y;
		
		SDL_RenderCopy(iRenderer, _bonusTexture.find(_bonusType)->second.get(), nullptr, &r);
	}
}
}

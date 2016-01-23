#include "propbomb.hpp"
#include "propexplosion.hpp"
#include "constants_resolution.hpp"
#include "constants_game.hpp"
#include "umpire.hpp"

// SDL
#include <SDL_image.h>

namespace bomberman {
namespace arsenal {

	PropBombPtr PropBomb::Create(int iTimeout, int iStrength, int iPlayerId) {
		auto bomb = std::make_shared<PropBomb>();
        bomb->id = constants::BOMBID;
		bomb->_timeout = iTimeout;
		bomb->_strength = iStrength;
		bomb->zlevel = constants::BOMB_ZLEVEL;
		bomb->_detonating = false;
		bomb->_frameId = 0;
		bomb->_nextFrameDueTime = 0;
		bomb->_playerId = iPlayerId;
		//_Bomb = std::shared_ptr<SDL_Texture>(IMG_LoadTexture(iRenderer, "drawable/propbomb.png"), SDL_DestroyTexture);
		return bomb;
	}

	void PropBomb::Evolve(const std::vector<InputState>& /*iInputs*/, uint32_t iTimestamp, const MapConstPtr &/*iPresentMap*/, const MapPtr &iFutureMap) const
	{
		if (iTimestamp >= _timeout || _detonating)
		{
			auto umpire = std::static_pointer_cast<Umpire>(iFutureMap->GetEntity(constants::UMPIRE));
			umpire->DecrementBombCount(_playerId);

			auto blast = PropExplosion::Create(iTimestamp);
			blast->SetX(this->GetX());
			blast->SetY(this->GetY());
			iFutureMap->SetEntity(blast);
		} 
		else 
		{
			auto bomb = std::make_shared<PropBomb>(*this);

			if (_nextFrameDueTime < iTimestamp)
			{
				bomb->_frameId++;
				bomb->_frameId %= 3;
				bomb->_nextFrameDueTime = iTimestamp + constants::BOMB_FRAME_UPDATE_DELAY;
			}

			iFutureMap->SetEntity(bomb);
		}
	}

	void PropBomb::Render(SDL_Renderer *iRenderer) const 
	{
		using namespace bomberman::constants;
		
		SDL_Rect sourceRect;
		sourceRect.w = 16;
		sourceRect.h = 32;
		sourceRect.x = 0 + _frameId * 16;
		sourceRect.y = 0;

		SDL_Rect r;
		r.w = TILE_WIDTH;
		r.h = TILE_HEIGHT;
		r.x = mx * SUBTILE_WIDTH + MAP_X;
		r.y = my * SUBTILE_WIDTH + MAP_Y;

		SDL_RenderCopy(iRenderer, _bomb.get(), &sourceRect, &r);
	}

	void PropBomb::Detonate()
	{
		_detonating = true;
	}
}
}

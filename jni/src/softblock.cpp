#include "softblock.hpp"
#include "constants.hpp"
#include "bonus.hpp"

// SDL
#include <SDL_image.h>

using bomberman::bonus::Bonus;

namespace bomberman {
namespace architecture {

	SoftBlockPtr SoftBlock::Create(double iBonusProbability) 
	{
		auto block = std::make_shared<SoftBlock>();
		block->zlevel = 2;
		block->elevel = constants::SOFTBLOCK_ELEVEL;
		block->isAlive = true;
		block->_bonusProbability = iBonusProbability;
		//_SoftBlock = std::shared_ptr<SDL_Texture>(IMG_LoadTexture(iRenderer, "drawable/softblock.png"), SDL_DestroyTexture);
		return block;
	}

	void SoftBlock::Evolve(const std::vector<InputState>& /*iInputs*/, uint32_t /*iTimestamp*/, const MapConstPtr &/*iPresentMap*/, const MapPtr &iFutureMap) const
	{
		if (!isAlive)
		{
			if (rand() < RAND_MAX * _bonusProbability) 
			{
				auto bonus = Bonus::Create();
				bonus->x = x;
				bonus->y = y;
				iFutureMap->SetEntity(bonus);
			}
			return;
		}

		iFutureMap->SetEntity(std::make_shared<SoftBlock>(*this));
	}

	void SoftBlock::Render(SDL_Renderer *iRenderer) const 
	{
		using namespace bomberman::constants;
		
		SDL_Rect r;
		r.w = TILE_WIDTH;
		r.h = TILE_HEIGHT;
		r.x = x * TILE_WIDTH + MAP_X;	// <- just for overscan
		r.y = y * TILE_WIDTH + MAP_Y;
		
		SDL_RenderCopy(iRenderer, _softBlock.get(), nullptr, &r);
	}

	void SoftBlock::Kill()
	{
		isAlive = false;
	}
}
}

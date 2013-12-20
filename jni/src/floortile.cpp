#include "floortile.hpp"
#include "constants_resolution.hpp"
#include "constants_game.hpp"

// SDL
#include <SDL_image.h>

namespace bomberman {
namespace architecture {

	FloorTilePtr FloorTile::Create() 
	{
		auto floorTile = std::make_shared<FloorTile>();
		floorTile->zlevel = constants::FLOOR_ZLEVEL;
		floorTile->elevel = constants::FLOOR_ELEVEL;
		//_FloorTile = std::shared_ptr<SDL_Texture>(IMG_LoadTexture(iRenderer, "drawable/floor.png"), SDL_DestroyTexture);
		return floorTile;
	}

	void FloorTile::Evolve(const std::vector<InputState>& /*iInputs*/, uint32_t /*iTimestamp*/, const MapConstPtr &/*iPresentMap*/, const MapPtr &iFutureMap) const
	{
		iFutureMap->SetEntity(std::make_shared<FloorTile>(*this));
	}

	void FloorTile::Render(SDL_Renderer *iRenderer) const 
	{
		using namespace bomberman::constants;
		
		SDL_Rect r;
		r.w = TILE_WIDTH;
		r.h = TILE_HEIGHT;
		r.x = x * TILE_WIDTH + MAP_X;	// <- just for overscan
		r.y = y * TILE_WIDTH + MAP_Y;

		SDL_RenderCopy(iRenderer, _floorTile.get(), nullptr, &r);
	}
}
}
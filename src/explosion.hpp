#pragma once

#include "entity.hpp"

// STL - libstdc++
#include <memory>

struct SDL_Texture;

namespace bomberman {
namespace arsenal {

	class Explosion;
	typedef std::shared_ptr<Explosion> ExplosionPtr;
	
	class Explosion : public Entity {
		public:
			enum Orientation 
			{
				Vertical,
				Horizontal,
				IsoTropic
			};

			static ExplosionPtr Create(int iTimeout, Orientation orientation);
			virtual void Evolve(const std::vector<InputState>& iInputs, Uint32 iTimestamp, const MapConstPtr &iPresentMap, const MapPtr &iFutureMap) const;
			virtual void Interact(const std::vector<InputState>& iInputs, Uint32 iTimestamp, const EntitySet &iOthers);
			virtual void Render(SDL_Renderer*) const;
		
		private:
			int _timeout;
			int _stage;
			Orientation _orientation;
			std::shared_ptr<SDL_Texture> _explosion;
	};
}
}

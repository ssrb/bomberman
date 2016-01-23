#include "menuscene.hpp"
#include "constants_resolution.hpp"
#include "utils.hpp"
#include "resourcemanager.hpp"

#include <algorithm>

using bomberman::resources::ResourceManager;

namespace bomberman {

MenuScene::MenuScene()
{
}

void MenuScene::Init(SDL_Window* window, SDL_Renderer* renderer)
{
	auto font = ResourceManager::GetSingleton()->GetFont("drawable/Gamegirl.ttf", 16 * constants::SPRITE_MAGNIFICATION);

	_selectionTwink = std::shared_ptr<Mix_Chunk>(Mix_LoadWAV("sound/select.wav"), Mix_FreeChunk);
	_background = ResourceManager::GetSingleton()->GetTexture("drawable/mainback.png");
	_bombcursor = ResourceManager::GetSingleton()->GetTexture("drawable/bombcursor.png");

	_newGame = utils::DrawString(renderer, font, "New Game", utils::MakeColor(0xffffffff));
	_credits = utils::DrawString(renderer, font, "Credits", utils::MakeColor(0xffffffff));

	_frameId = 0;
	_nextFrameDueTime = 0;

	selection = 0;

	_running = true;
}

void MenuScene::Update(const std::vector<InputState>& inputs, uint32_t timestamp)
{
	if (_nextFrameDueTime < timestamp)
	{
		_frameId++;
		_frameId %= 3;
		_nextFrameDueTime = timestamp + 150;
	}

	for(int i = 0; i < inputs.size(); i++)
	{
		if (inputs[i].GetButtonPressed(InputState::UP))
		{	
			Mix_PlayChannel(-1, _selectionTwink.get(), 0);
			selection = std::max(0, selection - 1);
		}

		if (inputs[i].GetButtonPressed(InputState::DOWN))
		{
			Mix_PlayChannel(-1, _selectionTwink.get(), 0);
			selection = std::min(1, selection + 1);
		}

		if (inputs[i].GetButtonPressed(InputState::B))
		{
			_running = false;

		}
	}
}

void MenuScene::Render(SDL_Renderer *renderer)
{	
	utils::DrawImage(renderer, _background, 0, 0, constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT);

	utils::DrawImage(renderer, _newGame, 300 * constants::SPRITE_MAGNIFICATION, 150 * constants::SPRITE_MAGNIFICATION);
	utils::DrawImage(renderer, _credits, 300 * constants::SPRITE_MAGNIFICATION, 165 * constants::SPRITE_MAGNIFICATION);

	SDL_Rect sourceRect;
	sourceRect.w = 16;
	sourceRect.h = 16;
	sourceRect.x = 0 + _frameId * 16;
	sourceRect.y = 0;

	SDL_Rect r;
	r.w = 16 * constants::SPRITE_MAGNIFICATION;
	r.h = 16 * constants::SPRITE_MAGNIFICATION;
	r.x = 284 * constants::SPRITE_MAGNIFICATION;
	r.y = 150 * constants::SPRITE_MAGNIFICATION + selection * 15 * constants::SPRITE_MAGNIFICATION;

	SDL_RenderCopy(renderer, _bombcursor.get(), &sourceRect, &r);
}

bool MenuScene::Running()
{
	return _running;
}

}
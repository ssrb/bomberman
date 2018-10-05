#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <map>
#include <memory>

#include "inputstate.hpp"
#include "constants_resolution.hpp"
#include "constants_input.hpp"
#include "printlog.hpp"
#include "gamescene.hpp"
#include "menuscene.hpp"
#include "setupscene.hpp"
#include "fadescene.hpp"
#include "victoryscene.hpp"
#include "resourcemanager.hpp"

using bomberman::resources::ResourceManager;

void PollEvents(std::vector<InputState> &oInputState);

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static std::map<int, InputState::Key> keyMap;

void run(std::shared_ptr<bomberman::SceneInterface> scene)
{
	std::vector<InputState> inputState(4);
	Uint32 time = SDL_GetTicks();
	scene->Init(window, renderer);
	
	while (scene->Running())
	{
	 	PollEvents(inputState);

		Uint32 now = SDL_GetTicks();
		
		scene->Update(inputState, now);

		if (SDL_GetTicks() - time > 12)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);
			scene->Render(renderer);
			SDL_RenderPresent(renderer);
			time = SDL_GetTicks();
		}
	}
}

void PollEvents(std::vector<InputState> &oInputState)
{
	SDL_Event e;

	for (int i=0; i<4; i++)
	for (auto keyIter = keyMap.begin(); keyIter != keyMap.end(); keyIter++)
	{
		oInputState[i].SetButtonPressed(keyIter->second, false);
		oInputState[i].SetButtonReleased(keyIter->second, false);
	}

	while ( SDL_PollEvent(&e) )
	{
		auto inputState = &oInputState[0];
		
		if (e.type == SDL_QUIT)
		{
			exit(0);
		}
		else if (e.type == SDL_FINGERUP)
		{
            printlog("%d UP\n", e.tfinger.fingerId);
			inputState->SetFingered(false);
		}
		else if (e.type == SDL_FINGERDOWN)
		{
            printlog("%d DOWN\n", e.tfinger.fingerId);
			inputState->SetFingered(true);
			inputState->SetFingerX(e.tfinger.x);
			inputState->SetFingerY(e.tfinger.y);
		}
		else if (e.type == SDL_KEYDOWN)
		{
			auto keyIter = keyMap.find(e.key.keysym.sym);
			if ( keyIter != keyMap.end() )
			{
				inputState->SetButtonPressed(keyIter->second, true);
				inputState->SetButtonState(keyIter->second, true);
			}
		}
		else if (e.type == SDL_KEYUP)
		{
			auto keyIter = keyMap.find(e.key.keysym.sym);
			if ( keyIter != keyMap.end() )
			{
				inputState->SetButtonReleased(keyIter->second, true);
				inputState->SetButtonState(keyIter->second, false);
			}
		}
	}
}

void game()
{
	// This is where the game's storyboard is encoded
	while (true)
	{
		std::shared_ptr<bomberman::MenuScene> menuScene(new bomberman::MenuScene());
		run(menuScene);

		if (menuScene->GetSelection() == bomberman::MenuScene::NEWGAME)
		{

			std::shared_ptr<bomberman::SetupScene> setupScene(new bomberman::SetupScene());
			run(setupScene);
			
			std::shared_ptr<bomberman::GameScene> ts(new bomberman::GameScene(setupScene->GetConfig()));
			std::shared_ptr<bomberman::FadeScene> cover(new bomberman::FadeScene(ts));
			run(cover);

			std::shared_ptr<bomberman::VictoryScene> vs(new bomberman::VictoryScene(ts->GetVictor()));
			std::shared_ptr<bomberman::FadeScene> fs(new bomberman::FadeScene(vs));
			run(fs);
		}
		else
		{
		}
	}
	
    while (true) {
		bomberman::PlayerConfigArray players;
        
		players[0].name = "Athos";
		players[0].spriteName = "drawable/miku2.png";
		players[0].present = true;
		players[0].isComputer = false;
		players[0].aiScript = "aiscripts/example.lua";
        
		players[1].name = "Porthos";
		players[1].spriteName = "drawable/duckie.png";
		players[1].present = true;
		players[1].isComputer = true;
		players[1].aiScript = "aiscripts/example.lua";
        
		players[2].name = "Aramis";
		players[2].spriteName = "drawable/manji.png";
		players[2].present = false;
		players[2].isComputer = true;
		players[2].aiScript = "aiscripts/example.lua";
        
		players[3].name = "D'Artagnan";
		players[3].spriteName = "drawable/whitebbman.png";
		players[3].present = false;
		players[3].isComputer = true;
		players[3].aiScript = "aiscripts/example.lua";
		
		
		std::shared_ptr<bomberman::GameScene> ts(new bomberman::GameScene(players));
		std::shared_ptr<bomberman::FadeScene> cover(new bomberman::FadeScene(ts));
        
		run(cover);
        
		std::shared_ptr<bomberman::VictoryScene> vs(new bomberman::VictoryScene(ts->GetVictor()));
		std::shared_ptr<bomberman::FadeScene> fs(new bomberman::FadeScene(vs));
        
		run(fs);
    }
}

int main(int argc, char** argv)
{
	keyMap[SDLK_UP] = InputState::UP;
	keyMap[SDLK_DOWN] = InputState::DOWN;
	keyMap[SDLK_LEFT] = InputState::LEFT;
	keyMap[SDLK_RIGHT] = InputState::RIGHT;
	keyMap[SDLK_a] = InputState::A;
	keyMap[SDLK_s] = InputState::B;
	keyMap[SDLK_z] = InputState::X;
	keyMap[SDLK_x] = InputState::Y;
	keyMap[SDLK_1] = InputState::L1;
	keyMap[SDLK_3] = InputState::L2;
	keyMap[SDLK_2] = InputState::R1;
	keyMap[SDLK_4] = InputState::R2;
	keyMap[SDLK_j] = InputState::L1;
	keyMap[SDLK_k] = InputState::L2;
	keyMap[SDLK_l] = InputState::R1;
	keyMap[SDLK_m] = InputState::R2;
	keyMap[SDLK_SPACE] = InputState::START;

	SDL_Init(SDL_INIT_EVERYTHING);   // Initialize SDL2
	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
	TTF_Init();

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) 
	{
		printlog("Mix_OpenAudio: %s\n", Mix_GetError());
	}
	using namespace bomberman::constants;

	int WIDTH = SCREEN_WIDTH, HEIGHT = SCREEN_HEIGHT;

	printlog("Window size: %d x %d!\n", WIDTH, HEIGHT);
    
	// Create an application window with the following settings:
	window = SDL_CreateWindow(
		"Bomberman",                 
		SDL_WINDOWPOS_UNDEFINED,           
		SDL_WINDOWPOS_UNDEFINED,           
		WIDTH,
		HEIGHT,
		SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL|SDL_WINDOW_ALLOW_HIGHDPI
	);
    
    

	// Check that the window was successfully made
	if(window == NULL)
	{   
		// In the event that the window could not be made...
		printlog("Could not create window: %s\n", SDL_GetError());
		return 1;
	}
	
	printlog("Beginning game with window=%p\n", window);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	ResourceManager::Initialize(renderer);

	try
	{	
		game();
	}
	catch(std::exception e)
	{
		printlog("Caught a std::exception! %s\n", e.what());
	}
	catch(...)
	{
		printlog("Caught an unknown exception!\n");
	}

	SDL_DestroyRenderer(renderer);

	TTF_Quit();

	Mix_CloseAudio();

	Mix_Quit();

	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit(); 
	
	printlog("Success!\n");
	
	return 0;
}

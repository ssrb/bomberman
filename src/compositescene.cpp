#include "compositescene.hpp"

CompositeScene::CompositeScene()
{
}

CompositeScene::~CompositeScene()
{
}

void CompositeScene::Init(SDL_Window *window, SDL_Renderer *renderer)
{
	for (auto scene : scenes)
	{
		scene->Init(window, renderer);
	};

	this->window = window;
	this->renderer = renderer;
}

void CompositeScene::Update(const std::vector<InputState> &inputs, Uint32 timestamp)
{
	for (auto scene : scenes)
	{
		scene->Update(inputs, timestamp);
	};

	scenes.remove_if([](std::shared_ptr<SceneInterface> scene) { return !scene->Running(); });
}

void CompositeScene::Render(SDL_Renderer *renderer)
{
	for (auto scene : scenes)
	{
		scene->Render(renderer);
	};
}

bool CompositeScene::Running() const
{
	return !scenes.empty();
}

void CompositeScene::AddScene(std::shared_ptr<SceneInterface> scene)
{
	scenes.push_front(scene);
}

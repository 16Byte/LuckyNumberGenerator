#include "SceneManager.hpp"

SceneManager::SceneManager()
    : currentScene(Scene::MainMenu), shouldExit(false)
{
}

void SceneManager::SetScene(Scene newScene)
{
    currentScene = newScene;
}

SceneManager::Scene SceneManager::GetCurrentScene() const
{
    return currentScene;
}

bool SceneManager::ShouldExit() const
{
    return shouldExit;
}

void SceneManager::RequestExit()
{
    shouldExit = true;
}

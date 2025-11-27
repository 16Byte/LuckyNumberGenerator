#include "MegaMillionsScene.hpp"
#include "raygui.h"

MegaMillionsScene::MegaMillionsScene(int screenWidth, SceneManager& sceneManager, MegaMillionsNumberGenerator* generator)
    : screenWidth(screenWidth), sceneManager(sceneManager), generator(generator)
{
}

void MegaMillionsScene::Draw()
{
    ClearBackground((Color){240, 240, 250, 255});

    // Title
    DrawText("MegaMillions Number Generator", 250, 50, 40, DARKBLUE);
    DrawRectangle(250, 100, 500, 3, DARKBLUE);

    float buttonY = 380.0f;
    float buttonWidth = 300.0f;
    float buttonHeight = 50.0f;
    float buttonX = (screenWidth - buttonWidth) / 2.0f;

    if (GuiButton((Rectangle){buttonX, buttonY + 140, buttonWidth, buttonHeight}, "Main Menu"))
        sceneManager.SetScene(SceneManager::Scene::MainMenu);
}

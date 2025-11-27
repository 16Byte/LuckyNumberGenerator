#include "PowerBallScene.hpp"
#include "raygui.h"

PowerBallScene::PowerBallScene(int screenWidth, SceneManager& sceneManager, PowerBallNumberGenerator* generator)
    : screenWidth(screenWidth), sceneManager(sceneManager), generator(generator)
{
}

void PowerBallScene::Draw()
{
    ClearBackground((Color){240, 240, 250, 255});

    // Title
    DrawText("PowerBall Number Generator", 250, 50, 40, DARKBLUE);
    DrawRectangle(250, 100, 500, 3, DARKBLUE);

    float buttonY = 380.0f;
    float buttonWidth = 300.0f;
    float buttonHeight = 50.0f;
    float buttonX = (screenWidth - buttonWidth) / 2.0f;

    if (GuiButton((Rectangle){buttonX, buttonY + 140, buttonWidth, buttonHeight}, "Main Menu"))
        sceneManager.SetScene(SceneManager::Scene::MainMenu);
}

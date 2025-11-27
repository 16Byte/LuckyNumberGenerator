#include "MainMenuScene.hpp"
#include "raygui.h"
#include <vector>

MainMenuScene::MainMenuScene(Texture2D powerballLogo, Texture2D megaMillionsLogo, int screenWidth, SceneManager& sceneManager)
    : powerballLogo(powerballLogo), megaMillionsLogo(megaMillionsLogo), screenWidth(screenWidth), sceneManager(sceneManager)
{
}

void MainMenuScene::Draw()
{
    ClearBackground((Color){240, 240, 250, 255});

    // Title
    DrawText("Lucky Number Generator", 250, 50, 40, DARKBLUE);
    DrawRectangle(250, 100, 500, 3, DARKBLUE);

    // Logo section
    float logoScale = 1.0f;
    float logoY = 140.0f;
    float logoSpacing = 150.0f;
        
    DrawTextureEx(powerballLogo, (Vector2){(screenWidth/2) + logoSpacing - (powerballLogo.width/2), logoY}, 0.0f, logoScale, WHITE);
    DrawTextureEx(megaMillionsLogo, (Vector2){(screenWidth/2) - logoSpacing - (megaMillionsLogo.width/2), logoY}, 0.0f, logoScale, WHITE);

    // Buttons
    float buttonY = 380.0f;
    float buttonWidth = 300.0f;
    float buttonHeight = 50.0f;
    float buttonX = (screenWidth - buttonWidth) / 2.0f;
        
    if (GuiButton((Rectangle){buttonX, buttonY, buttonWidth, buttonHeight}, "Generate PowerBall Numbers"))
    {
        sceneManager.SetScene(SceneManager::Scene::PowerBall_Generator);
    }
        
    if (GuiButton((Rectangle){buttonX, buttonY + 70, buttonWidth, buttonHeight}, "Generate MegaMillions Numbers"))
    {
        sceneManager.SetScene(SceneManager::Scene::MegaMillions_Generator);
    }
       
    if (GuiButton((Rectangle){buttonX, buttonY + 140, buttonWidth, buttonHeight}, "Quit Application"))
        sceneManager.RequestExit();
}

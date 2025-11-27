#define RAYGUI_IMPLEMENTATION
#include "MegaMillionsNumberGenerator.hpp"
#include "PowerBallNumberGenerator.hpp"
#include "FileManager.hpp"
#include "SceneManager.hpp"
#include "MainMenuScene.hpp"
#include "PowerBallScene.hpp"
#include "MegaMillionsScene.hpp"
#include <iostream>
#include "raylib.h"
#include <string>
#include "raygui.h"

using namespace std;

void InitData(FileManager& fm, LuckyNumberGenerator* NumGen, FileManager::LottoType lottoType)
{
    NumGen-> SetHistory(fm.GetFileContents(lottoType));
}

int main()
{
    const int screenWidth = 1000;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Lucky Number Generator");
    SetTargetFPS(60);

    // Load lottery logos
    Texture2D powerballLogo = LoadTexture("Assets/Sprites/powerball.png");
    Texture2D megaMillionsLogo = LoadTexture("Assets/Sprites/mega_millions.png");

    MegaMillionsNumberGenerator* MMNumGen = new MegaMillionsNumberGenerator();
    PowerBallNumberGenerator* PBNumGen = new PowerBallNumberGenerator();
    FileManager fm;

    InitData(fm, MMNumGen, FileManager::LottoType::MegaMillions);
    InitData(fm, PBNumGen, FileManager::LottoType::PowerBall);

    SceneManager sceneManager;

    // Create scene objects
    MainMenuScene mainMenu(powerballLogo, megaMillionsLogo, screenWidth, sceneManager);
    PowerBallScene powerBallScene(screenWidth, sceneManager, PBNumGen);
    MegaMillionsScene megaMillionsScene(screenWidth, sceneManager, MMNumGen);

    while (!sceneManager.ShouldExit()) //Application loop
    {
        BeginDrawing();

        if(WindowShouldClose())
            sceneManager.RequestExit();

        switch (sceneManager.GetCurrentScene())
        {
            case SceneManager::Scene::Default:
            case SceneManager::Scene::MainMenu:
            mainMenu.Draw();
            break;
            case SceneManager::Scene::MegaMillions_Generator:
            megaMillionsScene.Draw();
            break;
            case SceneManager::Scene::PowerBall_Generator:
            powerBallScene.Draw();
            break;
        }

        EndDrawing();
    }
    
    // Cleanup
    UnloadTexture(powerballLogo);
    UnloadTexture(megaMillionsLogo);
    CloseWindow();

    delete PBNumGen;
    delete MMNumGen;
    return 0;
}
#define RAYGUI_IMPLEMENTATION
#include "MegaMillionsNumberGenerator.hpp"
#include "PowerBallNumberGenerator.hpp"
#include "FileManager.hpp"
#include <iostream>
#include "raylib.h"
#include <string>
#include "raygui.h"

using namespace std;

enum class Scene {
    Default,
    MainMenu,
    PowerBall_Generator,
    MegaMillions_Generator,
};

Scene currentScene = Scene::MainMenu;
bool ShouldExitApplication = false;

void InitPowerBall(FileManager fm, PowerBallNumberGenerator* PBNumGen)
{
    auto powerballHistory = fm.GetFileContents(FileManager::LottoType::PowerBall);
    PBNumGen->SetHistory(powerballHistory);    
}

void InitMegaMillions(FileManager fm, MegaMillionsNumberGenerator* MMNumGen)
{
    auto megaMillionsHistory = fm.GetFileContents(FileManager::LottoType::MegaMillions);
    MMNumGen->SetHistory(megaMillionsHistory);    
}

//Returns an integer average of the quality of the luckyNumbers passed through it.
int GetOverallAverage(LuckyNumberGenerator* numGen, vector<int> luckyNumbers)
{
    double avgScore = numGen->CalculateAverageScore(luckyNumbers);
    return (int(avgScore * 100));
}

//Generates and prints out a set of lucky numbers depending on the type of LuckyNumberGenerator that is passed through
vector<int> PrintLuckyNumbers(LuckyNumberGenerator* numGen)
{
    vector<int> luckyNumbers = numGen->GetNumbers();

    for (size_t i = 0; i < luckyNumbers.size(); i++) 
    {
        string label = (i < 5) ? "Position " + to_string(i+1) : "Mega Ball";
        double quality = numGen->GetNumberQualityAtPosition(luckyNumbers[i], i);
        cout << label << ": " << luckyNumbers[i] << " (Quality: " << quality << "%)\n";
    }

    cout << GetOverallAverage(numGen, luckyNumbers);

    return luckyNumbers;
}

//Rolls until it finds a set of numbers that meets the user's desired quality
void GenerateNumbersUntilQualityMet(LuckyNumberGenerator* numGen, double targetQuality = -1)
{
    int quality = 0;
    vector<int> luckyNumbers;

    if(targetQuality > -1)
        while(quality < targetQuality)
            PrintLuckyNumbers(numGen);
    else
        PrintLuckyNumbers(numGen);
}

void DrawMainMenu(Texture2D powerballLogo, Texture2D megaMillionsLogo, int screenWidth, PowerBallNumberGenerator* PBNumGen, MegaMillionsNumberGenerator* MMNumGen)
{
    ClearBackground((Color){240, 240, 250, 255});

    // Title
    DrawText("Lucky Number Generator", 250, 50, 40, DARKBLUE);
    DrawRectangle(250, 100, 500, 3, DARKBLUE);

    // Logo section
    float logoScale = 1.0f;
    float logoY = 140.0f;
    float logoSpacing = 150.0f;
        
    DrawTextureEx(powerballLogo, (Vector2){(screenWidth/2) + logoSpacing - (powerballLogo.width/2), logoY}, 0.0f, logoScale, WHITE); // PowerBall logo
    DrawTextureEx(megaMillionsLogo, (Vector2){(screenWidth/2) - logoSpacing - (megaMillionsLogo.width/2), logoY}, 0.0f, logoScale, WHITE); // MegaMillions logo  

    // Buttons
    float buttonY = 380.0f;
    float buttonWidth = 300.0f;
    float buttonHeight = 50.0f;
    float buttonX = (screenWidth - buttonWidth) / 2.0f;

    vector<int> luckyNumbers;
        
    if (GuiButton((Rectangle){buttonX, buttonY, buttonWidth, buttonHeight}, "Generate PowerBall Numbers"))
    {
        // TODO: Navigate to PowerBall screen
        //luckyNumbers = PrintLuckyNumbers(PBNumGen);
        currentScene = Scene::PowerBall_Generator;
    }
        
    if (GuiButton((Rectangle){buttonX, buttonY + 70, buttonWidth, buttonHeight}, "Generate MegaMillions Numbers"))
    {
        // TODO: Navigate to MegaMillions screen
        //luckyNumbers = PrintLuckyNumbers(MMNumGen);
        currentScene = Scene::MegaMillions_Generator;
    }
       
    if (GuiButton((Rectangle){buttonX, buttonY + 140, buttonWidth, buttonHeight}, "Quit Application"))
        ShouldExitApplication = true; // Exit application loop
}

void DrawPowerBallScene(int screenWidth)
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
        currentScene = Scene::MainMenu;
}

void DrawMegaMillionsScene(int screenWidth)
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
        currentScene = Scene::MainMenu;
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

    InitMegaMillions(fm, MMNumGen);
    InitPowerBall(fm, PBNumGen);

    while (!ShouldExitApplication) //Application loop
    {
        BeginDrawing();
        
        //DrawMainMenu(powerballLogo, megaMillionsLogo, screenWidth, PBNumGen, MMNumGen);

        if(WindowShouldClose())
            ShouldExitApplication = true;

        switch (currentScene)
        {
            case Scene::Default:
            case Scene::MainMenu:
            DrawMainMenu(powerballLogo, megaMillionsLogo, screenWidth, PBNumGen, MMNumGen);
            break;
            case Scene::MegaMillions_Generator:
            DrawMegaMillionsScene(screenWidth);
            break;
            case Scene::PowerBall_Generator:
            DrawPowerBallScene(screenWidth);
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
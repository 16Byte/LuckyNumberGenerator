#include "MegaMillionsScene.hpp"
#include <vector>
#include "raygui.h"
#include <string>


using namespace std;

MegaMillionsScene::MegaMillionsScene(int screenWidth, SceneManager& sceneManager, MegaMillionsNumberGenerator* generator)
    : screenWidth(screenWidth), sceneManager(sceneManager), generator(generator)
{
    // Generate initial numbers
    luckyNumbers = generator->GetNumbers();
    lockedNumbers.resize(luckyNumbers.size(), false);
}

void MegaMillionsScene::Draw()
{
    ClearBackground((Color){0, 0, 0, 255});

    // Title
    DrawText("MegaMillions Number Generator", 250, 50, 40, WHITE);
    DrawRectangle(250, 100, 500, 3, WHITE);

    float buttonY = 380.0f;
    float buttonWidth = 300.0f;
    float buttonHeight = 50.0f;
    float buttonX = (screenWidth - buttonWidth) / 2.0f;

    if (GuiButton((Rectangle){buttonX, buttonY + 70, buttonWidth, buttonHeight}, "Generate MegaMillions Numbers"))
    {
        if (luckyNumbers.empty())
        {
            // First generation - create all new numbers
            luckyNumbers = generator->GetNumbers();
            lockedNumbers.resize(luckyNumbers.size(), false);
        }
        else
        {
            // Regenerate only unlocked numbers
            vector<int> newNumbers = generator->GetNumbers();
            for (size_t i = 0; i < luckyNumbers.size() && i < newNumbers.size(); i++)
            {
                if (!lockedNumbers[i])
                {
                    luckyNumbers[i] = newNumbers[i];
                }
            }
        }
    }

    // Display generated numbers
    if (!luckyNumbers.empty())
    {
        float startX = 150.0f;
        float spacing = 120.0f;
        float numberY = 180.0f;
        float circleSize = 50.0f;
        float buttonSize = 40.0f;

        // Display the 5 main numbers horizontally
        for (size_t i = 0; i < 5 && i < luckyNumbers.size(); i++)
        {
            float posX = startX + (i * spacing);
            
            // Draw circle background
            DrawCircle(posX, numberY, circleSize / 2, WHITE);
            
            // Draw number
            string numText = to_string(luckyNumbers[i]);
            int textWidth = MeasureText(numText.c_str(), 30);
            DrawText(numText.c_str(), posX - textWidth / 2, numberY - 15, 30, BLACK);
            
            // Draw quality below circle
            int quality = (int)generator->GetNumberQualityAtPosition(luckyNumbers[i], i);
            string qualityText = to_string(quality) + "%";
            int qWidth = MeasureText(qualityText.c_str(), 16);
            DrawText(qualityText.c_str(), posX - qWidth / 2, numberY + 40, 16, WHITE);
            
            // Draw button below quality (toggle lock)
            string buttonText = (lockedNumbers[i]) ? "L" : "^";
            if (GuiButton((Rectangle){posX - buttonSize / 2, numberY + 65, buttonSize, buttonSize}, buttonText.c_str()))
            {
                lockedNumbers[i] = !lockedNumbers[i];
            }
        }

        // Display the mega ball
        if (luckyNumbers.size() > 5)
        {
            float megaBallX = startX + (5 * spacing) + 40;
            
            // Draw circle background
            DrawCircle(megaBallX, numberY, circleSize / 2, GOLD);
            
            // Draw number
            string numText = to_string(luckyNumbers[5]);
            int textWidth = MeasureText(numText.c_str(), 30);
            DrawText(numText.c_str(), megaBallX - textWidth / 2, numberY - 15, 30, WHITE);
            
            // Draw quality
            int quality = (int)generator->GetNumberQualityAtPosition(luckyNumbers[5], 5);
            string qualityText = to_string(quality) + "%";
            int qWidth = MeasureText(qualityText.c_str(), 16);
            DrawText(qualityText.c_str(), megaBallX - qWidth / 2, numberY + 40, 16, WHITE);
            
            // Draw button (toggle lock)
            string buttonText = (lockedNumbers[5]) ? "L" : "^";
            if (GuiButton((Rectangle){megaBallX - buttonSize / 2, numberY + 65, buttonSize, buttonSize}, buttonText.c_str()))
            {
                lockedNumbers[5] = !lockedNumbers[5];
            }
        }

        // Display overall average
        int overallAverage = generator->GetOverallAverage(luckyNumbers);
        string avgText = "Overall Average: " + to_string(overallAverage) + "%";
        DrawText(avgText.c_str(), 150, 320, 24, WHITE);
    }

    if (GuiButton((Rectangle){buttonX, buttonY + 140, buttonWidth, buttonHeight}, "Main Menu"))
        sceneManager.SetScene(SceneManager::Scene::MainMenu);
}

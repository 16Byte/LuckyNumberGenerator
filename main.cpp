#include "MegaMillionsNumberGenerator.hpp"
#include "PowerBallNumberGenerator.hpp"
#include "FileManager.hpp"
#include <iostream>
#include "raylib.h"
#include <string>

using namespace std;

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
    {
        while(quality < targetQuality)
        {
            PrintLuckyNumbers(numGen);
        }
    }
    else
    {
        PrintLuckyNumbers(numGen);
    }
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Lucky Number Generator");
    SetTargetFPS(60);

    MegaMillionsNumberGenerator* MMNumGen = new MegaMillionsNumberGenerator();
    PowerBallNumberGenerator* PBNumGen = new PowerBallNumberGenerator();
    FileManager fm;

    InitMegaMillions(fm, MMNumGen);
    InitPowerBall(fm, PBNumGen);

    vector<int> luckyNumbers;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GRAY);
        DrawText("Lucky Number Generator", 190, 200, 20, LIGHTGRAY);

        //update
        if(IsKeyReleased(KEY_E))
        { //Powerball test
            cout << "Powerball Numbers" << endl;
            luckyNumbers = PrintLuckyNumbers(PBNumGen);
        }

        if (IsKeyReleased(KEY_R))
        { //MegaMillions test
            cout << "MegaMillions Numbers" << endl;
            luckyNumbers = PrintLuckyNumbers(MMNumGen);
        }

        string luckyNumbers_string = "Lucky Numbers: ";
        for(size_t i = 0; i < luckyNumbers.size(); i++)
        {
            luckyNumbers_string += to_string(luckyNumbers[i]);
            if(i < luckyNumbers.size() - 1) luckyNumbers_string += ", ";
        }

        DrawText(luckyNumbers_string.c_str(), 190, 100, 20, WHITE);
        
        EndDrawing();
    }
    CloseWindow();

    //Garbage Collection
    delete PBNumGen;
    delete MMNumGen;
    return 0;
}
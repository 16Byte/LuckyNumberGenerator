#include "MegaMillionsNumberGenerator.hpp"
#include "PowerBallNumberGenerator.hpp"
#include "FileManager.hpp"
#include <iostream>

using namespace std;

void Init(FileManager fm, PowerBallNumberGenerator* PBNumGen)
{
    auto powerballHistory = fm.GetFileContents(FileManager::LottoType::PowerBall);
    PBNumGen->SetHistory(powerballHistory);    
}

void GenerateLuckyNumbers(PowerBallNumberGenerator* PBNumGen)
{
    int avg = 0;

    //PBNumGen->PrintAllFrequencies();
    while(avg < 40)
    {
        vector<int> luckyNumbers = PBNumGen->GetNumbers();

        cout << "Your Lucky Numbers:\n";
        for (size_t i = 0; i < luckyNumbers.size(); i++) {
            string label = (i < 5) ? "Position " + to_string(i+1) : "Powerball";
            double quality = PBNumGen->GetNumberQualityAtPosition(luckyNumbers[i], i);
            cout << label << ": " << luckyNumbers[i] << " (Quality: " << quality << "%)\n";
        }

        // Calculate and display overall quality score -- FIX
        double avgScore = PBNumGen->CalculateAverageScore(luckyNumbers);
        avg = (int(avgScore * 100));
        cout << "\nOverall Quality Score: " << avg << "%" << endl;
    }
}

int main()
{
    //MegaMillionsNumberGenerator* MMNumGen;
    PowerBallNumberGenerator* PBNumGen = new PowerBallNumberGenerator();
    FileManager fm;

    Init(fm, PBNumGen);
    GenerateLuckyNumbers(PBNumGen);
}
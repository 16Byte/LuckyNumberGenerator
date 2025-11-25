#include "MegaMillionsNumberGenerator.hpp"
#include "PowerBallNumberGenerator.hpp"
#include "FileManager.hpp"
#include <iostream>

using namespace std;

int main()
{
    MegaMillionsNumberGenerator MMNumGen;
    PowerBallNumberGenerator PBNumGen;
    FileManager fm;

    auto powerballHistory = fm.GetFileContents(FileManager::LottoType::PowerBall);
    PBNumGen.SetHistory(powerballHistory);

    PBNumGen.PrintAllFrequencies();

    // Generate random lucky numbers
    vector<int> luckyNumbers = PBNumGen.GetNumbers();
    
    cout << "Your Lucky Numbers:\n";
    for (size_t i = 0; i < luckyNumbers.size(); i++) {
        string label = (i < 5) ? "Position " + to_string(i) : "Powerball";
        double quality = PBNumGen.GetNumberQualityAtPosition(luckyNumbers[i], i);
        cout << label << ": " << luckyNumbers[i] << " (Quality: " << quality << "%)\n";
    }
    
    // Calculate and display overall quality score
    double avgScore = PBNumGen.CalculateAverageScore(luckyNumbers);
    cout << "\nOverall Quality Score: " << (avgScore * 100) << "%" << endl;
}
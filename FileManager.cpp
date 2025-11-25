#include <iostream>
#include <fstream> // file I/O
#include <string>
#include <sstream> // parsing files
#include "FileManager.hpp"

using namespace std;

void FileManager::ReadAndCacheAll()
{
    PowerBallHistory = FileManager::GetFileContents(LottoType::PowerBall);
    int lineCount = 0;

    for(int y = 0; y < (int)PowerBallHistory.size(); y++)
    {
        for(int x = 0; x < (int)PowerBallHistory[y].size(); x++)
        {
            int num = PowerBallHistory[y][x];
            cout << num << " ";
        }
        cout << endl;
        lineCount++;
    }
    cout << "Total: " << lineCount << endl;
}

vector<vector<int>> FileManager::GetFileContents(FileManager::LottoType lottoType)
{
    string filename = "";

    if(lottoType == LottoType::PowerBall)
        filename = powerballPath;
    else if(lottoType == LottoType::MegaMillions)
        filename = megamillionsPath;

    //implement the csv file parsing
    vector<std::vector<int>> allDraws;
    ifstream file(filename);
    
    if (!file.is_open()) {
        // handle error - return empty or throw
        return allDraws;
    }
    
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        
        // Skip lottery name
        getline(ss, token, ',');
        
        // Skip date (month, day, year)
        getline(ss, token, ',');
        getline(ss, token, ',');
        getline(ss, token, ',');
        
        // Parse numbers
        vector<int> numbers;
        while (getline(ss, token, ',')) {
            numbers.push_back(stoi(token));
        }
        
        allDraws.push_back(numbers);
    }
    
    file.close();
    return allDraws;
}

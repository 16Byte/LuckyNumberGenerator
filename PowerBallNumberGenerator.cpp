#include "PowerBallNumberGenerator.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <set>
#include <algorithm>

using namespace std;

vector<int> PowerBallNumberGenerator::GetNumbers()
{
    vector<int> numbers;
    random_device rd;
    mt19937 gen(rd());
    
    // Generate 5 unique main numbers (1-69)
    set<int> mainNumbers;
    uniform_int_distribution<> mainDist(1, 69);
    
    while (mainNumbers.size() < 5) {
        mainNumbers.insert(mainDist(gen));
    }
    
    // Convert set to vector (sorted automatically)
    numbers.assign(mainNumbers.begin(), mainNumbers.end());
    
    // Generate 1 powerball number (1-26)
    uniform_int_distribution<> powerballDist(1, 26);
    numbers.push_back(powerballDist(gen));
    
    return numbers;
}
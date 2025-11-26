#include "MegaMillionsNumberGenerator.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <set>
#include <algorithm>

using namespace std;

vector<int> MegaMillionsNumberGenerator::GetNumbers()
{
    vector<int> numbers;
    random_device rd;
    mt19937 gen(rd());
    
    // Generate 5 unique main numbers (1-70)
    set<int> mainNumbers;
    uniform_int_distribution<> mainDist(1, 70);
    
    while (mainNumbers.size() < 5) {
        mainNumbers.insert(mainDist(gen));
    }
    
    // Convert set to vector (sorted automatically)
    numbers.assign(mainNumbers.begin(), mainNumbers.end());
    
    // Generate 1 mega ball number (1-25)
    uniform_int_distribution<> megaBallDist(1, 25);
    numbers.push_back(megaBallDist(gen));
    
    return numbers;
}
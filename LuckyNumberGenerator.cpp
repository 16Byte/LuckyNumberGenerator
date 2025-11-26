#include <iostream>
#include <vector>
#include <map>
#include "LuckyNumberGenerator.hpp"

using namespace std;

void LuckyNumberGenerator::SetHistory(const vector<vector<int>>& historyData)
{
    history = historyData;
}

map<int, int> LuckyNumberGenerator::GetNumberFrequency() const
{
    return CalculateFrequency();
}

map<int, int> LuckyNumberGenerator::CalculateFrequency() const
{
    map<int, int> numberFrequency;
    
    for (const auto& draw : history) {
        for (int num : draw) {
            numberFrequency[num]++;
        }
    }
    
    return numberFrequency;
}

vector<map<int, int>> LuckyNumberGenerator::GetPositionFrequency() const
{
    return CalculatePositionFrequency();
}

vector<map<int, int>> LuckyNumberGenerator::CalculatePositionFrequency() const
{
    if (history.empty()) return {};
    
    int numPositions = history[0].size();
    vector<map<int, int>> positionFrequencies(numPositions);
    
    for (const auto& draw : history) {
        for (size_t pos = 0; pos < draw.size(); pos++) {
            int number = draw[pos];
            positionFrequencies[pos][number]++;
        }
    }
    
    return positionFrequencies;
}

/**
 * Calculates the probability of the given numbers based on historical frequency. History must be populated via SetHistory() before calling this method
 * @param generatedNumbers Vector of lottery numbers to check
 * @return Probability as a decimal (0.0 to 1.0)
 */
double LuckyNumberGenerator::CalculateOdds(const vector<int>& generatedNumbers) const
{
    if (history.empty()) return -1.0;
    
    auto posFreq = GetPositionFrequency();
    double totalDraws = history.size();
    double probability = 1.0;
    
    for (size_t pos = 0; pos < generatedNumbers.size() && pos < posFreq.size(); pos++) {
        int number = generatedNumbers[pos];
        double frequency = posFreq[pos][number];
        double positionProb = frequency / totalDraws;
        probability *= positionProb;
    }
    
    return probability;
}

/**
 * Calculates an average quality score for the given numbers based on historical frequency.
 * Unlike CalculateOdds which multiplies probabilities, this averages them for a more
 * interpretable "quality" metric.
 * @param generatedNumbers Vector of lottery numbers to check
 * @return Average probability as a decimal (0.0 to 1.0)
 * @pre history must be populated via SetHistory() before calling this method
 */
double LuckyNumberGenerator::CalculateAverageScore(const vector<int>& generatedNumbers) const
{
    if (history.empty()) return -1.0;
    
    auto posFreq = GetPositionFrequency();
    double sum = 0.0;

    for (size_t pos = 0; pos < generatedNumbers.size() && pos < posFreq.size(); pos++)
    {
        int number = generatedNumbers[pos];
        double frequency = posFreq[pos][number];
        sum += frequency;
    }
    return sum / (generatedNumbers.size() * 100);
}

/**
 * Gets the quality score for a specific number at a specific position based on historical frequency.
 * @param number The lottery number to check
 * @param position The position (0-indexed) to check
 * @return Quality score as a percentage (0.0 to 100.0)
 * @pre history must be populated via SetHistory() before calling this method
 */
double LuckyNumberGenerator::GetNumberQualityAtPosition(int number, int position) const
{
    if (history.empty()) return -1.0;
    
    auto posFreq = GetPositionFrequency();
    if (position < 0 || position >= (int)posFreq.size()) return 0.0;
    
    double frequency = posFreq[position][number];
    //double totalDraws = history[position]; //using the entire data set. Is this the right way? I don't think so.
    
    return (frequency);
}

/**
 * Debug method to print all number frequencies across all positions.
 * @pre history must be populated via SetHistory() before calling this method
 */
void LuckyNumberGenerator::PrintAllFrequencies() const
{
    if (history.empty()) {
        cout << "No history data loaded." << endl;
        return;
    }
    
    cout << "=== Overall Number Frequencies ===" << endl;
    auto frequencies = GetNumberFrequency();
    for (const auto& [number, count] : frequencies) {
        cout << "Number " << number << ": " << count << " times" << endl;
    }
    
    cout << "\n=== Position-Based Frequencies ===" << endl;
    auto posFreq = GetPositionFrequency();
    for (size_t pos = 0; pos < posFreq.size(); pos++) {
        string label = (pos < posFreq.size() - 1) ? "Position " + to_string(pos) : "Powerball";
        cout << "\n" << label << ":" << endl;
        for (const auto& [number, count] : posFreq[pos]) {
            cout << "  Number " << number << ": " << count << " times" << endl;
        }
    }
}
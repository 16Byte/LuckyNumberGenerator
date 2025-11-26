#ifndef LUCKYNUMBERGENERATOR_HPP
#define LUCKYNUMBERGENERATOR_HPP

#include <vector>
#include <map>

class LuckyNumberGenerator
{
    public:
        virtual std::vector<int> GetNumbers() = 0;
        virtual ~LuckyNumberGenerator() {}
        
        void SetHistory(const std::vector<std::vector<int>>& historyData);
        std::map<int, int> GetNumberFrequency() const;
        std::vector<std::map<int, int>> GetPositionFrequency() const;
        double CalculateOdds(const std::vector<int>& generatedNumbers) const;
        double CalculateAverageScore(const std::vector<int>& generatedNumbers) const;
        double GetNumberQualityAtPosition(int number, int position) const;
        void PrintAllFrequencies() const;
        
    protected:
        std::vector<std::vector<int>> history;
        std::map<int, int> CalculateFrequency() const;
        std::vector<std::map<int, int>> CalculatePositionFrequency() const;
};

#endif
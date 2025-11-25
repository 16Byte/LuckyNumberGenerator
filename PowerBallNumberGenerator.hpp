#ifndef POWERBALLNUMBERGENERATOR_HPP
#define POWERBALLNUMBERGENERATOR_HPP

#include "LuckyNumberGenerator.hpp"

class PowerBallNumberGenerator : public LuckyNumberGenerator
{
    public:
        std::vector<int> GetNumbers() override;
};

#endif
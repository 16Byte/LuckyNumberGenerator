#ifndef MEGAMILLIONSNUMBERGENERATOR_HPP
#define MEGAMILLIONSNUMBERGENERATOR_HPP

#include "LuckyNumberGenerator.hpp"

class MegaMillionsNumberGenerator : public LuckyNumberGenerator
{
    public:
        std::vector<int> GetNumbers() override;
};

#endif
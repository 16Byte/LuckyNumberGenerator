#ifndef MEGAMILLIONSSCENE_HPP
#define MEGAMILLIONSSCENE_HPP

#include "raylib.h"
#include "SceneManager.hpp"
#include "MegaMillionsNumberGenerator.hpp"

class MegaMillionsScene
{
    public:
        MegaMillionsScene(int screenWidth, SceneManager& sceneManager, MegaMillionsNumberGenerator* generator);
        void Draw();
        
    private:
        int screenWidth;
        SceneManager& sceneManager;
        MegaMillionsNumberGenerator* generator;
};

#endif

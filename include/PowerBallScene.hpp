#ifndef POWERBALLSCENE_HPP
#define POWERBALLSCENE_HPP

#include "raylib.h"
#include "SceneManager.hpp"
#include "PowerBallNumberGenerator.hpp"

class PowerBallScene
{
    public:
        PowerBallScene(int screenWidth, SceneManager& sceneManager, PowerBallNumberGenerator* generator);
        void Draw();
        
    private:
        int screenWidth;
        SceneManager& sceneManager;
        PowerBallNumberGenerator* generator;
};

#endif

#ifndef MAINMENUSCENE_HPP
#define MAINMENUSCENE_HPP

#include "raylib.h"
#include "SceneManager.hpp"

class MainMenuScene
{
    public:
        MainMenuScene(Texture2D powerballLogo, Texture2D megaMillionsLogo, int screenWidth, SceneManager& sceneManager);
        void Draw();
        
    private:
        Texture2D powerballLogo;
        Texture2D megaMillionsLogo;
        int screenWidth;
        SceneManager& sceneManager;
};

#endif

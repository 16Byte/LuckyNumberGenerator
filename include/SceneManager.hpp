#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

class SceneManager
{
public:
    enum class Scene {
        Default,
        MainMenu,
        PowerBall_Generator,
        MegaMillions_Generator,
    };

    SceneManager();
    
    void SetScene(Scene newScene);
    Scene GetCurrentScene() const;
    bool ShouldExit() const;
    void RequestExit();

private:
    Scene currentScene;
    bool shouldExit;
};

#endif

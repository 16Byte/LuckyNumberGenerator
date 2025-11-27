#include <vector>
#include <string>

class FileManager
{
    public:
        void ReadAndCacheAll();
        enum class LottoType {
            PowerBall,
            MegaMillions,
        };
        std::vector<std::vector<int>> PowerBallHistory;
        std::vector<std::vector<int>> GetFileContents(LottoType lottoType);

    private: 
        const std::string powerballPath = "Assets/Data/powerball.csv";
        const std::string megamillionsPath = "Assets/Data/megamillions.csv";
};
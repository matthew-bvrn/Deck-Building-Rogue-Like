#include "game.h"
#include "ImageManager.h"
using namespace std;

class MapFromImage
{
public:

	MapFromImage(std::string filename) {
		sf::Image image;
		image.loadFromFile(filename);

		ofstream myfile;
		ofstream myfile2;
		myfile2.open("collision.txt");
		myfile.open("map.txt");

		myfile << "[";
		myfile2 << "[";

		for (int i = 0; i < image.getSize().y; i++)
		{
			myfile2 << "[";
			for (int j = 0; j < image.getSize().x; j++)
			{
				if (image.getPixel(j, i) == sf::Color(255, 255, 255))
				{
					myfile << "1";
					myfile2 << "1";
				}
				else if (image.getPixel(j, i) == sf::Color(255, 0, 0)) {
					myfile << "2";
					myfile2 << "0";
				}
				else
				{
					myfile << "0";
					myfile2 << "0";
				}
				myfile << ",";
				if (!(j == (image.getSize().x - 1)))
				{
					myfile2 << ",";
				}
			}
			myfile2 << "],\n";
			myfile << "\n";
		}
		myfile2 << "]";
		myfile << "]";
		myfile.close();
		myfile2.close();
	}
};

ImageManager imageManager;
float frameTime;
float runTime;

int main()
{
	srand(time(NULL));

	//0 is gameplay, one for tile to text conversion, 2 for map to text conversion
	int openingMode = 0;

	int windowedWidth = 35;
	int windowedHeight = 28;

	if (openingMode == 0)
	{
		//TODO move this into an entity handler class
		std::map<std::string, BattlingCharacterType> battlingCharacterTypes;
		battlingCharacterTypes.insert(std::pair<std::string, BattlingCharacterType>("player", BattlingCharacterType("player")));

		Game game(windowedWidth, windowedHeight,battlingCharacterTypes);

		game.loop();
	}
	else if (openingMode == 1)
	{
		MapFromImage mapFromImage("assets/map.png");
	}

	return 0;
}
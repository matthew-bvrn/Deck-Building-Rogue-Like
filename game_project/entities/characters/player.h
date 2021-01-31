#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <thread>
#include <assert.h>
#include <time.h>
#include "CardsInHand.h"
#include "entities\other\NumberEntity.h"
#include "BattlingCharacter.h"
#include "globalVariables.h"
#include "BattlingCharacterType.h"
#include "standaloneFunctions.h"
#include "CardActionMap.h"

class Player : public BattlingCharacter
{
public:

	Player(BattlingCharacterType* type, std::string _identity,ImageManager* imageManager) : BattlingCharacter(type, _identity, imageManager, sf::Vector2f(2*windowInfo.tileSizeInPixels,2* windowInfo.tileSizeInPixels))
	{
	}

	void action(std::map<int, bool> keyboardArray, float& playerDistanceFromEdgeX, float& playerDistanceFromEdgeY,
		std::vector<std::vector<int>>& collision, int renderMode, CardActionMap& cardActionMap);

	void initialiseBattleMode() override;

	void draw(sf::RenderWindow& window) override;

	void checkInputs(std::map<int, bool> keyboardArray);

	void resize();

	//This is the entity that displays the number of card points to the window. cardPoints stores the actual value
	NumberEntity cardPointsNumber;
	NumberEntity healthNumber;

};
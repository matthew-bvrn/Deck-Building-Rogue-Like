#include "Enemy.h"

Enemy::Enemy(BattlingCharacterType* type, std::string identity, int xPos, int yPos,WindowInfo windowInfo,ImageManager& imageManager) : BattlingCharacter(type, identity, imageManager)
{

	texture.loadFromFile("assets/slime.png");
	currentXTilePos = xPos;
	currentYTilePos = yPos;

	xPos = currentXTilePos * windowInfo.tileSizeInPixels;
	yPos = currentYTilePos * windowInfo.tileSizeInPixels;
	pathUpdateTimeout = 0;
	movementTimeout = type->movementTimeoutIdle;
	directionalArrow.initialise("directionalArrow.png", xPos, yPos, 0,imageManager);
}

void Enemy::action(int targetX, int targetY, WindowInfo windowInfo, std::vector<std::vector<int>> walkableTiles, std::vector<std::vector<int>>& collision)
{
	resetBehaviourTriggers();

	//Update path
	pathUpdateTimeout--;
	if (pathUpdateTimeout <= 0)
	{
		pathUpdateTimeout = pathUpdateTimeoutInterval;
		currentPath = pathfindNextSpace(targetX, targetY, windowInfo, walkableTiles);
	}

	//Movement
	movementTimeout -= frameTime;
	if (movementTimeout <= 0)
	{
		behaviourTriggers[initiateMotion] = true;

		for (int i = 1; i < currentPath.size(); i++)
		{
			if (currentXTilePos > currentPath[1].x)
			{
				direction = 1;
				break;
			}
			else if (currentXTilePos < currentPath[1].x)
			{
				direction = 3;
				break;
			}
			else if (currentYTilePos > currentPath[1].y)
			{
				direction = 0;

			}
			else if (currentYTilePos< currentPath[1].y)
			{
				direction = 2;
			}
		}
		movementTimeout = type->movementTimeoutIdle;
	}
	BattlingCharacter::action(collision,windowInfo, 1, direction);
}


//TODO Much of this code is reused from the example on the git page for the pathfinder library but I seriously need
//to reduce the nesting levels for readability
AStar::CoordinateList Enemy::pathfindNextSpace(int targetX, int targetY, WindowInfo windowInfo, std::vector<std::vector<int>> walkableTiles)
{

	AStar::Generator generator;
	// Set 2d map size.
	generator.setWorldSize({ static_cast<int>(walkableTiles[0].size()), static_cast<int>(walkableTiles.size()) });
	// You can use a few heuristics : manhattan, euclidean or octagonal.
	generator.setHeuristic(AStar::Heuristic::euclidean);
	generator.setDiagonalMovement(false);

	for (int i = 0; i < walkableTiles.size(); i++)
	{
		for (int j = 0; j < walkableTiles[0].size(); j++) {
			if (walkableTiles[i][j] == 0)
			{
				generator.addCollision({ j,i });
			}
		}
	}
	AStar::CoordinateList path = generator.findPath({ targetX, targetY }, { currentXTilePos, currentYTilePos });
	return path;
}
#include "CardAction.h"



CardAction::CardAction(int xPos, int yPos, float activationTime,
					   float destructionTime, AttackElement attackElement,
					   int attackDamage,CharType characterType) 
					   : xPos(xPos), yPos(yPos), activationTime(activationTime),
						 destructionTime(destructionTime), attackElement(attackElement),
						 attackDamage(attackDamage), characterType(characterType)
{
	aliveTime = 0.0;
	active = false;
}


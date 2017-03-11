#include "BlueLeever.h"
#include "Random.h"

BlueLeever::BlueLeever()
{
	movement = BLUELEEVER_MOVEMENT;
	maxDistance = random(LEEVER_MIN_DISTANCE, LEEVER_MAX_DISTANCE);
}

//Update object position
void BlueLeever::Update(GAME_FLT)
{
	position.y += (int)movement;
	if (abs(position.y - startPosition.y) >= maxDistance)
		movement *= -1.0;
}

//Calls object's texture's draw method
void BlueLeever::Draw(GAME_FLT, View * p_view)
{
	texture->Draw(gDevice->getRenderer(), p_view, position, angle);
}

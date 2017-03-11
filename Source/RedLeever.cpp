#include "RedLeever.h"
#include "Random.h"

RedLeever::RedLeever()
{
	movement = REDLEEVER_MOVEMENT;
	maxDistance = random(LEEVER_MIN_DISTANCE, LEEVER_MAX_DISTANCE);
}

//Update object's position
void RedLeever::Update(GAME_FLT)
{
	position.x += (int)movement;
	if (abs(position.x - startPosition.x) >= maxDistance)
		movement *= -1.0;
}

//Calls object's texture's draw method
void RedLeever::Draw(GAME_FLT, View *p_view)
{
	texture->Draw(gDevice->getRenderer(), p_view, position, angle);
}

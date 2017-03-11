#include "BlueOctorok.h"
#include "Random.h"

BlueOctorok::BlueOctorok()
{
	movement = random(BLUEOCTOROK_MOVEMENT_MIN, BLUEOCTOROK_MOVEMENT_MAX);
}

//Update object's position
void BlueOctorok::Update(GAME_FLT)
{
	angle -= movement;
	if (angle <= -360.0)
		angle = 0;
}

//Calls object's texture's draw method
void BlueOctorok::Draw(GAME_FLT, View *p_view)
{
	texture->Draw(gDevice->getRenderer(), p_view, position, angle);
}

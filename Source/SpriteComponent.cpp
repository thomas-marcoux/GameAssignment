#include "SpriteComponent.h"

bool SpriteComponent::Draw(View* p_view)
{
	texture->Draw(gDevice->getRenderer(), p_view, position, angle);
	return true;
}

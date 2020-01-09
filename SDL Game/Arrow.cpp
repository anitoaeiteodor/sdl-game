#include "Arrow.h"

const char* Arrow::arrowSpritePath = R"(assets\Sprites\Bows\regular_arrow.png)";
Vector2D Arrow::arrowSize = { 30, 80 };

Arrow::Arrow(SDL_Renderer* rend, Vector2D size, Vector2D src, Vector2D dest, float dmg, const char* tex)
	: Projectile(rend, size, src, dest, tex)
{
	this->dmg = dmg;

	double theta = atan(((float)dest.y - src.y) / ((float)dest.x - src.x));
	if (dest.x < src.x)
		theta += M_PI;
	theta += M_PI / 2;
	theta = theta * 57.2957;
	
	this->theta = theta;
}

Arrow::~Arrow()
{
}

void Arrow::Update()
{
	pos = pos + speed;
}

void Arrow::Render(float dt)
{
	Vector2D posAux = pos + speed * dt;

	SDL_Rect projPos = { (int)(posAux.x - size.x / 2), (int)(posAux.y - size.y / 2),
		(int)(size.x * .75f), (int)(size.y * .75f) };
	SDL_Rect pos = { 0, 0, (int)size.x, (int)size.y };

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (speed.x > 0)
		flip = SDL_FLIP_HORIZONTAL;

	SDL_RenderCopyEx(renderer, sprite, &pos, &projPos, theta, nullptr, flip);
}

GameObjID Arrow::GetID()
{
	return id;
}

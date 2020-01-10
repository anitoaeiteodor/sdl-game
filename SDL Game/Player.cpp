#include "Player.h"
#include "TextureManager.h"
#include <iostream>

Player::Player(SDL_Renderer* rend, Vector2D pos, Vector2D size)
{
	renderer = rend;
	this->pos = pos;
	this->size = size;
	mousePos.x = mousePos.y = 0;
	speed.x = speed.y = 0;
	CreateAnimationSystem();

	this->bow = new RegularBow(rend, pos, Bow::bowSize, R"(assets\Sprites\Bows\regular_bow.png)", .5f);
}

Player::~Player()
{
	delete anSys;
	anSys = 0;
}

GameObjID Player::GetID()
{
	return id;
}

void Player::Update()
{
	Vector2D* offset;
	Orientation ori = Orientation::Right;

	Vector2D newPos = pos + speed;

	if (newPos.x - size.x / 2 > 0 && newPos.x + size.x / 2 < Game::WINDOW_WIDTH)
		pos.x = newPos.x;
	if (newPos.y - size.y / 2 > 0 && newPos.y + size.y / 2 < Game::WINDOW_HEIGHT)
		pos.y = newPos.y;

	double theta = 0;
	if (speed.x || speed.y)
	{
		anSys->ProcessInput(Command::RUN);
		offset = Bow::bowOffsetWalk;
		theta = Bow::bowOffsetAngleWalk[anSys->GetCurrentNode()];
	}
	else
	{
		anSys->ProcessInput(Command::IDLE);
		offset = Bow::bowOffsetIdle;
	}
	Vector2D bowPos;
	int frame = anSys->GetCurrentNode();
	if (mousePos.x < pos.x)
	{
		ori = Orientation::Left;
		bowPos = { pos.x - offset[frame].x, pos.y + offset[frame].y };
	}
	else
	{
		ori = Orientation::Right;
		bowPos = { pos.x + offset[frame].x, pos.y + offset[frame].y };
	}
	std::cout << bowPos.x << ' ' << bowPos.y << '\n';

	bow->UpdateByPlayer(bowPos, ori, theta);
}


void Player::Render(float dt)
{
	Vector2D posAux = pos + speed * dt;

	SDL_Rect playerPos = { (int)(posAux.x - size.x / 2), (int)(posAux.y - size.y / 2),
		(int)size.x, (int)size.y };
	SDL_Rect pos = { 0, 0, (int)size.x, (int)size.y };

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (posAux.x > mousePos.x)
		flip = SDL_FLIP_HORIZONTAL;

	SDL_RenderCopyEx(renderer, GetTex(), &pos, &playerPos, 0, nullptr, flip);

	bow->Render(dt);
}

Vector2D Player::GetPos()
{
	return pos;
}

Vector2D Player::GetSize()
{
	return size;
}

bool Player::CheckCollision(GameObj* other)
{
	return false;
}

void Player::SetSpeed(Vector2D speed)
{
	this->speed = speed;
}

void Player::SetMousePos(Vector2D pos)
{
	mousePos = pos;
}

Arrow* Player::FireArrow(Vector2D dest)
{
	return bow->FireArrow(dest);
}

void Player::SetBow(Bow* bow)
{
	this->bow = bow;
}

SDL_Texture* Player::GetTex()
{
	return anSys->GetNextFrame();
}

void Player::CreateAnimationSystem()
{
	// temporary
	Animation* idle = new Animation(renderer);
	Animation* run = new Animation(renderer);
	idle->CreateFrames(R"(assets\Sprites\Player\idle\idle_def_0.png)", 2, 2, 160, 160, 2);
	run->CreateFrames(R"(assets\Sprites\Player\walk\walk_def_0.png)", 2, 2, 160, 160, 2);
	
	anSys = new AnimationSystem(2);
	anSys->AddAnimation(idle);
	anSys->AddAnimation(run);
	
	anSys->AddTrigger(0, 1, Command::RUN);
	anSys->AddTrigger(1, 1, Command::RUN);
	anSys->AddTrigger(0, 0, Command::IDLE);
	anSys->AddTrigger(1, 0, Command::IDLE);
}

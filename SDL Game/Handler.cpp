#include "Handler.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"

#include <unordered_set>
#include <iostream>

Handler::Handler()
{

}

Handler::~Handler()
{
	for (auto& obj : handler)
		if (obj)
		{
			delete obj;
			obj = 0;
		}
	handler.clear();
}

void Handler::AddObj(GameObj* obj)
{
	if (!obj)
		return;
	handler.push_back(obj);
}

void Handler::RemoveObj(GameObj* obj)
{
	int pos = 0;
	for (auto& item : handler)
	{
		if (item == obj)
			break;
		pos++;
	}
	if (pos < handler.size())
	{
		delete handler[pos];
		handler.erase(handler.begin() + pos);
	}
}

void Handler::ClearHandler()
{
	handler.clear();
}

int Handler::ObjCount()
{
	return (int)handler.size();
}

void Handler::Update()
{
	static int timeSincePlayerHurt = 0;

	Vector2D playerPos = { 0, 0 };
	for (auto& obj : handler)
	{
		if (obj->GetID() == GameObjID::Player)
			playerPos = obj->GetPos();
	}

	std::vector<GameObj*> toDestroy;
	std::unordered_set<GameObj*> monstersColided;


	for (int i = (int)handler.size() - 1; i > 0; i--)
	{
		if (!handler[i])
			continue;
		for (int j = i - 1; j >= 0; j--)
		{
			if (!handler[j])
				continue;

			if (((handler[i]->GetID() == GameObjID::Player && handler[j]->GetID() == GameObjID::Monster)
				|| (handler[i]->GetID() == GameObjID::Monster && handler[j]->GetID() == GameObjID::Player))
				&& CheckCollision(handler[i], handler[j]))
			{
				if (SDL_GetTicks() - timeSincePlayerHurt < PLAYER_IMMORTAL_DELAY)
					continue;

				if (handler[j]->GetID() == GameObjID::Player && ((Player*)handler[j])->IsAlive())
				{
					int dmg = ((Enemy*)handler[i])->GetDmg();
					int health = ((Player*)handler[j])->TakeDmg(dmg);
					if (health <= 0)
						((Player*)handler[j])->Die();
				}
				else if (handler[i]->GetID() == GameObjID::Player && ((Player*)handler[i])->IsAlive())
				{
					int dmg = ((Enemy*)handler[j])->GetDmg();
					int health = ((Player*)handler[i])->TakeDmg(dmg);
					if (health <= 0)
						((Player*)handler[i])->Die();
				}
				timeSincePlayerHurt = SDL_GetTicks();
				std::cout << "Collision between monster and player\n";
			}

			if (((handler[i]->GetID() == GameObjID::Arrow && handler[j]->GetID() == GameObjID::Monster)
				|| (handler[i]->GetID() == GameObjID::Monster && handler[j]->GetID() == GameObjID::Arrow))
				&& CheckCollision(handler[i], handler[j]))
			{
				if (handler[j]->GetID() == GameObjID::Monster)
				{
					int dmg = ((Arrow*)handler[i])->GetDmg();
					int health = ((Enemy*)handler[j])->TakeDmg(dmg);
					if (health <= 0)
						((Enemy*)handler[j])->Die();

					handler[i] = nullptr;
					toDestroy.push_back(handler[i]);
				}
				else
				{
					int dmg = ((Arrow*)handler[j])->GetDmg();
					int health = ((Enemy*)handler[i])->TakeDmg(dmg);
					if (health <= 0)
						((Enemy*)handler[i])->Die();

					handler[j] = nullptr;
					toDestroy.push_back(handler[j]);
				}
				std::cout << "Collision between monster and arrow\n";
				break;
			}
		}
	}

	for (auto& destr : toDestroy)
	{
		//Vector2D pos = destr->GetPos();
		//std::cout << "Deleted " << pos.x << ' ' << pos.y << '\n';
		RemoveObj(destr);
	}
	toDestroy.clear();

	for (int i = (int)handler.size() - 1; i >= 0; i--)
	{
		GameObj* obj = handler[i];
		if (obj == nullptr)
		{
			toDestroy.push_back(obj);
			continue;
		}
		if (IsOutOfBounds(obj))
			toDestroy.push_back(obj);

		if (obj->GetID() == GameObjID::Player && !((Player*)obj)->Player::IsAlive())
			toDestroy.push_back(obj);

		if (obj->GetID() == GameObjID::Monster && ((Enemy*)obj)->Enemy::IsAlive())
			((Enemy*)obj)->Enemy::SetPlayerPos(playerPos);
		else if(obj->GetID() == GameObjID::Monster && !((Enemy*)obj)->Enemy::IsAlive())
			toDestroy.push_back(obj);

		obj->Update();
	}

	for (auto& destr : toDestroy)
	{
		//Vector2D pos = destr->GetPos();
		//std::cout << "Deleted " << pos.x << ' ' << pos.y << '\n';
		RemoveObj(destr);
	}
	toDestroy.clear();
}

void Handler::Render(float dt)
{
	for (auto& obj : handler)
		obj->Render(dt);
}

GameObj* Handler::GetPlayer()
{
	Player* res = nullptr;
	for (auto& obj : handler)
		if (obj->GetID() == GameObjID::Player)
			res = (Player*)obj;
	return res;
}

bool Handler::IsOutOfBounds(GameObj* obj)
{
	Vector2D pos = obj->GetPos();
	
	if (pos.x > Game::WINDOW_WIDTH || pos.x < 0 || pos.y < 0 || pos.y > Game::WINDOW_HEIGHT)
		return true;
	return false;
}

bool Handler::CheckCollision(GameObj* objA, GameObj* objB)
{
	Vector2D posA, posB, sizeA, sizeB;
	posA = objA->GetPos();
	sizeA = objA->GetSize();
	posB = objB->GetPos();
	sizeB = objB->GetSize();


	SDL_Rect rectA = { (int)posA.x, (int)posA.y, (int)sizeA.x, (int)sizeA.y };
	SDL_Rect rectB = { (int)posB.x, (int)posB.y, (int)sizeB.x, (int)sizeB.y };

	return SDL_HasIntersection(&rectA, &rectB);
}

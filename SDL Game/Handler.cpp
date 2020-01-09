#include "Handler.h"
#include "Game.h"
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
	delete handler[pos];
	handler.erase(handler.begin() + pos);
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
	std::vector<GameObj*> toDestroy;
	for (auto& obj : handler)
	{
		if (IsOutOfBounds(obj))
			toDestroy.push_back(obj);
		obj->Update();
	}

	for (auto& destr : toDestroy)
	{
		Vector2D pos = destr->GetPos();
		std::cout << "Deleted " << pos.x << ' ' << pos.y << '\n';
		RemoveObj(destr);
	}
	toDestroy.clear();
}

void Handler::Render(float dt)
{
	for (auto& obj : handler)
		obj->Render(dt);
}

bool Handler::IsOutOfBounds(GameObj* obj)
{
	Vector2D pos = obj->GetPos();
	
	if (pos.x > Game::WINDOW_WIDTH || pos.x < 0 || pos.y < 0 || pos.y > Game::WINDOW_HEIGHT)
		return true;
	return false;
}

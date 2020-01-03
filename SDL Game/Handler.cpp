#include "Handler.h"

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
	for (auto& obj : handler)
		obj->Update();
}

void Handler::Render(float dt)
{
	for (auto& obj : handler)
		obj->Render(dt);
}

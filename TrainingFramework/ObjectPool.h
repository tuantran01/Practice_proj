#pragma once
#include "SpriteAnimation.h"

class ObjectPool
{
public:
	ObjectPool();
	ObjectPool(int size);
	~ObjectPool();

	SpriteAnimation* accqire();
	void release(SpriteAnimation* spriteAnimation);
	
private:
	std::vector<SpriteAnimation*> m_listSpriteAnimation;
	
};
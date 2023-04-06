#include "ObjectPool.h"
#include <vector>


ObjectPool::ObjectPool(int size)
{
	for (size_t i = 0; i < size; i++)
	{
		m_listSpriteAnimation.push_back(new SpriteAnimation());
	}
}

ObjectPool::~ObjectPool()
{
	for (auto obj : m_listSpriteAnimation)
	{
		delete obj;
	}
}

SpriteAnimation* ObjectPool::accqire()
{
	if (m_listSpriteAnimation.size() > 0)
	{
		SpriteAnimation* obj = m_listSpriteAnimation.back();
		m_listSpriteAnimation.pop_back();
		return obj;
	}
	return nullptr;
}

void ObjectPool::release(SpriteAnimation* spriteAnimation)
{
	m_listSpriteAnimation.push_back(spriteAnimation);
}


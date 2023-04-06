#pragma once

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "SpriteAnimation.h"
#include "Sprite2D.h"
#include "Sprite3D.h"

class Player
{
public :
	Player();
	~Player();

	void Init();
	void Update(GLfloat deltatime);
	void Draw();
	
private:
	float m_speed;
};
#include "GSPlay.h"

#include <stdlib.h>
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include "SpriteAnimation.h"



GSPlay::GSPlay()
{
	m_KeyPress = 0;
}


GSPlay::~GSPlay()
{
}



std::shared_ptr<SpriteAnimation> mainObj = nullptr;
std::shared_ptr<SpriteAnimation> obstacleObj = nullptr,
								 obstacleObj1 = nullptr,
								 obstacleObj2 = nullptr,
                                 obstacleObj3 = nullptr;
std::string sound = "Run-Amok.mp3";
std::int32_t score = 0;
std::float_t f_speed = 0.0f;
std::float_t f_gravity = 200.0f;
std::float_t f_backgroundSpeed = 200.0f;

void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	// background
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2.0f, (float)Globals::screenHeight / 2.0f);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);
	// background 2
	m_background2 = std::make_shared<Sprite2D>(model, shader, texture);
	m_background2->Set2DPosition((float)Globals::screenWidth / 2.0f + Globals:: screenWidth , (float)Globals::screenHeight / 2.0f);
	m_background2->SetSize(Globals::screenWidth, Globals::screenHeight);

	// ground
	texture = ResourceManagers::GetInstance()->GetTexture("Ground.tga");
	m_ground = std::make_shared<Sprite2D>(model, shader, texture);
	m_ground->SetSize(Globals::screenWidth / 2.0f, 100);
	m_ground->Set2DPosition((float)m_ground->GetSize().x / 2.0f, (float)Globals::screenHeight - 50.0f);

	// ground 2
	m_ground2 = std::make_shared<Sprite2D>(model, shader, texture);
	m_ground2->SetSize(Globals::screenWidth / 2.0f, 100);
	m_ground2->Set2DPosition((float)Globals::screenWidth - m_ground2->GetSize().x / 2.0f, (float)Globals::screenHeight - 50.0f);
	
	// ground 3
	m_ground3 = std::make_shared<Sprite2D>(model, shader, texture);
	m_ground3->SetSize(Globals::screenWidth / 2.0f, 100);
	m_ground3->Set2DPosition((float)Globals::screenWidth + m_ground3->GetSize().x / 2.0f, (float)Globals::screenHeight - 50.0f);

	// ground 4
	m_ground4 = std::make_shared<Sprite2D>(model, shader, texture);
	m_ground4->SetSize(Globals::screenWidth / 2.0f, 100);
	m_ground4->Set2DPosition((float)Globals::screenWidth * 2 - m_ground4->GetSize().x / 2.0f, (float)Globals::screenHeight - 50.0f);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50.0f, 50.0f);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("slkscrb.ttf");
	m_score = std::make_shared< Text>(shader, font, "0", TextColor::RED, 1.0f);
	m_score->Set2DPosition(Vector2(5.0f, 25.0f));

	//animation
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("Astronaut_Run.tga");
	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 1, 0, 0.1f);
	obj->Set2DPosition(240.0f, (float)Globals::screenHeight - 100);
	obj->SetSize(70, 70);
	m_listAnimation.push_back(obj);
	m_KeyPress = 0;
	mainObj = obj;
	m_listAnimation.push_back(mainObj);

	//coin
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("coin.tga");
	std::shared_ptr<SpriteAnimation> obj2 = std::make_shared<SpriteAnimation>(model, shader, texture, 12, 1, 0, 0.1f);
	obj2->Set2DPosition(500.0f, 500.0f);
	obj2->SetSize(0, 0);
	obstacleObj = obj2;
	m_listObstacle.push_back(obstacleObj);

	std::shared_ptr<SpriteAnimation> obj3 = std::make_shared<SpriteAnimation>(model, shader, texture, 12, 1, 0, 0.1f);
	obj3->Set2DPosition(-1.0f, -1.0f);
	obj3->SetSize(0, 0);
	obstacleObj1 = obj3;
	m_listObstacle.push_back(obstacleObj1);

	std::shared_ptr<SpriteAnimation> obj4 = std::make_shared<SpriteAnimation>(model, shader, texture, 12, 1, 0, 0.1f);
	obj4->Set2DPosition(-1.0f, -1.0f);
	obj4->SetSize(0, 0);
	obstacleObj2 = obj4;
	m_listObstacle.push_back(obstacleObj2);

	std::shared_ptr<SpriteAnimation> obj5 = std::make_shared<SpriteAnimation>(model, shader, texture, 12, 1, 0, 0.1f);
	obj5->Set2DPosition(-1.0f, -1.0f);
	obj5->SetSize(0, 0);
	obstacleObj3 = obj5;
	m_listObstacle.push_back(obstacleObj3);

	//Obstacle
	/*shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("Obstacle.tga");
	std::shared_ptr<SpriteAnimation> obj6 = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 1, 0, 0.1f);
	obj6->Set2DPosition(500.0f, 500.0f);
	obj6->SetSize(0, 0);
	obstacleObj4 = obj6;*/




	//sound
	std::string name = "Lobby-Time.mp3";
	ResourceManagers::GetInstance()->StopSound(name);
	ResourceManagers::GetInstance()->PlaySound(sound, true);
}



void GSPlay::Exit()
{
}


void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}


void GSPlay::HandleEvents()

{
	//Handle key event, insert more condition if you want to handle more than 4 default key
	if (m_KeyPress & 1)//Handle event when key 'A' was pressed
	{
		
	}
	if (m_KeyPress & (1 << 1))//Handle event when key 'S' was pressed
	{
		
	}
	if (m_KeyPress & (1 << 2))//Handle event when key 'D' was pressed
	{
		//Code to handle event
	}
	if (m_KeyPress & (1 << 3))//Handle event when key 'W' was pressed
	{
		if (mainObj->Get2DPosition().y <= 0)
		{
			mainObj->Set2DPosition(mainObj->Get2DPosition().x, mainObj->Get2DPosition().y);
		}
		else
		{
			mainObj->Set2DPosition(mainObj->Get2DPosition().x, mainObj->Get2DPosition().y - f_speed);
		}

	}
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)//Insert more case if you want to handle more than 4 default key
{
	if (bIsPressed)
	{
		switch (key)
		{
		case KEY_MOVE_LEFT://Key 'A' was pressed
			m_KeyPress |= 1;
			break;
		case KEY_MOVE_BACKWARD://Key 'S' was pressed
			m_KeyPress |= 1 << 1;
			break;
		case KEY_MOVE_RIGHT://Key 'D' was pressed
			m_KeyPress |= 1 << 2;
			break;
		case KEY_MOVE_FORWARD://Key 'W' was pressed
			m_KeyPress |= 1 << 3;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (key)
		{
		case KEY_MOVE_LEFT://Key 'A' was released
			m_KeyPress ^= 1;
			break;
		case KEY_MOVE_BACKWARD://Key 'S' was released
			m_KeyPress ^= 1 << 1;
			break;
		case KEY_MOVE_RIGHT:
			m_KeyPress ^= 1 << 2;//Key 'D' was released
			break;
		case KEY_MOVE_FORWARD://Key 'W' was released
			m_KeyPress ^= 1 << 3;
			break;
		default:
			break;
		}
	}
}

//Handle button event
void GSPlay::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(float x, float y)
{
	//Code to handle mouse event
}

void GSPlay::Update(float deltaTime)
{
	f_speed = 500.0f;
	f_speed *= deltaTime;
	HandleEvents();
	// Gravity
	if (mainObj->Get2DPosition().y < (float)Globals::screenHeight - 100)
	{
		float f_velocity = f_gravity * deltaTime;
		mainObj->Set2DPosition(mainObj->Get2DPosition().x, mainObj->Get2DPosition().y + f_velocity );
	}
	// moving background
	m_background->Set2DPosition(m_background->Get2DPosition().x - f_backgroundSpeed * deltaTime, m_background->Get2DPosition().y);
	m_background2->Set2DPosition(m_background2->Get2DPosition().x - f_backgroundSpeed * deltaTime, m_background2->Get2DPosition().y);
	if (m_background->Get2DPosition().x < (float) -Globals::screenWidth / 2)
	{
		m_background->Set2DPosition(m_background->Get2DPosition().x + Globals::screenWidth * 2, m_background->Get2DPosition().y);
	}
	if (m_background2->Get2DPosition().x < (float)-Globals::screenWidth / 2)
	{
		m_background2->Set2DPosition(m_background2->Get2DPosition().x + Globals::screenWidth * 2, m_background2->Get2DPosition().y);
	}

	// moving ground
	m_ground->Set2DPosition(m_ground->Get2DPosition().x - f_backgroundSpeed * deltaTime, m_ground->Get2DPosition().y);
	m_ground2->Set2DPosition(m_ground2->Get2DPosition().x - f_backgroundSpeed * deltaTime, m_ground2->Get2DPosition().y);
	m_ground3->Set2DPosition(m_ground3->Get2DPosition().x - f_backgroundSpeed * deltaTime, m_ground3->Get2DPosition().y);

	if (m_ground->Get2DPosition().x < (float)-Globals::screenWidth / 2)
	{
		m_ground->Set2DPosition(m_ground->Get2DPosition().x + Globals::screenWidth * 2, m_ground->Get2DPosition().y);
	}
	if (m_ground2->Get2DPosition().x < (float)-Globals::screenWidth / 2)
	{
		m_ground2->Set2DPosition(m_ground2->Get2DPosition().x + Globals::screenWidth * 2, m_ground2->Get2DPosition().y);
	}

	//ObstacleMoving
	
	for (auto it : m_listObstacle)
	{
		it->Set2DPosition(it->Get2DPosition().x - f_backgroundSpeed * deltaTime, it->Get2DPosition().y);
		

		if (it->Get2DPosition().x <= 0)
		{
			it->SetSize(50.0f, 50.0f);
			int temp = rand() % 451 + 10;
			it->Set2DPosition(1280.0f, (GLfloat)temp);
		}
	}
	
	

	// check collision
	for (auto it : m_listObstacle)
	{
		if (CheckCollision(mainObj, it))
		{
			it->SetSize(0,0);
			score +=1;
			m_score->SetText(std::to_string(score));
			m_score->Update(deltaTime);
			break;
		}
	}


	//Update button list
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

	//Update animation list
	for (auto it : m_listAnimation)
	{
		it->Update(deltaTime);
	}

	//Update Obstacle list
	for (auto it : m_listObstacle)
	{
		it->Update(deltaTime);
	}
}

void GSPlay::Draw()
{
	//Render background
	m_background->Draw();
	m_background2->Draw();

	//Render ground
	m_ground->Draw();
	m_ground2->Draw();

	//Render score text
	m_score->Draw();

	//Render button list
	for (auto it : m_listButton)
	{
		it->Draw();
	}

	//Render animation list
	for (auto it : m_listAnimation)
	{
		it->Draw();
	}

	//Render Obstacle list
	for (auto it : m_listObstacle)
	{
		it->Draw();
	}
}


bool GSPlay::CheckCollision(std::shared_ptr<SpriteAnimation> &one, std::shared_ptr<SpriteAnimation> &two)
{
	// collision x-axis?
	bool collisionX = one->Get2DPosition().x + one->GetWidth() >= two->Get2DPosition().x &&
		two->Get2DPosition().x + two->GetWidth() >= one->Get2DPosition().x;
	// collision y-axis?
	bool collisionY = one->Get2DPosition().y + one->GetHeight() >= two->Get2DPosition().y &&
		two->Get2DPosition().y + two->GetHeight() >= one->Get2DPosition().y;
	// collision only if on both axes
	return collisionX && collisionY;
}
#include "GSPlay.h"

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
std::string sound = "Run-Amok.mp3";
std::int32_t score = 0;

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
	texture = ResourceManagers::GetInstance()->GetTexture("bg_main.tga");
	m_background2 = std::make_shared<Sprite2D>(model, shader, texture);
	m_background2->Set2DPosition((float)Globals::screenWidth / 2.0f + Globals:: screenWidth , (float)Globals::screenHeight / 2.0f);
	m_background2->SetSize(Globals::screenWidth, Globals::screenHeight);

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
	m_score = std::make_shared< Text>(shader, font, "score: 10", TextColor::RED, 1.0f);
	m_score->Set2DPosition(Vector2(5.0f, 25.0f));

	//animation
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("Astronaut_Run.tga");
	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 1, 0, 0.1f);
	obj->Set2DPosition(240.0f, 400.0f);
	obj->SetSize(70, 70);
	m_listAnimation.push_back(obj);
	m_KeyPress = 0;
	mainObj = obj;
	m_listAnimation.push_back(mainObj);

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
		mainObj->Set2DPosition(mainObj->Get2DPosition().x, mainObj->Get2DPosition().y + 1);
	}
	if (m_KeyPress & (1 << 2))//Handle event when key 'D' was pressed
	{
		//Code to handle event
	}
	if (m_KeyPress & (1 << 3))//Handle event when key 'W' was pressed
	{
		mainObj->Set2DPosition(mainObj->Get2DPosition().x, mainObj->Get2DPosition().y - 1);
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
	HandleEvents();
	// moving background
	m_background->Set2DPosition(m_background->Get2DPosition().x - 100.0f * deltaTime, m_background->Get2DPosition().y);
	m_background2->Set2DPosition(m_background2->Get2DPosition().x - 100.0f * deltaTime, m_background2->Get2DPosition().y);
	if (m_background->Get2DPosition().x < (float) -Globals::screenWidth / 2)
	{
		m_background->Set2DPosition(m_background->Get2DPosition().x + Globals::screenWidth * 2, m_background->Get2DPosition().y);
	}
	if (m_background2->Get2DPosition().x < (float)-Globals::screenWidth / 2)
	{
		m_background2->Set2DPosition(m_background2->Get2DPosition().x + Globals::screenWidth * 2, m_background2->Get2DPosition().y);
	}
	//score
	score += 1 * deltaTime;
	std::string str = "score: " + std::to_string(score);
	m_score->SetText(str);
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
}

void GSPlay::Draw()
{
	//Render background
	m_background->Draw();
	m_background2->Draw();

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
}
#include "GSMenu.h"
#include "Camera.h"
GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU), 
	m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_textGameName(nullptr)
{
}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2.0f, Globals::screenHeight / 2.0f);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_play.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.0f , (float)(Globals::screenHeight / 2.0f) + 50.0f);
	button->SetSize(150, 150);
	button->SetOnClick([]() {
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50.0f, 50.0f);
	button->SetSize(50, 50);
	button->SetOnClick([]() {

		exit(0);
		});
	m_listButton.push_back(button);

	//mute button
	ResourceManagers::GetInstance()->is_muted = false;
	texture = ResourceManagers::GetInstance()->GetTexture("btn_music.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50.0f, Globals::screenHeight - 50);
	button->SetSize(50, 50);
	button->SetOnClick([button, texture]() {
		//Change texture on click
		if (button->GetTexture() == ResourceManagers::GetInstance()->GetTexture("btn_music.tga"))
		{
			button->SetTexture(ResourceManagers::GetInstance()->GetTexture("btn_music_off.tga"));
			ResourceManagers ::GetInstance()->StopSound("Lobby-Time.mp3");
			ResourceManagers ::GetInstance()->is_muted = true;
			
		}
		else
		{
			button->SetTexture(ResourceManagers::GetInstance()->GetTexture("btn_music.tga"));
			ResourceManagers::GetInstance()->PlaySound("Lobby-Time.mp3");
			ResourceManagers::GetInstance()->is_muted = false;
		}
	});
	m_listButton.push_back(button);


	// game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("slkscrb.ttf");
	m_textGameName = std::make_shared< Text>(shader, font, "Space Runner ", TextColor::WHITE, 2.0f);
	m_textGameName->Set2DPosition(Vector2(160, 150));

	std::string name = "Lobby-Time.mp3";
	ResourceManagers::GetInstance()->PlaySound(name);
} 

void GSMenu::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSMenu::Pause()
{
}

void GSMenu::Resume()
{
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSMenu::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSMenu::HandleMouseMoveEvents(float x, float y)
{
}

void GSMenu::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_textGameName->Draw();
}

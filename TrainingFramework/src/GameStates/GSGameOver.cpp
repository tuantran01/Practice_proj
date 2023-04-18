#include "GSGameOver.h"
#include "Camera.h"

GSGameOver::GSGameOver() : GameStateBase(StateType::STATE_GAMEOVER),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_textGameName(nullptr)
{

}

GSGameOver::~GSGameOver()
{
}

std::string strBgSoundName = "Run - Amok.mp3";
std::string strMenuSoundName = "Lobby-Time.mp3";
void GSGameOver::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main.tga");
	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2.0f, Globals::screenHeight / 2.0f);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);
	// restart button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.0f, (float)(Globals::screenHeight / 2.0f) + 50.0f);
	button->SetSize(150, 150);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button);
	// mute button
	if (ResourceManagers::GetInstance()->is_muted)
	{
		texture = ResourceManagers::GetInstance()->GetTexture("btn_music_off.tga");
	}
	else
	{
		texture = ResourceManagers::GetInstance()->GetTexture("btn_music.tga");
	}
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50.0f, Globals::screenHeight - 50.0f);
	button->SetSize(50, 50);
	button->SetOnClick([button]() {
		if (button->GetTexture() == ResourceManagers::GetInstance()->GetTexture("btn_music.tga"))
		{
			button->SetTexture(ResourceManagers::GetInstance()->GetTexture("btn_music_off.tga"));
			ResourceManagers::GetInstance()->StopSound("Lobby-Time.mp3");
			ResourceManagers::GetInstance()->is_muted = true;

		}
		else
		{
			button->SetTexture(ResourceManagers::GetInstance()->GetTexture("btn_music.tga"));
			ResourceManagers::GetInstance()->PlaySound("Lobby-Time.mp3");
			ResourceManagers::GetInstance()->is_muted = false;
		}
		});
	 m_listButton.push_back(button);
	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50.0f);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);
	// game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("slkscrb.ttf");
	m_textGameName = std::make_shared< Text>(shader, font, "Game Over", TextColor::WHITE, 3.0f);
	m_textGameName->Set2DPosition(Vector2(160, 150));
	std::string name = "Lobby-Time.mp3";
	ResourceManagers::GetInstance()->PlaySound(name);
}

void GSGameOver::Exit()
{
	ResourceManagers::FreeInstance();
}

void GSGameOver::Pause()
{
}

void GSGameOver::Resume()
{
}

void GSGameOver::HandleEvents()
{
}

void GSGameOver::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSGameOver::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		it->HandleTouchEvents(x, y, bIsPressed);
	}
}

void GSGameOver::HandleMouseMoveEvents(float x, float y)
{
}

void GSGameOver::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSGameOver::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_textGameName->Draw();
}
#include "GameButton.h"

GameButton::GameButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(-1, model, shader, texture), m_pBtClick(nullptr), m_isHolding(false)
{
}

GameButton::~GameButton()
{
}

void GameButton::SetOnClick(std::function<void(void)> pBtClick)
{
	m_pBtClick = pBtClick;
}

bool GameButton::HandleTouchEvents(GLfloat x, GLfloat y, bool bIsPressed)
{
	bool isHandled = false;
	if (bIsPressed)
	{
		if ((m_position.x - m_iWidth / 2.0f <= x)  && (x <= m_position.x + m_iWidth / 2.0f)
			&& (m_position.y - m_iHeight / 2.0f <= y) && (y <= m_position.y + m_iHeight / 2.0f))
		{
			// The button is being pressed down
			m_isHolding = true;
		}
	}
	else
	{
		if ((m_position.x - m_iWidth / 2.0f <= x) && (x <= m_position.x + m_iWidth / 2.0f)
			&& (m_position.y - m_iHeight / 2.0f <= y) && (y <= m_position.y + m_iHeight / 2.0f)
			&& m_isHolding == true)
		{
			// Only perform click action when the same button was pressed down and released
			m_pBtClick();
			isHandled = true;
		}
		m_isHolding = false;
	}
	return isHandled;
}

bool GameButton::IsHolding()
{
	return m_isHolding;
}

#pragma once
#include"GameConfig.h"
#include <string>
#include <vector>
#include "ft2build.h"
#include FT_FREETYPE_H

struct GlyphData
{
	int left;
	int top;
	int width;
	int height;
	float u0, u1;
	float v0, v1;
	int advanceX;
	int advanceY;
};

class Font
{

public:
	Font(const std::string& font);
	~Font();
	bool		Init(const std::string& font);
	GLuint		GetFontTextureId();
	GLuint		GetFontVboId();
	FT_Face		GetFace();
	FT_GlyphSlot GetGlyphSlot();
	const bool	GetGlyphData(const char c, GlyphData* glyphData);

	void SetName(std::string name) {
		m_name = name;
	}
	std::string GetName() {
		return m_name;
	}
	void SetId(GLuint id) {
		m_id = id;
	}
	GLuint GetId() {
		return m_id;
	}

private:
	std::string		m_name;
	GLuint			m_id;
	GLuint			m_vboId;
	GLuint			m_textureId;

	FT_Library		m_library;
	FT_Face			m_face;
	FT_GlyphSlot	m_glyphSlot;

	std::vector<GlyphData> m_glyphData;
};

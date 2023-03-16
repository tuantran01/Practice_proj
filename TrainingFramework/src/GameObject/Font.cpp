#include "Font.h"
#include "GameConfig.h"



Font::Font(const std::string& font)
{
	Init(font);
}

Font::~Font()
{
	FT_Done_Face(m_face);
	FT_Done_FreeType(m_library);
}

bool Font::Init(const std::string& font)
{
	std::string _font = font;

	if (FT_Init_FreeType(&m_library))
	{
		printf("Could not init freetype library\n");
		return false;
	}

	if (FT_New_Face(m_library, _font.c_str(), 0, &m_face)) {
		printf("Could not open font %s\n", font.c_str());
		return false;
	}
	FT_Set_Pixel_Sizes(m_face, 0, 48);
	m_glyphSlot = m_face->glyph;

	const int k_glyphSlotSize = 64;
	const int k_atlasSize = 1024;
	unsigned char* buffer = new unsigned char[k_atlasSize * k_atlasSize];
	memset(buffer, 0, k_atlasSize * k_atlasSize);
	int x = 0;
	int y = 0;

	for (int c = 32; c < 126; c++)
	{
		FT_Load_Char(m_face, c, FT_LOAD_RENDER);
		for (int h = 0; h < m_glyphSlot->bitmap.rows; h++)
		{
			memcpy(&buffer[(y + h) * k_atlasSize + x], &m_glyphSlot->bitmap.buffer[h * m_glyphSlot->bitmap.width], m_glyphSlot->bitmap.width);
		}

		GlyphData glyphData;
		glyphData.left = m_glyphSlot->bitmap_left;
		glyphData.top = m_glyphSlot->bitmap_top;
		glyphData.width = m_glyphSlot->bitmap.width;
		glyphData.height = m_glyphSlot->bitmap.rows;
		glyphData.u0 = (float)x / k_atlasSize;
		glyphData.u1 = (float)(x + glyphData.width) / k_atlasSize;
		glyphData.v0 = (float)(y + glyphData.height) / k_atlasSize;
		glyphData.v1 = (float)y / k_atlasSize;
		glyphData.advanceX = m_glyphSlot->advance.x;
		glyphData.advanceY = m_glyphSlot->advance.y;
		m_glyphData.push_back(glyphData);

		x += k_glyphSlotSize;

		if (x >= k_atlasSize)
		{
			x = 0;
			y += k_glyphSlotSize;
		}
	}

	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, k_atlasSize, k_atlasSize, 0, GL_ALPHA, GL_UNSIGNED_BYTE, buffer);

	glBindTexture(GL_TEXTURE_2D, 0);

	glGenBuffers(1, &m_vboId);
	return true;
}

const bool Font::GetGlyphData(const char c, GlyphData* glyphData)
{
	*glyphData = m_glyphData[c - 32];
	return true;
}


GLuint Font::GetFontTextureId()
{
	return m_textureId;
}

GLuint Font::GetFontVboId()
{
	return m_vboId;
}

FT_Face Font::GetFace() {
	return m_face;
}

FT_GlyphSlot Font::GetGlyphSlot() {
	return m_glyphSlot;
}
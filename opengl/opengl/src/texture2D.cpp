#include <glerrorcheck.h>
#include <texture2D.h>
#include <ext\stb_image.h>




Texture2D::Texture2D(const std::string path)
	:	m_renderID(0),
		m_filePath(path),
		m_localBuffer(NULL),
		m_width(0),
		m_height(0),
		m_bitsPerPixel(0)
{
	stbi_set_flip_vertically_on_load(true);
	m_localBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bitsPerPixel, 4);

	GLCALL(glGenTextures(1, &m_renderID));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_renderID));

	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

	if(m_localBuffer){
		stbi_image_free(m_localBuffer);
	}
}


Texture2D::~Texture2D()
{
	GLCALL(glDeleteTextures(1, &m_renderID));
}

void Texture2D::Bind(unsigned int slot) const
{
	GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_renderID));
}


void Texture2D::UnBind() const
{
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}
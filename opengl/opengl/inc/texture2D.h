#pragma once
#include <iostream>

class Texture2D
{
public:
	Texture2D(const std::string path);
	~Texture2D();
	void Bind(unsigned int slot = 0) const;
	void UnBind() const;
	inline int GetWidth() const {return m_width;}
	inline int GetHeight() const {return m_height;}

private:
	unsigned int m_renderID;
	std::string m_filePath;
	unsigned char* m_localBuffer;
	int m_width;
	int m_height;
	int m_bitsPerPixel;
	
};


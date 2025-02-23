#include "Texture.h"
#include <cstring>
#include <GL/freeglut.h>
#include <FreeImage.h>


Texture::Texture(const std::string name) 
	: textName{ name }
	, Object { "Texture", name } {

	textId = 0;
	if (strstr((const char*)glGetString(GL_EXTENSIONS), "GL_EXT_texture_filter_anisotropic")) {
		isAnisotropicSupported = true;
		glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisotropicLevel);
	}

}

Texture::~Texture() {
}


void Texture::rendering(const glm::mat4& cameraInv) const {
	glBindTexture(GL_TEXTURE_2D, textId);

	// Set circular coordinates:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set anisotropic filtering:
	if (isAnisotropicSupported)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropicLevel);
	else
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);

	// Set trilinear filter and mipmapping:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

void Texture::setTextId() {
	if (textId) {
		glDeleteTextures(1, &textId);
	}
	glGenTextures(1, &textId);
	glBindTexture(GL_TEXTURE_2D, textId);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	std::string filePath = Texture::path + textName;
	FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(filePath.c_str(), 0), filePath.c_str());
	if (!bitmap) {
		bitmapExists = false;
		return;
	}

	FreeImage_FlipVertical(bitmap);

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA,
		FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap),
		GL_BGRA_EXT, GL_UNSIGNED_BYTE,
		(void*)FreeImage_GetBits(bitmap));

	// Release bitmap
	FreeImage_Unload(bitmap);
}


void Texture::setPath(const std::string& path) {
	Texture::path = path;
}

std::string Texture::getPath() {
	return path;
}

bool Texture::getAnisotropicLevel() {
	return anisotropicLevel;
}


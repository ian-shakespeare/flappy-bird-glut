#include "TextureManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const int num_textures = 6;
unsigned int texName[num_textures];

TextureManager::TextureManager()
{
	string textures[num_textures] = {
		"images/player.png",
		"images/pipe_body.png",
		"images/pipe_rim.png",
		"images/pipe_body_top.png",
		"images/pipe_rim_top.png",
		"images/background.jpg"
	};
	for (int i = 0; i < num_textures; i++)
	{
		look_up.insert(std::pair<string, unsigned int>(textures[i], i));
	}
}

void TextureManager::InitializeTextures()
{
	const char max_file_size = 100;
	char imageFiles[num_textures][max_file_size] = {
		"images/player.png",
		"images/pipe_body.png",
		"images/pipe_rim.png",
		"images/pipe_body_top.png",
		"images/pipe_rim_top.png",
		"images/background.jpg"
	};
	glGenTextures(num_textures, texName);

	for (int i = 0; i < num_textures; i++)
	{
		glBindTexture(GL_TEXTURE_2D, texName[i]);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(imageFiles[i], &width, &height, &nrChannels, 0);
		if (data)
		{
			if (nrChannels == 3)
			{
				gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

			}
			else
			{
				gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

			}
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}
}

void TextureManager::StartTexture(string name)
{
	glColor3d(1, 1, 1);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, texName[look_up[name]]);
}

void TextureManager::EndTexture()
{
	glDisable(GL_TEXTURE_2D);
	glColor3d(0, 0, 0);
}
// texture.h
// Alex Rutan / PA
// 11/22/15
// Bailey Dishman
// 12/4/18

#ifndef TEXTURE_EXIST
#define TEXTURE_EXIST

#include <SDL.h>
#include <SDL_image.h>
#include <string.h>


// Texture


class Texture
{

    private:

		// The hardware texture
		SDL_Texture* m_Texture;

		// Image dimensions
		int m_Width;
		int m_Height;

    public:

		// Constructor
		Texture();

		// Destructor
        ~Texture();

		// Getter methods for image dimensions
		int getWidth();
		int getHeight();

		void clearTexture();

		bool loadTextureFile(const char *path);

		// Renders texture at given point
		void render(int x, int y, SDL_Rect* clip = NULL);


}; // End of Texture

#endif //TEXTURE_EXISTS

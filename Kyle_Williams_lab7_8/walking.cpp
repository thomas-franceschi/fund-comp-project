//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <iostream>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );
		
		#ifdef _SDL_TTF_H
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif
		
		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Displays updated graphics on screen
void print( LTexture* );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gPressTexture;

LTexture gUpTexture0;
LTexture gUpTexture1;
LTexture gUpTexture2;
LTexture gUpTexture3;

LTexture gDownTexture0;
LTexture gDownTexture1;
LTexture gDownTexture2;
LTexture gDownTexture3;

LTexture gLeftTexture0;
LTexture gLeftTexture1;
LTexture gLeftTexture2;
LTexture gLeftTexture3;

LTexture gRightTexture0;
LTexture gRightTexture1;
LTexture gRightTexture2;
LTexture gRightTexture3;

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	
	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load press texture
	if( !gPressTexture.loadFromFile( "./DOWN_0.png" ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}
//======================================================================================================================//
	//Load up texture
	if( !gUpTexture0.loadFromFile( "./UP_0.png" ) )
	{
		printf( "Failed to load up texture!\n" );
		success = false;
	}
	//Load up texture
	if( !gUpTexture1.loadFromFile( "./UP_1.png" ) )
	{
		printf( "Failed to load up texture!\n" );
		success = false;
	}
	//Load up texture
	if( !gUpTexture2.loadFromFile( "./UP_2.png" ) )
	{
		printf( "Failed to load up texture!\n" );
		success = false;
	}
	//Load up texture
	if( !gUpTexture3.loadFromFile( "./UP_3.png" ) )
	{
		printf( "Failed to load up texture!\n" );
		success = false;
	}

//======================================================================================================================//

	//Load down texture
	if( !gDownTexture0.loadFromFile( "./DOWN_0.png" ) )
	{
		printf( "Failed to load down texture!\n" );
		success = false;
	}

	//Load down texture
	if( !gDownTexture1.loadFromFile( "./DOWN_1.png" ) )
	{
		printf( "Failed to load down texture!\n" );
		success = false;
	}

	//Load down texture
	if( !gDownTexture2.loadFromFile( "./DOWN_2.png" ) )
	{
		printf( "Failed to load down texture!\n" );
		success = false;
	}

	//Load down texture
	if( !gDownTexture3.loadFromFile( "./DOWN_3.png" ) )
	{
		printf( "Failed to load down texture!\n" );
		success = false;
	}

//======================================================================================================================//

	//Load left texture
	if( !gLeftTexture0.loadFromFile( "./LEFT_0.png" ) )
	{
		printf( "Failed to load left texture!\n" );
		success = false;
	}

	//Load left texture
	if( !gLeftTexture1.loadFromFile( "./LEFT_1.png" ) )
	{
		printf( "Failed to load left texture!\n" );
		success = false;
	}

	//Load left texture
	if( !gLeftTexture2.loadFromFile( "./LEFT_2.png" ) )
	{
		printf( "Failed to load left texture!\n" );
		success = false;
	}

	//Load left texture
	if( !gLeftTexture3.loadFromFile( "./LEFT_3.png" ) )
	{
		printf( "Failed to load left texture!\n" );
		success = false;
	}

//======================================================================================================================//

	//Load right texture
	if( !gRightTexture0.loadFromFile( "./RIGHT_0.png" ) )
	{
		printf( "Failed to load right texture!\n" );
		success = false;
	}

	//Load right texture
	if( !gRightTexture1.loadFromFile( "./RIGHT_1.png" ) )
	{
		printf( "Failed to load right texture!\n" );
		success = false;
	}

	//Load right texture
	if( !gRightTexture2.loadFromFile( "./RIGHT_2.png" ) )
	{
		printf( "Failed to load right texture!\n" );
		success = false;
	}

	//Load right texture
	if( !gRightTexture3.loadFromFile( "./RIGHT_3.png" ) )
	{
		printf( "Failed to load right texture!\n" );
		success = false;
	}

//======================================================================================================================//

	return success;
}

void close()
{
	//Free loaded images
	gPressTexture.free();

	gUpTexture0.free();
	gUpTexture1.free();
	gUpTexture2.free();
	gUpTexture3.free();

	gDownTexture0.free();
	gDownTexture1.free();
	gDownTexture2.free();
	gDownTexture3.free();

	gLeftTexture0.free();
	gLeftTexture1.free();
	gLeftTexture2.free();
	gLeftTexture3.free();

	gRightTexture0.free();
	gRightTexture1.free();
	gRightTexture2.free();
	gRightTexture3.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void print( LTexture* currentTexture )
{
	//Clear screen
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );

	//Render current texture
	currentTexture->render( 0, 0 );

	//Update screen
	SDL_RenderPresent( gRenderer );

}

int main( int argc, char* args[] )
{

	int clipSwitch = 0;
	int waitTime = 100;
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Current rendered texture
			LTexture* currentTexture = NULL;

			//While application is running
			while( !quit )
			{
				cout << "Dont quit" << endl;
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					cout << "Polling..." << endl;
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}
				cout << "hmmm..." << endl;
				//Set texture based on current keystate
				const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
				cout << "hit a key" << endl;
				if( currentKeyStates[ SDL_SCANCODE_UP ] )
				{
					cout << "KeyUp" << endl;

					currentTexture = &gUpTexture0;
					usleep( waitTime );
					print( currentTexture );

					currentTexture = &gUpTexture1;
					usleep( waitTime );
					print( currentTexture );

					currentTexture = &gUpTexture2;
					usleep( waitTime );
					print( currentTexture );

					currentTexture = &gUpTexture3;
					usleep( waitTime );
					print( currentTexture );

					clipSwitch = 1;
					
				}
				else if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
				{

					currentTexture = &gDownTexture0;
					usleep( waitTime );
					print( currentTexture );

					currentTexture = &gDownTexture1;
					usleep( waitTime );
					print( currentTexture );

					currentTexture = &gDownTexture2;
					usleep( waitTime );
					print( currentTexture );

					currentTexture = &gDownTexture3;
					usleep( waitTime );
					print( currentTexture );

					clipSwitch = 2;

				}
				else if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
				{

					currentTexture = &gLeftTexture0;
					usleep( waitTime );
					print( currentTexture );

					currentTexture = &gLeftTexture1;
					usleep( waitTime );
					print( currentTexture );

					currentTexture = &gLeftTexture2;
					usleep( waitTime );
					print( currentTexture );

					currentTexture = &gLeftTexture3;
					usleep( waitTime );
					print( currentTexture );

					clipSwitch = 3;

				}
				else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
				{

					currentTexture = &gRightTexture0;
					usleep( waitTime );
					print( currentTexture );

					currentTexture = &gRightTexture1;
					usleep( waitTime );
					print( currentTexture );

					currentTexture = &gRightTexture2;
					usleep( waitTime );
					print( currentTexture );

					currentTexture = &gRightTexture3;
					usleep( waitTime );
					print( currentTexture );

					clipSwitch = 4;

				}
				else
				{
					cout << clipSwitch << endl;
					switch ( clipSwitch ){
						case 1:
							currentTexture = &gUpTexture0;
							break;
						case 2:
							currentTexture = &gDownTexture0;
							break;
						case 3:
							currentTexture = &gLeftTexture0;
							break;
						case 4:
							currentTexture = &gRightTexture0;
							break;
						default:
							currentTexture = &gDownTexture0;

					}

				}

				print( currentTexture );
			}
		}
	}
	cout << "Closing time..." << endl;
	//Free resources and close SDL
	close();

	return 0;
}
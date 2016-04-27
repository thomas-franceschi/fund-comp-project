// Pokemon: Notre Dame Edition

// Kyle Williams, Brittany DiGenova, Thomas Franceschi

// Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <vector>

#include "trainer.h" // Include the trainer class

using namespace std;

// Screen dimension constants
const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 580;

// Texture wrapper class
class LTexture
{
	public:
		// Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		// Loads image at specified path
		bool loadFromFile( std::string path );
		
		#ifdef _SDL_TTF_H
		// Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif
		
		// Deallocates texture
		void free();

		// Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		// Set blending
		void setBlendMode( SDL_BlendMode blending );

		// Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		// Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		// Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		// The actual hardware texture
		SDL_Texture* mTexture;

		// Image dimensions
		int mWidth;
		int mHeight;
};

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// Load background graphics
bool loadBackground( std::string path );

// Displays updated graphics on screen
void print( LTexture*, LTexture*, int, int );

// Moves the x position for the background
int xMoveLeft( int );
int xMoveRight( int );

// Moves the y position for the background
int yMoveUp( int );
int yMoveDown( int );

void battleGFX( int );
// walking functions
int canWalk( int, int, int);
// int enterMorrissey( int&, int&, int&);

// The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The window renderer
SDL_Renderer* gRenderer = NULL;

// Scene textures
LTexture gPressTexture;

// Upward facing trainer sprite objects
LTexture gUpTexture0;
LTexture gUpTexture1;
LTexture gUpTexture2;
LTexture gUpTexture3;

// Downward facing trainer sprite objects
LTexture gDownTexture0;
LTexture gDownTexture1;
LTexture gDownTexture2;
LTexture gDownTexture3;

// Leftward facing trainer sprite objects
LTexture gLeftTexture0;
LTexture gLeftTexture1;
LTexture gLeftTexture2;
LTexture gLeftTexture3;

// Rightward facing trainer sprite objects
LTexture gRightTexture0;
LTexture gRightTexture1;
LTexture gRightTexture2;
LTexture gRightTexture3;

// Pokemon world texture objects
LTexture background;
LTexture morrissey;

// Pokemon battle texture objects
LTexture encounterGFX;
LTexture battleTXT;
LTexture trainerBackGFX;

LTexture SquirtleGFX;
LTexture DragoniteGFX;
LTexture MankeyGFX;
LTexture CharmanderGFX;
LTexture MagikarpGFX;
LTexture PidgeyGFX;

//======================================================================================================================//

// Functions used with the LTexture class based on the class from Lazyfoo

LTexture::LTexture()
{
	// Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	// Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	// Get rid of preexisting texture
	free();

	// The final texture
	SDL_Texture* newTexture = NULL;

	// Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		// Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		// Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			// Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;

		}

		// Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	// Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	// Get rid of preexisting texture
	free();

	// Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		// Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			// Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		// Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	
	// Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	// Free texture if it exists
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
	// Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	// Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	// Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	// Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	// Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	// Render to screen
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
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		// Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		// Create window
		gWindow = SDL_CreateWindow( "Pokemon Blue & Gold", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			// Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				// Initialize PNG loading
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
	// Loading success flag
	bool success = true;

	// Load press texture
	if( !gPressTexture.loadFromFile( "./DOWN_0.png" ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}
//======================================================================================================================//
	// Load up texture
	if( !gUpTexture0.loadFromFile( "./UP_0.png" ) )
	{
		printf( "Failed to load up texture!\n" );
		success = false;
	}
	// Load up texture
	if( !gUpTexture1.loadFromFile( "./UP_1.png" ) )
	{
		printf( "Failed to load up texture!\n" );
		success = false;
	}
	// Load up texture
	if( !gUpTexture2.loadFromFile( "./UP_2.png" ) )
	{
		printf( "Failed to load up texture!\n" );
		success = false;
	}
	// Load up texture
	if( !gUpTexture3.loadFromFile( "./UP_3.png" ) )
	{
		printf( "Failed to load up texture!\n" );
		success = false;
	}

//======================================================================================================================//

	// Load down texture
	if( !gDownTexture0.loadFromFile( "./DOWN_0.png" ) )
	{
		printf( "Failed to load down texture!\n" );
		success = false;
	}

	// Load down texture
	if( !gDownTexture1.loadFromFile( "./DOWN_1.png" ) )
	{
		printf( "Failed to load down texture!\n" );
		success = false;
	}

	// Load down texture
	if( !gDownTexture2.loadFromFile( "./DOWN_2.png" ) )
	{
		printf( "Failed to load down texture!\n" );
		success = false;
	}

	// Load down texture
	if( !gDownTexture3.loadFromFile( "./DOWN_3.png" ) )
	{
		printf( "Failed to load down texture!\n" );
		success = false;
	}

//======================================================================================================================//

	// Load left texture
	if( !gLeftTexture0.loadFromFile( "./LEFT_0.png" ) )
	{
		printf( "Failed to load left texture!\n" );
		success = false;
	}

	// Load left texture
	if( !gLeftTexture1.loadFromFile( "./LEFT_1.png" ) )
	{
		printf( "Failed to load left texture!\n" );
		success = false;
	}

	// Load left texture
	if( !gLeftTexture2.loadFromFile( "./LEFT_2.png" ) )
	{
		printf( "Failed to load left texture!\n" );
		success = false;
	}

	// Load left texture
	if( !gLeftTexture3.loadFromFile( "./LEFT_3.png" ) )
	{
		printf( "Failed to load left texture!\n" );
		success = false;
	}

//======================================================================================================================//

	// Load right texture
	if( !gRightTexture0.loadFromFile( "./RIGHT_0.png" ) )
	{
		printf( "Failed to load right texture!\n" );
		success = false;
	}

	// Load right texture
	if( !gRightTexture1.loadFromFile( "./RIGHT_1.png" ) )
	{
		printf( "Failed to load right texture!\n" );
		success = false;
	}

	// Load right texture
	if( !gRightTexture2.loadFromFile( "./RIGHT_2.png" ) )
	{
		printf( "Failed to load right texture!\n" );
		success = false;
	}

	// Load right texture
	if( !gRightTexture3.loadFromFile( "./RIGHT_3.png" ) )
	{
		printf( "Failed to load right texture!\n" );
		success = false;
	}

//======================================================================================================================//

	// Load background image
	if( !background.loadFromFile( "./notre_dame_pokemon_map.png" ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

		if( !morrissey.loadFromFile( "./morrissey_inside.png" ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

//================================================================================//

	// Load battle texture
	if( !encounterGFX.loadFromFile( "./encounter.png" ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

//================================================================================//

	// Load trainer texture
	if( !trainerBackGFX.loadFromFile( "./trainerBack.png" ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

//================================================================================//

	// Load battle text texture
	if( !battleTXT.loadFromFile( "./battletext.png" ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

//================================================================================//

	// Load wild squirtle texture
	if( !SquirtleGFX.loadFromFile( "./squirtle.png" ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

//================================================================================//

	// Load wild dragonite texture
	if( !DragoniteGFX.loadFromFile( "./dragonite.png" ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

//================================================================================//

	// Load wild magikarp texture
	if( !MagikarpGFX.loadFromFile( "./magikarp.png" ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

//================================================================================//

	// Load wild charmander texture
	if( !CharmanderGFX.loadFromFile( "./charmander.png" ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

//================================================================================//

	// Load wild pidgey texture
	if( !PidgeyGFX.loadFromFile( "./pidgey.png" ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

//================================================================================//

	// Load wild mankey texture
	if( !MankeyGFX.loadFromFile( "./mankey.png" ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	return success;
} // end of load media function

void close()
{
	// Free loaded images
	gPressTexture.free();

	// Free up textures
	gUpTexture0.free();
	gUpTexture1.free();
	gUpTexture2.free();
	gUpTexture3.free();

	// Free down textures
	gDownTexture0.free();
	gDownTexture1.free();
	gDownTexture2.free();
	gDownTexture3.free();

	// Free left textures
	gLeftTexture0.free();
	gLeftTexture1.free();
	gLeftTexture2.free();
	gLeftTexture3.free();

	// Free right textures
	gRightTexture0.free();
	gRightTexture1.free();
	gRightTexture2.free();
	gRightTexture3.free();

	// Free world map textures
	background.free();
	morrissey.free();

	// Free battle textures
	encounterGFX.free();
	trainerBackGFX.free();
	battleTXT.free();

	SquirtleGFX.free();
	CharmanderGFX.free();
	MankeyGFX.free();
	DragoniteGFX.free();
	MagikarpGFX.free();
	PidgeyGFX.free();

	// Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

//======================================================================================================================//

// This function renders the trainer, the background, and the Morrissey inside
//  The trainer sprites is rendered in the center of the screen, while the background
//  and Morrissey are rendered based on the x and y parameters to allow for movement by the trainer
void print( LTexture* currentTexture, LTexture* background, LTexture* morrissey, int x, int y, int inMorrissey )
{
	// Clear screen
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );

	// Render the background
	background->render( x, y );

	if (inMorrissey == 1) morrissey->render( x, y );

	// Render current texture
	currentTexture->render( SCREEN_WIDTH/2, SCREEN_HEIGHT/2 );

	// Update screen
	SDL_RenderPresent( gRenderer );

}


void battleGFX( int i ){

	// Clear screen
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );

	// Render the battle textures: background, trainer, Pokemon, and text
	encounterGFX.render(0, 0);
	trainerBackGFX.render(50, 165);
	battleTXT.render(30, 425);

	// switches the random Pokemon that is encountered
	switch (i){
		case 0:
			CharmanderGFX.render(440, 95);
			break;
		case 1:
			MankeyGFX.render(440, 95);
			break;
		case 2:
			SquirtleGFX.render(440, 95);
			break;
		case 3:
			MagikarpGFX.render(440, 95);
			break;
		case 4:
			PidgeyGFX.render(440, 95);
			break;
		case 5:
			DragoniteGFX.render(440, 95);
			break;
	}

	SDL_RenderPresent( gRenderer );

}

// This function increments the x value of where the background is being rendered 
//  to make it appear like the trainer sprite is walking around
int xMoveLeft( int x, int y, int inMorrissey )
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

	// Checks if player is not out of bounds, or in Morrissey Hall
	if (canWalk(x + 3, y, inMorrissey) == 1){

		// Checks if space bar is pressed to run
		if(currentKeyStates[SDL_SCANCODE_SPACE]) x += 3;
		else{
			x++;
		}

	}

	return x;

}

// This function decrements the x value of where the background is being rendered 
//  to make it appear like the trainer sprite is walking around
int xMoveRight( int x, int y, int inMorrissey )
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

	// Checks if player is not out of bounds, or in Morrissey Hall
	if (canWalk(x - 3, y, inMorrissey) == 1){

		// Checks if space bar is pressed to run
		if(currentKeyStates[SDL_SCANCODE_SPACE]) x -= 3;
		else{
			x--;
		}

	}

	return x;

}

// This function increments the y value of where the background is being rendered 
//  to make it appear like the trainer sprite is walking around
int yMoveUp( int x, int y, int inMorrissey )
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

	// Checks if player is not out of bounds, or in Morrissey Hall
	if (canWalk(x, y + 3, inMorrissey) == 1){	

		// Checks if space bar is pressed to run
		if(currentKeyStates[SDL_SCANCODE_SPACE]) y += 3;
		else{
			y++;
		}

	}

	return y;

}

// This function deccrements the y value of where the background is being rendered 
//  to make it appear like the trainer sprite is walking around
int yMoveDown( int x, int y, int inMorrissey )
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

	// Checks if player is not out of bounds, or in Morrissey Hall
	if (canWalk(x, y - 3, inMorrissey) == 1){

		// Checks if space bar is pressed to run
		if(currentKeyStates[SDL_SCANCODE_SPACE]) y -= 3;
		else{
			y--;
		}

	}

	return y;

}

//Wild pokemon encounter-----------------------------------------------------
void wildBattle( int x, int y, Trainer trainer, Pokemon &wildPoke, LTexture *encounterGFX, int i ){
	srand(time(NULL));
	int encounter = rand() % 5;
	char battleOver = ' ';
	//cout << "encounter number" << encounter << endl;

	//square patch on south quad
	if ( x <= -632 && x >= -1004){
		if ( y <= -1940 && y >= -2108) {
			if ( encounter == 0 ){
				cout << "You've encountered a wild " << wildPoke.get_name() << endl;
				while ( battleOver != 'e' )
				{
					battleGFX( i );
					trainer.encounter_pokemon( wildPoke );
					cout << "press 'e' to exit battle and 's' to list stats" << endl;
					cin >> battleOver;
					if (battleOver == 's' ) {
						trainer.list_stats();
						battleOver = 'e';
					}
					if (battleOver != 'e' && battleOver != 's') battleOver = ' ';
			 	}
			}
		}
	}

	cout << "STATS:" << endl;
	trainer.list_stats();
}

//enterMorrissey/exitMorrissey----------------------------------------------------------------

// This function checks to see if the player is within the certain x and y parameters that puts the trainer in Morrissey
int enterMorrissey( int &x, int &y, int inMorrissey ) {
	if (inMorrissey == 1) return 1;
	if ( x <= -715 && x >= -720){
		if ( y <= -1390 && y >= -1405){
			x = -1136;
			y = -1390;
			return 1;
		}
	}
	else return 0;
}

// This function checks to see if the player is within the certain x and y parameters that puts the trainer out of Morrissey
int exitMorrissey( int &x, int &y, int inMorrissey){
	// exit front door
	if (inMorrissey == 1 && x <= -1130 && x >= -1140 && y <= -1395 && y >= -1450) {
		x = -716;
		y = -1410;
		return 0;
	}
	// exit right side door
	if (inMorrissey == 1 && x <= -2048 && x >= -2058 && y <= -1158 && y >= -1166) {
		x = -1027;
		y = -1338;
		return 0;
	}
	// exit left side door
	if (inMorrissey == 1 && x <= -150 && x >= -160 && y <= -1158 && y >= -1166) {
		x = -637;
		y = -1322;
		return 0;
	}

	else if (inMorrissey == 0) return 0;
	else if (inMorrissey == 1) return 1;
	else return 0;
}

//canWalk--------------------------------------------------------------------

// This function checks to see if the player can move the trainer in the specified areas so as not to go out of bounds
int canWalk( int x, int y, int inMorrissey ){
	//overworld boundaries
	if ( inMorrissey != 1 ) {
		//out of bounds
		if ( x + 3 > 0 ) return 0;
		if ( y + 3 > -113 ) return 0;
		if ( x + 3 < -2618 ) return 0;
		if ( y + 3 < -2274 ) return 0;
		//Upper left corner bound
		if ( x > -1225 && y > -378 ) return 0;
		//upper right corner bound
		if ( x < -1680 && y > -950 ) return 0;
		//lake
		//if ( x <= -758 && x >= -1066 && y <= -1354 && y >= -1446) return 0;

		//morrissey
		if ( x <= -640 && x >= -1024 && y <= -1235 && y >= -1402) return 0;
		if ( x <= -640 && x >= -838 && y <= -1065 && y >= -1402) return 0;
		if ( x <= -572 && x >= -696 && y <= -1330 && y >= -1446) return 0;
		if ( x <= -758 && x >= -1066 && y <= -1354 && y >= -1446) return 0;
		//parking lot trees
		if ( x <= -190 && x >= -468 && y <= -1148 && y >= -1284) return 0;
		//volleyb all net
		if ( x <= -308 && x >= -340 && y <= -1004 && y >= -1172) return 0;



		//Howard Hall
		if ( x <= -1101 && x >= -1289 && y <= -1353 && y >= -1791) return 0;
		if ( x <= -1101 && x >= -1353 && y <= -1553 && y >= -1791) return 0;
		//Badin Hall
		if ( x <= -1430 && x >= -1616 && y <= -1363 && y >= -1791) return 0;
		if ( x <= -1430 && x >= -1697 && y <= -1523 && y >= -1775) return 0;
		if ( x <= -1430 && x >= -1635 && y <= -1600 && y >= -1791) return 0;
		//Bond Hall
		if ( x <= -1101 && x >= -1288 && y <= -988 && y >= -1240) return 0;
		if ( x <= -1101 && x >= -1370 && y <= -1171 && y >= -1240) return 0;
		if ( x <= -1101 && x >= -1370 && y <= -988 && y >= -1109) return 0;
		//Bond dumpster and truck
		if ( x <= -953 && x >= -1110 && y <= -1005 && y >= -1093) return 0;
		//Lyons to left edge
		if ( x <= 0 && x >= -551 && y <= -1360 && y >= -1776) return 0;
		if ( x <= -313 && x >= -551 && y <= -1776 && y >= -1855) return 0;
		if ( x <= 0 && x >= -301 && y <= -1776 && y >= -1855) return 0;
		//CoMo
		if ( x <= -1904 && x >= -2212 && y <= -1432 && y >= -1792) return 0;


		//South quad upper trees + fenced areas
		if ( x <= -541 && x >= -1067 && y <= -1740 && y >= -1855) return 0;
		if ( x <= -1083 && x >= -1183 && y <= -1777 && y >= -1855) return 0;
		if ( x <= -1211 && x >= -1371 && y <= -1353 && y >= -1855) return 0;
		if ( x <= -1560 && x >= -1720 && y <= -1353 && y >= -1855) return 0;
		if ( x <= -1904 && x >= -1988 && y <= -1432 && y >= -1855) return 0;
		if ( x <= -2128 && x >= -2212 && y <= -1432 && y >= -1855) return 0;


		//South quad lower trees
		if ( x <= 0 && x >= -388 && y <= -2130 && y >= -2250) return 0;
		if ( x <= -472 && x >= -1064 && y <= -2130 && y >= -2250) return 0;
		if ( x <= -1084 && x >= -1552 && y <= -2130 && y >= -2250) return 0;
		if ( x <= -1780 && x >= -2600 && y <= -2130 && y >= -2250) return 0;




		//Lyons parking lot
		if ( x <= 0 && x >= -193 && y <= -987 && y >= -1400 ) return 0;

		else return 1;

	}
	//inside morrissey boundaries
	else if ( inMorrissey == 1){
		return 1;
	}
	else return 1;
}



//Main function--------------------------------------------------------------
int main( int argc, char* args[] )
{

	int clipSwitch = 0; // determines the frame to render when the player stops moving
	int framecounter = 0; // count the frames being rendered
	int waitTime = 10; 
	int x = -716; // initial x position
	int y = -1450; // initial y position
	int inMorrissey = 0; // integer telling whether or not the player is inside Morrissey
	string name;
	int pokemon_val = 0;

	// Trainer object instantiation

	//Ask user what they want to be named
	cout << "Hello friend! What would you like your training name to be: ";
	cin >> name;
	cout << endl;
	//Trainers
	Trainer trainer(name, 2); //Sets trainers name to inputted value
	cout << "Welcome " << name << "!" << endl << endl;

	Trainer fatherV( "Father V", 0); //Initialize Father V

	//Pokemon
	//Initialize firetype pokemon
	Firetype Charmander("Charmander", 39, 39, 52, 43, 3, 12, 0, 0, 0);
	Firetype Mankey("Mankey", 40, 40, 80, 35, 3, 12, 0, 0, 0); 

	//Initialize watertype pokemon 
	Watertype Squirtle("Squirtle", 44, 44, 48, 65, 4, 12, 0, 0, 0 );
	Watertype Magikarp("Magikarp", 20, 20, 10, 55, 3, 12, 0, 0, 0);

	//Initialize Flyingtype Pokemon
	Flyingtype Pidgey("Pidgey", 40, 40, 45, 40, 3, 12, 0, 0, 0);
	Flyingtype Dragonite("Dragonite", 91, 91, 134, 95, 20, 40, 0, 0, 0);


	//Potions
	Potion potion("potion", 20);
	Potion super_potion ("super_potion", 50);
		

	//Moves 
	Moves pound("Pound", 40, 90);
	Moves hydro_pump("Hydro Pump", 110, 80);
	Moves headbutt("Headbutt", 70, 100);
	Moves tackle("Tackle", 50, 90);
	Moves bodyslam("Bodyslam", 85, 75);
	Moves peck("Peck", 35, 100);
	Moves flamethrower("Flamethrower", 90 , 100); 
	Moves splash("Splash", 0, 0);
	Moves vinewhip("Vine Whip", 45, 100);
	Moves quick_attack("Quick Attack", 40, 100);
	Moves thunder("Thunder", 110, 70);
	Moves powder_snow("Powder Snow", 40, 100);
	Moves slash("Slash", 70, 100);
	Moves rock_slide("Rock Slide", 75, 90);
	Moves wing_attack("Wing Attack", 60, 100);


	//Give Pokemon moves
	Charmander.add_move(pound);
	Charmander.add_move(tackle);
	Charmander.add_move(flamethrower);

	Mankey.add_move(vinewhip);
	Mankey.add_move(slash);
	Mankey.add_move(rock_slide);

	Squirtle.add_move(splash);
	Squirtle.add_move(hydro_pump);
	Squirtle.add_move(tackle);

	Magikarp.add_move(splash);
	Magikarp.add_move(pound);
	Magikarp.add_move(quick_attack);

	Pidgey.add_move(wing_attack);
	Pidgey.add_move(quick_attack);
	Pidgey.add_move(peck);

	Dragonite.add_move(wing_attack);
	Dragonite.add_move(thunder);
	Dragonite.add_move(tackle);

	trainer.catch_pokemon(Squirtle);
	trainer.catch_pokemon(Pidgey);
	trainer.add_potion(potion);
	trainer.add_potion(super_potion);

	fatherV.catch_pokemon(Dragonite);
	fatherV.catch_pokemon(Mankey);
	fatherV.catch_pokemon(Magikarp);
	fatherV.catch_pokemon(Charmander);

	vector < Pokemon > game_pokemon;
	game_pokemon.push_back(Charmander);
	game_pokemon.push_back(Mankey);
	game_pokemon.push_back(Squirtle);
	game_pokemon.push_back(Magikarp);
	game_pokemon.push_back(Pidgey);
	game_pokemon.push_back(Dragonite);


	//give fatherv Pokemon

	// Start up SDL and create window
	if( !init() ) printf( "Failed to initialize!\n" );
	else {
		// Load media
		if( !loadMedia() ) printf( "Failed to load media!\n" );
		else {	
			// Main loop flag
			bool quit = false;

			// Event handler
			SDL_Event e;

			// Current rendered texture
			LTexture* currentTexture = NULL;
			
			// While application is running
			while( !quit ) {
				// Handle events on queue
				while( SDL_PollEvent( &e ) != 0 ) {
					// User requests quit
					if( e.type == SDL_QUIT ) quit = true;
				}
				// randomizes Pokemon that a trainer can encounter
				srand(time(NULL));
				pokemon_val = rand () % game_pokemon.size();
				for (int i = 0; i < game_pokemon.size(); i++ ) {
					game_pokemon[i].set_hit_points(game_pokemon[i].get_max_hit_points()); //Make all encounterable pokemon full health
				}
				//cout << "MENU: " << endl << "===================" << "PRESS 1 to list stats" << endl << "PRESS 2 to list Pokemon" << endl << "PRESS e TO EXIT" << endl;
				//Trainer.check_press();
				// Set texture based on current keystate
				const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
				
					// When "up" arrow key is held down...
					if( currentKeyStates[ SDL_SCANCODE_UP ] ){

						// moves the trainer in the y direction, rendering a different up image each frame to
						//  make it look like the tainer is walking with one foot forward at a time
						if (framecounter%4 == 0) currentTexture = &gUpTexture0;
						y = yMoveUp( x, y, inMorrissey );
						print( currentTexture, &background, &morrissey, x, y, inMorrissey );

						if (framecounter%4 == 1) currentTexture = &gUpTexture1;
						y = yMoveUp( x, y, inMorrissey );
						print( currentTexture, &background, &morrissey, x, y, inMorrissey );

						if (framecounter%4 == 2) currentTexture = &gUpTexture2;
						y = yMoveUp( x, y, inMorrissey );
						print( currentTexture, &background, &morrissey, x, y, inMorrissey );

						if (framecounter%4 == 3) currentTexture = &gUpTexture3;
						y = yMoveUp( x, y, inMorrissey );
						print( currentTexture, &background, &morrissey, x, y, inMorrissey );
						
						// sets stopping sprite image to one facing the same direction the sprite was walking
						clipSwitch = 1;

						// checks if trainer has entered a wild Pokemon battle
						wildBattle(x, y, trainer, game_pokemon[pokemon_val], &encounterGFX, pokemon_val);

						// displays x and y position and framecount to terminal
						cout << x << endl << y << endl;
						//cout << "frame count:" << framecounter << endl;
					}
					// When "down" arrow key is held down...
					else if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
					{
						// moves the trainer in the y direction, rendering a different down image each frame to
						//  make it look like the tainer is walking with one foot forward at a time
						if (framecounter%4 == 0) currentTexture = &gDownTexture0;
						y = yMoveDown( x, y, inMorrissey );
						print( currentTexture, &background, &morrissey, x, y, inMorrissey );

						if (framecounter%4 == 1) currentTexture = &gDownTexture1;
						y = yMoveDown( x, y, inMorrissey );
						print( currentTexture, &background, &morrissey, x, y, inMorrissey );

						if (framecounter%4 == 2) currentTexture = &gDownTexture2;
						y = yMoveDown( x, y, inMorrissey );
						print( currentTexture, &background, &morrissey, x, y, inMorrissey );

						if (framecounter%4 == 3) currentTexture = &gDownTexture3;
						y = yMoveDown( x, y, inMorrissey );
						print( currentTexture, &background, &morrissey, x, y, inMorrissey );

						// sets stopping sprite image to one facing the same direction the sprite was walking
						clipSwitch = 2;

						// checks if trainer has entered a wild Pokemon battle
						wildBattle(x, y, trainer, game_pokemon[pokemon_val], &encounterGFX, pokemon_val);

						// displays x and y position and framecount to terminal
						cout << x << endl << y << endl;
						//cout << "frame count:" << framecounter << endl;
					}
					// When "left" arrow key is held down...
					else if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
					{

						// moves the trainer in the x direction, rendering a different left image each frame to
						//  make it look like the tainer is walking with one foot forward at a time
						if (framecounter%4 == 0) currentTexture = &gLeftTexture0;
						x = xMoveLeft( x, y, inMorrissey );
						print( currentTexture, &background, &morrissey, x, y, inMorrissey );

						if (framecounter%4 == 1) currentTexture = &gLeftTexture1;
						x = xMoveLeft( x, y, inMorrissey );
						print( currentTexture, &background, &morrissey, x, y, inMorrissey );

						if (framecounter%4 == 2) currentTexture = &gLeftTexture2;
						x = xMoveLeft( x, y, inMorrissey );
						print( currentTexture, &background, &morrissey, x, y, inMorrissey );

						if (framecounter%4 == 3) currentTexture = &gLeftTexture3;
						x = xMoveLeft( x, y, inMorrissey );
						print( currentTexture, &background, &morrissey, x, y, inMorrissey );

						// sets stopping sprite image to one facing the same direction the sprite was walking
						clipSwitch = 3;

						// checks if trainer has entered a wild Pokemon battle
						wildBattle(x, y, trainer, game_pokemon[pokemon_val], &encounterGFX, pokemon_val);

						// displays x and y position and framecount to terminal
						cout << x << endl << y << endl;
						//cout << "frame count:" << framecounter << endl;

					}
					// When "right" arrow key is held down...
					else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
					{

						// moves the trainer in the x direction, rendering a different right image each frame to
						//  make it look like the tainer is walking with one foot forward at a time
						if (framecounter%4 == 0) currentTexture = &gRightTexture0;
						x = xMoveRight( x, y, inMorrissey );
						print( currentTexture, &background, &morrissey, x, y, inMorrissey );

						if (framecounter%4 == 1) currentTexture = &gRightTexture1;
						x = xMoveRight( x, y, inMorrissey );
						print( currentTexture, &background, &morrissey, x, y, inMorrissey );

						if (framecounter%4 == 2) currentTexture = &gRightTexture2;
						x = xMoveRight( x, y, inMorrissey );
						print( currentTexture, &background, &morrissey, x, y, inMorrissey );

						if (framecounter%4 == 3) currentTexture = &gRightTexture3;
						x = xMoveRight( x, y, inMorrissey );
						print( currentTexture, &background, &morrissey, x, y, inMorrissey );

						// sets stopping sprite image to one facing the same direction the sprite was walking
						clipSwitch = 4;

						// checks if trainer has entered a wild Pokemon battle
						wildBattle(x, y, trainer, game_pokemon[pokemon_val] , &encounterGFX, pokemon_val);

						// displays x and y position and framecount to terminal
						cout << x << endl << y << endl;
						//cout << "frame count:" << framecounter << endl;
					}
					else
					{
						// sets the position of the trainer sprite to face the direction that
						//  he was facing before the user let go of one of the  arrow keys
						switch ( clipSwitch )
						{
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
				
				// checks if the trainer has entered Morrissey
				inMorrissey = enterMorrissey( x, y, inMorrissey);
				inMorrissey = exitMorrissey( x, y, inMorrissey);
				
				// increment frames
				framecounter++;
				//if ( framecounter > 10000) framecounter = 0;
				print( currentTexture, &background, &morrissey, x, y, inMorrissey );				
			}
		}
		//	close();
	}

	//Free resources and close SDL



	//return 0;
}

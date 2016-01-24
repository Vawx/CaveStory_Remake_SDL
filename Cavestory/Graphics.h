/** -----------------------------------------
 * Remaking Cavestory using SDL 2.0
 * https://www.youtube.com/watch?v=ETvApbD5xRo&index=1&list=PLNOBk_id22bw6LXhrGfhVwqQIa-M2MsLa
 * Instruction by Limeoats : www.limeoats.com
 * Kyle Langley
 * www.dotvawxgames.com
 * 2015
 * -----------------------------------------*/

/**
 * Holds all information dealing with graphics for the game
 */

#pragma once
#include <string>
#include <map>
#include <SDL.h>
#include "CaveRectangle.h"

class Graphics
{
public:
	
	/** Constructor */
	Graphics( );

	/** Destructor */
	~Graphics( );

	/** Load image into m_SpriteSheets map (hash)
	 * @param FilePath : File path to load image from.
	 */
	SDL_Surface *LoadImage( const std::string &FilePath );

	/** Draws textures to SDL_Window
	 * @param Texture : Texture to draw
	 * @param SourceRectangle : Size of texture to draw
	 * @param DestinationRectangle : Where on SDL_Window to draw texture
	 */
	void BlitSurface( SDL_Texture* Source, SDL_Rect* SourceRectangle, SDL_Rect* DestinationRectangle );

	/**
	 * Draws whats in the surface renderer to the SDL_Window
	 */
	void RenderTexture( );

	/** Draws triangle */
	void DrawTexture( CaveRectangle &Rectangle );

	/**
	 * Clears everything to the SDL_Window
	 */
	void Clear( );

	/** 
	 * @return SDL_Renderer 
	 */
	SDL_Renderer* GetRenderer( ) const;

	/** 
	 * @return SDL_Window 
	 */
	SDL_Window* GetWindow( ) const;

private:

	/** Main game window */
	SDL_Window * m_Window;

	/** Main game renderer */
	SDL_Renderer* m_Renderer;

	/** GL context */
	SDL_GLContext m_GLContext;

	/** Buffer to hold sprite sheets */
	std::map<std::string, SDL_Surface*> m_SpriteSheets;
};
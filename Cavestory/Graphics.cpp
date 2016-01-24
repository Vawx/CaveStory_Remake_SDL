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
#include <SDL.h>
#include <SDL_image.h>
#include "Graphics.h"
#include "Globals.h"
#include "CaveRectangle.h"

// Constructor
Graphics::Graphics( )
{
	SDL_CreateWindowAndRenderer( GameGlobals::SCREEN_WIDTH, GameGlobals::SCREEN_HEIGHT, 0, &m_Window, &m_Renderer );
	SDL_SetWindowTitle( m_Window, "Cavestory" );
}

// Destructor
Graphics::~Graphics( )
{
	SDL_DestroyWindow( m_Window );
	SDL_DestroyRenderer( m_Renderer );
}

// Load image into m_SpriteSheets map (hash)
SDL_Surface* Graphics::LoadImage( const std::string &FilePath )
{
	if ( m_SpriteSheets.count( FilePath ) == 0 )
	{
		m_SpriteSheets[ FilePath ] = IMG_Load( FilePath.c_str( ) );
	}
	return m_SpriteSheets[ FilePath ];
}

// Draws textures to SDL_Window
void Graphics::BlitSurface( SDL_Texture* Source, SDL_Rect* SourceRectangle, SDL_Rect* DestinationRectangle )
{
	SDL_RenderCopy( m_Renderer, Source, SourceRectangle, DestinationRectangle );
}


// Draws whats in the surface renderer to the SDL_Window
void Graphics::RenderTexture( )
{
	SDL_RenderPresent( m_Renderer );
}

// Draws triangle
void Graphics::DrawTexture( CaveRectangle &Rectangle )
{
	SDL_Texture *texture = SDL_CreateTextureFromSurface( m_Renderer, LoadImage( "Content/Debug/red.png" ) );
	SDL_Rect sourceRectangle = { 0, 0, 64, 64 };
	SDL_Rect destinationRectangle = { Rectangle.GetLeft( ), Rectangle.GetTop( ), Rectangle.GetWidth( ), Rectangle.GetHeight( ) };
	BlitSurface( texture, &sourceRectangle, &destinationRectangle );
}


// Clears everything to the SDL_Window
void Graphics::Clear( )
{
	SDL_RenderClear( m_Renderer );
}


// SDL_Renderer 
SDL_Renderer* Graphics::GetRenderer( ) const
{
	return m_Renderer;
}

 
// SDL_Window 
SDL_Window* Graphics::GetWindow( ) const
{
	return m_Window;
}
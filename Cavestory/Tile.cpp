/** -----------------------------------------
 * Remaking Cavestory using SDL 2.0
 * https://www.youtube.com/watch?v=ETvApbD5xRo&index=1&list=PLNOBk_id22bw6LXhrGfhVwqQIa-M2MsLa
 * Instruction by Limeoats : www.limeoats.com
 * Kyle Langley
 * www.dotvawxgames.com
 * 2015
 * -----------------------------------------*/

#pragma once
#include "Tile.h"
#include "Graphics.h"
#include <SDL.h>

// Default constructor 
Tile::Tile( ){ }

// Constructor
Tile::Tile( SDL_Texture *TileSet, 
			Vector2 Size, 
			Vector2 TileSetPosition, 
			Vector2 Position ) :
			m_TileSet( TileSet ),
			m_Size( Size ),
			m_TileSetPosition( TileSetPosition ),
			m_Position( Vector2( Position.X * GameGlobals::SPRITE_SCALE, Position.Y * GameGlobals::SPRITE_SCALE ) )
{

}

// Called per frame
void Tile::Tick( float DeltaTime )
{

}

// To draw tileset on SDL_Window
void Tile::Draw( Graphics &Graphic )
{
	SDL_Rect destinationRectangle = { m_Position.X, m_Position.Y, m_Size.X * GameGlobals::SPRITE_SCALE, m_Size.Y * GameGlobals::SPRITE_SCALE };
	SDL_Rect sourceRectangle = { m_TileSetPosition.X, m_TileSetPosition.Y, m_Size.X, m_Size.Y };

	Graphic.BlitSurface( m_TileSet, &sourceRectangle, &destinationRectangle );
}
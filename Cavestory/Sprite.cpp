/** -----------------------------------------
 * Remaking Cavestory using SDL 2.0
 * https://www.youtube.com/watch?v=ETvApbD5xRo&index=1&list=PLNOBk_id22bw6LXhrGfhVwqQIa-M2MsLa
 * Instruction by Limeoats : www.limeoats.com
 * Kyle Langley
 * www.dotvawxgames.com
 * 2015
 * -----------------------------------------*/

#pragma once
#include "Sprite.h"
#include "Graphics.h"
#include "Globals.h"

// Default Constructor
Sprite::Sprite( )
{
}

// Constructor
Sprite::Sprite( Graphics &Graphic, const std::string &FilePath, int SourceX, int SourceY, int Width, int Height, float PosX, float PosY )
{
	_X = PosX;
	_Y = PosY;
	_SourceRectangle.x = SourceX;
	_SourceRectangle.y = SourceY;
	_SourceRectangle.w = Width;
	_SourceRectangle.h = Height;

	// Scale destination size with SPRITE_SCALE
	_DestinationRectangle.w = _SourceRectangle.w * GameGlobals::SPRITE_SCALE;
	_DestinationRectangle.h = _SourceRectangle.h * GameGlobals::SPRITE_SCALE;
	
	_SpriteSheet = SDL_CreateTextureFromSurface( Graphic.GetRenderer( ), Graphic.LoadImage( FilePath ) );
	if ( _SpriteSheet == NULL )
	{
		printf( "\nError: Unable to load image\n" );
	}

	_BoundingBox = CaveRectangle( _X, _Y, Width * GameGlobals::SPRITE_SCALE, Height * GameGlobals::SPRITE_SCALE );
}

// Destructor
Sprite::~Sprite( )
{

}

// On each frame
void Sprite::Update( )
{
	_BoundingBox = CaveRectangle( _X, _Y, _SourceRectangle.w * GameGlobals::SPRITE_SCALE, _SourceRectangle.h * GameGlobals::SPRITE_SCALE );
}

// Draw sprite to SDL_Window
void Sprite::Draw( Graphics &Graphic, int X, int Y )
{
	_DestinationRectangle.x = X;
	_DestinationRectangle.y = Y;
	Graphic.BlitSurface( _SpriteSheet, &_SourceRectangle, &_DestinationRectangle );
}


// Return collision bounding box 
CaveRectangle Sprite::GetBoundingBox( ) const
{
	return _BoundingBox;
}

// Determine which side of bounding box is colliding
CollisionSides::Side Sprite::GetCollisionSide( CaveRectangle &Other ) const
{
	int amountRight, amountLeft, amountTop, amountBottom;
	amountRight = GetBoundingBox( ).GetRight( ) - Other.GetLeft( );
	amountLeft = Other.GetRight( ) - GetBoundingBox( ).GetLeft( );
	amountTop = Other.GetBottom( ) - GetBoundingBox( ).GetTop( );
	amountBottom = GetBoundingBox( ).GetBottom( ) - Other.GetTop( );

	int amountValues[ 4 ] = { abs( amountRight ), abs( amountLeft ), abs( amountTop ), abs( amountBottom ) };
	int lowest = amountValues[ 0 ];
	for ( int i = 0; i < 4; i++ )
	{
		if ( amountValues[ i ] < lowest )
		{
			lowest = amountValues[ i ];
		}
	}

	if ( lowest == abs( amountRight ) )
	{
		return CollisionSides::Side::RIGHT;
	}
	else if ( lowest == abs( amountLeft ) )
	{
		return CollisionSides::Side::LEFT;
	}
	else if ( lowest == abs( amountTop ) )
	{
		return CollisionSides::Side::TOP;
	}
	else if ( lowest == abs( amountBottom ) )
	{
		return CollisionSides::Side::BOTTOM;
	}
	return CollisionSides::Side::NONE;
}

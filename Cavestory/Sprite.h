/** -----------------------------------------
 * Remaking Cavestory using SDL 2.0
 * https://www.youtube.com/watch?v=ETvApbD5xRo&index=1&list=PLNOBk_id22bw6LXhrGfhVwqQIa-M2MsLa
 * Instruction by Limeoats : www.limeoats.com
 * Kyle Langley
 * www.dotvawxgames.com
 * 2015
 * -----------------------------------------*/

/**
 * Holds all information for individual spritess
 */

#pragma once
#include <SDL.h>
#include <string>
#include "CaveRectangle.h"
#include "Graphics.h"
#include "Globals.h"


class Sprite
{
public:

	/** Default constructor */
	Sprite( );

	/** Constructor 
	 * @param Graphic : To draw to SDL_Window
	 * @param FilePath : Texture File path for sprite
	 * @param SourceX : X position on texture to get sprite from
	 * @param SourceY : Y position on texture to get sprite from
	 * @param Width : Size of sprite, wide
	 * @param Height : Size of sprite, tall
	 * @param PosX : Screen position, X
	 * @param PosY : Screen positino, Y
	 */
	Sprite( Graphics &Graphic, const std::string &FilePath, int SourceX, int SourceY, int Width, int Height, float PosX, float PosY );

	/** Destructor */
	virtual ~Sprite( );

	/** On each frame */
	virtual void Update( );

	/**
	 * Draw sprite to SDL_Window
	 * @param Graphic : Graphics class
	 * @param X : Screen position, in pixels, X
	 * @param Y : Screen position, in pixels, Y
	 */
	void Draw( Graphics &Graphic, int X, int Y );

	/** Determine which side of bounding box is colliding
	 * @param Other : Rectangle to check collision of
	 */
	CollisionSides::Side GetCollisionSide( CaveRectangle &Other ) const;

	/** Return collision bounding box */
	CaveRectangle GetBoundingBox( ) const;

protected:

	/** Area of sprite to render */
	SDL_Rect _SourceRectangle;

	/** Render size of the sprite */
	SDL_Rect _DestinationRectangle;

	/** Sprite sheet for this sprite */
	SDL_Texture* _SpriteSheet;

	/** Collision bounding box */
	CaveRectangle _BoundingBox;

	/** Sizes */
	float _X, _Y;

private:

};
/** -----------------------------------------
 * Remaking Cavestory using SDL 2.0
 * https://www.youtube.com/watch?v=ETvApbD5xRo&index=1&list=PLNOBk_id22bw6LXhrGfhVwqQIa-M2MsLa
 * Instruction by Limeoats : www.limeoats.com
 * Kyle Langley
 * www.dotvawxgames.com
 * 2015
 * -----------------------------------------*/

/**
 * Holds global variabls for Game
 */

#pragma once

namespace GameGlobals
{
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	const float SPRITE_SCALE = 2.0f;
}

namespace CollisionSides
{
	enum Side
	{
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		NONE
	};

	inline Side GetOppositeSide( Side From )
	{
		switch( From )
		{
		case TOP:
			return BOTTOM;
		case BOTTOM:
			return TOP;
		case LEFT:
			return RIGHT;
		case RIGHT:
			return LEFT;
		default:
			return NONE;
		}
	}
}

enum Direction
{
	LEFT, 
	RIGHT,
	UP, 
	DOWN,
};

struct Vector2
{
	int X, Y;
	Vector2( ) : X( 0 ), Y( 0 ) { }
	Vector2( int X, int Y ) : X( X ), Y( Y ) { }
	static Vector2 Zero( ) { return Vector2( 0,0 ); }
};

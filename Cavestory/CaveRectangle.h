/** -----------------------------------------
 * Remaking Cavestory using SDL 2.0
 * https://www.youtube.com/watch?v=ETvApbD5xRo&index=1&list=PLNOBk_id22bw6LXhrGfhVwqQIa-M2MsLa
 * Instruction by Limeoats : www.limeoats.com
 * Kyle Langley
 * www.dotvawxgames.com
 * 2015
 * -----------------------------------------*/

#pragma once
#include "Globals.h"

class CaveRectangle
{
public:

	/** Default constructor */
	CaveRectangle( ) { }

	/** Constructor 
	 * @param X : Position X
	 * @param Y : Position Y
	 * @param Width : Width
	 * @param Height : Height
	 */
	CaveRectangle( int X, int Y, int Width, int Height ) :
			   m_X( X ),
			   m_Y( Y ),
			   m_Width( Width ),
			   m_Height( Height )
	{
	}

	/** Destructor */
	~CaveRectangle( ) { }

	/** Get center of rectangle, on X */
	inline int GetCenterX( ) const { return m_X + m_Width / 2; }

	/** Get center of rectangle, on Y */
	inline int GetCenterY( ) const { return m_Y + m_Height / 2; }

	/** Get center of rectangle, on X and Y */
	inline Vector2 GetCenter( ) const { return Vector2( m_X + m_Width / 2, m_Y + m_Height / 2 ); }

	/** Get left of the rectangle */
	inline int GetLeft( ) const { return m_X; }

	/** Get right of the rectangle */
	inline int GetRight( ) const { return m_X + m_Width; }

	/** Get top of the rectangle */
	inline int GetTop( ) const { return m_Y; }

	/** Get bottom of the rectangle */
	inline int GetBottom( ) const { return m_Y + m_Height; }

	/** Get width of the rectangle */
	inline int GetWidth( ) const { return m_Width; }

	/** Get height of the rectangle */
	inline int GetHeight( ) const { return m_Height; }

	/** Get side of rectangle based on side
	 * @param Side : Collision side to get from 
	 * @return Position of rectangle side
	 */
	int GetSide( const CollisionSides::Side Side ) const 
	{
		switch( Side )
		{
		case CollisionSides::Side::BOTTOM:
			return GetBottom( );
		case CollisionSides::Side::TOP:
			return GetTop( );
		case CollisionSides::Side::LEFT:
			return GetLeft( );
		case CollisionSides::Side::RIGHT:
			return GetRight( );
		default:
			CollisionSides::Side::NONE;
		}
	}

	/** Checks if other rectangle is colliding with this
	 * @param Other : Other rectangle to check
	 * @return true( colliding) : false( not colliding )
	 */
	inline bool CollidesWith( const CaveRectangle &Other ) const
	{
		return GetRight( ) >= Other.GetLeft( ) &&
			   GetBottom( ) >= Other.GetTop( ) &&
			   GetLeft( ) <= Other.GetRight( ) &&
			   GetTop( ) <= Other.GetBottom( );
	}

	/** Check if this rectangle is valid (within ranges of what a rectangle is) */
	inline bool IsValid( ) const
	{
		return m_X >= 0 && m_Y >= 0 && m_Height >= 0 && m_Width >= 0;
	}

private:

	/** Rectangle position, X */
	int m_X;

	/** Rectangle position, Y */
	int m_Y;

	/** Rectangle width */
	int m_Width;

	/** Rectangle height */
	int m_Height;
};
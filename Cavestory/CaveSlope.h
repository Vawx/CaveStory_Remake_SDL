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
#include "CaveRectangle.h"
#include <cmath>

class CaveSlope
{
public:

	/** Default constructor */
	CaveSlope( ) { };

	/** Constructor 
	 * @param PointOne : First point of Slope
	 * @param PointTwo : Second point of slope 
	 */
	CaveSlope( Vector2 PointOne, Vector2 PointTwo ) :
		m_PointOne( PointOne ),
		m_PointTwo( PointTwo )
	{
		if ( m_PointTwo.X - m_PointOne.X != 0 )
		{
			m_Slope = ( fabs( (float)m_PointTwo.Y ) - fabs( (float)m_PointOne.Y ) ) / ( fabs( (float)m_PointTwo.X ) - fabs( (float)m_PointOne.X ) );		
		}
	}

	/** Get angle of slope */
	inline float GetSlope( ) const { return m_Slope; };

	/** Get position one */
	inline Vector2 GetPointOne( ) const { return m_PointOne; }

	/** get position two */
	inline Vector2 GetPointTwo( ) const { return m_PointTwo; }

	/** What this slope collides with 
	 * @param Other : To check if colliding.
	 */
	bool CollidesWith( const CaveRectangle &Other ) const
	{
		return ( Other.GetRight( ) >= m_PointTwo.X &&
				 Other.GetLeft( ) <= m_PointOne.X &&
				 Other.GetTop( ) <= m_PointTwo.Y &&
				 Other.GetBottom( ) >= m_PointOne.Y ) 
			||	
			   ( Other.GetRight( ) >= m_PointOne.X &&
				 Other.GetLeft( ) <= m_PointTwo.X &&
				 Other.GetTop( ) <= m_PointOne.Y &&
				 Other.GetBottom( ) >= m_PointTwo.Y )
			||
			   ( Other.GetLeft( ) <= m_PointOne.X &&
				 Other.GetRight( ) >= m_PointTwo.X &&
				 Other.GetTop( ) <= m_PointOne.Y &&
				 Other.GetBottom( ) >= m_PointTwo.Y )
			||
			   ( Other.GetLeft( ) <= m_PointTwo.X &&
				 Other.GetRight( ) >= m_PointOne.X &&
				 Other.GetTop( ) <= m_PointTwo.Y &&
				 Other.GetBottom( ) >= m_PointOne.Y );
	}

private:

	/** First point of slope */
	Vector2 m_PointOne;

	/** Second point of slope */
	Vector2 m_PointTwo;

	/** Angle of slope */
	float m_Slope;
};
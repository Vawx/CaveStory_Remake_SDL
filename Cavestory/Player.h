/** -----------------------------------------
 * Remaking Cavestory using SDL 2.0
 * https://www.youtube.com/watch?v=ETvApbD5xRo&index=1&list=PLNOBk_id22bw6LXhrGfhVwqQIa-M2MsLa
 * Instruction by Limeoats : www.limeoats.com
 * Kyle Langley
 * www.dotvawxgames.com
 * 2015
 * -----------------------------------------*/

#pragma once
#include "Graphics.h"
#include "AnimatedSprite.h"
#include "Globals.h"
#include "CaveSlope.h"

class Player : public AnimatedSprite
{
public:

	/** Constructor */
	Player( );

	/** Constructor
	 * @param Graphic : To draw player to SDL_Window
	 * @param X : Location on screen to draw, X
	 * @param Y : Location on screen to draw, Y
	 */
	Player( Graphics &Graphic, float X, float Y );

	/** Draw player to SDL_Window
	 * @param Graphic : Graphics to draw texture with.
	 */
	void Draw( Graphics &Graphic );

	/** Called per frame
	 * @param DeltaTime : Last frame time.
	 */
	void Tick( float DeltaTime );

	/** Move player in direction
	 * @param MoveDirection : Direction to move 
	 */
	void MovePlayer( Direction MoveDirection );

	/** Stop moving player */
	void StopMoving( );

	/** Jump player */
	void Jump( );
	
	/** Check and handle any collision with rectangle
	 * @param Collidng : Group of colliding
	 */
	void HandleTileCollision( std::vector<CaveRectangle> &Colliding );
	
	/** Check and handle any collision with slope
	 * @param Collidng : Group of colliding
	 */
	void HandleSlopeCollision( std::vector<CaveSlope> &Collidng );

	/** Called when an animation is done
	 * @param CurrentAnimation : Name of animation that is done.
	 */
	virtual void AnimationDone( std::string CurrentAnimation );

	/** Initialize animations for sprite */
	virtual void SetupAnimation( );

	/** Get X and Y player position */
	inline Vector2 GetXY( ) const { return Vector2( m_DX, m_DY ); }

	/** Get X player position */
	inline float GetX( ) const { return m_DX; }

	/** Get Y player position */
	inline float GetY( ) const { return m_DY; }

private:

	/** Changes in position on screen */
	float m_DX, m_DY;

	/** Direction player is facing */
	Direction m_Facing;

	/** If on ground */
	bool bGrounded;
};
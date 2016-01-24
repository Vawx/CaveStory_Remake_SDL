/** -----------------------------------------
 * Remaking Cavestory using SDL 2.0
 * https://www.youtube.com/watch?v=ETvApbD5xRo&index=1&list=PLNOBk_id22bw6LXhrGfhVwqQIa-M2MsLa
 * Instruction by Limeoats : www.limeoats.com
 * Kyle Langley
 * www.dotvawxgames.com
 * 2015
 * -----------------------------------------*/

#pragma once
#include "Player.h"
#include "Graphics.h"
#include "CaveSlope.h"

namespace PlayerStats
{
	const float WALK_SPEED = 0.2f;
	const float GRAVITY = 0.002f;
	const float GRAVITY_MAX = 0.8f;
	const float JUMP_SPEED = 0.7f;
}

// Default constructor
Player::Player( ) { }

// Constructor
Player::Player( Graphics &Graphic, 
			  float X, 
			  float Y ) :
			  AnimatedSprite( Graphic, 
			  "Content/Sprites/MyChar.png", 
			  0,
			  0,
			  16,
			  16, 
			  X, 
			  Y, 
			  100 ),
			  m_DX( 0 ),
			  m_DY( 0 ),
			  m_Facing( Direction::RIGHT ),
			  bGrounded( false )
{
	Graphic.LoadImage( "Content/Sprites/MyChar.png" );
	SetupAnimation( );
	PlayAnimation( "IdleRight" );
}

// Draw player to SDL_Window
void Player::Draw( Graphics &Graphic )
{
	AnimatedSprite::Draw( Graphic, _X, _Y );
}

// Called per frame
void Player::Tick( float DeltaTime )
{
	m_DY += ( m_DY <= PlayerStats::GRAVITY_MAX ) ? PlayerStats::GRAVITY : 0;	

	_Y += m_DY * DeltaTime;
	_X += m_DX * DeltaTime;

	AnimatedSprite::Tick( DeltaTime );
}

// Called when an animation is done
void Player::AnimationDone( std::string CurrentAnimation )
{

}

// Initialize animations for sprite
void Player::SetupAnimation( )
{
	AddAnimation( 3, 0, 0, "RunLeft", 16, 16, Vector2( 0,0 ) );
	AddAnimation( 3, 0, 16, "RunRight", 16, 16, Vector2( 0,0 ) );

	AddAnimation( 1, 0, 0, "IdleLeft", 16, 16, Vector2( 0,0 ) );
	AddAnimation( 1, 0, 16, "IdleRight", 16, 16, Vector2( 0,0 ) );
}

// Move player in direction
void Player::MovePlayer( Direction MoveDirection )
{
	switch( MoveDirection )
	{
	case Direction::LEFT:
			m_DX = -PlayerStats::WALK_SPEED;
			PlayAnimation( "RunLeft" );
			m_Facing = Direction::LEFT;
		break;
		case Direction::RIGHT:
			m_DX = PlayerStats::WALK_SPEED;
			PlayAnimation( "RunRight" );
			m_Facing = Direction::RIGHT;
		break;
	}
}

// Stop moving player 
void Player::StopMoving( )
{
	m_DX = 0.f;
	switch( m_Facing )
	{
	case Direction::LEFT:
		PlayAnimation( "IdleLeft" );
		break;
	case Direction::RIGHT:
		PlayAnimation( "IdleRight" );
		break;
	}
}

// Jump player
void Player::Jump( )
{
	if ( bGrounded )
	{
		m_DY = 0.f;
		m_DY -= PlayerStats::JUMP_SPEED;
		bGrounded = false;
	}
}

// Check and handle any collision with rectangle(s)
void Player::HandleTileCollision( std::vector<CaveRectangle> &Colliding )
{
	for( int i = 0; i < Colliding.size( ); i++ )
	{
		CollisionSides::Side collidingSide = Sprite::GetCollisionSide( Colliding.at( i ) );
		switch( collidingSide )
		{
		case CollisionSides::Side::TOP:
			m_DY = 0.f;
			_Y = Colliding.at( i ).GetBottom( ) + 1;
			if ( bGrounded )
			{
				m_DX = 0.f;
				_X -= m_Facing == Direction::RIGHT ? 0.5f : -0.5f;
			}
			break;
		case CollisionSides::Side::BOTTOM:
			_Y = Colliding.at( i ).GetTop( ) - _BoundingBox.GetHeight( ) - 1;
			m_DY = 0.f;
			bGrounded = true;
			break;
		case CollisionSides::Side::LEFT:
			_X = Colliding.at( i ).GetRight( ) + 1;
			break;
		case CollisionSides::Side::RIGHT:
			_X = Colliding.at( i ).GetLeft( ) - _BoundingBox.GetWidth( ) - 1;
			break;
		}
	}
}

// Check and handle any collision with slope(s)
void Player::HandleSlopeCollision( std::vector<CaveSlope> &Collidng )
{
	for ( int i = 0; i < Collidng.size( ); i++ )
	{
		int nearestPoint = ( Collidng.at( i ).GetPointOne( ).Y - ( Collidng.at( i ).GetSlope( ) * fabs( (float)Collidng.at( i ).GetPointOne( ).X ) ) );
		int playerCenterX = _BoundingBox.GetCenterX( );
		int newPlayerY = ( Collidng.at( i ).GetSlope( ) * playerCenterX ) + nearestPoint - 8;

		if ( bGrounded )
		{
			_Y = newPlayerY - _BoundingBox.GetHeight( );
			_Y = _Y;
		}
	}
}

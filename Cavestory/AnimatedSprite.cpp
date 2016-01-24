/** -----------------------------------------
 * Remaking Cavestory using SDL 2.0
 * https://www.youtube.com/watch?v=ETvApbD5xRo&index=1&list=PLNOBk_id22bw6LXhrGfhVwqQIa-M2MsLa
 * Instruction by Limeoats : www.limeoats.com
 * Kyle Langley
 * www.dotvawxgames.com
 * 2015
 * -----------------------------------------*/

#pragma once
#include "AnimatedSprite.h"
#include "Graphics.h"

#include <iostream>

// Default constructor
AnimatedSprite::AnimatedSprite( ) { }

// Constructor
AnimatedSprite::AnimatedSprite( Graphics &Graphic, 
								const std::string &FilePath,
								int SourceX,
								int SourceY, 
								int Width, 
								int Height, 
								float PosX, 
								float PosY, 
								float UpdateTime ) :
								Sprite( Graphic, FilePath, SourceX, SourceY, Width, Height, PosX, PosY ),
								m_FrameIndex( 0 ),
								_TimeToUpdate( UpdateTime ),
								bVisible( true ),
								bCurrentAnimationOnce( false ),
								_CurrentAnimation( "" )
{
	// If not initialized to 0.f, default is set to: -9.25596e+061
	m_TimeElapsed = 0.f;
}

// Destructor
AnimatedSprite::~AnimatedSprite( )
{

}

// Cuts up and adds an animation to map(hash) of animations, from texture sheet
void AnimatedSprite::AddAnimation( int Frames, int X, int Y, std::string Name, int Width, int Height, Vector2 Offset )
{
	std::vector<SDL_Rect> rectangles;
	for ( int i = 0; i < Frames; i++ )
	{
		SDL_Rect spriteRect = { ( i + X ) * Width, Y, Width, Height };
		rectangles.push_back( spriteRect );
	}
	m_Animations.insert( std::pair<std::string, std::vector<SDL_Rect>>( Name, rectangles ) );
	m_Offsets.insert( std::pair<std::string, Vector2>( Name, Offset ) );
}

// Clears out the map(hash) of animations for this sprite 
void AnimatedSprite::ResetAnimations( )
{
	m_Animations.clear( );
	m_Offsets.clear( );
}

// Stops current animation playing 
void AnimatedSprite::StopAnimation( )
{
	m_FrameIndex = 0;
	AnimationDone( _CurrentAnimation );
}

// Changes visiblity of sprite of animation
void AnimatedSprite::SetVisible( bool bIsVisible )
{
	bVisible = bIsVisible;
}

// Play animation
void AnimatedSprite::PlayAnimation( std::string Animation, bool bOnce )
{
	bCurrentAnimationOnce = bOnce;
	if ( _CurrentAnimation != Animation )
	{
		_CurrentAnimation = Animation;
		m_FrameIndex = 0;
	}
}

// Called per frame
void AnimatedSprite::Tick( float DeltaTime )
{
	Sprite::Update( );
	m_TimeElapsed += DeltaTime;
	if ( m_TimeElapsed > _TimeToUpdate )
	{
		if ( bCurrentAnimationOnce )
		{
			SetVisible( false );
			m_FrameIndex = 0;
			AnimationDone( _CurrentAnimation );
		}
		else
		{
			m_FrameIndex++;
			if ( m_FrameIndex > m_Animations[ _CurrentAnimation ].size( ) -1 )
			{
				if ( bCurrentAnimationOnce )
				{
					SetVisible( false );
				}
				StopAnimation( );
			}
		}
		m_TimeElapsed = 0.f;
	}
}

// Draw texture to SDL_Window
void AnimatedSprite::Draw( Graphics &Graphic, int X, int Y )
{
	if ( bVisible )
	{
		SDL_Rect destinationRectangle = { X + m_Offsets[ _CurrentAnimation ].X, 
										  Y + m_Offsets[ _CurrentAnimation ].Y,
										  _DestinationRectangle.w,
										  _DestinationRectangle.h };

		SDL_Rect sourceRectangle = m_Animations[ _CurrentAnimation ][ m_FrameIndex ];
		Graphic.BlitSurface( _SpriteSheet, &sourceRectangle, &destinationRectangle );
	}
}
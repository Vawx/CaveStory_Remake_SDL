/** -----------------------------------------
 * Remaking Cavestory using SDL 2.0
 * https://www.youtube.com/watch?v=ETvApbD5xRo&index=1&list=PLNOBk_id22bw6LXhrGfhVwqQIa-M2MsLa
 * Instruction by Limeoats : www.limeoats.com
 * Kyle Langley
 * www.dotvawxgames.com
 * 2015
 * -----------------------------------------*/

namespace GameStats
{
	const int FPS = 50;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

#pragma once
#include <algorithm>
#include <SDL.h>
#include "Game.h"
#include "Graphics.h"
#include "Input.h"

// Constructor
Game::Game( )
{
	if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		SDL_Quit( );
	}

	GameLoop( );
}

// Destructor
Game::~Game( )
{

}

// Game Loop 
void Game::GameLoop( )
{
	Graphics graphics;
	Input input;
	SDL_Event sdlEvent;
	m_Player = Player( graphics, 280.f, 252.f );
	m_Level = Level( "Level1", Vector2( 100, 100 ), graphics );

	float lastUpdateTime = SDL_GetTicks( );	

	while( true )
	{
		// Update input
		input.Update( );

		// SDL Events
		if ( SDL_PollEvent( &sdlEvent ) )
		{
			// Key is down
			if ( sdlEvent.type == SDL_KEYDOWN )
			{				
				// is it repeating
				if ( sdlEvent.key.repeat == 0 )
				{
					input.KeyDownEvent( sdlEvent );
				}
			}
			// Key is released
			else if ( sdlEvent.type == SDL_KEYUP )
			{
				input.KeyUpEvent( sdlEvent );
			}
			// User quits
			else if ( sdlEvent.type == SDL_QUIT )
			{
				return;
			}
		}

		// Quit if escape is pressed
		if ( input.WasKeyPressed( SDL_SCANCODE_ESCAPE ) )
		{
			return;
		}

		// Player character 
		if ( input.IsKeyHeld( SDL_SCANCODE_LEFT ) || input.IsKeyHeld( SDL_SCANCODE_A ) )
		{
			m_Player.MovePlayer( Direction::LEFT );
		}
		else if ( input.IsKeyHeld( SDL_SCANCODE_RIGHT ) || input.IsKeyHeld( SDL_SCANCODE_D ) )
		{
			m_Player.MovePlayer( Direction::RIGHT );
		}
		else
		{
			m_Player.StopMoving( );
		}

		// Jump
		if ( input.WasKeyPressed( SDL_SCANCODE_SPACE ) )
		{
			m_Player.Jump( );
		}

		// Debug
		bDrawDebug = ( input.IsKeyHeld( SDL_SCANCODE_5 ) ) ? true : false;

		const float CURRENT_TIME_IN_MS = SDL_GetTicks( );
		float elapsedTimeInMS = CURRENT_TIME_IN_MS - lastUpdateTime;
		lastUpdateTime = CURRENT_TIME_IN_MS;

		Tick( std::fmin( elapsedTimeInMS, GameStats::MAX_FRAME_TIME ) ); 
		Draw( graphics );
	}

	SDL_Quit( );
}

// Draw to screen 
void Game::Draw( Graphics &Graphic )
{
	Graphic.Clear( );
	m_Level.Draw( Graphic );

	if ( bDrawDebug )
	{
		m_Level.DrawCollision( Graphic );
	}

	m_Player.Draw( Graphic );
	Graphic.RenderTexture( );
}

// Called per frame 
void Game::Tick( float DeltaTime )
{
	m_Player.Tick( DeltaTime );
	m_Level.Tick( DeltaTime );

	// Check collisions
	std::vector<CaveRectangle> levelObjects = m_Level.CheckTileCollision( m_Player.GetBoundingBox( ) );
	if ( levelObjects.size( ) > 0 )
	{
		m_Player.HandleTileCollision( levelObjects );
	}

	std::vector<CaveSlope> levelSlopes = m_Level.CheckSlopeCollision( m_Player.GetBoundingBox( ) );
	if ( levelSlopes.size( ) > 0  )
	{
		m_Player.HandleSlopeCollision( levelSlopes );
	}
}


/** -----------------------------------------
 * Remaking Cavestory using SDL 2.0
 * https://www.youtube.com/watch?v=ETvApbD5xRo&index=1&list=PLNOBk_id22bw6LXhrGfhVwqQIa-M2MsLa
 * Instruction by Limeoats : www.limeoats.com
 * Kyle Langley
 * www.dotvawxgames.com
 * 2015
 * -----------------------------------------*/

#pragma once
#include "Input.h"

// On each frame - resets keys no longer relevant
void Input::Update( )
{
	m_PressedKeys.clear( );
	m_ReleasedKeys.clear( );
}

// Key up event, from being pressed
void Input::KeyUpEvent( const SDL_Event& SDLEvent )
{
	m_ReleasedKeys[ SDLEvent.key.keysym.scancode ] = true;
	m_HeldKeys[ SDLEvent.key.keysym.scancode ] = false;
}

// Key down event, from pressed
void Input::KeyDownEvent( const SDL_Event& SDLEvent )
{
	m_PressedKeys[ SDLEvent.key.keysym.scancode ] = true;
	m_HeldKeys[ SDLEvent.key.keysym.scancode ] = true;
}

// Key was pressed event
bool Input::WasKeyPressed( SDL_Scancode Key )
{
	return m_PressedKeys[ Key ];
}

// Key was released event
bool Input::WasKeyReleased( SDL_Scancode Key )
{
	return m_ReleasedKeys[ Key ];
}

// Key is down event
bool Input::IsKeyHeld( SDL_Scancode Key )
{
	return m_HeldKeys[ Key ];
}
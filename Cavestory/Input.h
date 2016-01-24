/** -----------------------------------------
 * Remaking Cavestory using SDL 2.0
 * https://www.youtube.com/watch?v=ETvApbD5xRo&index=1&list=PLNOBk_id22bw6LXhrGfhVwqQIa-M2MsLa
 * Instruction by Limeoats : www.limeoats.com
 * Kyle Langley
 * www.dotvawxgames.com
 * 2015
 * -----------------------------------------*/

/**
 * Keeps track of keyboard state(s)
 */

#pragma once
#include <SDL.h>
#include <map>

class Input
{
public:

	/** On each frame - resets keys no longer relevant */
	void Update( );

	/** Key up event, from being pressed
	 * @param SDLEvent : Event of released key
	 */
	void KeyUpEvent( const SDL_Event& SDLEvent );

	/** Key down event, from pressed
	 * @param SDLEvent : Event of released key
	 */
	void KeyDownEvent( const SDL_Event& SDLEvent );

	/** Key was pressed event
	 * @param SDLEvent : Event of released key
	 * @return Key was pressed
	 */
	bool WasKeyPressed( SDL_Scancode Key );

	/** Key was released event
	 * @param SDLEvent : Event of released key
	 * @return Key was released
	 */
	bool WasKeyReleased( SDL_Scancode Key );

	/** Key is down event
	 * @param SDLEvent : Event of released key
	 * @return Key is down
	 */
	bool IsKeyHeld( SDL_Scancode Key );

private:

	/** Currently pressed keys in hash : KeyCode + on(true) off(false) */
	std::map<SDL_Scancode, bool> m_PressedKeys;

	/** Currently held keys in hash : KeyCode + on(true) off(false) */
	std::map<SDL_Scancode, bool> m_HeldKeys;

	/** Currently held keys in hash : KeyCode + on(true) off(false) */
	std::map<SDL_Scancode, bool> m_ReleasedKeys;

};
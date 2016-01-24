/** -----------------------------------------
 * Remaking Cavestory using SDL 2.0
 * https://www.youtube.com/watch?v=ETvApbD5xRo&index=1&list=PLNOBk_id22bw6LXhrGfhVwqQIa-M2MsLa
 * Instruction by Limeoats : www.limeoats.com
 * Kyle Langley
 * www.dotvawxgames.com
 * 2015
 * -----------------------------------------*/

/**
 * Holds all information for main game loop
 */

#pragma once
#include "Graphics.h"
#include "Player.h"
#include "Level.h"

class Game
{

public:
	Game( );
	~Game( );

private:
	/** Game Loop */
	void GameLoop( );

	/** Draw to SDL_Window
	 * @param Graphic : Graphics class that draws
	 */
	void Draw( Graphics &Graphic );

	/** Called per frame 
	 * @param DeltaTime : Time of last frame
	 */
	void Tick( float DeltaTime );

	/** Player sprite */
	Player m_Player;

	/** Level */
	Level m_Level;

	/** To draw debug or not */
	bool bDrawDebug;
};
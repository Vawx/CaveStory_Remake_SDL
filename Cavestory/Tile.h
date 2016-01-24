/** -----------------------------------------
 * Remaking Cavestory using SDL 2.0
 * https://www.youtube.com/watch?v=ETvApbD5xRo&index=1&list=PLNOBk_id22bw6LXhrGfhVwqQIa-M2MsLa
 * Instruction by Limeoats : www.limeoats.com
 * Kyle Langley
 * www.dotvawxgames.com
 * 2015
 * -----------------------------------------*/

#pragma once
#include <SDL.h>
#include "Globals.h"
#include "Graphics.h"

class Tile
{
public:

	/** Default constructor */
	Tile( );

	/** Constructor
	 * @param TileSet : Tileset texture to use for Tile
	 * @param Size : Size of tileset
	 * @param TileSetPosition : Where on the tile set
	 * @param Position : Where on the level *
	 */
	Tile( SDL_Texture *TileSet, Vector2 Size, Vector2 TileSetPosition, Vector2 Position );

	/** Called per frame
	 * @param DeltaTime : Time of last frame 
	 */
	void Tick( float DeltaTime );

	/** To draw tileset on SDL_Window
	 * @param Graphic : Used to draw
	 */
	void Draw( Graphics &Graphic );

private:

	/** The tileset */
	SDL_Texture* m_TileSet;

	/** Size of tileset */
	Vector2 m_Size;

	/** Where on the tileset the tile is. */
	Vector2 m_TileSetPosition;

	/** Where on the level the tileset is */
	Vector2 m_Position;
};
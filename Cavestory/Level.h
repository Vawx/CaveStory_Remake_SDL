/** -----------------------------------------
 * Remaking Cavestory using SDL 2.0
 * https://www.youtube.com/watch?v=ETvApbD5xRo&index=1&list=PLNOBk_id22bw6LXhrGfhVwqQIa-M2MsLa
 * Instruction by Limeoats : www.limeoats.com
 * Kyle Langley
 * www.dotvawxgames.com
 * 2015
 * -----------------------------------------*/

#pragma once
#include <string>
#include <vector>
#include <SDL_image.h>
#include "Globals.h"
#include "Graphics.h"
#include "Tile.h"
#include "CaveRectangle.h"
#include "CaveSlope.h"


/** TileSet Data */
struct TileSet
{
	SDL_Texture *Texture;
	int FirstGID;

	TileSet( ) 
	{
		FirstGID = -1;
	}

	TileSet( SDL_Texture *TileTexture, int GID )
	{
		Texture = TileTexture;
		FirstGID = GID;
	}
};

class Level
{
public:
	/** Default constructor */
	Level( );

	/** Constructor
	 * @param MapName : Name of map
	 * @param SpawnPoint : Player spawn point, on map
	 * @param Graphic : To draw on SDL_Window
	 */
	Level( std::string MapName, Vector2 SpawnPoint, Graphics &Graphic );

	/** Destructor */
	~Level( );

	/** Called per frame
	 * @param DeltaTime : Time of last frame.
	 */
	void Tick( float DeltaTime );

	/** Draw the level
	 * @param Graphics : To draw with.
	 */
	void Draw( Graphics &Graphic );

	/** Draws collision for the level, as texture
	 * @param Graphic : to draw with
	 */
	void DrawCollision( Graphics &Graphic );

	/** Check if two rectangles are colliding
	 * @param Other : To check 
	 * @return The colliding rectangle(s)
	 */
	std::vector<CaveRectangle> CheckTileCollision( const CaveRectangle &Other );

	/** Check if two colliders are colliding
	 * @param Other : To check 
	 * @return The colliding slope(s)
	 */
	std::vector<CaveSlope> CheckSlopeCollision( const CaveRectangle &Other );

private:

	/** Positions to draw background texture */
	std::vector<SDL_Rect> m_BackgroundPositions;

	/** Name of map */
	std::string m_MapName;

	/** Point to spawn player */
	Vector2 m_SpawnPoint;

	/** Width and height of entire level */
	Vector2 m_Size;

	/** Tile size on level */
	Vector2 m_TileSize;

	/** Background texture image */
	SDL_Texture *m_BackgroundTexture;

	/** List of tiles */
	std::vector<Tile> m_TileList;

	/** Tile sets on map */
	std::vector<TileSet> m_TileSets;

	/** Where collision rectangles are within the map */
	std::vector<CaveRectangle> m_CollisionRectangles;

	/** Where collision slopes are within the map */
	std::vector<CaveSlope> m_CollisionSlopes;

	/** Load map
	 * @param MapName : Name of map 
	 * @param Graphic : To draw with 
	 */
	void LoadMap( std::string MapName, Graphics &Graphic );

	/** Stores background texture locations */
	void StoreBackgroundLocations( );

	/** Get the tile set screen position based on tile and GID from XML
	 * @param Tile : Tile set (holds level texture)
	 * @param GID : XML "gid" currently held
	 */
	Vector2 GetTileSetPosition( TileSet Tile, int GID );

};
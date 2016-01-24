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
#include <sstream>
#include <algorithm>
#include <cmath>
#include "Level.h"
#include "Graphics.h"
#include "CaveRectangle.h"
#include "tinyxml2.h"
#include "CaveUtility.h"

/** To avoid tinyxml2::xxxxx */
using namespace tinyxml2;

// Default constructor 
Level::Level( )
{

}

// Constructor
Level::Level( std::string MapName, 
			  Vector2 SpawnPoint, 
			  Graphics &Graphic ) :
			  m_MapName( MapName ),
			  m_SpawnPoint( SpawnPoint ),
			  m_Size( Vector2::Zero( ) )
{
	LoadMap( m_MapName, Graphic );
	StoreBackgroundLocations( );
}

// Destructor 
Level::~Level( )
{

}

// Called per frame
void Level::Tick( float DeltaTime )
{

}


// Draw the level
void Level::Draw( Graphics &Graphic )
{
	SDL_Rect sourceRectangle = { 0, 0, 64, 64 };	
	for ( std::vector<SDL_Rect>::size_type i = 0; i != m_BackgroundPositions.size( ); i++ )
	{
		Graphic.BlitSurface( m_BackgroundTexture, &sourceRectangle, &m_BackgroundPositions[ i ] );
	}

	for ( int i = 0; i < m_TileList.size( ); i++ )
	{
		m_TileList.at( i ).Draw( Graphic );
	}
}

// Draws collision for the level, as texture
void Level::DrawCollision( Graphics &Graphic )
{
	for( int i = 0; i < m_CollisionRectangles.size( ); i++ )
	{
		Graphic.DrawTexture( m_CollisionRectangles[ i ] );
	}
}

// Stores background texture locations
void Level::StoreBackgroundLocations( )
{
	SDL_Rect destinationRectangle = { 64 * GameGlobals::SPRITE_SCALE, 64 * GameGlobals::SPRITE_SCALE, 64, 64 };
	for ( int x = 0; x < m_Size.X / 64; x++ )
	{
		for ( int y = 0; y < m_Size.Y / 64; y++ )
		{
			destinationRectangle.x = x * 64;
			destinationRectangle.y = y * 64;
			m_BackgroundPositions.push_back( destinationRectangle );
		}
	}
}

// Loads map
void Level::LoadMap( std::string MapName, Graphics &Graphic )
{
	m_BackgroundTexture = SDL_CreateTextureFromSurface( Graphic.GetRenderer( ), Graphic.LoadImage( "Content/Backgrounds/bkBlue.png" ) );

	XMLDocument document;
	std::stringstream ss;
	ss << "Content/Levels/" << MapName << ".tmx";
	document.LoadFile( ss.str( ).c_str( ) );

	XMLElement* mapNode = document.FirstChildElement( "map" );
	mapNode->QueryIntAttribute( "width", &m_Size.X );
	mapNode->QueryIntAttribute( "height", &m_Size.Y );
	mapNode->QueryIntAttribute( "tilewidth", &m_TileSize.X );
	mapNode->QueryIntAttribute( "tileheight", &m_TileSize.Y );

	XMLElement* tileSet = mapNode->FirstChildElement( "tileset" );
	if ( tileSet )
	{
		// will be true if NextSiblingElement is valid
		while( tileSet )
		{
			int firstGID;
			const char* source = tileSet->FirstChildElement( "image" )->Attribute( "source" );
			char* path;
			std::stringstream ss2;
			ss2 << source;;
			tileSet->QueryIntAttribute( "firstgid", &firstGID );
			SDL_Texture* texture = SDL_CreateTextureFromSurface( Graphic.GetRenderer( ), Graphic.LoadImage( ss2.str( ) ) );
			m_TileSets.push_back( TileSet( texture, firstGID ) );

			tileSet = tileSet->NextSiblingElement( "tileset" );
		}
	}

	XMLElement* layer = mapNode->FirstChildElement( "layer" );
	if ( layer )
	{
		// will be true if NextSiblingElement is valid
		while( layer )
		{
			XMLElement* data = layer->FirstChildElement( "data" );
			if ( data )
			{
				// will be true if NextSiblingElement is valid
				while( data )
				{
					XMLElement* tile = data->FirstChildElement( "tile" );
					if ( tile )
					{
						int tileCounter = 0;

						// will be true if NextSiblingElement is valid
						while( tile )
						{
							if ( tile->IntAttribute( "gid" ) == 0 )
							{
								tileCounter++;
								if ( tile->NextSiblingElement( "tile" ) )
								{
									tile = tile->NextSiblingElement( "tile" ); 
									continue;
								}
								else
								{
									break;
								}
							}

							int nextGID = tile->IntAttribute( "gid" );
							TileSet nextTileSet;
							for ( int i = 0; i < m_TileSets.size( ); i++ )
							{
								if ( m_TileSets[ i ].FirstGID <= nextGID )
								{
									nextTileSet = m_TileSets.at( i );
									break;
								}
							}

							if ( nextTileSet.FirstGID == -1 )
							{
								tileCounter++;
								if ( tile->NextSiblingElement( "tile" ) )
								{
									tile = tile->NextSiblingElement( "tile" );
									continue;
								}
								else
								{
									break;
								}
							}

							int xPos = 0;
							int yPos = 0;
							xPos = tileCounter % m_Size.X;
							xPos *= m_TileSize.X;
							yPos += m_TileSize.Y * ( tileCounter / m_Size.X );
							Vector2 finalTilePosition = Vector2( xPos, yPos );

							Vector2 finalTileSetPosition = GetTileSetPosition( nextTileSet, nextGID );

							Tile newTile( nextTileSet.Texture, Vector2( m_TileSize.X, m_TileSize.Y ), finalTileSetPosition, finalTilePosition );
							m_TileList.push_back( newTile );
							tileCounter++;

							tile = tile->NextSiblingElement( "tile" );
						}
					}

					data = data->NextSiblingElement( "data" );
				}
			}

			layer = layer->NextSiblingElement( "layer" );
		}
	}

	// objects group ( collision, spawn points, etc )
	XMLElement *objectGroup = mapNode->FirstChildElement( "objectgroup" );
	if ( objectGroup )
	{
		while ( objectGroup )
		{
			const char* collisionName = objectGroup->Attribute( "name" );
			std::stringstream name;
			name << collisionName;
			if ( name.str( ) == "Collision" )
			{
				XMLElement *collideObject = objectGroup->FirstChildElement( "object" );
				if ( collideObject )
				{
					while( collideObject )
					{
						float x, y, width, height;
						x = collideObject->FloatAttribute( "x" );
						y = collideObject->FloatAttribute( "y" );
						width = collideObject->FloatAttribute( "width" );
						height = collideObject->FloatAttribute( "height" );

						m_CollisionRectangles.push_back( CaveRectangle( 
									   std::ceil( x ) * GameGlobals::SPRITE_SCALE,
									   std::ceil( y ) * GameGlobals::SPRITE_SCALE,
									   std::ceil( width ) * GameGlobals::SPRITE_SCALE,
									   std::ceil( height ) * GameGlobals::SPRITE_SCALE ) );

						collideObject = collideObject->NextSiblingElement( "object" );
					}
				}
			}
			else if( name.str( ) == "Slope" )
			{
				XMLElement *slopeObject = objectGroup->FirstChildElement( "object" );
				if ( slopeObject )
				{
					while( slopeObject )
					{
						std::vector<Vector2> slopePoints;
						Vector2 pointOne = Vector2( std::ceil( slopeObject->FloatAttribute( "x" ) ), std::ceil( slopeObject->FloatAttribute( "y" ) ) );

						XMLElement *slopePolyLine = slopeObject->FirstChildElement( "polyline" );
						if ( slopePolyLine )
						{
							std::vector<std::string> polyPairs;
							const char* slopePointNames = slopePolyLine->Attribute( "points" );

							std::stringstream pointsName;
							pointsName << slopePointNames;
							CaveUtiltity::Split( pointsName.str( ), polyPairs, ' ' );

							for ( int i = 0; i < polyPairs.size( ); i++ )
							{
								std::vector<std::string> ps;
								CaveUtiltity::Split( polyPairs.at( i ), ps, ',' );
								slopePoints.push_back( Vector2( std::stoi( ps.at( 0 ) ), std::stoi( ps.at( 1 ) ) ) );
							}
						}

						for ( int i = 0; i < slopePoints.size( ); i += 2 )
						{
							m_CollisionSlopes.push_back( CaveSlope( Vector2( ( pointOne.X + slopePoints.at( i < 2 ? i : i - 1 ).X ) * GameGlobals::SPRITE_SCALE,
																			 ( pointOne.Y + slopePoints.at( i < 2 ? i : i - 1 ).Y ) * GameGlobals::SPRITE_SCALE ),
																	Vector2( ( pointOne.X + slopePoints.at( i < 2 ? i + 1 : i ).X ) * GameGlobals::SPRITE_SCALE,
																			 ( pointOne.Y + slopePoints.at( i < 2 ? i + 1 : i ).Y ) * GameGlobals::SPRITE_SCALE ) ) );
						}

						slopeObject = slopeObject->NextSiblingElement( "object" );
					}
				}
			}

			objectGroup = objectGroup->NextSiblingElement( "objectgroup" );
		}
	}
}

// Get the tile set screen position based on tile and GID from XML
Vector2 Level::GetTileSetPosition( TileSet Tile, int GID )
{
	int tileSetWidth, tileSetHeight;
	SDL_QueryTexture( Tile.Texture, NULL, NULL, &tileSetWidth, &tileSetHeight );

	int tileSetPosX = GID % ( tileSetWidth / m_TileSize.X ) - 1;
	tileSetPosX *= m_TileSize.X;

	int shiftAmount = (( GID - Tile.FirstGID ) / ( tileSetWidth / m_TileSize.X ) );
	int tileSetPosY = m_TileSize.Y * shiftAmount;

	return Vector2( tileSetPosX, tileSetPosY );
}

// Check if two rectangles are colliding
std::vector<CaveRectangle> Level::CheckTileCollision( const CaveRectangle &Other )
{
	std::vector<CaveRectangle> colliding;
	for( int i = 0; i < m_CollisionRectangles.size( ); i++ )
	{
		if ( m_CollisionRectangles.at( i ).CollidesWith( Other ) )
		{
			colliding.push_back( m_CollisionRectangles.at( i ) );
		}
	}
	return colliding;
}

// Check if two colliders are colliding
std::vector<CaveSlope> Level::CheckSlopeCollision( const CaveRectangle &Other )
{
	std::vector<CaveSlope> colliding;
	for ( int i = 0; i < m_CollisionSlopes.size( ); i++ )
	{
		if ( m_CollisionSlopes.at( i ).CollidesWith( Other ) )
		{
			colliding.push_back( m_CollisionSlopes.at( i ) );
		}
	}
	return colliding;
}
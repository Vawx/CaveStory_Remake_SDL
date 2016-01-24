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

class CaveUtiltity
{
public:
	/** Splits any found Character in Text and returns them as a vector
	 * @param Text : string to search through
	 * @param Strings : Found characters, added in vector
	 * @param Character : Character to find in string
	 */
	static unsigned int Split( const std::string &Text, std::vector<std::string> &Strings, char Character )
	{
		int position = Text.find( Character );
		int initialPosition = 0;
		Strings.clear( );
		while ( position != std::string::npos )
		{
			Strings.push_back( Text.substr( initialPosition, position - initialPosition + 1 ) );
			initialPosition = position + 1;
		
			position = Text.find( Character, initialPosition );
		}
		Strings.push_back( Text.substr( initialPosition, std::min<int>( position, Text.size( ) - ( initialPosition + 1 ) ) ) );
		return Strings.size( );
	}
private:
};
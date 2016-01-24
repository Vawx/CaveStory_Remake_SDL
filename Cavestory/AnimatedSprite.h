/** -----------------------------------------
 * Remaking Cavestory using SDL 2.0
 * https://www.youtube.com/watch?v=ETvApbD5xRo&index=1&list=PLNOBk_id22bw6LXhrGfhVwqQIa-M2MsLa
 * Instruction by Limeoats : www.limeoats.com
 * Kyle Langley
 * www.dotvawxgames.com
 * 2015
 * -----------------------------------------*/

/**
 * Holds logic for animating sprites
 */

#pragma once
#include <map>
#include <string>
#include <vector>
#include <SDL.h>
#include "Graphics.h"
#include "Sprite.h"
#include "Globals.h"

class AnimatedSprite : public Sprite
{
public:
	// Default constructor
	AnimatedSprite( );

	/** Constructor
	 * @param Graphic : To draw to SDL_Window
	 * @param FilePath : Content path for texture sheet
	 * @param SourceX : Location X on texture sheet to draw from
	 * @param SourceY : Location Y on texture sheet to draw from
	 * @param Width : Width of sprite from texture sheet
	 * @param Height : Height of sprite from texture sheet
	 * @param PosX : Location X on screen to draw sprite
	 * @param PosY : Location Y on screen to draw sprite
	 * @param UpdateTime : How often the sprite animation is updated
	 */
	AnimatedSprite( Graphics &Graphic, 
					const std::string &FilePath, 
					int SourceX, 
					int SourceY, 
					int Width, 
					int Height, 
					float PosX, 
					float PosY, 
					float UpdateTime );

	// Destructor
	~AnimatedSprite( );

	/** Play animation
	 * @param Animation : Name of animation
	 * @param bOnce : Play animation once(true) : loop animation(false)
	 */
	void PlayAnimation( std::string Animation, bool bOnce = false );

	/** Called per frame
	 * @param DeltaTime : Time of last frame
	 */
	void Tick( float DeltaTime );

	/** Draw texture to SDL_Window
	 * @param Graphic : Graphics class 
	 * @param X : Location on screen to draw texture, X
	 * @param Y : Location on screen to draw texture, Y
	 */
	void Draw( Graphics &Graphic, int X, int Y );

protected:

	/** Time between animation update */
	float _TimeToUpdate;

	/** Play current animation only once */
	bool bCurrentAnimationOnce;

	/** Name of current animation */
	std::string _CurrentAnimation;

	/** Cuts up and adds an animation to map(hash) of animations, from texture sheet
	 * @param Frames : Frames of the animation to add
	 * @param X : Position on the texture sheet, X
	 * @param Y : Position on the texture shett, Y
	 * @param Name : Name of the animation to add
	 * @param Width : Width of animation, on texture sheet
	 * @param Height : Height of animation, on texture sheet
	 * @param Offset : Offset position of sprite on texture sheet
	 */
	void AddAnimation( int Frames, int X, int Y, std::string Name, int Width, int Height, Vector2 Offset );

	/** Clears out the map(hash) of animations for this sprite */
	void ResetAnimations( );

	/** Stops current animation playing */
	void StopAnimation( );

	/** Changes visiblity of sprite of animation
	* @param bIsVisible : Visible( true ) : Hidden( false )
	*/
	void SetVisible( bool bIsVisible );

	/** Called when an animation is done
	 * @param CurrentAnimation : Name of animation that is done.
	 */
	virtual void AnimationDone( std::string CurrentAnimation ) = 0;

	/** Initialize animations for sprite */
	virtual void SetupAnimation( ) = 0;

private:

	/** All the texture XY areas, representing animations this sprite has */
	std::map<std::string, std::vector<SDL_Rect>> m_Animations;

	/** Texture area offset in pixesl */
	std::map<std::string, Vector2> m_Offsets;

	/** What frame in the animtion is being used */
	int m_FrameIndex;

	/** Elapsed time used for frame changes */
	double m_TimeElapsed;

	/** Is sprite visible */
	bool bVisible;
};
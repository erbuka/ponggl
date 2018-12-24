#include <iostream>
#include "GameEngine.h"
#include "libs/Randomizer.h"
#include <cmath>
GameEngine::GameEngine(GLfloat fieldWidth, GLfloat fieldLength, GLfloat padsWidth, GLfloat ballRadius)
{
	Randomizer::init();

	this->cpuOpponent = false;
	
	this->fieldWidth = fieldWidth;
	this->fieldLength = fieldLength;
	this->padsWidth = padsWidth;
	this->ballRadius = ballRadius;

	this->reset();
}

GameEngine::GameEngine(GLfloat fieldWidth, GLfloat fieldLength, GLfloat padsWidth, GLfloat ballRadius, bool cpuOpponent)
{
	Randomizer::init();

	this->cpuOpponent = cpuOpponent;
	
	this->fieldWidth = fieldWidth;
	this->fieldLength = fieldLength;
	this->padsWidth = padsWidth;
	this->ballRadius = ballRadius;

	this->reset();
}

GameEngine::~GameEngine(void)
{
}

void GameEngine::reset()
{ 
	pX = pY = pZ = vX = vY = vZ = pad1VelX = pad2VelX = 0;
	pad1X = pad2X = 0;
	gameState = Idle;
}

void GameEngine::throwBall() {
	if (gameState == Idle) {
		GLfloat *angle = Randomizer::nextTrigonometricAngle();
		vX = angle[1] * 8;
		vY = angle[0] * 8;
		gameState = Playing;
	}
}

void GameEngine::update(GLfloat dt) {

	// controlling cpu opponent
	if(cpuOpponent)
		controlCPUOpponent();

	// updating ball position
	pX += vX * dt;
	pY += vY * dt;
	pZ += vZ * dt;

	// updating pads position
	pad1X += pad1VelX * dt;
	pad2X += pad2VelX * dt;

	// checking pad1 bounds

	pad1X = clamp(pad1X, -fieldWidth / 2 + padsWidth / 2, fieldWidth / 2 - padsWidth / 2);
	pad2X = clamp(pad2X, -fieldWidth / 2 + padsWidth / 2, fieldWidth / 2 - padsWidth / 2);


	if (pY >= -fieldLength / 2 && pY <= fieldLength / 2)
	{
		// checking ball collisions on walls
		if (pX < -fieldWidth / 2 + ballRadius) {
			pX = -fieldWidth / 2 + ballRadius;
			vX = -vX;
		}
		else if (pX > fieldWidth / 2 - ballRadius) {
			pX = fieldWidth / 2 - ballRadius;
			vX = -vX;
		}

		// checking ball collisions on pads
		if (pY <= -fieldLength / 2 + ballRadius) 
		{
			if (pad2X - padsWidth / 2 <= pX && pad2X + padsWidth / 2 >= pX) {
				pY = -fieldLength / 2 + ballRadius;
				float ratio = (pX - pad2X + padsWidth / 2) / padsWidth - 0.5f;
				vY = -vY / 4.0f + (1.0f - abs(ratio)) * 8.0f;
				vX = ratio * 8.0f;
			}
		}
		else if (pY >= fieldLength / 2 - ballRadius) 
		{
			if (pad1X - padsWidth / 2 <= pX && pad1X + padsWidth / 2 >= pX) {
				pY = fieldLength / 2 - ballRadius;
				float ratio = (pX - pad1X + padsWidth / 2) / padsWidth - 0.5f;
				vY = -vY / 4.0f - (1.0f - abs(ratio)) * 8.0f;
				vX = ratio * 8.0f;
			}
		}
	}
	else
	{
		vZ -= 9.8f * dt;
		pZ += vZ * dt;

		if (pZ < -4)
		{
			reset();
		}

	}



}

float GameEngine::clamp(float value, float min, float max)
{
	return std::fmaxf(min, std::fminf(max, value));
}

void GameEngine::controlCPUOpponent() {
	if(pY > 0 || vY > 0) {
		if(pad2X > padsWidth/2)
			setPad2VelX(-PadSpeed);
		else if(pad2X < -padsWidth /2)
			setPad2VelX(PadSpeed);
		else
			setPad2VelX(0);
	} else {
		if(pX > pad2X)
			setPad2VelX(PadSpeed);
		else if(pX < pad2X)
			setPad2VelX(-PadSpeed);
		else
			setPad2VelX(0);
	}
}
#pragma once
#include <gl\glew.h>

class GameEngine
{
private:

	enum GameState
	{
		Idle, Playing
	};

	static constexpr float PadSpeed = 4.0f;

	bool cpuOpponent;
		
	GLfloat fieldWidth, fieldLength;
	GLfloat padsWidth;
	GLfloat ballRadius;

	GLfloat pX, pY, pZ, vX, vY, vZ;

	GLfloat pad1X, pad2X, pad1VelX, pad2VelX;

	GameState gameState;

public:
	GameEngine(GLfloat fieldWidth, GLfloat fieldLength, GLfloat padsWidth, GLfloat ballRadius);
	GameEngine(GLfloat fieldWidth, GLfloat fieldLength, GLfloat padsWidth, GLfloat ballRadius, bool cpuOpponent);
	~GameEngine(void);

	void reset();

	void throwBall();

	void update(GLfloat dt);

	GLfloat getFieldWidth() { return fieldWidth;}
	GLfloat getFieldLength() { return fieldLength;}
	GLfloat getPadsWidth() { return padsWidth; }

	GLfloat getBallX() { return pX; }
	GLfloat getBallY() { return pY; }
	GLfloat getBallZ() { return pZ; }

	GLfloat getPad1X() { return pad1X; }
	GLfloat getPad2X() { return pad2X; }

	void setPad1VelX(GLfloat vel) { pad1VelX = vel; }
	void setPad2VelX(GLfloat vel) { pad2VelX = vel; }


	float clamp(float value, float min, float max);

	void controlCPUOpponent();
};


#pragma once

#include <string>
#include <ctime>
#include <random>
#include "glut.h"
#include "graphics.h"
#include "Player.h"
#include "Level.h"
#include "TextureManager.h"

extern unsigned int texName[6];

typedef enum {
	ACTIVE,
	PAUSED,
	DEAD,
} GameState;

class GlutApp
{
private:
	char* WindowName;
	double mScreenX = 700;
	double mScreenY = 500;
	class Player* mPlayer;
	class Level* mLevel;
	class TextureManager* mTextureManager;
	GameState mGameState = PAUSED;
	unsigned int mScore = 0;
public:
	GlutApp();
	~GlutApp();
	void Update();
	void Start(int argc, char** argv, const char* name);
	void SetState(GameState state);
	GameState GetState();
	void Reset();
	double GetScreenX();
	double GetScreenY();
	Player* GetPlayer();
	TextureManager* GetTextureManager();
	bool Collides(double x, double y, double w, double h);
	void Score() { mScore++; };
	double GetScore() { return mScore; };
};
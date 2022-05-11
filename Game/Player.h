#pragma once

#include <iostream>
#include "graphics.h"
#include "GlutApp.h"

class Player
{
private:
	class GlutApp* mApp;
	double mX, mY;
	double mRot = 0.0;
	double mWidth;
	double mHeight;
	double mDX = 0;
	double mDY = 0;
	double mMax_Gravity = -5.0;
public:
	Player(GlutApp* app, double x, double y, double w, double h);
	~Player();
	void Draw();
	void Update();
	void Flap();
	double GetX() { return mX; };
	double GetY() { return mY; };
	double GetWidth() { return mWidth; };
	double GetHeight() { return mHeight; };
	void SetX(double x);
	void SetY(double y);
	void SetRotation(double r);
};
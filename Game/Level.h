#pragma once

#include <deque>
#include "graphics.h"
#include "GlutApp.h"

using std::deque;

class Pipe {
private:
	double mX, mY;
	double mWidth = 100;
	double mGapSize = 200;
public:
	Pipe(double x, double y);
	void Draw(class TextureManager* tm);
	double GetX();
	double GetY();
	double GetWidth();
	double GetGapSize();
	void SetX(double x);
};

class Level
{
private:
	class GlutApp* mApp;
	deque<Pipe*> mPipes;
	double mDX = -5;
public:
	Level(GlutApp* app);
	~Level();
	void Update();
	void Draw();
	void RemoveAllPipes();
	void RemovePipes();
	void CreatePipes();
	deque<Pipe*> GetPipes();
};
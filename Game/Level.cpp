#include "Level.h"

Pipe::Pipe(double x, double y)
	: mX(x), mY(y) {}

void Pipe::Draw(class TextureManager* tm)
{
	tm->StartTexture("images/pipe_body.png");
	DrawRectangle(mX, 0, mX + mWidth, mY - mGapSize/2);
	tm->EndTexture();

	tm->StartTexture("images/pipe_rim.png");
	DrawRectangle(mX, mY - mWidth/2 - mGapSize / 2, mX + mWidth, mY - mGapSize / 2);
	tm->EndTexture();

	tm->StartTexture("images/pipe_body_top.png");
	DrawRectangle(mX, mY + mGapSize/2, mX + mWidth, 700);
	tm->EndTexture();

	tm->StartTexture("images/pipe_rim_top.png");
	DrawRectangle(mX, mY + mGapSize / 2, mX + mWidth, mY + mWidth / 2 + mGapSize / 2);
	tm->EndTexture();
}

double Pipe::GetX()
{
	return mX;
}

double Pipe::GetY()
{
	return mY;
}

double Pipe::GetWidth()
{
	return mWidth;
}

double Pipe::GetGapSize()
{
	return mGapSize;
}

void Pipe::SetX(double x)
{
	mX = x;
}

Level::Level(GlutApp* app) : mApp(app)
{
	CreatePipes();
}

Level::~Level()
{
	for (Pipe* p : mPipes)
	{
		delete p;
	}
	mApp = NULL;
}

void Level::Update()
{
	for (Pipe* p : mPipes)
	{
		p->SetX(p->GetX() + mDX);
	}

	if (!mPipes.empty() && mPipes.front()->GetX() < -mPipes.front()->GetWidth())
	{
		RemovePipes();
	}

	if (mPipes.back()->GetX() < mApp->GetScreenX() - 4.5 * mPipes.back()->GetWidth())
	{
		CreatePipes();
	}
}

void Level::Draw()
{
	mApp->GetTextureManager()->StartTexture("images/background.jpg");
	DrawRectangle(0, 0, mApp->GetScreenX(), mApp->GetScreenY());
	mApp->GetTextureManager()->EndTexture();

	for (Pipe* p : mPipes)
	{
		p->Draw(mApp->GetTextureManager());
	}
}

void Level::RemoveAllPipes()
{
	while (!mPipes.empty())
	{
		delete mPipes.back();
		mPipes.pop_back();
	}
}

void Level::RemovePipes()
{
	mApp->Score();
	delete mPipes.front();
	mPipes.pop_front();
}

void Level::CreatePipes()
{
	double y = (rand() % 200) + 150;
	Pipe* pipe = new Pipe(mApp->GetScreenX(), y);
	mPipes.push_back(pipe);
}

deque<Pipe*> Level::GetPipes()
{
	return mPipes;
}
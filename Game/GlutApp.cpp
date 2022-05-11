#include "GlutApp.h"

GlutApp::GlutApp()
{
	mPlayer = new Player(this, 50.0, 200.0, 50.0, 50.0);
	mLevel = new Level(this);
	mTextureManager = new TextureManager();
}

GlutApp::~GlutApp()
{
	delete mPlayer;
	delete mLevel;
	delete mTextureManager;
}

void GlutApp::Update()
{
	if (mGameState == ACTIVE)
	{
		mLevel->Update();
		mPlayer->Update();

		if (Collides(mPlayer->GetX(), mPlayer->GetY(),
			mPlayer->GetWidth(), mPlayer->GetHeight()))
		{
			SetState(DEAD);
		}
	}
	mLevel->Draw();
	mPlayer->Draw();

	// DRAW "HUD"
	if (mGameState == ACTIVE)
	{
		std::string sv = std::to_string(mScore);
		char st[10] = "SCORE:";
		strcat_s(st, sv.c_str());
		DrawText(10.0, 10.0, st);
		glColor3d(1.0, 1.0, 0);
		DrawText(11.0, 11.0, st);
		glColor3d(0, 0, 0);
	}
	else if (mGameState == PAUSED)
	{
		char pt[33] = "PAUSED! Press SPACE to resume...";
		DrawText(mScreenX / 4, mScreenY / 2, pt);
		glColor3d(1.0, 1.0, 0);
		DrawText(mScreenX / 4 + 1, mScreenY / 2 + 1, pt);
		glColor3d(0, 0, 0);
	}
	else
	{
		char dt[32] = "DEAD! Press SPACE to restart...";
		DrawText(mScreenX / 4, mScreenY / 2, dt);
		glColor3d(1.0, 1.0, 0);
		DrawText(mScreenX / 4 + 1, mScreenY / 2 + 1, dt);
		glColor3d(0, 0, 0);
	}

	glutPostRedisplay();
}

void GlutApp::Start(int argc, char** argv, const char* name)
{
	srand(time(0));
	SetCurrentApp(this);
	StartGlut(argc, argv, name);
}

void GlutApp::SetState(GameState state)
{
	mGameState = state;
}

GameState GlutApp::GetState()
{
	return mGameState;
}

void GlutApp::Reset()
{
	mLevel->RemoveAllPipes();
	mLevel->CreatePipes();

	mPlayer->SetX(50.0);
	mPlayer->SetY(200.0);
	mPlayer->SetRotation(0.0);

	mScore = 0;

	SetState(PAUSED);
}

double GlutApp::GetScreenX()
{
	return mScreenX;
}

double GlutApp::GetScreenY()
{
	return mScreenY;
}

Player* GlutApp::GetPlayer()
{
	return mPlayer;
}

TextureManager* GlutApp::GetTextureManager()
{
	return mTextureManager;
}

bool GlutApp::Collides(double x, double y, double w, double h)
{
	// GROUND and CEILING
	if (mPlayer->GetY() < 0)
	{
		return true;
	}

	if (mPlayer->GetX() <
		mLevel->GetPipes().front()->GetX() + mLevel->GetPipes().front()->GetWidth()
		&& mPlayer->GetX() + mPlayer->GetWidth()
		> mLevel->GetPipes().front()->GetX())
	{
		if (mPlayer->GetY()
			< mLevel->GetPipes().front()->GetY() - mLevel->GetPipes().front()->GetGapSize() / 2
			|| mPlayer->GetY() + mPlayer->GetHeight()
			> mLevel->GetPipes().front()->GetY() + mLevel->GetPipes().front()->GetGapSize() / 2)
		{
			return true;
		}
	}
	return false;
}
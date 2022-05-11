#include "Player.h"

Player::Player(GlutApp* app, double x, double y, double w, double h)
	: mApp(app), mX(x), mY(y), mWidth(w), mHeight(h) {}

Player::~Player()
{
	mApp = NULL;
}

void Player::Draw()
{
	glPushMatrix();
	glTranslated(mX, mY, 0);
	glRotated((GLdouble)mRot, 0, 0, 1);

	mApp->GetTextureManager()->StartTexture("images/player.jpg");

	DrawRectangle(0, 0, mWidth, mHeight);
	glPopMatrix();

	mApp->GetTextureManager()->EndTexture();
}

void Player::Update()
{
	if (mY + mHeight + mDY > mApp->GetScreenY()) {
		mY = mApp->GetScreenY() - mHeight;
		mDY = 0;
	}
	else {
		// GRAVITY
		mY += mDY;
	}
	// acceleration
	if (mDY > mMax_Gravity)
	{
		mDY -= 0.5;
	}
	if (mDY < mMax_Gravity)
	{
		mDY = mMax_Gravity;
	}

	mRot = (60 * (mDY + 5) / 15) - 30;
}

void Player::Flap()
{
	mDY += 15.0;
}

void Player::SetX(double x)
{
	mX = x;
}

void Player::SetY(double y)
{
	mY = y;
}

void Player::SetRotation(double r)
{
	mRot = r;
}
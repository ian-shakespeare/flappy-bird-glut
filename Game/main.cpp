#include "GlutApp.h"

int main(int argc, char** argv)
{
	GlutApp* app = new GlutApp();
	app->Start(argc, argv, "My Game");
	for (;;) {
		app->Update();
	}
}
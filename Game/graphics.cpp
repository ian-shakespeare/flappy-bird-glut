// Code by Dr. Bart Stander with some modifications by Ian Shakespeare, 2022

#include "graphics.h"

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

// Global Variables (Only what you need!)
//double current_app->mScreenX = 700;
//double current_app->mScreenY = 500;
GlutApp* current_app;

void SetCurrentApp(class GlutApp* curr)
{
	current_app = curr;
}

// 
// Functions that draw basic primitives
//
void DrawCircle(double x1, double y1, double radius)
{
	glBegin(GL_POLYGON);
	for(int i=0; i<32; i++)
	{
		double theta = (double)i/32.0 * 2.0 * 3.1415926;
		double x = x1 + radius * cos(theta);
		double y = y1 + radius * sin(theta);
		glVertex2d(x, y);
	}
	glEnd();
}

void DrawRectangle(double x1, double y1, double x2, double y2)
{
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex2d(x1,y1);
	glTexCoord2f(1, 1); glVertex2d(x2,y1);
	glTexCoord2f(1, 0); glVertex2d(x2,y2);
	glTexCoord2f(0, 0); glVertex2d(x1,y2);
	glEnd();
}

void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
	glBegin(GL_TRIANGLES);
	glVertex2d(x1,y1);
	glVertex2d(x2,y2);
	glVertex2d(x3,y3);
	glEnd();
}

// Outputs a string of text at the specified location.
void DrawText(double x, double y, const char *string)
{
	void *font = GLUT_BITMAP_HELVETICA_18;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
	
	int len, i;
	glRasterPos2d(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++) 
	{
		glutBitmapCharacter(font, string[i]);
	}

    glDisable(GL_BLEND);
}


//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Test lines that draw all three shapes and some text.
	// Delete these when you get your code working.
	current_app->Update();

	glutSwapBuffers();

	//glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y)
{
	switch (c) 
	{
		/*case 27: // escape character means to quit the program
			delete current_app;
			exit(0);
			break;*/
		case 27:
			if (current_app->GetState() != PAUSED)
				current_app->SetState(PAUSED);
			else
			{
				std::cout << current_app->GetScore() << std::endl;
				delete current_app;
				exit(0);
			}
			break;
		case 'r':
			current_app->Reset();
			break;
		case ' ':
			if (current_app->GetState() == PAUSED)
				current_app->SetState(ACTIVE);
			else if (current_app->GetState() == DEAD)
			{
				current_app->Reset();
				current_app->SetState(ACTIVE);
			}
			else
				current_app->GetPlayer()->Flap();
		default:
			return; // if we don't care, return without glutPostRedisplay()
	}

	glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h)
{
	// Reset our global variables to the new width and height.
	//current_app->mScreenX = w;
	//current_app->mScreenY = h;

	// Set the pixel resolution of the final picture (Screen coordinates).
	glViewport(0, 0, current_app->GetScreenX(), current_app->GetScreenY());

	// Set the projection mode to 2D orthographic, and set the world coordinates:
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, current_app->GetScreenX(), 0, current_app->GetScreenY());
	glMatrixMode(GL_MODELVIEW);
	glutReshapeWindow(current_app->GetScreenX(), current_app->GetScreenY());
}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
	}
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
	{
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
	{
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) 
	{
	}
	glutPostRedisplay();
}

int StartGlut(int argc, char** argv, const char* name)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(current_app->GetScreenX(), current_app->GetScreenY());
	glutInitWindowPosition(50, 50);

	int fullscreen = 0;
	if (fullscreen)
	{
		glutGameModeString("800x600:32");
		glutEnterGameMode();
	}
	else
	{
		glutCreateWindow(name);
	}

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	glColor3d(0, 0, 0); // forground color
	glClearColor(1, 1, 1, 0); // background color
	current_app->GetTextureManager()->InitializeTextures();

	glutMainLoop();

	return 0;
}
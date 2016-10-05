// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

// glfw includes
#include <GLFW/glfw3.h>

// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"
#include "GLSphereSpot.h"
#include "GLRedSphere.h"
#include "GLBlueSphere.h"
#include "GLGreenSphere.h"
#include "GLYellowSphere.h"

using namespace std;

// The handle to the window object
GLFWwindow* window;

// Define some of the global variables we're using for this sample
GLuint program;

/* A trackball to move and rotate the camera view */
extern Trackball trackball;

int main(int argc, const char * argv[])
{


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// Init glfw, create a window, and init glew

	// Init the GLFW Window
	window = initWindow();


	// Init the glew api
	initGlew();



	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// Create some models

	// coordinate system
	CoordSystem* cs = new CoordSystem(40.0);


	GLRedSphere* red_sphere = new GLRedSphere(0.0, 0.0, 0.0, 10.0, 90, 50);
	GLBlueSphere* blue_sphere = new GLBlueSphere(25.0, 0.0, 0.0, 10.0, 90, 50);
	GLGreenSphere* green_sphere = new GLGreenSphere(50.0, 0.0, 0.0, 10.0, 180, 200);
	GLYellowSphere* yellow_sphere = new GLYellowSphere(75.0, 0.0, 0.0, 10.0, 180, 200);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// Main render loop

	static const GLfloat clear_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	// This sets the camera to a new location
	// the first parameter is the eye position, the second the center location, and the third the up vector. 
	SetViewAsLookAt(glm::vec3(37.0f, 0.0f, 80.0f), glm::vec3(37.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));


	// Enable depth test
	// ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
	glEnable(GL_DEPTH_TEST);

	//sphere->enableNormalVectorRenderer();

	// This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
	while (!glfwWindowShouldClose(window))
	{

		// Clear the entire buffer with our green color (sets the background to be green).
		glClearBufferfv(GL_COLOR, 0, clear_color);
		glClearBufferfv(GL_DEPTH, 0, clear_depth);


		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//// This renders the objects

		// Set the trackball locatiom
		SetTrackballLocation(trackball.getRotationMatrix());

		// draw the objects
		//cs->draw();

		red_sphere->draw();
		blue_sphere->draw();
		green_sphere->draw();
		yellow_sphere->draw();

		//// This renders the objects
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		// Swap the buffers so that what we drew will appear on the screen.
		glfwSwapBuffers(window);
		glfwPollEvents();

	}


	delete cs;


}


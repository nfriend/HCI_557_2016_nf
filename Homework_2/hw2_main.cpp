//
//  main.cpp
//  OpenGL4Test
//
//  Created by Rafael Radkowski on 5/28/15.
//  Copyright (c) 2015 -. All rights reserved.
//

// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"

// this line tells the compiler to use the namespace std.
// Each object, command without a namespace is assumed to be part of std. 
using namespace std;




static const string vs_string =
"#version 410 core                                                 \n"
"                                                                   \n"
"uniform mat4 projectionMatrix;                                    \n"
"uniform mat4 viewMatrix;                                           \n"
"uniform mat4 modelMatrix;                                          \n"
"in vec3 in_Position;                                               \n"
"                                                                   \n"
"in vec3 in_Color;                                                  \n"
"out vec3 pass_Color;                                               \n"
"                                                                  \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);  \n"
"    pass_Color = in_Color;                                         \n"
"}                                                                 \n";

// Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
static const string fs_string =
"#version 410 core                                                 \n"
"                                                                  \n"
"in vec3 pass_Color;                                                 \n"
"out vec4 color;                                                    \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    color = vec4(pass_Color, 1.0);                               \n"
"}                                                                 \n";




/// Camera control matrices
glm::mat4 projectionMatrix; // Store the projection matrix
glm::mat4 viewMatrix; // Store the view matrix
glm::mat4 modelMatrix; // Store the model matrix




// The handle to the window object
GLFWwindow*         window;


// Define some of the global variables we're using for this sample
GLuint program;







///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Fill this functions with your model code.

// USE THESE vertex array objects to define your objects
unsigned int vaoID[2];
unsigned int vboID[4];

int ts_vertices_count = 102;
float* ts_vertices = new float[ts_vertices_count];
float* ts_colors = new float[102];

float* pg_vertices = new float[18];
float* pg_colors = new float[18];

/*!
 ADD YOUR CODE TO CREATE THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
unsigned int createTriangleStripModel(void)
{
	// use the vertex array object vaoID[0] for this model representation

	ts_vertices[0] = 0; ts_vertices[1] = 0; ts_vertices[2] = 3; // 1
	ts_colors[0] = 0.0; ts_colors[1] = 0.0; ts_colors[2] = 1.0; 

	ts_vertices[3] = 1; ts_vertices[4] = 0; ts_vertices[5] = 3; 
	ts_colors[3] = 0.0; ts_colors[4] = 1.0; ts_colors[5] = 0.0;

	ts_vertices[6] = 0; ts_vertices[7] = 1; ts_vertices[8] = 3; 
	ts_colors[6] = 1.0; ts_colors[7] = 0.0; ts_colors[8] = 0.0;

	ts_vertices[9] = 1; ts_vertices[10] = 1; ts_vertices[11] = 3; // 2
	ts_colors[9] = 0.0; ts_colors[10] = 0.0; ts_colors[11] = 1.0;

	ts_vertices[12] = 0; ts_vertices[13] = 1; ts_vertices[14] = 1; // 3
	ts_colors[12] = 0.0; ts_colors[13] = 0.0; ts_colors[14] = 1.0;

	ts_vertices[15] = 1; ts_vertices[16] = 1; ts_vertices[17] = 1; // 4
	ts_colors[15] = 0.0; ts_colors[16] = 1.0; ts_colors[17] = 0.0;

	ts_vertices[15] = 1; ts_vertices[16] = 1; ts_vertices[17] = 1; // 5
	ts_colors[15] = 0.0; ts_colors[16] = 1.0; ts_colors[17] = 0.0;

	ts_vertices[18] = 1; ts_vertices[19] = 1; ts_vertices[20] = 3;
	ts_colors[18] = 0.0; ts_colors[19] = 1.0; ts_colors[20] = 0.0;

	ts_vertices[21] = 1; ts_vertices[22] = 0; ts_vertices[23] = 1;
	ts_colors[21] = 0.0; ts_colors[22] = 1.0; ts_colors[23] = 0.0;

	ts_vertices[24] = 1; ts_vertices[25] = 0; ts_vertices[26] = 3; // 6
	ts_colors[24] = 0.0; ts_colors[25] = 1.0; ts_colors[26] = 0.0;


	return 1;
}

/*!
 ADD YOUR CODE TO CREATE A MODEL USING PRIMITIVES OF YOUR CHOISE TO THIS FUNCTION
 */
unsigned int createPolygonModel(void)
{
	pg_vertices[0] = -0.5; pg_vertices[1] = -0.5; pg_vertices[2] = 1.5; // Bottom left corner
	pg_colors[0] = 1.0; pg_colors[1] = 1.0; pg_colors[2] = 1.0; // Bottom left corner

	pg_vertices[3] = -0.5; pg_vertices[4] = 0.5; pg_vertices[5] = 1.5; // Top left corner
	pg_colors[3] = 1.0; pg_colors[4] = 0.0; pg_colors[5] = 0.0; // Top left corner

	pg_vertices[6] = 0.5; pg_vertices[7] = 0.5; pg_vertices[8] = 1.5; // Top Right corner
	pg_colors[6] = 0.0; pg_colors[7] = 1.0; pg_colors[8] = 0.0; // Top Right corner

	pg_vertices[9] = 0.5; pg_vertices[10] = -0.5; pg_vertices[11] = 1.5; // Bottom right corner
	pg_colors[9] = 0.0; pg_colors[10] = 0.0; pg_colors[11] = 1.0; // Bottom right corner

	pg_vertices[12] = -0.5; pg_vertices[13] = -0.5; pg_vertices[14] = 1.5; // Bottom left corner
	pg_colors[12] = 1.0; pg_colors[13] = 1.0; pg_colors[14] = 1.0; // Bottom left corner

	pg_vertices[15] = 0.5; pg_vertices[16] = 0.5; pg_vertices[17] = 1.5; // Top Right corner
	pg_colors[15] = 0.0; pg_colors[16] = 1.0; pg_colors[17] = 0.0; // Top Right corner

	return 1;
}



/*!
 ADD YOUR CODE TO RENDER THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
void renderTriangleStripModel(void)
{

	// Bind the buffer and switch it to an active buffer
	glGenVertexArrays(2, &vaoID[0]);
	glBindVertexArray(vaoID[0]);

	glGenBuffers(2, vboID);

	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
	glBufferData(GL_ARRAY_BUFFER, ts_vertices_count * sizeof(GLfloat), ts_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, ts_vertices_count * sizeof(GLfloat), ts_colors, GL_STATIC_DRAW);

	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// HERE: THIS CAUSES AN ERROR BECAUSE I DO NOT KNOW HOW MANY TRIANGLES / VERTICES YOU HAVE.
	// COMPLETE THE LINE
	// Draw the triangles
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
	glDrawArrays(GL_TRIANGLE_STRIP, 5, 4);


	// Unbind our Vertex Array Object
	glBindVertexArray(0);
}



/*!
 ADD YOUR CODE TO RENDER THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
void renderPolygonModel(void)
{

	// Bind the buffer and switch it to an active buffer
	glGenVertexArrays(2, &vaoID[0]);
	glBindVertexArray(vaoID[0]);

	glGenBuffers(2, vboID);

	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), pg_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), pg_colors, GL_STATIC_DRAW);

	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// HERE: THIS CAUSES AN ERROR BECAUSE I DO NOT KNOW HOW MANY TRIANGLES / VERTICES YOU HAVE.
	// COMPLETE THE LINE
	// Draw the triangles
	//glDrawArrays(GL_POLYGON, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Unbind our Vertex Array Object
	glBindVertexArray(0);
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*!
 This function creates the two models
 */
void setupScene(void) {

	createTriangleStripModel();
	renderTriangleStripModel();

	/*createPolygonModel();
	renderPolygonModel();*/
}

int main(int argc, const char * argv[])
{

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// Init glfw, create a window, and init glew

	// Init the GLFW Window
	window = initWindow();


	// Init the glew api
	initGlew();

	// Prepares some defaults
	CoordSystemRenderer* coordinate_system_renderer = new CoordSystemRenderer(10.0);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// The Shader Program starts here

	// Vertex shader source code. This draws the vertices in our window. We have 3 vertices since we're drawing an triangle.
	// Each vertex is represented by a vector of size 4 (x, y, z, w) coordinates.
	static const string vertex_code = vs_string;
	static const char * vs_source = vertex_code.c_str();

	// Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
	static const string fragment_code = fs_string;
	static const char * fs_source = fragment_code.c_str();

	// This next section we'll generate the OpenGL program and attach the shaders to it so that we can render our triangle.
	program = glCreateProgram();

	// We create a shader with our fragment shader source code and compile it.
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fs_source, NULL);
	glCompileShader(fs);

	// We create a shader with our vertex shader source code and compile it.
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vs_source, NULL);
	glCompileShader(vs);

	// We'll attach our two compiled shaders to the OpenGL program.
	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);

	// We'll specify that we want to use this program that we've attached the shaders to.
	glUseProgram(program);

	//// The Shader Program ends here
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/// IGNORE THE NEXT PART OF THIS CODE
	/// IGNORE THE NEXT PART OF THIS CODE
	/// IGNORE THE NEXT PART OF THIS CODE
	// It controls the virtual camera

	// Set up our green background color
	static const GLfloat clear_color[] = { 0.6f, 0.7f, 1.0f, 1.0f };
	static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };


	projectionMatrix = glm::perspective(1.1f, (float)800 / (float)600, 0.1f, 100.f);
	modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Create our model matrix which will halve the size of our model
	viewMatrix = glm::lookAt(glm::vec3(1.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	int projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrix"); // Get the location of our projection matrix in the shader
	int viewMatrixLocation = glGetUniformLocation(program, "viewMatrix"); // Get the location of our view matrix in the shader
	int modelMatrixLocation = glGetUniformLocation(program, "modelMatrix"); // Get the location of our model matrix in the shader


	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader


	 //// The Shader Program ends here
	//// START TO READ AGAIN
	//// START TO READ AGAIN
	//// START TO READ AGAIN
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	glBindAttribLocation(program, 0, "in_Position");
	glBindAttribLocation(program, 1, "in_Color");



	// this creates the scene
	setupScene();

	int i = 0;

	// Enable depth test
	// ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
	glEnable(GL_DEPTH_TEST);

	// This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
	while (!glfwWindowShouldClose(window))
	{

		// Clear the entire buffer with our green color (sets the background to be green).
		glClearBufferfv(GL_COLOR, 0, clear_color);
		glClearBufferfv(GL_DEPTH, 0, clear_depth);

		// this draws the coordinate system
		coordinate_system_renderer->draw();

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//// This generate the object
		// Enable the shader program
		glUseProgram(program);

		// this changes the camera location
		glm::mat4 rotated_view = viewMatrix * GetRotationMatrix();
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &rotated_view[0][0]); // send the view matrix to our shader


		// This moves the model to the right
		//modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader


		// This line renders your triangle strip model
		renderTriangleStripModel();


		// This moves the model to the left
		//modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, -0.0f, 0.0f));
		//glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader

		// This line renders your Ppolygon model
		renderPolygonModel();


		// disable the shader program
		glUseProgram(0);


		//// This generate the object
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		// Swap the buffers so that what we drew will appear on the screen.
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	// delete the coordinate system object
	delete coordinate_system_renderer;

	// Program clean up when the window gets closed.
	glDeleteVertexArrays(2, vaoID);
	glDeleteProgram(program);
}


#pragma once

#include <string>
#include <vector>
#include "Exception.h"
#include "lodepng.h"
#include <GL/glut.h> // GLUT stuff - includes OpenGL headers as well

using namespace std;

namespace ImageIO {

	//helper image class - internal
	class GLImage {
	public:
		GLImage(const std::vector<unsigned char>& _buffer, unsigned int _width, unsigned int _height) :
			buffer((GLubyte*)&_buffer[0]), width(_width), height(_height) {}

		GLubyte* buffer;
		unsigned int width;
		unsigned int height;
	};

	std::vector<GLImage*> images;

	// display
	// The GLUT display function
	void display()
	{
		int id = glutGetWindow() - 1;
		glClear(GL_COLOR_BUFFER_BIT);
		// Draw image
		glLoadIdentity();
		glRasterPos2f(-1, 1);
		glPixelZoom(1, -1);
		glDrawPixels(images[id]->width, images[id]->height,
			GL_RGBA, GL_UNSIGNED_BYTE,
			images[id]->buffer);

		glutSwapBuffers();
	}

	// keyboard
	// The GLUT keyboard function
	void keyboard(unsigned char key, int x, int y) {
		if (key == 27)
			exit(0);
	}

	// Initialize OpenGL/GLUT
	void Init(int argc, char**argv) {
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
		glClearColor(1.0, 1.0, 1.0, 0.0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	}

	//load PNG file
	void LoadPNGImage(const string& file_name, std::vector<unsigned char>& image_buffer, unsigned int& width, unsigned int& height) {
		// Create the image in the array
		unsigned error = lodepng::decode(image_buffer, width, height, file_name.c_str());

		if (error != 0)
			throw Exception(lodepng_error_text(error));
	}

	//add display window for a specific image
	void AddWindow(const string& window_name, const std::vector<unsigned char>& image_buffer, const unsigned int width, const unsigned int height) {
		glutInitWindowSize(width, height);
		int id = glutCreateWindow(window_name.c_str());
		glutDisplayFunc(display);
		glutKeyboardFunc(keyboard);
		images.push_back(new GLImage(image_buffer, width, height));
	}

	//main loop that goes forever
	void MainLoop() {
		glutMainLoop();
	}
}

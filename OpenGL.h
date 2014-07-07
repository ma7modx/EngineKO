#pragma comment(lib, "glew32.lib")
//#pragma comment(lib, "opengl32.lib")
// Project Properties -> Linker -> Input -> Additional Dependencies
#pragma once
#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <GL\freeglut.h>

//#include <SDL/SDL.h>
/*
#include <SDL/SDL_main.h>
#include <SDL/SDL_filesystem.h>
#include <SDL/SDL_config.h>
#include <SDL/SDL_video.h>
#include <SDL/SDL_system.h>
#include <SDL/SDL_surface.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_events.h>
#include <SDL/SDL_gamecontroller.h>
*/
#include "stb_image.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include "GraphicsManager.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vertex.h"
#include "Matrix.h"
using namespace std;
class OpenGL :public GraphicsManager
{
public:
	static bool ClosePrograme , updateFinished , drawFinished;
	const static int orthoValues = 10 ;
	static float angle ;

	OpenGL(int iArgc, char** cppArgv, Window window) :GraphicsManager(window)
	{
		this->widnow = window;
		this->iArgc = iArgc;
		this->cppArgv = cppArgv;
	}
	void Start()
	{
		glutInit(&iArgc, cppArgv);

		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
		glutInitWindowSize(this->widnow.WindoWidth, this->widnow.Windowheight);
		glutInitWindowPosition(this->widnow.Windowposition.X, this->widnow.Windowposition.Y);
		glutCreateWindow(this->widnow.Title.c_str());

		//glOrtho (0, this->widnow.WindoWidth, this->widnow.Windowheight, 0, this->widnow.Near,  this->widnow.Far);
		glutInitContextVersion(4, 1);
		glutInitContextProfile(GLUT_CORE_PROFILE);

		if (glewInit()) {
			cout << "Unable to initialize GLEW ... exiting" << endl;
			exit(EXIT_FAILURE);
		}

		cout << glGetString(GL_VERSION) <<endl;
		cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl ;


		glFlush();
		glClearColor(this->widnow.color.R, this->widnow.color.G, this->widnow.color.B, 1);

	
		glEnable(GL_DEPTH_TEST);

		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);

	
		
		// anti aliasing
		glEnable (GL_POINT_SMOOTH);
		glEnable (GL_LINE_SMOOTH);
		glEnable (GL_POLYGON_SMOOTH);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glBlendFunc (GL_SRC_ALPHA_SATURATE, GL_ONE_MINUS_SRC_ALPHA);
		glLineWidth (2);
  
   

		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(this->widnow.Angle, this->widnow.WindoWidth / this->widnow.Windowheight, this->widnow.Near, this->widnow.Far);
		glMatrixMode(GL_MODELVIEW);
		
		glViewport(0, 0, this->widnow.WindoWidth, this->widnow.Windowheight);
		 /*
		glViewport(0, 0, this->widnow.WindoWidth, this->widnow.Windowheight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-orthoValues, orthoValues,
			-orthoValues,orthoValues,
			-orthoValues, orthoValues);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		 */


		GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat light_specular[] = { 1.0,1.0, 1.0, 1.0 };
		GLfloat light_position[] = { 0, 1.0, 1.0, 0.0 };
		
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

	}
	//-------------------------------------------------------------------------
	static int frameCount ,previousTime;
	static void calculateFPS()
	{
		//  Increase frame count
		frameCount++;

		//  Get the number of milliseconds since glutInit called
		//  (or first call to glutGet(GLUT ELAPSED TIME)).
		int currentTime = glutGet(GLUT_ELAPSED_TIME);

		//  Calculate time passed
		int timeInterval = currentTime - previousTime;
		if(timeInterval > 1000)
		{
			//  calculate the number of frames per second
			int fps = frameCount / (timeInterval / 1000.0f);
			cout << fps <<endl;
			//  Set time
			previousTime = currentTime;

			//  Reset frame count
			frameCount = 0;
		}
	}
	static void UpdateCall();
	static void DrawCALL();
	static void Close();
	static void Timer(int iUnused);
	void LOOP();

	void SetVertexPosition(Vector3 pos)
	{
		glVertex3f(pos.X, pos.Y, pos.Z);
	}
	void SetVertexColor(MColor color)
	{
		glColor3f(color.R, color.G, color.B);
	}
	void SetVertexTexCoord(Vector2 texcoord)
	{
		glTexCoord2f(texcoord.X, texcoord.Y);
	}
	void SetVertexNormal(Vector3 normal)
	{
		glNormal3f(normal.X, normal.Y, normal.Z);
	}
	void BindTexture(unsigned int ID)
	{
		glBindTexture(GL_TEXTURE_2D, ID);
	}
	unsigned int LoadTexture(const char*filename)
	{
		unsigned int texbufferID;

		glGenTextures(1, &texbufferID);
		glBindTexture(GL_TEXTURE_2D, texbufferID);

		int width = -1, height, dipth;
		auto load = stbi_load(filename, &width, &height, &dipth, 4);

		if(width == -1) std :: cout << "Wrong TexturePath " << filename << std :: endl ;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, load);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		return texbufferID;
	}
	void DeleteTexture(int size , unsigned int* ptr);
	void DeleteTexture(unsigned int* IDptr);

	void BeginTriangle()
	{
		glBegin(GL_TRIANGLES);
	}
	void EndTriangle()
	{
		glEnd();
	}
	void BeginLine()
	{
		glBegin(GL_LINES);
	}
	void EndLine()
	{
		glEnd();
	}
	void BeginQuad()
	{
		glBegin(GL_QUADS);
	}
	void EndQuad()
	{
		glEnd();
	}
	void BeginDrawList(int& ID)
	{
		ID = glGenLists(1);
		glNewList(ID, GL_COMPILE);//--
	}
	void EndDrawList()
	{
		glEndList();
	}

	void VBOModeDraw(int numOfVertices, int strideBetweenVertices, void* pointerToTheBeginingOfData[], VertexData mode, Shapes shape)
	{
		GPUModeActive(mode);

		VertexDataPointer(numOfVertices , strideBetweenVertices , pointerToTheBeginingOfData , mode);

		VBODraw(numOfVertices , shape) ;

		GPUModeDeactive(mode);
	}

	void VBOShaderModeDraw(int numOfVertices, int numOfShaders, int ShaderAttributesindices[], int strideBetweenVertices, void* pointerToTheBeginingOfData[], VertexData mode, Shapes shape)
	{
		GPUShaderModeActive(numOfShaders, ShaderAttributesindices); 

		ShaderAttributePointer( ShaderAttributesindices , strideBetweenVertices, pointerToTheBeginingOfData, mode) ;

		VBODraw(numOfVertices , shape) ;

		GPUShaderModeDeactive(numOfShaders, ShaderAttributesindices);
	}
	void IVBOModeDraw(unsigned int ibo, int numOfIndices ,int numOfVertices , int strideBetweenVertices, void* pointerToTheBeginingOfData[], VertexData mode, Shapes shape)
	{
		GPUModeActive(mode);

		VertexDataPointer(numOfVertices , strideBetweenVertices , pointerToTheBeginingOfData , mode);

		BindBuffer(BufferType::ELEMENT_BUFFER , ibo);

		IVBODraw(numOfVertices , shape) ;

		GPUModeDeactive(mode);
	}
	void IVBOShaderModeDraw(unsigned int ibo , int numOfIndices, int numOfShaderAttributes, int ShaderAttributesindices[], int strideBetweenVertices, void* pointerToTheBeginingOfData[], VertexData mode, Shapes shape)
	{
		// num of attributes
		GPUShaderModeActive(numOfShaderAttributes, ShaderAttributesindices); 

		ShaderAttributePointer( ShaderAttributesindices , strideBetweenVertices, pointerToTheBeginingOfData, mode) ;

		BindBuffer(BufferType::ELEMENT_BUFFER , ibo);

		IVBODraw(numOfIndices , shape);

		GPUShaderModeDeactive(numOfShaderAttributes, ShaderAttributesindices);
	}
	void ReserveBuffer(unsigned int& BufID)
	{
		glGenBuffers(1, &BufID);
	}
	void DeleteBuffer(int size , unsigned int* ptr) ;
	void DeleteBuffer(unsigned int* IDptr) ;
	void FillBuffer(unsigned int BufID, void* data, int sizeOfarray, GPUDrawMode Mode, BufferType BType)
	{
		//glGenBuffers(1, &BufID);

		int mode;
		if (Mode == GPUDrawMode::STATIC)
			mode = GL_STATIC_DRAW;
		else if (Mode == GPUDrawMode::DYNAMIC)
			mode = GL_DYNAMIC_DRAW;
		else
			mode = GL_STREAM_DRAW;

		int btype;
		if (BType == BufferType::ARRAY_BUFFER)
			btype = GL_ARRAY_BUFFER;
		else
			btype = GL_ELEMENT_ARRAY_BUFFER;

		glBindBuffer(btype, BufID);
		glBufferData(btype, sizeOfarray, data, mode);
	}
	void BindBuffer(BufferType Btype , unsigned int BufID)
	{
		if(Btype == BufferType::ARRAY_BUFFER)
			glBindBuffer(GL_ARRAY_BUFFER, BufID);
		else
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufID);
	}


	unsigned int LoadShader(const char *vertex_file_path, const char *fragment_file_path , unsigned int& out_VS , unsigned int& out_FS )
	{
		unsigned int  programID;
		std::string source;
		cout << endl << endl;
		loadFile(vertex_file_path, source);
		out_VS = loadShader(source, GL_VERTEX_SHADER);
		source = "";
		cout << endl << endl;
		loadFile(fragment_file_path, source);
		out_FS = loadShader(source, GL_FRAGMENT_SHADER);

		programID = glCreateProgram();
		glAttachShader(programID, out_VS);
		glAttachShader(programID, out_FS);

		glLinkProgram(programID);

		glDetachShader(programID , out_VS);
		glDetachShader(programID , out_FS);

		return programID;
	}
	void DeleteShader(unsigned int programID, unsigned int VS , unsigned int FS)
	{
		glDeleteShader(VS);
		glDeleteShader(FS);
		glUseProgram(0);
		glDeleteProgram(programID);
	}
	void ActiveShader(unsigned int ID)
	{
		glUseProgram(ID);
	}
	void DeactiveShader()
	{
		glUseProgram(0);
	}
	int GetShaderAttrib(unsigned int ID, const char* attribName)
	{
		return glGetAttribLocation(ID, attribName);
	}
	int GetShaderUniform(unsigned int ID, const char* attribName)
	{
		return glGetUniformLocation(ID, attribName);
	}
	void ShaderUniformf(unsigned int Location, float f1)
	{
		glUniform1f(Location, f1);
	}
	void ShaderUniformf(unsigned int Location, Vector2 vec)
	{
		glUniform2f(Location, vec.X, vec.Y);
	}
	void ShaderUniformf(unsigned int Location, Vector3 vec)
	{
		glUniform3f(Location, vec.X, vec.Y, vec.Z);
	}
	void ShaderUniformMat(unsigned int Location, Matrix mat)
	{
		glUniformMatrix4fv(Location, 1, GL_FALSE, (const float*)mat.Mtrx);
	}
	void ListDrawBegin(int &ID)
	{
		ID = glGenLists(1);
		glNewList(ID, GL_COMPILE);
	}
	virtual void ListDrawEnd()
	{
		glEndList();
	}
	void DeleteDrawList(int ID);
	virtual void ListDraw(int ID)
	{
		glCallList(ID);
	}

private:
	void loadFile(const char* fn, std::string& str)
	{
		std::ifstream in(fn);
		if (!in.is_open())
		{
			std::cout << "The file " << fn << " cannot be opened \n";
			return;
		}
		char tmp[900];
		while (!in.eof())
		{
			in.getline(tmp, 900);
			str += tmp;
			str += '\n';
		}
	}
	unsigned int loadShader(std::string& source, unsigned int mode)
	{
		unsigned int id;
		id = glCreateShader(mode);

		const char* csource = source.c_str();

		glShaderSource(id, 1, &csource, NULL);
		glCompileShader(id);
		char error[1000];
		glGetShaderInfoLog(id, 1000, NULL, error);
		if (mode == GL_VERTEX_SHADER)
			cout << "Vertex Shader ";
		else
			cout << "Fragment Shader ";
		std::cout << "Compile status: \n" << error;
		if (error[0] == '\0')
			cout << "Succeeded " << char(1);
		cout << endl;
		return id;
	}

	void GPUModeActive(VertexData Mode)
	{
		if (Mode.Mode & 1)
			glEnableClientState(GL_VERTEX_ARRAY);
		if (Mode.Mode & 2)
			glEnableClientState(GL_COLOR_ARRAY);
		if (Mode.Mode & 4)
			glEnableClientState(GL_NORMAL_ARRAY);
		if (Mode.Mode & 8)
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	void GPUModeDeactive(VertexData Mode)
	{
		if (Mode.Mode & 1)
			glDisableClientState(GL_VERTEX_ARRAY);
		if (Mode.Mode & 2)
			glDisableClientState(GL_COLOR_ARRAY);
		if (Mode.Mode & 4)
			glDisableClientState(GL_NORMAL_ARRAY);
		if (Mode.Mode & 8)
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	}
	void VertexDataPointer(int numOfVertices, int strideBetweenVertices, void* pointerToTheBeginingOfData[], VertexData mode)
	{
		if (mode.Mode & 1)
			glVertexPointer(numOfVertices, GL_FLOAT, strideBetweenVertices, pointerToTheBeginingOfData[0]);
		if (mode.Mode & 2)
			glColorPointer(numOfVertices, GL_FLOAT, strideBetweenVertices, pointerToTheBeginingOfData[1]);
		if (mode.Mode & 4)
			glNormalPointer(GL_FLOAT, strideBetweenVertices, pointerToTheBeginingOfData[3]);

	}
	void GPUShaderModeActive(int numOfShaders, int Shadersindices[])
	{
		for (int i = 0; i < numOfShaders; ++i)
			if(Shadersindices[i] != -1)
				glEnableVertexAttribArray(Shadersindices[i]);
			
	}

	void GPUShaderModeDeactive(int numOfShaderAttributes, int Shadersindices[])
	{
		for (int i = 0; i < numOfShaderAttributes; ++i)
			if(Shadersindices[i] != -1)
				glDisableVertexAttribArray(Shadersindices[i]);
			
	}
	void ShaderAttributePointer(int ShaderAttributesindices[] , int strideBetweenVertices, void* pointerToTheBeginingOfData[] , VertexData mode) 
	{
		if (mode.Mode & 1)
			glVertexAttribPointer(ShaderAttributesindices[0], 3, GL_FLOAT, GL_FALSE, strideBetweenVertices, pointerToTheBeginingOfData[0]);
		if (mode.Mode & 2)
			glVertexAttribPointer(ShaderAttributesindices[1], 3, GL_FLOAT, GL_FALSE, strideBetweenVertices, pointerToTheBeginingOfData[1]);
		if (mode.Mode & 4)
			glVertexAttribPointer(ShaderAttributesindices[2], 3, GL_FLOAT, GL_FALSE, strideBetweenVertices, pointerToTheBeginingOfData[2]);
		if (mode.Mode & 8)
			glVertexAttribPointer(ShaderAttributesindices[3], 2, GL_FLOAT, GL_FALSE, strideBetweenVertices, pointerToTheBeginingOfData[3]);
	}
	void VBODraw(int numOfVertices, Shapes shape)
	{
		glDrawArrays(GetShape(shape), 0, numOfVertices);
	}
	void IVBODraw(int numOfIndices, Shapes shape)
	{
		glDrawElements(GetShape(shape), numOfIndices , GL_UNSIGNED_INT, 0);
	}
	int GetShape(Shapes shape)
	{
		int glshape;
		if (shape == Shapes::TRIANGLE)
			glshape = GL_TRIANGLES;
		else if (shape == Shapes::LINE)
			glshape = GL_LINES;
		else
			glshape = GL_QUADS;
		return glshape ;
	}
};

/*
	unsigned int loadTexture(const char* name)
	{
	SDL_Surface* img=IMG_Load(name);
	SDL_PixelFormat form={NULL,32,4,0,0,0,0,8,8,8,8,0xff000000,0x00ff0000,0x0000ff00,0x000000ff,0,255};
	SDL_Surface* img2=SDL_ConvertSurface(img,&form,SDL_SWSURFACE);
	unsigned int texture;
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img2->w,img2->h,0,GL_RGBA, GL_UNSIGNED_INT_8_8_8_8,img2->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	SDL_FreeSurface(img);
	SDL_FreeSurface(img2);
	return texture;
	}
	*/
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")

#pragma once

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GL\GL.h>
#include <GL\GLU.h>
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
		//glutInitContextVersion(4, 2);
glutCreateWindow(this->widnow.Title.c_str());
		
		cout << glGetString(GL_VERSION) <<endl;
		cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl ;

		glewExperimental = GL_TRUE;
		glewInit();


		GLclampf r = this->widnow.color.R, g = this->widnow.color.G, b = this->widnow.color.B;
		glClearColor(r, g, b, 1);

		glEnable(GL_BLEND);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(this->widnow.Angle, this->widnow.WindoWidth / this->widnow.Windowheight, this->widnow.Near, this->widnow.Far);
		glMatrixMode(GL_MODELVIEW);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat light_specular[] = { 1.0,1.0, 1.0, 1.0 };
		GLfloat light_position[] = { 0, 1.0, 1.0, 0.0 };
		glShadeModel(GL_SMOOTH);

		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		
		int s(0);
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
	static void UpdateCall()
	{
		calculateFPS();
		
		GameController::GetGameController()->GameUpdateLOOP();
		// calculate elapsed time
		glutPostRedisplay();
	}
	static void DrawCALL()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GameController::GetGameController()->GameDrawLOOP();

		glutSwapBuffers();
	}
	static void Timer(int iUnused)
	{
		glutPostRedisplay();
		glutTimerFunc(GameController::GetGameController()->Graphicsmanager->widnow.FramesPerSec, Timer, 1);//1 to 30 to inf [very fast = 1] , 10
	}
	void LOOP()
	{
		/*
		SDL_Event event;

		while (SDL_PollEvent(&event)){}
		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_w:
				cout << "be5" << endl;
				break;
			}
		}
		*/
		glutIdleFunc(UpdateCall);
		glutDisplayFunc(DrawCALL);
		//	Timer(1) ;
		glutMainLoop();
		
	}

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
	unsigned int LoadTexture(const char*filename)
	{
		unsigned int texbufferID;

		glGenTextures(1, &texbufferID);
		glBindTexture(GL_TEXTURE_2D, texbufferID);

		int width, height, dipth;
		auto load = stbi_load(filename, &width, &height, &dipth, 4);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, load);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		return texbufferID;
	}
	/*
	void AllocateTexture(unsigned int *TexID)
	{
	glGenTextures(1,TexID) ;
	}
	void BindTexture(int TexID)
	{
	glBindTexture(GL_TEXTURE_2D , TexID) ;
	}
	void AssignTexture(int width,int height,int dipth , void *Pixels)
	{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	*/
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
	void IVBOShaderModeDraw(unsigned int ibo , int numOfIndices, int numOfShaders, int ShaderAttributesindices[], int strideBetweenVertices, void* pointerToTheBeginingOfData[], VertexData mode, Shapes shape)
	{
		GPUShaderModeActive(numOfShaders, ShaderAttributesindices); 

		ShaderAttributePointer( ShaderAttributesindices , strideBetweenVertices, pointerToTheBeginingOfData, mode) ;

		BindBuffer(BufferType::ELEMENT_BUFFER , ibo);

		IVBODraw(numOfIndices , shape);

		GPUShaderModeDeactive(numOfShaders, ShaderAttributesindices);
	}
	void ReserveBuffer(unsigned int& BufID)
	{
	glGenBuffers(1, &BufID);
	}
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


	unsigned int LoadShader(const char *vertex_file_path, const char *fragment_file_path)
	{
		unsigned int vertexShader, fragmentShader, programID;
		std::string source;
		cout << endl << endl;
		loadFile(vertex_file_path, source);
		vertexShader = loadShader(source, GL_VERTEX_SHADER);
		source = "";
		cout << endl << endl;
		loadFile(fragment_file_path, source);
		fragmentShader = loadShader(source, GL_FRAGMENT_SHADER);

		programID = glCreateProgram();
		glAttachShader(programID, vertexShader);
		glAttachShader(programID, fragmentShader);

		glLinkProgram(programID);

		return programID;
	}
	void DeleteShader(unsigned int programID)
	{
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

		//if(mode.Mode & 8)
		//gltexturepointer
	}
	void GPUShaderModeActive(int numOfShaders, int Shadersindices[])
	{
		for (int i = 0; i < numOfShaders; ++i)
			glEnableVertexAttribArray(Shadersindices[i]);
	}

	void GPUShaderModeDeactive(int numOfShaderAttributes, int Shadersindices[])
	{
		for (int i = 0; i < numOfShaderAttributes; ++i)
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





/*	unsigned int LoadShader(const char *vertex_file_path,const char *fragment_file_path)
{
// Create the shaders
unsigned int VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
unsigned int FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

// Read the Vertex Shader code from the file
string VertexShaderCode;
ifstream VertexShaderStream(vertex_file_path, ios::in);
if(VertexShaderStream.is_open())
{
std::string Line = "";
while(getline(VertexShaderStream, Line))
VertexShaderCode += "\n" + Line;
VertexShaderStream.close();
}
else
fprintf(stdout,"Cannot open vertexShader : %s \n" , vertex_file_path) ;


// Read the Fragment Shader code from the file
string FragmentShaderCode;
ifstream FragmentShaderStream(fragment_file_path, ios::in);
if(FragmentShaderStream.is_open()){
string Line = "";
while(getline(FragmentShaderStream, Line)) // endline after each line
FragmentShaderCode += "\n" + Line;
FragmentShaderStream.close();
}
else
fprintf(stdout,"Cannot open fragmentShader : %s \n" , fragment_file_path) ;

GLint Result = GL_FALSE;
int InfoLogLength;

// Compile Vertex Shader
printf("Compiling shader : %s\n", vertex_file_path);
char const * VertexSourcePointer = VertexShaderCode.c_str();
glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
glCompileShader(VertexShaderID);

// Check Vertex Shader
glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
vector<char> VertexShaderErrorMessage(InfoLogLength);
if(VertexShaderErrorMessage.size() == 0)
printf("VertexShaderErrorMessage out of range \n");
else
{
glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);
}
// Compile Fragment Shader
printf("Compiling shader : %s\n", fragment_file_path);
char const * FragmentSourcePointer = FragmentShaderCode.c_str();
glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
glCompileShader(FragmentShaderID);

// Check Fragment Shader
glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
vector<char> FragmentShaderErrorMessage(InfoLogLength);
if(FragmentShaderErrorMessage.size() == 0)
printf("FragmentShaderErrorMessage out of range \n");
else
{
glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);
}

// Link the program
fprintf(stdout, "Linking program\n");
GLuint ProgramID = glCreateProgram();
glAttachShader(ProgramID, VertexShaderID);
glAttachShader(ProgramID, FragmentShaderID);
glLinkProgram(ProgramID);

// Check the program
glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
if(ProgramErrorMessage.size() == 0)
printf("ProgramErrorMessage out of range \n");
else
{
glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
}

//	glDeleteShader(VertexShaderID);
//	glDeleteShader(FragmentShaderID);

return ProgramID;
}
*/

int OpenGL::frameCount = 0 ;
int OpenGL::previousTime = 0;
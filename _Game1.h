#pragma once 
#include <iostream>
#include "PartOfGamePlay.h"
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include "Texture.h"
#include "Vector3.h"
#include "Vertex.h"
#include "ImmedientShapes.h"
#include "MColor.h"
#include "RenderManager.h"
#include "Shader.h"
#include "GameController.h"
#include "GraphicsManager.h"
#include "GeometryIVBO.h"
#include "MemoryManager.h"
#include "Mesh.h"
#include "ObjLoader.h"
#include "InputDeviceManager.h"
#include "Button.h"
#include "UIManager.h"
#include "BasicShader.h"
using namespace std ;

class _Game1 : public PartOfGamePlay
{
public :

	Triangle *T;
	Mesh* mesh ;
	Shader *shader ;
	Shader *tranShader;
	GeometryIVBO* GPU ;
	Shader* sshader ;
	GeometryIVBO* shaderGPU;
	VertexAttributes* att;
	Texture* tex;
	BasicShader* basicShader;

	unsigned int img;
	float r ;
	void Initialize()
	{
		r = 0 ;

		mesh = new Mesh("mesh" , "meshmesh.obj");
		Vertex *V1, *V2,*V3 ;
		V1 = new VertexColor(Vector3(0,0,0) , MColor::Blue ) ;
		V2 = new  VertexColor(Vector3(1,1,0)  ,MColor::Black) ;
		V3 = new VertexColor(Vector3(-1,1,0) ,MColor::Red) ;
		T = new Triangle(V1 , V2 , V3) ;

		VertexColor offset[3] = {VertexColor( Vector3(0,0,0) , MColor(10,2,4)) ,VertexColor (Vector3(1,1,0), MColor(10,200,4)) ,VertexColor(Vector3(-1,1,0), MColor(10,2,200))}  ;

		int ind [] = {0,1,2} ;

		GPU = new GeometryIVBO(3 , offset , 3 , ind) ;
		//		 tex = new Texture(1) ;

		sshader = new Shader("mshader" , "vertex.vs","fragment.frag") ;
		tranShader = new Shader ("masd" , "TransofrmationShader.vs" , "SimpleFragmentShader.frag") ;

		float Z_ = 0 ;
		//VertexColor vc [4]={VertexColor( Vector3(-0.2,0.2,-Z_) , MColor(10,2,4)) ,VertexColor (Vector3(-0.2,-0.2,-Z_), MColor(10,200,4)) ,VertexColor(Vector3(0.2,-0.2,-Z_), MColor(10,2,200)) , VertexColor(Vector3(0.2,0.2,-Z_), MColor(10,2,200))};  
		VertexTexture vc [4]={VertexTexture( Vector3(-0.2,0.2,-Z_) , Vector2(0,0)) ,VertexTexture (Vector3(-0.2,-0.2,-Z_), Vector2(0,1)) ,VertexTexture(Vector3(0.2,-0.2,-Z_), Vector2(1,1)) , VertexTexture(Vector3(0.2,0.2,-Z_), Vector2(1,0))};  

		int ass [] = {0,1 , 2 ,	3 } ;
		cout << "Geometry IVBO ...\n" ;
		shaderGPU= new GeometryIVBO(4 , vc , 4 , ass);

		cout << "texture ...\n" ;
		tex = new Texture("sjs" , "images22.bmp");
		cout <<tex->GetID() <<endl ;

		att = new VertexAttributes() ;

		cout << "initialization finished ...\n" <<endl ;
		fsttime = 1 ;
		
		basicShader = new BasicShader();
	}
	int fsttime ;
	void Update()
	{
	}
	void DebugException(char* str )
	{
		if(fsttime)
		{
			cout << str << " ...\n";
		}
	}
	void Draw()
	{
		DebugException("begin Drawing");
		// pass the camera matrix to the render manager
		
		DebugException("Triangle1");
		T->Debug();
		
		DebugException("Triangle2");
		GPU->Draw();
		
		DebugException("mesh");
		glPushMatrix();
		glColor3f(0.3f,0.0f,0.0f);
		glLoadIdentity();
		glScalef(1,1,1);
		glTranslatef(0,0,-2);
		glRotatef(r+=0.04,1,1,0);
		mesh->Draw();
		glPopMatrix();
		
		DebugException("texture");
		r+= 0.04;
		
		tex->Use();
		
		basicShader->SetUniforms(BasicShaderUniforms::SCALE , Matrix::Scale(Vector3(10)));
		basicShader->SetUniforms(BasicShaderUniforms::TRANSFORMATION , Matrix::Rotation(Vector3(r , 20 , 0))  * Matrix::Translation(Vector3(0,2,2)));

		basicShader->Begin(); 
		shaderGPU->Draw(4, basicShader->GetAttributes(), Shapes::QUAD); 
		basicShader->End();
		
		
		DebugException("finished drawing");
		fsttime = 0 ;
	}
	bool Finished() 
	{
	
		return 0 ;
	}
	void Delete()
	{
		mesh->Delete();
		delete mesh;
		
		delete att ;
		
		delete T ;
		
		tranShader->Delete(); 
		delete tranShader;

		GPU->Delete();
		delete GPU;

		sshader->Delete();
		delete sshader;

		shaderGPU->Delete();
		delete shaderGPU;
		
		delete tex ;

		delete basicShader;
	}
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
};
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
#include "RenderingManager.h"
#include "Shader.h"
#include "GameController.h"
#include "GraphicsManager.h"
#include "GeometryIVBO.h"
#include "MemoryManager.h"
#include "Mesh.h"
#include "ObjLoader.h"
#include "InputDeviceManager.h"
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
	Texture* tex;
	int ID ;
	unsigned int img;
	float r ;
	void Initialize()
	{
		IVertex& vref = VertexColor(Vector3(1) , MColor::Red) ;
		cout <<vref.GetSize()<<endl;
		IVertex v = VertexColor(Vector3(1) , MColor::Red) ;
		cout <<v.GetSize()<<endl;

		r = 0 ;
		cout << (1<<2) <<endl;
	
		for(int m = 1 ;	m < MoveList::P6 ;	m <<= 1)
			cout << (MoveList)m << " " ;
			cout <<endl ;
			
			
			
			mesh = new Mesh("mesh" , "SimpleCubeAdv.obj");

		Vertex *V1, *V2,*V3 ;
		V1 = new VertexColor(Vector3(0,0,-7) , MColor::Blue ) ;
		V2 = new  VertexColor(Vector3(1,1,-7)  ,MColor::Black) ;
		V3 = new VertexColor(Vector3(-1,1,-7) ,MColor::Red) ;
		T = new Triangle(V1 , V2 , V3) ;

		IVertex *cc [3];
		cc[0]=  new Vertex( Vector3(0,22,-7)) ;cc[1] = new Vertex (Vector3(1,1,-7)) ;cc[2] = new Vertex(Vector3(-1,1,-7));

		VertexColor offset[3] = {VertexColor( Vector3(0,0,-7) , MColor(10,2,4)) ,VertexColor (Vector3(1,1,-7), MColor(10,200,4)) ,VertexColor(Vector3(-1,1,-7), MColor(10,2,200))}  ;

		int ind [] = {0,1,2} ;

		GPU = new GeometryIVBO(3 , offset , 3 , ind) ;
		 tex = new Texture(1) ;
		
		 ID = tex->LoadTexture("001.bmp");

		sshader = new Shader("mshader" , "vertex.vs","fragment.frag") ;
		tranShader = new Shader ("masd" , "TransofrmationShader.vs" , "SimpleFragmentShader.fragmentshader") ;

		VertexColor vc [4]={VertexColor( Vector3(-2,2,-90) , MColor(10,2,4)) ,VertexColor (Vector3(-2,-2,-90), MColor(10,200,4)) ,VertexColor(Vector3(2,-2,-90), MColor(10,2,200)) , VertexColor(Vector3(2,2,-90), MColor(10,2,200))};  

		int ass [] = {0,1 , 2 ,	3 } ;
		shaderGPU= new GeometryIVBO(4 , vc , 4 , ass);

		glActiveTexture(GL_TEXTURE0);

		//  img=loadTexture("img.jpg");
	}
	void Update()
	{

	}

	void Draw()
	{
		// pass the camera matrix to the render manager

		T->Debug();
		GPU->Draw();

	glBindTexture(GL_TEXTURE_2D , ID );
	/*
	glBegin(GL_QUADS);
	{
		glVertex3f(0,1,-30); glTexCoord2f(0,1);

		glVertex3f(0,0,-30); glTexCoord2f(0,0);
		glVertex3f(1,0,-30); glTexCoord2f(1,0);
		glVertex3f(1,1,-30); glTexCoord2f(1,1);
	}
	glEnd();
	*/

		glPushMatrix();
		glColor3f(1,0,0);
		glLoadIdentity();
		glTranslatef(0,0,-10);
		glRotatef(r+=0.04,1,0,0);
		mesh->Draw();
		glPopMatrix();
		

		// sshader->Active();
		
		tranShader->Active();

		tranShader->SetUniform("projection" , Matrix::Translation(Vector3(r+= 0.01,0,0)) ) ; // update

		// geo draw will get att frm the shader 
		// 

		//sshader->SetUniform("color" , Vector3(0.6,1,0.4)) ;
		VertexAttributes* att = new VertexAttributes(2) ;

		att->AddAttribute(tranShader->GetAttribute("vertex"), VertexData::VERTEX) ;
		att->AddAttribute(tranShader->GetAttribute("inputcolor"),  VertexData::COLOR);

		// send shader , draw mode
		shaderGPU->Draw(2, att->GetAttributes(), Shapes::QUAD); 

		tranShader->Deactive();
		//sshader->Deactive();

		
	}
	bool Finished() 
	{
		bool ret = false ;
		if(ret)
			//delete m , T  ;
				delete T ;
		return ret ; 
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
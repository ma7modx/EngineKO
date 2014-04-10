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
		
		sshader = new Shader("mshader" , "vertex.vs","fragment.frag") ;
		tranShader = new Shader ("masd" , "TransofrmationShader.vs" , "LightFragShader.frag") ;

		float Z_ = 0 ;
		//VertexColor vc [4]={VertexColor( Vector3(-0.2,0.2,-Z_) , MColor(10,2,4)) ,VertexColor (Vector3(-0.2,-0.2,-Z_), MColor(10,200,4)) ,VertexColor(Vector3(0.2,-0.2,-Z_), MColor(10,2,200)) , VertexColor(Vector3(0.2,0.2,-Z_), MColor(10,2,200))};  
		//VertexTexture vc [4]={VertexTexture( Vector3(-0.2,0.2,-Z_) , Vector2(0,0)) ,VertexTexture (Vector3(-0.2,-0.2,-Z_), Vector2(0,1)) ,VertexTexture(Vector3(0.2,-0.2,-Z_), Vector2(1,1)) , VertexTexture(Vector3(0.2,0.2,-Z_), Vector2(1,0))};  
		VertexTextureNormal vc [4]={VertexTextureNormal( Vector3(-0.2,0.2,-Z_) , Vector2(0,0) , Vector3(0,0,-1)) ,VertexTextureNormal (Vector3(-0.2,-0.2,-Z_), Vector2(0,1), Vector3(-1,0,0)) ,VertexTextureNormal(Vector3(0.2,-0.2,-Z_), Vector2(1,1), Vector3(0,0,1)) , VertexTextureNormal(Vector3(0.2,0.2,-Z_), Vector2(1,0), Vector3(0,0,1))};  
		cout << "VertexSize !! : " << sizeof VertexTextureNormal <<endl; 
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
		// pass the camera matrix to the render manager
		
		T->Debug();
		
		GPU->Draw();
		
		glPushMatrix();
		glColor3f(0.3f,0.0f,0.0f);
		glLoadIdentity();
		glScalef(1,1,1);
		glTranslatef(0,0,-2);
		glRotatef(r+=0.04,1,1,0);
		mesh->Draw();
		glPopMatrix();
		
		r+= 0.04;
		
		
		tex->Use();
		
		basicShader->SetUniforms(BasicShaderUniforms::SCALE , Matrix::Scale(Vector3(10)));
		basicShader->SetUniforms(BasicShaderUniforms::TRANSFORMATION , Matrix::Rotation(Vector3(r , 20 , 0))  * Matrix::Translation(Vector3(0,2,2)));

		basicShader->Begin(); 
		shaderGPU->Draw(basicShader->GetAttributes(), Shapes::QUAD); 
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
		delete mesh;
		delete att ;
		delete T ;
		delete tranShader;
		delete GPU;
		delete sshader;
		delete shaderGPU;
		delete tex ;
		delete basicShader;
	}
	
};
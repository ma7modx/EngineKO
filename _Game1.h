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
#include "Camera.h"
using namespace std ;

class _Game1 : public PartOfGamePlay
{
public :

	Triangle *T;
	Mesh* mesh ;
	GeometryIVBO* GPU ;
	GeometryIVBO* shaderGPU;
	GeometryIVBO* Line [3] ;
	Texture* tex;
	BasicShader* basicShader;
	BasicShader* basicShader2;
	Camera* camera;
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
		
		float Z_ = 0 ;
		VertexTextureNormal vc [4]={VertexTextureNormal( Vector3(-0.2,0.2,-Z_) , Vector2(0,0) , Vector3(0,0,1)) ,VertexTextureNormal (Vector3(-0.2,-0.2,-Z_), Vector2(0,1), Vector3(0,0,1)) ,VertexTextureNormal(Vector3(0.2,-0.2,-Z_), Vector2(1,1), Vector3(0,0,1)) , VertexTextureNormal(Vector3(0.2,0.2,-Z_), Vector2(1,0), Vector3(0,0,1))};  
		cout << "VertexSize !! : " << sizeof VertexTextureNormal <<endl; 
		int ass [] = {0,1 , 2 ,	3 } ;
		cout << "Geometry IVBO ...\n" ;
		shaderGPU= new GeometryIVBO(4 , vc , 4 , ass);

		cout << "texture ...\n" ;
		tex = new Texture("sjs" , "images22.bmp");
		cout <<tex->GetID() <<endl ;

		cout << "initialization finished ...\n" <<endl ;
		fsttime = 1 ;
		
		VertexColorNormal vl1[2] = { VertexColorNormal(Vector3(0,0,0) , MColor(0,1,0) , Vector3(0,0,0)) ,  VertexColorNormal(Vector3(0,1,0) , MColor(0,1,0) , Vector3(0,0,0)) };
		VertexColorNormal vl2[2] = { VertexColorNormal(Vector3(0,0,0) , MColor(1,0,0) , Vector3(0,0,0)), VertexColorNormal(Vector3(1,0,0) , MColor(1,0,0) , Vector3(0,0,0)) } ;
		VertexColorNormal vl3[2] = { VertexColorNormal(Vector3(0,0,0) , MColor(0,0,1) , Vector3(0,0,0)), VertexColorNormal(Vector3(0,0,1) , MColor(0,0,1) , Vector3(0,0,0)) } ;
		int i1[2] = { 0 , 1 } ;
		int i2[2] = { 0 , 1 } ;
		int i3[2] = { 0 , 1 } ;

		Line[0] = new GeometryIVBO(2,vl1 , 2 , i1) ;
		Line[1] = new GeometryIVBO(2,vl2 , 2 , i2) ;
		Line[2] = new GeometryIVBO(2,vl3 , 2 , i3) ;

		basicShader = new BasicShader();
		basicShader2 = new BasicShader("ay 7aga" , "TransofrmationShader.vs" , "LightFragShader22.frag");
		camera = new Camera(Vector3(0,0,0) , Vector3(0,0,1));
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
		
		//T->Debug();
		
		//GPU->Draw();
		
		glPushMatrix();
		glColor3f(0.3f,0.0f,0.0f);
		glLoadIdentity();
		glScalef(1,1,1);
		glTranslatef(0,0,-2);
		glRotatef(r+=0.04,1,1,0);
		//mesh->Draw();
		glPopMatrix();
		
		 camera->MoveCameraDirection(Vector3(0,0,1));
		 //camera->MoveCameraPosition(Vector3(r/10,r/10,0));

		
		//glActiveTexture(GL_TEXTURE0);
		tex->Use();
		
		Matrix camerMatrix = camera->GetCameraMatrixLookAt() ;
		Matrix proj =  Matrix::PerspectiveFOV(50 , 1.3 , -1 , 1);	// so weird ! 
		//Matrix proj =  Matrix::OrthoGraphic(-5,5,-5,5,-5,5);
		float MovZ = r ;
		cout << MovZ << endl ; 
		basicShader2->SetTrasnformationUniforms(proj , camerMatrix ,  Matrix::Scale(10)* Matrix::Translation(Vector3(0,0,2+r))) ;
		basicShader2->SetUniforms(BasicShaderUniforms::ISTEXTURE , Matrix(1) ) ;
		basicShader2->Begin(); 
		//VertexTextureNormal vt ;
		//basicShader2->Customize(vt.GetData().Mode);
		shaderGPU->Draw(basicShader2->GetAttributes(), Shapes::QUAD); 
		basicShader2->End();
		
	//VertexColorNormal vc ;
		basicShader->SetTrasnformationUniforms( proj , camerMatrix , Matrix::Scale(Vector3(1))) ;
		basicShader->SetUniforms(BasicShaderUniforms::ISTEXTURE , Matrix(0) ) ;
		basicShader->Begin(); 
	
		//basicShader->Customize(vc.GetData().Mode);
		
		Line[0]->Draw(4,basicShader->GetAttributes(), Shapes::LINE);
		Line[1]->Draw(4,basicShader->GetAttributes(), Shapes::LINE); 
		Line[2]->Draw(4,basicShader->GetAttributes(), Shapes::LINE); 
		basicShader->End();
		
		
		basicShader->SetUniforms(BasicShaderUniforms::TRANSFORMATION , Matrix::Translation(Vector3(0,0,10)) );
		basicShader->SetUniforms(BasicShaderUniforms::ISTEXTURE , Matrix(0) ) ;
		basicShader->Begin(); 
		//basicShader->Customize(vc.GetData().Mode);
		
		Line[0]->Draw(4,basicShader->GetAttributes(), Shapes::LINE);
		Line[1]->Draw(4,basicShader->GetAttributes(), Shapes::LINE); 
		Line[2]->Draw(4,basicShader->GetAttributes(), Shapes::LINE); 
		basicShader->End();
		
	
	}
	bool Finished() 
	{
		return 0 ;
	}
	void Delete()
	{
		delete mesh;
		delete T ;
		delete GPU;
		delete shaderGPU;
		delete tex ;
		delete basicShader;
		delete basicShader2;
		delete camera;
		delete Line[0];
		delete Line[1];
		delete Line[2];

	}
	
};
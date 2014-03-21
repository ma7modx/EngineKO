#include"Camera.h"
#include"Light.h"
#include "Shader.h"
#include<vector>
#include <map>
using namespace std;
class SceneManager;
class RenderManager 
{
public:
	RenderManager()
	{
		// add transformation shaders to gameobject
	}
	Light GetLight(int index)
	{
		return *lights[index];
	}
	void AddLight(Light* L)
	{
		lights.push_back(L);
	}
	void SetCamera(Camera* Cam)
	{
		camera = Cam;
	}
	Camera GetCamera()
	{
		return *camera; 
	}
	vector< Shader* > GetGameObjectShaders()
	{
		return shadersMap["GameObject"];
	}
	vector< Shader* > GetCustomShader(string s)
	{
		return shadersMap[s];
	}
	void AddShader(string s , Shader* v) // add shader to existing list
	{
		shadersMap[s].push_back(v) ;
	}
	void MakeNewShaders(string s , vector<Shader*> v) // make new shader list
	{
		shadersMap[s] = v;
	}
	void SetWorldViewMatrix(Matrix m)
	{
		worldViewMatrix = m;
	}
	Matrix GetWorldViewMatrix()
	{
		return worldViewMatrix;
	}
	void Draw();
private:
	Matrix worldViewMatrix;
	SceneManager* sceneManager;
	Camera* camera;
	vector<Light*> lights;
	map<string , vector<Shader*> > shadersMap;
};
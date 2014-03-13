#include"Camera.h"
#include"Light.h"
#include "Shader.h"
#include<vector>


class RenderManager 
{
public:
	vector<Light> lights;
	Camera mainCamera;
	Shader shader;
	Light GetLight(int index)
	{
		return lights[index];
	}
	void AddLight(Light L)
	{
		lights.push_back(L);
	}
	void SetCamera(Camera Cam)
	{
		mainCamera = Cam;
	}
	void Draw()
	{

	}
private:
};
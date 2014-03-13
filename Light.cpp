#include "Light.h"

Light::Light(GameObject* lightSource , Vector3 ambient ,Vector3 diffuse ,Vector3 specular) : GameComponent(lightSource, lightSource->GetPosition())
{
	this->lightSource = lightSource ; this->ambient = ambient ; this->diffuse = diffuse ; this->specular = specular ;
}

void Light::ApplyShader()
{

}
void Light::Update()
{
	//lightSource->Update();
}
void Light::Draw()
{
//	lightSource->Draw();
}

Shader* Light::GetShader()
{
	return lightShader ;
}
Light::~Light()
{
	delete lightSource;
	delete lightShader; 
}
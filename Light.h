#pragma once
#include "Vector3.h"
#include "Shader.h"
#include "GameObject.h"
#include "GameComponent.h"

class Light : public GameComponent
{
public:
	Vector3 ambient , diffuse , specular ;

	Light(GameObject* lightSource , Vector3 ambient ,Vector3 diffuse ,Vector3 specular);
	void ApplyShader();
	void Update();
	void Draw();
	Shader* GetShader();
	~Light();

private:
	GameObject* lightSource;
	Shader* lightShader;
};
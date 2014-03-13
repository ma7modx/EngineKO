#include "Scene.h"
#include "SceneGraph.h"
class SceneManager
{
public:

	SceneManager(Scene* scene , SceneGraph* sceneGraph)
	{
		this->scene = scene ; 
		this->sceneGraph = sceneGraph ;
	}
	void Update() 
	{
		for (int i = 0 ; i < scene->GetChilds().size() ; ++i)
		{
			if( sceneGraph->Apply((scene->GetChilds())[i]) ) 
				// draw
				;
		}
	}
	void SetScene(Scene* s)
	{
		scene = s;
	}
	Scene* GetCurrentScene()
	{
		return scene;
	}
	void SetSceneGraph(SceneGraph* graph)
	{
		sceneGraph = graph;
	}
	~SceneManager()
	{
		delete scene;
		delete sceneGraph;
	}

private:

	SceneGraph* sceneGraph;
	Scene* scene;
	Camera* camera;
};
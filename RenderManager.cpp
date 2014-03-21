#include "RenderManager.h"
#include "SceneManager.h"

void RenderManager::Draw()
	{
		vector<GameObject> sceneChilds = sceneManager->GetCurrentScene().GetChilds() ;
		for (int i = 0 ; i < sceneChilds.size() ; ++i)
		{
			if(sceneManager->ApplySceneGraph(&sceneChilds[i]))
				sceneChilds[i].GetDrawBhavior()->Draw();
		}

	}
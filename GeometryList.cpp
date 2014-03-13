#include "GeometryList.h"
#include "GameController.h"
#include "GraphicsManager.h"

	void GeometryList::BeginList()
	{
		ID = -1 ;
		GameController::GetGameController()->Graphicsmanager->ListDrawBegin(ID);
	}
	void GeometryList::EndList()
	{
		GameController::GetGameController()->Graphicsmanager->ListDrawEnd();
	}
	void GeometryList::Add(Shape* v)
	{
		v->Draw();
	}
	void GeometryList::Draw()
	{
		GameController::GetGameController()->Graphicsmanager->ListDraw(ID); 
	}


class GraphicsManager ;
class GamePlayManager ;
class ResourceManager ;
class MemoryManager ;

class GameController
{
public :
	GraphicsManager* Graphicsmanager ;
	GamePlayManager* GamePlaymanager; 
	ResourceManager* Resourcemanager;
	MemoryManager* Memorymanager;

	GameController(GraphicsManager* Graphicsmanager, MemoryManager* Memorymanager);
  
	void GameUpdateLOOP();

	void GameDrawLOOP();

	void GameEnd();

	static GameController* GetGameController()
	{
		return Controller ;
	}

private :
	static GameController* Controller ;

};

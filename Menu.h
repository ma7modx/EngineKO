#include <vector>
#include "Button.h"
#include "Vector2.h"

using namespace std ;
class Menu
{
public:
	Menu(int numOfButtons ,Vector2 position ,  float height , float width , bool autoArranging);
	void Show();
	~Menu();

private:
	bool autoArranging;
	Vector2 psoition ;
	float height , width ;
	vector<Button*> buttons ;
};

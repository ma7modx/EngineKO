#include <iostream>
using namespace std ;
class DepugManager
{
public:
	DepugManager();
	static void ShowMessage(const char* msg)
	{
		cout << msg <<endl;
	}
	~DepugManager();

private:

};

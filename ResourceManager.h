#include <map>
#include <string>
using namespace std ;
class Resource;

class ResourceManager 
{
public :
	int Register(string name , Resource* resource);

	Resource* Get(string name);

	int Delete(string name);
	
	
private :
	map<string , Resource*> Resources ;
};
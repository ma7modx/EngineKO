#pragma  once
class GameObject;

class IBehavior 
{
	public:
	GameObject* parent ;
	virtual void Input() {}
	virtual void ExecuteBehavior() {}
};

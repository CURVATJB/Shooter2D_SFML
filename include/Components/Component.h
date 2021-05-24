#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component
{
public:

	virtual ~Component() = default; 
	virtual void TickComponent(int64_t deltaTime = 0) = 0;

public:
	GameObject* m_owner = nullptr;

};

#endif //COMPONENT_H




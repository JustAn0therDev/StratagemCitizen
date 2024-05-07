#pragma once
class Scene
{
public:
	virtual void Input() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual bool GetShouldEndScene() const = 0;
};


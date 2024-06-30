#pragma once
class Scene
{
public:
	virtual void Input(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual bool GetShouldEndScene() const = 0;
};


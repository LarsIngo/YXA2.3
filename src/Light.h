#pragma once
#include "Entity.h"

class Light : public Entity
{
private:
	float mSpread;
	float mRange;
protected:

public:
	Light();
	~Light();

	float GetSpread() { return mSpread; }
	float GetRange() { return mRange; }
};

Light::Light() : Entity()
{
	mSpread = 2.f*pi;
	mRange = 20.f;
}

Light::~Light()
{

}
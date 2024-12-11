#pragma once
#include "Globals.h"

#include <memory>
#include <iostream>

// Base of all objects also know as a GameObject in some game engines
class Object
{
public:

	Object(Shape shape, const Point2f& position);
	
	Object(Object&&)					= delete;
	Object operator&=(const Object&)	= delete;
	Object operator&=(Object&&)			= delete;

	~Object() {};


	virtual void Draw() const;
	virtual void Update(float elapsedSec) {};

	bool	IsDead() const;

	float	GetSize() const;
	Shape	GetShape() const;
	Point2f GetPosition() const;
	Color4f GetColor() const;
	Circlef GetHitBox() const;

	void SetSize(float newSize);
	void SetShape(Shape newShape);
	void SetPosition(Point2f pos);
	void SetPosition(float posX, float posY);
	void SetColor(const Color4f& color);
	void SetColor(float r, float g, float b, float a);



private:
	Shape	m_Shape;
	Color4f m_Color;

	float	m_Size;
	float	m_Angle;



protected:
	Object(const Object&) = default;



 	Point2f m_Position;
	
	bool	m_bDead;



};

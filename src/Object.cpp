#include "Object.h"
#include "utils.h"


Object::Object(Shape shape, const Point2f& position) :
	m_Shape		{ shape },
	m_Color		{ Color4f(1.f, 1.f, 1.f, 1.f) },
	m_Size		{ 5.f },
	m_Angle		{ 0.f },
	m_Position	{ position },
	m_bDead		{ false	}
{
}


void Object::Draw() const
{
	utils::SetColor(m_Color);

	if (m_Shape == Shape::Circle)
	{
		utils::FillEllipse(m_Position, m_Size, m_Size);
		return;
	}

	std::vector<Point2f> arrVertices;

	const int nrVertices
	{		
		m_Shape == Shape::Triangle	? 3 :
		m_Shape == Shape::Square	? 4 :
		m_Shape == Shape::Pentagon	? 5 :
		m_Shape == Shape::Hexagon	? 6 : 7 
	};

	const float anglePerVertex{ 360.f / nrVertices };


	for (size_t i{ 0 }; i < nrVertices; ++i)
		arrVertices.push_back(Point2f(	m_Position.x - m_Size * cosf((i * anglePerVertex + m_Angle) * utils::g_toRadians),
										m_Position.y - m_Size * sinf((i * anglePerVertex + m_Angle) * utils::g_toRadians)));

	utils::FillPolygon(arrVertices);

}


#pragma region Getters/Setters


bool Object::IsDead() const
{
	return m_bDead;
}


float Object::GetSize() const
{
	return m_Size;
}

Shape Object::GetShape() const
{
	return m_Shape;
}

Point2f Object::GetPosition() const
{
	return m_Position;
}

Color4f Object::GetColor() const
{
	return m_Color;
}

Circlef Object::GetHitBox() const
{
	return Circlef(m_Position, m_Size);
}


void Object::SetSize(float newSize)
{
	if (newSize <= 0)
		std::abort();

	m_Size = newSize;
}

void Object::SetShape(Shape newShape)
{
	if (newShape > Shape::Circle)
		newShape = Shape::Triangle;

	m_Shape = newShape;
}

void Object::SetPosition(Point2f pos)
{
	m_Position = pos;
}

void Object::SetPosition(float posX, float posY)
{
	m_Position = Point2f(posX, posY);
}

void Object::SetColor(const Color4f& color)
{
	m_Color = color;
}

void Object::SetColor(float r, float g, float b, float a)
{
	m_Color = Color4f(r, g, b, a);
}


#pragma endregion



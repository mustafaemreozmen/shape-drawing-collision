#include "Shape.h"
#include <iostream>
#include<cstdlib>
#include <thread>    
#include <chrono>    
using namespace std;
using namespace glm;

Shape::Shape(float x, float y, float length, ShapeEnum shapeEnum)
{
	m_Position = vec3(x, y, 0.0f);
	m_Color.r = (10 + rand() % 15) / 25.0;
	m_Color.g = (10 + rand() % 15) / 25.0;
	m_Length = length;
	m_Direction = Shape::DIRECTION(rand() % 3);
	m_shapeEnum = shapeEnum;
}

vec3 Shape::getPosition()
{
	return m_Position;
}
vec4 Shape::getColor()
{
	return m_Color;
}
Shape::DIRECTION Shape::getDirection()
{
	return m_Direction;
}

Shape::ShapeEnum Shape::getShapeEnum() {
	return m_shapeEnum;
}
void Shape::setDirection(Shape::DIRECTION dir)
{
	m_Direction = dir;
}
void Shape::move()
{
	//Frame Collision Detection
	if (m_Position.x > 1.0f) {
		m_Direction = Shape::DIR_LEFT;
		cout << "Alan disina cikti, sola gidiyor\n";
	}
	if (m_Position.y > 1.0f)
	{
		m_Direction = Shape::DIR_DOWN;
		cout << "Alan disina cikti, asagi gidiyor\n";
	}
	if (m_Position.y < -1.0f)
	{
		m_Direction = Shape::DIR_UP;
		cout << "Alan disina cikti, yukari gidiyor\n";
	}
	if (m_Position.x < -1.0f)
	{
		m_Direction = Shape::DIR_RIGHT;
		cout << "Alan disina cikti, saga gidiyor\n";
	}

	switch (m_Direction)
	{
	case DIR_LEFT:
		m_Position -= vec3(m_Length, 0.0f, 0.0f);
		break;
	case DIR_RIGHT:
		m_Position += vec3(m_Length, 0.0f, 0.0f);
		break;
	case DIR_UP:
		m_Position += vec3(0.0f, m_Length, 0.0f);
		break;
	case DIR_DOWN:
		m_Position -= vec3(0.0f, m_Length, 0.0f);
		break;
	}
}
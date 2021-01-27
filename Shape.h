#ifndef SQUARE_H
#define SQUARE_H
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
class Shape
{
public:

    enum DIRECTION
    {
        DIR_LEFT = -1,
        DIR_RIGHT = 0,
        DIR_UP = 1,
        DIR_DOWN = 2

    };

    enum ShapeEnum {
        Triangle = 0,
        Circle = 1,
        Square = 2
    };

    Shape(float  x, float y, float length, ShapeEnum shapeEnum);

    glm::vec3 getPosition();
    glm::vec4 getColor();

    DIRECTION getDirection();
    ShapeEnum getShapeEnum();
    void setDirection(DIRECTION dir);

    void move();

private:

    glm::vec4   m_Color;
    glm::vec3   m_Position;
    float       m_Length;
    ShapeEnum   m_shapeEnum;
    DIRECTION   m_Direction;
};


#endif
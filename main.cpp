using namespace std;
using namespace glm;

#include <iostream>
#include <thread>    
#include <chrono>         
#include<glad/glad.h>
#include<glm/vec3.hpp>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<vector>
#include "ShaderProgram.h"
#include "Shape.h"

const float LENGTH = rand() % 100 / 10.0f;
const float SPEED = rand() % 25 / 1000.0f;

float vertices[] = {
	-LENGTH / 2,  LENGTH / 2, 0.0f,
	-LENGTH / 2, -LENGTH / 2, 0.0f,
	 LENGTH / 2, -LENGTH / 2, 0.0f,

	-LENGTH / 2,  LENGTH / 2, 0.0f,
	 LENGTH / 2, -LENGTH / 2, 0.0f,
	 LENGTH / 2,  LENGTH / 2, 0.0f,
};

vector<vec3>      verticesCircle;
vector<unsigned int>   indices;
vector<Shape*>    shapeList;

unsigned int VBO;
unsigned int VAO;
unsigned int EBO;

bool CheckCollision(Shape* one, Shape* two) //Çarpışma tespitinin yapıldığı bool fonksiyon
{
	bool collisionX = one->getPosition().x + LENGTH >= two->getPosition().x &&
		two->getPosition().x + LENGTH >= one->getPosition().x;
	bool collisionY = one->getPosition().y + LENGTH >= two->getPosition().y &&
		two->getPosition().y + LENGTH >= one->getPosition().y;
	return collisionX && collisionY;
}

bool moveShape() //Şekilleri hareket ettiren fonksiyon
{
	if (CheckCollision(shapeList[1], shapeList[0])) {
		cout << "CARPISMA TESPIT EDILDI";
		return false;
	}
	for (auto next : shapeList)
		next->move();
	return true;
}

void drawShape(ShaderProgram& program) //Şekil çizimlerinin gerçekleştirildiği metod
{
	for (auto next : shapeList)
	{
		program.setVec3("uMove", next->getPosition());
		program.setVec4("uColor", next->getColor());
		Shape::ShapeEnum shapeType = next->getShapeEnum();
		switch (shapeType)
		{
		case Shape::Circle:
			glDrawArrays(GL_TRIANGLES, 0, verticesCircle.size());
			break;
		case Shape::Square:
			glDrawArrays(GL_TRIANGLES, 0, 6);
			break;
		case Shape::Triangle:
			glDrawArrays(GL_TRIANGLES, 0, 3);
			break;
		default:
			glDrawArrays(GL_TRIANGLES, 0, 6);
			break;
		}
	}
}
float createRandomNumber() {
	if (rand() % 2 == 1)
		return rand() % 100 / 100.0f;
	return -1 * rand() % 100 / 100.0f;
}
void addShape()
{
	Shape* newShape = new Shape(createRandomNumber(), createRandomNumber(), SPEED, Shape::ShapeEnum(rand() % 3));
	shapeList.push_back(newShape);
}


int main(int argc, char** argv)
{
	srand(time(0));
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Collision Detection", NULL, NULL);
	if (window == NULL)
	{
		cout << "Pencere Olusturulamadi" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Glad olusturulurken bir sorun olustu" << endl;
		return -1;
	}
	buildCircle();
	addShape();
	addShape();

	ShaderProgram program;

	program.attachShader("./simplevs.glsl", GL_VERTEX_SHADER);
	program.attachShader("./simplefs.glsl", GL_FRAGMENT_SHADER);
	program.link();

	program.addUniform("uMove");
	program.addUniform("uColor");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		program.use();
		glBindVertexArray(VAO);
		drawShape(program);
		if (!moveShape())
			break;
		this_thread::sleep_for(chrono::milliseconds(70));
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}
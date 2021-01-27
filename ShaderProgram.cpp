#include"ShaderProgram.h"
#include<glad/glad.h>
#include<fstream>
#include<iostream>
using namespace std;
ShaderProgram::ShaderProgram()
{
	m_ProgramId = glCreateProgram();
}
ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_ProgramId);
}
void ShaderProgram::link()
{
	glLinkProgram(m_ProgramId);
	int isLinked;
	char log[512];
	glGetShaderiv(m_ProgramId, GL_LINK_STATUS, &isLinked);
	if (!isLinked)
	{
		glGetProgramInfoLog(m_ProgramId, 512, 0, log);
		cout << "Program Linking Error:" << endl << log << endl;
	}

}

void ShaderProgram::use()
{
	glUseProgram(m_ProgramId);
}
void ShaderProgram::addUniform(const string& varName)
{
	m_UniformVars[varName] = glGetUniformLocation(m_ProgramId, varName.c_str());
}
void ShaderProgram::setFloat(const string& varName, float value)
{
	glUniform1f(m_UniformVars[varName], value);
}
void ShaderProgram::setVec3(const string& varName, const glm::vec3& value)
{
	glUniform3f(m_UniformVars[varName], value.x, value.y, value.z);
}
void ShaderProgram::setVec4(const string& varName, const glm::vec4& value)
{
	glUniform4f(m_UniformVars[varName], value.r, value.g, value.b, value.a);
}
void ShaderProgram::attachShader(const char* fileName, unsigned int shaderType)
{
	unsigned int shaderId = glCreateShader(shaderType);

	string sourceCode = getShaderFromFile(fileName);

	const char* chSourceCode = &sourceCode[0];

	glShaderSource(shaderId, 1, &chSourceCode, 0);

	glCompileShader(shaderId);

	int isCompiled;
	char log[512];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);

	if (!isCompiled)
	{
		glGetShaderInfoLog(shaderId, 512, 0, log);
		string strType;
		switch (shaderType)
		{
		case GL_VERTEX_SHADER:
			strType = "Vertex Shader";
			break;
		case GL_FRAGMENT_SHADER:
			strType = "Fragment Shader";
			break;
		}
		cout << "Shader Type:" << strType << endl << log << endl;
	}
	glAttachShader(m_ProgramId, shaderId);
	glDeleteShader(shaderId);
}
string ShaderProgram::getShaderFromFile(const char* fileName)
{
	ifstream file(fileName);

	string data;

	if (file.is_open())
	{
		char readChar;
		while ((readChar = file.get()) != EOF)
		{
			data += readChar;
		}
		file.close();
	}
	return data;
}
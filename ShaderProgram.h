#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include<string>
#include<map>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
using namespace std;
using namespace glm;
class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	void attachShader(const char* fileName, unsigned int shaderType);
	void link();
	void use();
	void addUniform(const string& varName);
	void setFloat(const string& varName, float value);
	void setVec3(const string& varName, const vec3& value);
	void setVec4(const string& varName, const vec4& value);
private:
	string getShaderFromFile(const char* fileName);
	map<string, unsigned int>  m_UniformVars;
	unsigned int    m_ProgramId;
};


#endif
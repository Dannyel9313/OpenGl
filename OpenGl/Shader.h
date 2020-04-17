#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

enum class ETypeOfShader
{
	eVertex,
	eFragment,
	eNumType
};

class Shader
{
public:
	/* shader c-tor */
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

	/* method to activate shader */
	void UseProgram();
	//TODO overide uniform 
	/* utility uniform functions */
	void SetBool(const std::string& strName, bool value) const;
	void SetInt(const std::string& strName, int value) const;
	void SetFloat(const std::string& strName, float value) const;
private:
	/* method that reads a file and return as a string */
	std::string ReadFile(const char* filePath);
	/* method that compile given shader code and return shade id*/
	unsigned int CompileShader(const char* shaderCode,ETypeOfShader eType);
	/* method that creates a program from vertex and fragment shader */
	void CreateProgram();

	unsigned int m_nProgramID = 1000000;

	const char* vShaderCode = "";
	unsigned int vShaderId = 1000000;
	const char* fShaderCode = "";
	unsigned int fShaderId = 1000000;


};

#endif // !SHADER_H
#include "Shader.h"


Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	std::string vertexCode = ReadFile(vertexShaderPath);
	std::string fragmentCode = ReadFile(fragmentShaderPath);
	vShaderCode = vertexCode.c_str();
	fShaderCode = fragmentCode.c_str();
	vShaderId = CompileShader(vShaderCode, ETypeOfShader::eVertex);
	fShaderId = CompileShader(fShaderCode, ETypeOfShader::eFragment);
	CreateProgram();
	

}

std::string Shader::ReadFile(const char* filePath)
{
	std::ifstream fileObject;
	fileObject.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	std::string shaderCode = "";
	try
	{
		fileObject.open(filePath);
		std::stringstream stream;
		stream << fileObject.rdbuf();
		shaderCode = stream.str();
		return shaderCode;
	}
	catch (const std::ifstream::failure& e)
	{
		std::cout << "The file " << filePath << " can not be succesfully readed !!!" << std::endl;
	}
	return shaderCode;
}

unsigned int Shader::CompileShader(const char* shaderCode, ETypeOfShader eType)
{
	unsigned int shader;
	int success;
	char infoLog[512];
	switch(eType)
	{
		case ETypeOfShader::eVertex:
			shader = glCreateShader(GL_VERTEX_SHADER);
			break;
		case ETypeOfShader::eFragment:
			shader = glCreateShader(GL_FRAGMENT_SHADER);
			break;
	}
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		if (eType == ETypeOfShader::eVertex)
		{
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		else
		{
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	};
	return shader;
}

void Shader::CreateProgram()
{
	char infoLog[512];
	int succes;
	m_nProgramID = glad_glCreateProgram();
	glAttachShader(m_nProgramID, vShaderId);
	glAttachShader(m_nProgramID, fShaderId);
	glLinkProgram(m_nProgramID);
	glGetProgramiv(m_nProgramID, GL_LINK_STATUS, &succes);
	if (!succes)
	{
		glGetProgramInfoLog(m_nProgramID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vShaderId);
	glDeleteShader(fShaderId);
}

void Shader::UseProgram()
{
	glUseProgram(m_nProgramID);
}

void Shader::SetBool(const std::string& strName, bool value) const
{
	glUniform1i(glGetUniformLocation(m_nProgramID, strName.c_str()), int(value));
}

void Shader::SetInt(const std::string& strName, int value) const
{
	glUniform1i(glGetUniformLocation(m_nProgramID, strName.c_str()), value);
}

void Shader::SetFloat(const std::string& strName, float value) const
{
	glUniform1f(glGetUniformLocation(m_nProgramID, strName.c_str()), value);
}

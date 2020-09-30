#include <Shader.h>
#include <Error.h>
#include <print.h>


Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
    :m_renderer_id(0)
{
    m_renderer_id = createShader(vertexShader, fragmentShader);
}
Shader::~Shader() {
    GLCALL(glDeleteProgram(m_renderer_id));
}
unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = Shader::compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = Shader::compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    //deleting the intermediate shader objects
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)malloc(length * sizeof(char));
        glDeleteShader(id);
        return 0;
    }
    return id;
}
void Shader::bindShader() const {
    GLCALL(glUseProgram(m_renderer_id));
}
void Shader::unbindShader() const {
    GLCALL(glUseProgram(0));
}
void Shader::setUniform1f(const std::string& name, float value) {
    GLCALL(glUniform1f(getUniformLocation(name), value));
}
void Shader::setUniform1i(const std::string& name, int value) {
    GLCALL(glUniform1i(getUniformLocation(name), value));
}
void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    GLCALL(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}
void Shader::setUniformMat4f(const std::string& name, const glm::mat4 matrix) {
    GLCALL(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}
void Shader::setUniform1iv(const std::string& name) {
    int sampler[2] = { 0,1 };
    glUniform1iv(getUniformLocation(name), 2, sampler);
}

int Shader::getUniformLocation(const std::string& name) {
    GLCALL(int location = glGetUniformLocation(m_renderer_id, name.c_str()));
    if (location == -1)
        print("Uniform name error" + name);
    return location;
}

/* 
* compileshaders.c
*/

#include "scop.h"
#include "config.h"
#include <fcntl.h> //open
#include <unistd.h> //read

static unsigned int shaderCompiler(t_data *data, char const *shaderData, GLuint type)
{
    int             temp;
    unsigned int    ShaderId;

    temp = 0;
    ShaderId = glCreateShader(type);
    glShaderSource(ShaderId, 1, &shaderData, NULL);
    glCompileShader(ShaderId);
    glGetShaderiv(ShaderId, GL_COMPILE_STATUS, &temp); // check compilation
    if(!temp)
        secureExit(data, "Shader compilation error");
    return ShaderId;
}

static unsigned int fragmentShader(t_data *data, char *path)
{
    unsigned int id;
    int fragmentShaderFD;

    fragmentShaderFD = open(path, O_RDONLY);
    if (fragmentShaderFD < 0)
        secureExit(data, "Invalid Fragment Shader file");
    if (!(data->shader.fragmentShaderData = ft_filetostr(fragmentShaderFD, 512)))
        secureExit(data, "An error occured during shader file allocation");
    id = shaderCompiler(data, data->shader.fragmentShaderData, GL_FRAGMENT_SHADER); // check shader compilation
    ft_strdel(&data->shader.fragmentShaderData);
    close(fragmentShaderFD);

    return id;
}

static unsigned int vertexShader(t_data *data, char *path)
{
    unsigned int id;
    int vertexShaderFD;

    vertexShaderFD = open(path, O_RDONLY);
    if (vertexShaderFD < 0)
        secureExit(data, "Invalid Vertex Shader file");
    if (!(data->shader.vertexShaderData = ft_filetostr(vertexShaderFD, 512)))
        secureExit(data, "An error occured during shader file allocarion");
    id = shaderCompiler(data, data->shader.vertexShaderData, GL_VERTEX_SHADER); // check shader compilation
    ft_strdel(&data->shader.vertexShaderData);
    close(vertexShaderFD);

    return id;
}

[...]
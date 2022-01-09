/* 
* light.c
*/

#include "scop.h"

[...]

static void setVBO(t_data *data, unsigned int *VertexSize)
{
    unsigned int VBO;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, *VertexSize * sizeof(float), data->light.vertexBuffer, GL_STATIC_DRAW);
    ft_memdel((void**)&data->light.vertexBuffer);
}

static void setEBO(t_data *data, unsigned int *ElementSize)
{
    unsigned int EBO;

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, *ElementSize * sizeof(int), data->light.indicesBuffer, GL_STATIC_DRAW);
    ft_memdel((void**)&data->light.indicesBuffer);
}

static void setVertexBufferAttributes()
{
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void setLightData(t_data *data)
{
    unsigned int VertexSize, ElementSize;

    glGenVertexArrays(1, &data->light.vaoID);
    glBindVertexArray(data->light.vaoID);

    getVertexBuffer(data, &VertexSize);
    getIndicesBuffer(data, &ElementSize);
    setVBO(data, &VertexSize);
    setEBO(data, &ElementSize);
    setVertexBufferAttributes();

    glBindVertexArray(0);
}
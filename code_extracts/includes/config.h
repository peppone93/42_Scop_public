/* 
* config.h
*/

#ifndef CONFIG_H
#define CONFIG_H

#include "libft.h"
#include "materials.h"
#include <fcntl.h>

#define TOKENS_SIZE 6
#define COLOR_TOKEN "COLOR"
#define MATERIAL_TOKEN "MATERIAL"
#define TEXTURE_NAME_TOKEN "TEXTURENAME"
#define TEXTURE_MODE_TOKEN "TEXTUREMODE"
#define VTX_SHADER_TOKEN "VERTEXSHADER"
#define FRG_SHADER_TOKEN "FRAGMENTSHADER"

#define GRAY 16777215
#define TEXTURE_PATH "./textures/"
#define DEFAULT_TEXTURE "./textures/pony.bmp"

#define SHADER_VTX_PATH "./shaders/vertex/"
#define SHADER_FRG_PATH "./shaders/fragment/"
#define DEFAULT_MODEL_VTX_SHADER "./shaders/vertex/Complete.vshade"
#define DEFAULT_MODEL_FRG_SHADER "./shaders/fragment/42.fshade"
#define LIGHT_VERTEX_SHADER "./shaders/vertex/Position.vshade"
#define LIGHT_FRAGMENT_SHADER "./shaders/fragment/LightCube.fshade"

#define FILENAMELIMIT 100
#define VALUEINVALIDATOR 3
#define VALUELIMIT 30

#define MAXRES_X 1920
#define MAXRES_Y 1080
#define MINRES 500

typedef struct		s_config
{
	char			*textureName;
    char			*modelVertexShader;
    char			*modelFragmentShader;
    char			*file;
	unsigned char	defaultConf;
	i_materialIDX	material;
	unsigned int	winWidth;
	unsigned int	winHeight;
	unsigned int	modelColor;
	unsigned char	texutureMode;
	unsigned char	isFpsMode;
	unsigned char	isLightOn;
	unsigned char	isXRayOn;
	unsigned char	isRotationBlocked;
	float			modelBbox;
	float			inputSpeed;
	unsigned char	isTextureVisible;
	unsigned int	U_textureDepthID;
	unsigned int	U_isLightOnID;
	float			textureDepth;
}					t_config;

typedef char (*configType)(t_config *config, const char *value);

void cleanConfig(t_config *config);
void handleArguments(int ac, char** av, t_config *config);
void parseConfig(t_config *config);

void putConfigMessage(unsigned char *defaultConf);

#endif // CONFIG_H
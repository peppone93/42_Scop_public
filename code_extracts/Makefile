#scop

NAME = scop

# COLOR------------------------
CLRR = \033[0;31m
CLRG = \033[0;32m
CLRB = \033[0;34m
CLRC = \033[0;36m
CLRW = \033[0m
TAG_GLAD = $(CLRC)[GLAD] $(CLRW)
TAG_GLFW = $(CLRC)[GLFW] $(CLRW)
TAG_LBFT = $(CLRC)[LBFT] $(CLRW)
TAG_LVEC = $(CLRC)[LVEC] $(CLRW)
TAG_LBMP = $(CLRC)[LBMP] $(CLRW)
TAG_LMTX = $(CLRC)[LMTX] $(CLRW)
TAG_SCOP = $(CLRB)[SCOP] $(CLRW)
#------------------------------

# UTILITY----------------------
CC = gcc
CFLAGS = -Wall -Wextra -Werror
GCC = $(CC) $(CFLAGS)
#------------------------------

# PATH-------------------------
C_FILES =	main.c cleaner.c inputs.c callbacks.c gameloop.c\
			compileshaders.c handleshaders.c model.c textures.c\
			camera.c light.c material.c scene.c config.c
P_FILES =	parser.c p_cleaner.c p_counter.c p_filler.c p_utility.c\
			p_faces.c p_textures.c p_converter.c

SRC_D = ./srcs/
OBJ_D = ./compiled/
GLD_D = ./libs/glad/
LFT_D = ./libs/libft/
VEC_D = ./libs/vec/
GLF_D = ./libs/glfw/
BMP_D = ./libs/bmp/
MTX_D = ./libs/mtx/
INC_D = ./includes/
PRS_D = $(SRC_D)parser/
GLF_B = $(GLF_D)build/

I_SCOP = $(INC_D)scop.h
I_CONF = $(INC_D)config.h
I_PRSR = $(INC_D)parser.h

OBJ =	$(addprefix $(OBJ_D), $(C_FILES:.c=.o) $(P_FILES:.c=.o))
LIB =	$(LFT_D)libft.a $(BMP_D)bmp.a $(VEC_D)vec.a $(MTX_D)mtx.a
LIB +=	$(GLF_B)src/libglfw3.a $(GLD_D)glad.a

INC  = -I $(INC_D)
INC += -I $(GLD_D)include/glad/
INC += -I $(GLD_D)include/KHR/
INC += -I $(GLF_D)include/
INC += -I $(LFT_D)include/
INC += -I $(BMP_D)include/
INC += -I $(VEC_D)include/
INC += -I $(MTX_D)include/

FWK = -framework OpenGL -framework IOKit -framework Cocoa
#------------------------------

all: compile_libs $(NAME)
	@printf	"$(TAG_SCOP)Everything done\n"

compile_libs: lib_glfw lib_glad lib_ft lib_bmp lib_vec lib_mtx

lib_glad:
	@make -s -C $(GLD_D)

lib_glfw: $(GLF_B)

$(GLF_B):
	@mkdir -p $(GLF_B)
	@cd $(GLF_B); \
	cmake ../
	@cd ../
	@make -s -C $(GLF_B)
	@printf	"\r$(TAG_GLFW)$(CLRG)%-50s$(CLRW) [$(CLRG)%s$(CLRW)]\n" "Lib glfw compiled" "✔"

lib_ft:
	@make -s -C $(LFT_D)
lib_bmp:
	@make -s -C $(BMP_D)
lib_vec:
	@make -s -C $(VEC_D)
lib_mtx:
	@make -s -C $(MTX_D)

#EXE
$(NAME): $(OBJ_D) $(OBJ) $(LIB)
	@printf	"$(TAG_SCOP)%-50s [$(CLRR)%s$(CLRW)]" "Scop compiled" "✘"
	@$(GCC) $(OBJ) $(LIB) $(FWK) -o $@
	@printf	"\r$(TAG_SCOP)$(CLRG)%-50s$(CLRW) [$(CLRG)%s$(CLRW)]\n" "Scop compiled" "✔"

#OBJ
$(OBJ_D)%.o: $(SRC_D)%.c $(I_SCOP) $(I_CONF)
	@printf "$(TAG_SCOP)%-50s [$(CLRR)%s$(CLRW)]" "Object $@ created" "✘"
	@$(GCC) $(INC) -c $< -o $@
	@printf "\r$(TAG_SCOP)%-50s [$(CLRG)%s$(CLRW)]\n" "Object $@ created" "✔"

$(OBJ_D)%.o: $(PRS_D)%.c $(I_PRSR)
	@printf "$(TAG_SCOP)%-50s [$(CLRR)%s$(CLRW)]" "Object $@ created" "✘"
	@$(GCC) $(INC) -c $< -o $@
	@printf "\r$(TAG_SCOP)%-50s [$(CLRG)%s$(CLRW)]\n" "Object $@ created" "✔"

#DIR
$(OBJ_D):
	@mkdir -p $(OBJ_D)

# CLEAN-------------------------
clean:
	@printf	"$(TAG_SCOP)%-50s [$(CLRG)%s$(CLRW)]\n" "Scop objects removed" "∙"
	@rm -Rf $(OBJ_D) #scop obj
	@make -s -C $(GLD_D) clean
	@make -s -C $(BMP_D) clean
	@make -s -C $(LFT_D) clean
	@make -s -C $(VEC_D) clean
	@make -s -C $(MTX_D) clean

fclean: clean
	@printf	"$(TAG_SCOP)%-50s [$(CLRG)%s$(CLRW)]\n" "Scop removed" "∙"
	@rm -Rf $(NAME) #scop exe
	@make -s -C $(GLD_D) sclean
	@make -s -C $(BMP_D) sclean
	@make -s -C $(LFT_D) sclean
	@make -s -C $(VEC_D) sclean
	@make -s -C $(MTX_D) sclean

hclean: clean
	@printf	"$(TAG_SCOP)%-50s [$(CLRG)%s$(CLRW)]\n" "Scop removed" "∙"
	@rm -Rf $(NAME) #scop exe
	@printf	"$(TAG_GLFW)%-50s [$(CLRG)%s$(CLRW)]\n" "Lib Glfw removed" "∙"
	@if [ -f $(GLF_B) ]; then make -s -C $(GLF_B) clean; fi #glfw makefile
	@rm -Rf $(GLF_B)
	@make -s -C $(GLD_D) sclean
	@make -s -C $(BMP_D) sclean
	@make -s -C $(LFT_D) sclean
	@make -s -C $(VEC_D) sclean
	@make -s -C $(MTX_D) sclean

re: fclean all

print:
	@printf "obj: $(OBJ)\n"
	@printf "obj_d: $(OBJ_D)\n"
	@printf "src_d: $(SRC_D)\n"
# ------------------------------

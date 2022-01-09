#

NAME = mtx.a

# COLOR------------------------
CLRR = \033[0;31m
CLRG = \033[0;32m
CLRB = \033[0;34m
CLRC = \033[0;36m
CLRW = \033[0m
TAG_VEC = $(CLRC)[LMTX] $(CLRW)
#------------------------------

# UTILITY----------------------
CC = gcc
CFLAGS = -Wall -Wextra -Werror
GCC = $(CC) $(CFLAGS)
ARRC = libtool -static -o $(NAME) # ar rc cause "symbol(s) not found for architecture x86_64"
RLIB = ranlib $(NAME)
#------------------------------

# PATH-------------------------
C_FILES =	mtx4.c mtx4axerotation.c mtx4dot.c mtx4translation.c\
			mtx4vectormlt.c mtx4xrotation.c mtx4yrotation.c mtx4zrotation.c\
			mtx4perspective.c mtx4negate.c mtx4transpose.c mtx4lookat.c\
			mtx4copy.c mtx4scale.c mtx4puretranslation.c mtx4displace.c\
			mtx3.c mtx3normal.c
SRC_D = ./src/
OBJ_D = ./compiled/
INC = -I ./include/
INC += -I ./../libft/include/
INC += -I ./../vec/include/
SRC = $(addprefix $(SRC_D), $(C_FILES))
OBJ = $(addprefix $(OBJ_D), $(C_FILES:.c=.o))
#------------------------------

all: $(NAME)

#EXE
$(NAME) : $(OBJ_D) $(OBJ)
	@printf	"$(TAG_VEC)%-50s [$(CLRR)%s$(CLRW)]" "Lib Matrix compiled" "✘"
	@$(ARRC) $(OBJ) ./../libft/libft.a ./../vec/vec.a
	@$(RLIB)
	@printf	"\r$(TAG_VEC)$(CLRG)%-50s$(CLRW) [$(CLRG)%s$(CLRW)]\n" "Lib Matrix compiled" "✔"

#OBJ
$(OBJ_D)%.o : $(SRC_D)%.c
	@printf	"$(TAG_VEC)%-50s [$(CLRR)%s$(CLRW)]" "Object: $@ created" "✘"
	@$(GCC) -o $@ -c $< $(INC)
	@printf	"\r$(TAG_VEC)%-50s [$(CLRG)%s$(CLRW)]\n" "Object: $@ created" "✔"

#DIR
$(OBJ_D):
	@mkdir -p $(OBJ_D)

clean:
	@rm -Rf $(OBJ_D)
	@printf	"$(TAG_VEC)%-50s [$(CLRG)%s$(CLRW)]\n" "Lib mtx objects removed" "∙"

fclean: clean
	@rm -f $(NAME)
	@printf	"$(TAG_VEC)%-50s [$(CLRG)%s$(CLRW)]\n" "Lib mtx removed" "∙"

sclean:
	@rm -f $(NAME)
	@printf	"$(TAG_VEC)%-50s [$(CLRG)%s$(CLRW)]\n" "Lib mtx removed" "∙"

re: fclean all
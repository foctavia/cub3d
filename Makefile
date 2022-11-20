# Colors
RED			= "\033[1;31m"
GREEN		= "\033[1;32m"
RESET		= "\033[m"

# Compilation flags
ifeq ($(DMEM),1)
MEM 		= -fsanitize=address
endif

ifeq ($(DTHREAD),1)
MEM 		= -fsanitize=thread
endif

# Variables
NAME 		= cub3d
MINILIBX 	= $(INCDIR)minilibx-linux/libmlx_Linux.a
CC 			= cc
CFLAGS		= -Wall -Wextra -Werror -g3

OBJDIR 		= objs/
SRCDIR		= src/
INCDIR		= inc/

SRC			=	cub3d.c \
				parsing/start.c parsing/parsing.c parsing/init.c parsing/identifier.c parsing/content.c parsing/textures.c parsing/colors.c parsing/copy.c parsing/checker.c parsing/walls.c \
				rendering/render.c rendering/draw.c rendering/window.c rendering/move.c rendering/player.c rendering/mlx.c \
				raycasting/raycast.c raycasting/horizontal.c raycasting/vertical.c raycasting/utils.c \
				utils/error.c utils/gnl.c utils/is.c utils/mem.c utils/str.c utils/file.c utils/clean.c utils/display.c

OBJ 		= $(addprefix ${OBJDIR}, ${SRC:.c=.o})
INC 		= -I./${INCDIR} -I./minilibx-linux
MLX 		= -L./${INCDIR}minilibx-linux -lmlx
MLXLIBX 	= -lXext -lX11 -lm -lz 

all: $(NAME) 

$(OBJDIR)%.o : $(SRCDIR)%.c
	mkdir -p ${@D}
	$(CC) $(CFLAGS) $(MEM) $(INC) -c $< -o $@

$(NAME) : $(OBJ) $(MINILIBX)
	@echo -n "Compiling cub3d"
	@$(CC) $(CFLAGS) $(MEM) $(INC) $(OBJ) $(MINILIBX) $(MLXLIBX) -o $@
	@echo ${GREEN}"\t\tOK"${RESET}

$(MINILIBX) :
	@echo -n "Compiling minilibx"
	@make -s -C${INCDIR}minilibx-linux > /dev/null 2>&1
	@echo ${GREEN}"\tOK"${RESET}

clean :
	rm -rf $(OBJDIR)
	@make clean -s -C${INCDIR}/minilibx-linux

fclean: clean
	rm -f $(NAME)

re: fclean all
	make all

.PHONY: all clean fclean re
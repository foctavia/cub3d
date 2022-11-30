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

SRC_PARSING	= parsing/
SRC_UTILS	= utils/
SRC_RENDER	= rendering/
SRC_RAYCAST = raycasting/

SRC			=	cub3d.c \
				$(addprefix ${SRC_PARSING}, start.c			parsing.c		init.c \
											identifier.c	content.c		textures.c \
											colors.c		copy.c			checker.c \
											walls.c) \
				$(addprefix ${SRC_RENDER},	render.c		draw.c			window.c \
											move.c			player.c		mlx.c \
											bresenham.c		rotate.c) \
				$(addprefix ${SRC_RAYCAST},	raycast.c		dda.c			texture.c \
											utils.c) \
				$(addprefix ${SRC_UTILS},	error.c			gnl.c			is.c \
											mem.c			str.c			file.c \
											clean.c			display.c)

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
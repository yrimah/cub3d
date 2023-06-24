

BLU			= \033[0;34m
GRN			= \033[0;32m
RED			= \033[0;31m
RST			= \033[0m
END			= \e[0m

SRCS 	=	src/cub3D.c src/check_error.c src/errors_utils.c src/init_map.c src/utils.c src/key_input.c src/texture.c src/raycast.c src/raycast_draw.c\
			src/raycast_init.c src/raycast_utils.c  src/player.c src/minimap.c src/animation.c src/mouse_move.c src/tex_check.c
NAME		= cub3D
OBJS_DIR	= objs/
OBJS		= $(SRCS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))
CC			= cc -g
CC_FLAGS	= -Wall -Werror -Wextra
MLB_FLAGS	= libft/libft.a #mlx/libmlx.a -no-pie -lm -lX11 -lXext
MLX_flags	= -lmlx -framework OpenGL -framework AppKit 
$(OBJS_DIR)%.o : %.c include/cub3d.h
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)src
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@printf	"\033[2K\r${BLU}[BUILD - $(NAME)]${RST} '$<' $(END)"

$(NAME): $(OBJECTS_PREFIXED) maker
	@$(CC) -o $(NAME) $(OBJECTS_PREFIXED) $(CC_FLAGS) $(MLX_flags) $(MLB_FLAGS)
	@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME)$(END)\n"

all: $(NAME)

maker:
#make -C mlx
	@make -C libft

clean:
	@rm -rf $(OBJS_DIR)
	@make clean -C libft
	@echo "${GRN}[CLEAN]${RST} done"

fclean: clean
#@make clean -C mlx
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "${GRN}[FCLEAN]${RST} done"

re: fclean all

.PHONY:		all clean fclean re

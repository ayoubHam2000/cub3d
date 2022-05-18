# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/22 09:30:37 by aben-ham          #+#    #+#              #
#    Updated: 2022/05/18 15:26:21 by aben-ham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UTIL_FILES = \
	utils/ft_arrlen.c \
	utils/ft_substr.c \
	utils/ft_atoi.c \
	utils/ft_memcpy.c \
	utils/ft_memset.c \
	utils/ft_split.c \
	utils/int_check.c \
	utils/msk_split.c \
	utils/ft_strchr.c \
	utils/ft_strdup.c \
	utils/ft_strjoin.c \
	utils/ft_strlcpy.c \
	utils/ft_strlen.c \
	utils/ft_strncmp.c \
	utils/ft_strrchr.c \
	utils/ft_error.c \
	utils/ft_error_exit.c \
	utils/ft_strcmp.c \
	utils/ft_in.c \
	utils/ft_malloc/add_address.c \
	utils/ft_malloc/free_all.c \
	utils/ft_malloc/ft_addrs_exclude.c \
	utils/ft_malloc/malloc.c \
	utils/ft_malloc/malloc_error.c \
	utils/queue_c/q_clear.c \
	utils/queue_c/q_dequeue.c \
	utils/queue_c/q_enqueue.c \
	utils/get_next_line/get_next_line_utils.c \
	utils/get_next_line/get_next_line.c \
	utils/queue_c/q_init.c 

MainFiles = \
	_cub3d/draw/draw_line.c \
	_cub3d/draw/draw_map.c \
	_cub3d/draw/draw_square.c \
	_cub3d/draw/draw_rectangle.c \
	_cub3d/ray_casting/ray_casting.c \
	_cub3d/graphics/texture.c \
	_cub3d/graphics/color.c \
	_cub3d/events/exit_cube3d.c \
	_cub3d/events/on_key_up.c \
	_cub3d/events/mouse_move.c \
	_cub3d/events/on_key_down.c \
	_cub3d/map/check_identifier.c \
	_cub3d/map/check_map.c \
	_cub3d/map/get_map.c \
	_cub3d/map/get_map_matrix.c \
	_cub3d/map/get_types.c \
	_cub3d/map/map_utils.c \
	_cub3d/map/read_file.c \
	_cub3d/map/load_tex_from_file.c \
	_cub3d/utils/check_args.c \
	_cub3d/utils/init_mlx.c \
	_cub3d/utils/ft_put_pixel.c \
	_cub3d/utils/ft_put_pixel_color.c \
	_cub3d/utils/replace_image.c \
	_cub3d/utils/get_prog.c \
	_cub3d/utils/is_tile.c \
	_cub3d/game_util.c \
	_cub3d/game.c


FILES = \
	$(UTIL_FILES) \
	$(MainFiles) \
	main.c

#-Wall -Wextra -Werror
CFLAGS = -g -I includes/
FLAGS = -framework opengl -framework Appkit -fsanitize=address

#CFLAGS = -g -I includes/ -I/usr/include -Imlx_linux
#FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -fsanitize=address

# -fsanitize=address
DEPFLAGS = -MMD -MF $(@:.o=.d)

NAME = cub3d
MLX_LIB_NAME = libmlx.dylib
MLX_DIR = minilibx

OBJ_DIR = _OUT/

OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

deps = $(OBJ:.o=.d)

all : $(NAME)

$(MLX_LIB_NAME) :
	make -C $(MLX_DIR)
	mv $(MLX_DIR)/$(MLX_LIB_NAME) .

$(NAME) : $(OBJ) $(MLX_LIB_NAME)
	gcc $(MLX_LIB_NAME) $(OBJ) $(FLAGS) -o $(NAME)

$(OBJ) : $(OBJ_DIR)%.o : %.c
	mkdir -p $(dir $@)
	gcc $(CFLAGS) -c $(@:_OUT/%.o=%.c) $(DEPFLAGS) -o $@

-include $(deps)

clean :
	make -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(MLX_LIB_NAME)
	rm -f $(NAME)

re : fclean all

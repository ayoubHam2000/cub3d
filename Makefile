# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/22 09:30:37 by aben-ham          #+#    #+#              #
#    Updated: 2022/03/29 13:09:10 by aben-ham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UTIL_FILES = \
	utils/ft_substr.c \
	utils/ft_atoi.c \
	utils/ft_memcpy.c \
	utils/ft_memset.c \
	utils/ft_split.c \
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
	_cub3d/map/get_map.c \
	_cub3d/utils/check_args.c \
	_cub3d/utils/init_mlx.c \
	_cub3d/utils/init_prog.c


FILES = \
	$(UTIL_FILES) \
	$(MainFiles) \
	main.c

#-Wall -Wextra -Werror
CFLAGS = -Wall -Wextra -Werror -g -I includes/
FLAGS = -lmlx -framework opengl -framework Appkit
# -fsanitize=address
DEPFLAGS = -MMD -MF $(@:.o=.d)

NAME = cub3d

OBJ_DIR = _OUT/

OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

deps = $(OBJ:.o=.d)

all : $(NAME)

$(NAME) : $(OBJ)
	gcc  $(OBJ) $(FLAGS) -o $(NAME)

$(OBJ) : $(OBJ_DIR)%.o : %.c
	mkdir -p $(dir $@)
	gcc $(CFLAGS) -c $(@:_OUT/%.o=%.c) $(DEPFLAGS) -o $@

-include $(deps)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

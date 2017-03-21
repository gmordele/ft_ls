#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/17 00:00:01 by gmordele          #+#    #+#              #
#    Updated: 2017/03/21 13:00:32 by gmordele         ###   ########.fr        #
#                                                                              #
#******************************************************************************#


NAME		=	ft_ls

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

SRC			=	ft_ls.c				list_dir.c			make_arr.c		\
				sort_arr.c			comp_func.c			print.c			\
				print_col1.c		print_col2.c		make_arr_arg.c	\
				list_dir_arg.c		print_l_option.c	perm.c			\
				dir_info.c

OBJ			=	$(SRC:%.c=%.o)

DEST_SRC	=	src/

DEST_INC	=	./include/

DEST_LIB	=	libft/

LIBFT		=	$(DEST_LIB)libft.a

all 		:	$(NAME)

$(NAME)		:	$(OBJ) $(LIBFT)
	$(CC) $(FLAGS) -o $(NAME) $(LIBFT) $(OBJ) -I$(DEST_INC)

%.o			:	$(DEST_SRC)%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(DEST_INC)

$(LIBFT)	:
	make -C $(DEST_LIB)

clean		:
	rm -f $(OBJ)
	make clean -C $(DEST_LIB)

fclean		:	clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re			:	fclean all

.PHONY:all clean fclean re

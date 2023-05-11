# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madaguen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/25 05:25:07 by madaguen          #+#    #+#              #
#    Updated: 2023/05/04 21:16:30 by madaguen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC				= so_long2.c\
				  get_next_line.c
SRCBONUS			= 
OBJS				= ${SRC:.c=.o}
OBJBONUS			= ${SRCBONUS:.c=.o}
HEADER				= so_long.h
CC					= clang
FLAGS				= -Wall -Wextra -Werror -g3
FLAGSDEBUG			= -Wall -Wextra -Werror -g -fsanitize=address
NAME				= so_long
NAMEBONUS			= 
NAMEDEBUG			= so_long_debug
NAMEDEBUGBONUS		= 


%.o : %.c
		$(CC) $(FLAGS) -I/usr/include -Imlx_linux -O3 -c -o $@ $^

all: lib
		make $(NAME)
	
lib :
		make -C mlx_linux/

bonus: $(NAMEBONUS)

debug: $(NAMEDEBUG)

bonusdebug: $(NAMEDEBUGBONUS)

$(NAME): $(OBJS) $(HEADER)
		$(CC) $(FLAGS) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -o $(NAME)

$(NAMEBONUS): $(OBJBONUS) $(HEADER)
		$(CC) $(FLAGS) $(OBJBONUS) -o $(NAMEBONUS)

$(NAMEDEBUG): $(OBJS) $(HEADER)
		$(CC) $(FLAGSDEBUG) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -o $(NAMEDEBUG)

$(NAMEDEBUGBONUS): $(OBJBONUS) $(HEADER)
		$(CC) $(FLAGSDEBUG) $(OBJBONUS) -o $(NAMEDEBUGBONUS)

clean:
		rm -f $(OBJS) $(OBJBONUS)

fclean: clean
		rm -f $(NAME) $(NAMEBONUS) $(NAMEDEBUG) $(NAMEDEBUGBONUS)

re:		fclean 
		make all

.PHONY: all clean fclean re debug

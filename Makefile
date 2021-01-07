# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/27 12:11:42 by gdrake            #+#    #+#              #
#    Updated: 2021/01/06 12:15:24 by gdrake           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_containers

FLAGS = -std=c++98 -Wall -Wextra -Werror

SRCS = main.cpp 

OBJS = $(SRCS:.cpp=.o)

MAKE_DEPS = $(SRCS:.cpp=.d)

all: $(NAME)

$(NAME): $(OBJS) 
	clang++ $(FLAGS) $(OBJS) -I./ -o $(NAME)

clean:
	rm -rf $(OBJS) $(MAKE_DEPS)

fclean: clean
	rm -rf $(NAME)

re:	fclean $(NAME)

%.o: %.cpp
	clang++ $(FLAGS) -c $< -o $@ -MD

include $(wildcard $(MAKE_DEPS))

.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adoyle <adoyle@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/08 19:00:09 by adoyle            #+#    #+#              #
#    Updated: 2019/08/08 19:03:36 by adoyle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=a.out

.PHONY: all clean fclean re

all: 
	gcc src/sounds.c include/sounds.h -g -L /Users/adoyle/homebrew/lib -lSDL2-2.0.0 -I /Users/adoyle/homebrew/include -L /Users/adoyle/homebrew/lib -lSDL2_mixer-2.0.0

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(NAME)

re: fclean all
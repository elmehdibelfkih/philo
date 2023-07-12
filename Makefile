# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/06 03:53:38 by ebelfkih          #+#    #+#              #
#    Updated: 2023/07/10 15:45:13 by ebelfkih         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
ONAME = functions.a 
MAIN = main/philo.c
CC = cc -Wall -Werror -Wextra
RM = @rm -f
AR = @ar rc
FILES = main/philo.c code/parcing.c code/utils1.c 
OBJ = $(FILES:.c=.o) 

RED = \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[0;35m


%.o : %.c header/philo.h 
	$(CC) -o $@ -c $<

all : $(ONAME) $(NAME)
	@echo "${GREEN} archive files are created"
	@echo "${PURPLE} executable files are created"
	@echo "${PURPLE} bonus executable file is created"

$(NAME) : $(ONAME)
	$(CC) $(MAIN) $(ONAME) -o $(NAME)


$(ONAME) : $(OBJ)
	@echo "${GREEN} wait ..."
	$(AR) $(ONAME) $^

mandatory : $(NAME)
	@echo "${GREEN} start compiling"
	@echo "${GREEN} archive files are created"
	@echo "${PURPLE} executable files are created"

clean :
	$(RM) $(OBJ) $(ONAME)
	@echo "${RED} archive files are removed"
	

fclean: clean
	$(RM) $(NAME) $(ONAME) $(BONUS_NAME) $(IN_OUT)
	@echo "${RED} executable file removed"

re: fclean all 

.PHONY: clean fclean re bonus all mandatory
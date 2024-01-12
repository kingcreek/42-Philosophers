# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/04 15:47:46 by imurugar          #+#    #+#              #
#    Updated: 2023/04/05 16:36:40 by imurugar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# /* ~~~~~~~ FOLDERS DIR ~~~~~~~ */
SRCS_DIR	= ./src/
OBJ_DIR 	= ./obj/
INC_DIR		= ./inc/

# /* ~~~~~~~ FILES ~~~~~~~ */
INC =	philo.h

SRCS	=	main.c \
			message.c \
			philo_actions.c \
			utils.c \
			cleaner.c \
			parser.c \
			philo_die.c \

OBJ_FILES	= $(SRCS:.c=.o)

SRC = $(addprefix $(SRCS_DIR), $(SRCS))
OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
INCLUDES = $(addprefix $(INC_DIR), $(INC))

# /* ~~~~~~~ TESTING FLAGS ~~~~~~~ */
SANITIZE =
 SANITIZE = -g3 -fsanitize=address
#  SANITIZE = -g3 -fsanitize=thread

# /* ~~~~~~~ COMPILING INFO ~~~~~~~ */
GCC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -Ofast -O3 -march=native $(SANITIZE)
IFLAGS:= -I ./inc

# /* ~~~~~~~ OTHER ~~~~~~~ */
NAME = philo
RM = rm -f

# /* ~~~~~~~ Colors ~~~~~~~ */
RED:="\033[1;31m"
GREEN:="\033[1;32m"
PURPLE:="\033[1;35m"
CYAN:="\033[1;36m"
EOC:="\033[0;0m"

all: obj ${NAME}		

obj:
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o:$(SRCS_DIR)%.c $(INCLUDES)
	$(GCC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<

$(NAME): $(OBJS)
	@echo $(CYAN) " - Compiling $@" $(RED)
	$(GCC) $(OBJS) $(CFLAGS) -o $(NAME)
	@echo $(GREEN) "[FINISHED OK]" $(EOC)

clean:
	@echo $(PURPLE) "[🧹Cleaning...🧹]" $(EOC)
	${RM} -Rf $(OBJ_DIR)

fclean: clean
	@echo $(PURPLE) "[🧹FCleaning...🧹]" $(EOC)
	${RM} -f $(NAME)

re: 	fclean all

.PHONY: all clean fclean re
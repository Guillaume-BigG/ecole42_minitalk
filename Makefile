# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/08 14:30:03 by gbeaudoi          #+#    #+#              #
#    Updated: 2024/02/27 20:13:40 by gbeaudoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################### COLORS #####################################

RESET		:=	\e[0m
BOLD		:=	\e[1m
DIM		:=	\e[2m
ITAL		:=	\e[3m
UNDERLINE	:=	\e[4m

BLACK		:=	\e[30m
GRAY		:=	\e[90m
RED		:=	\e[31m
GREEN		:=	\e[32m
YELLOW		:=	\e[33m
ORANGE		:=	\e[38;5;208m
BLUE		:=	\e[34m
PURPLE		:=	\e[35m
PINK		:=	\033[38;2;255;182;193m
CYAN		:=	\e[36m

BRIGHT_BLACK	:=	\e[90m
BRIGHT_GREEN	:=	\e[92m
BRIGHT_YELLOW	:=	\e[93m
BRIGHT_BLUE	:=	\e[94m
BRIGHT_PURPLE	:=	\e[95m
BRIGHT_CYAN	:=	\e[96m


################################### BASICS ###################################

CLIENT		=	client
CLIENT_BONUS  =	client_bonus

SERVER		=	server
SERVER_BONUS  =	server_bonus

LIBFT = libft/

CC		=	cc
CFLAGS		=	-Wall -Wextra -Werror -I $(INC)
INC		=	include/
LIBC		=	ar -rcs
RM		=	rm -rf


################################### SOURCES ###################################

CLIENT_FILE	= client.c check_arguments.c utils.c

SERVER_FILE	=	server.c check_arguments.c utils.c

CLIENT_BONUS_FILE	= client_bonus.c check_arguments_bonus.c utils_bonus.c

SERVER_BONUS_FILE	= server_bonus.c check_arguments_bonus.c utils_bonus.c

######################## COMBINE DIRECTORIES AND FILES ########################

SRC_DIR		= src/
SRC_DIR_BONUS = src_bonus/

SRC_CLIENT 		= 	$(addprefix $(SRC_DIR), $(CLIENT_FILE))
SRC_SERVER		= 	$(addprefix $(SRC_DIR), $(SERVER_FILE))
SRC_BONUS_CLIENT	= 	$(addprefix $(SRC_DIR_BONUS), $(CLIENT_BONUS_FILE))
SRC_BONUS_SERVER	= 	$(addprefix $(SRC_DIR_BONUS), $(SERVER_BONUS_FILE))


OBJ_DIR		=	obj/
OBJ_DIR_BONUS = obj_bonus/


OBJ_CLIENT 		= 	$(addprefix $(OBJ_DIR), $(CLIENT_FILE:.c=.o))
OBJ_SERVER		= 	$(addprefix $(OBJ_DIR), $(SERVER_FILE:.c=.o))
OBJ_BONUS_CLIENT	= 	$(addprefix $(OBJ_DIR_BONUS), $(CLIENT_BONUS_FILE:.c=.o))
OBJ_BONUS_SERVER	= 	$(addprefix $(OBJ_DIR_BONUS), $(SERVER_BONUS_FILE:.c=.o))

#################################### MANDATORY ####################################

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $^ -o $@ -L$(LIBFT) -lft

$(SERVER): $(OBJ_SERVER)
	@make -C $(LIBFT)
	@cp $(LIBFT)/libft.a .
	$(CC) $(CFLAGS) $^ -o $@ -L$(LIBFT) -lft

all:		$(SERVER) $(CLIENT) 

.DEFAULT_GOAL := all

#################################### BONUS ####################################

$(OBJ_DIR_BONUS)%.o: $(SRC_DIR_BONUS)%.c | $(OBJ_DIR_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_BONUS):
	mkdir -p $(OBJ_DIR_BONUS)

$(CLIENT_BONUS): $(OBJ_BONUS_CLIENT)
	$(CC) $(CFLAGS) $^ -o $@ -L$(LIBFT) -lft

$(SERVER_BONUS): $(OBJ_BONUS_SERVER)
	@make -C $(LIBFT)
	@cp $(LIBFT)/libft.a .
	$(CC) $(CFLAGS) $^ -o $@ -L$(LIBFT) -lft

bonus:		$(SERVER_BONUS) $(CLIENT_BONUS) 

#################################### RULES ####################################

clean:
		@$(RM) $(OBJ_DIR)
		@$(RM) $(OBJ_DIR_BONUS)
		@make clean -C $(LIBFT)
		@printf "$(BOLD)$(PINK)[MINITALK]: $(RESET)$(PINK)object files $(RESET)\t\t=> CLEANED! \n\n"

fclean: 	clean
			@$(RM) $(CLIENT) $(CLIENT_BONUS) $(SERVER) $(SERVER_BONUS)
			@$(RM) $(LIBFT)/libft.a
			@$(RM) libft.a
			@printf "$(BOLD)$(PURPLE)[LIBFT]: $(RESET)$(PURPLE)exec. files $(RESET)\t=> CLEANED! \n\n"
			@printf "$(BOLD)$(BRIGHT_PURPLE)[MINITALK]: $(RESET)$(BRIGHT_PURPLE)exec. files $(RESET)\t=> CLEANED! \n\n"

re:		fclean all
			@printf "\n\n $(BOLD)$(YELLOW)Cleaning done! $(RESET)\n"
			
.PHONY:		all clean fclean re bonus
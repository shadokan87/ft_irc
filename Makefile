# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mescande <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 14:03:19 by mescande          #+#    #+#              #
#    Updated: 2022/04/26 16:18:01 by matthieu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		?=	ircserv

MAKE		+= --no-print-directory

CXX			=	c++

ifndef CXXFLAGS
CXXFLAGS		=	-std=c++98 -Wall -Wextra -Werror
CXXFLAGS		+=	-g
CXXFLAGS		+=	-fsanitize=address
endif

LEN_NAME	=	`printf "%s" $(NAME) | wc -c`
DELTA		=	$$(echo "$$(tput cols)-32-$(LEN_NAME)" | bc)

SRC_DIR		=	
OBJ_DIR		=	objs/

INC_FLAGS	=	-iquote includes/ -iquote class/ -iquote .

SRC_LIST	=	\
				commands/errors.cpp \
				commands/replies.cpp \
				commands/EXIT.cpp \
				commands/USER.cpp \
				commands/PASS.cpp \
				commands/NICK.cpp \
				commands/JOIN.cpp \
				commands/LIST.cpp \
				commands/PING_PONG.cpp \
				commands/PRIVMSG.cpp \
				commands/PART.cpp\
				commands/TOPIC.cpp\
				commands/MODE.cpp\
				commands/KICK.cpp\
				class/Server.cpp\
				class/Client.cpp\
				class/Channel.cpp\
				parsing/parser.cpp\
				main.cpp\

SRC			=	$(addprefix $(OBJ_DIR), $(SRC_IST))
OBJ			=	$(addprefix $(OBJ_DIR), $(SRC_LIST:.cpp=.o))
DIR			=	$(sort $(dir $(OBJ)))
NB			=	$(words $(SRC_LIST))
INDEX		=	0

SHELL		:=	$(shell which bash)

all: 
	@$(MAKE) -j $(NAME)
	@printf "\r\033[38;5;117m✓ MAKE $@\033[0m\033[K\n"

$(NAME):		$(OBJ) Makefile $(LIB_DIR)$(LIB_LIB) 
	@$(CXX) $(CXXFLAGS) -MMD $(OBJ) -o $@ $(INC_FLAGS)
	@printf "\r\033[38;5;117m✓ MAKE $(NAME)\033[0m\033[K\n"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp Makefile | $(DIR)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval TO_DO=$(shell echo $$((20-$(INDEX)*20/$(NB) - 1))))
	@$(eval COLOR=$(shell list=(160 196 202 208 215 221 227 226 190 154 118 84 46); index=$$(($(PERCENT) * $${#list[@]} / 100)); echo "$${list[$$index]}"))
	@printf "\r\033[38;5;%dm↻ [%s]: %2d%% `printf '█%.0s' {0..$(DONE)}`%*s❙%s\033[0m\033[K" $(COLOR) $(NAME) $(PERCENT) $(TO_DO) "" "$(shell echo "$@" | sed 's/^.*\/\(.*\).[och]$$/\1/')"
	@$(CXX) $(CXXFLAGS) -MMD -c $< -o $@ $(INC_FLAGS)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

$(DIR):
	@mkdir -p $@

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f *output
	@printf "\r\033[33;5;117m✓ MAKE $@\033[0m\033[K\n"

fclean: clean
	@rm -rf $(NAME)
	@printf "\r\033[33;5;117m✓ MAKE $@\033[0m\033[K\n"

re: fclean
	@$(MAKE) all

test:
	$(MAKE) $(NAME)
	./$(NAME) $(ARGS)

valgrind:
	@$(MAKE) all
	@valgrind ./$(NAME) $(ARGS)

help:
	@echo "all	: compiling everything that changed, linking, not relinking\n"
	@echo "clean	: destroy all objects and linking files from program and libs\n"
	@echo "fclean	: clean and destroy exec files and libs"
	@echo "re	: fclean all"
	@echo "nolib	: destroy object of programs only (not lib) then compiling again"
	@echo "norme	: execute a norme test on all code files but do no compile"
	@echo "help	: print this help"
	@echo "test	: compile, and run the program with ARGS for argument (default : $$""(ARGS) = '$(ARGS)')"
	@echo "valgrind: compile and run the program with valgrind and ARGS for argument"

.PHONY: all clean fclean re

-include $(OBJ:.o=.d)

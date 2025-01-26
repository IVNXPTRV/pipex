# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/02 16:48:06 by ipetrov           #+#    #+#              #
#    Updated: 2025/01/26 19:58:40 by ipetrov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -Wunreachable-code -g -MMD -MF
#-Wall -Wextra -Werror -Wunreachable-code

RM					=	rm -rf

# Name of the output library
NAME 				=	pipex

# Include directories
INCLUDE_DIRS		=	\
						./include \
						./lib/elibft/include \

# Source directories
VPATH				=	\
						./src:\

# Include flags
INCLUDE				=	$(addprefix -I , $(INCLUDE_DIRS))

# Libraries
LIB 				=	\
						./lib/elibft/elibft.a \

# Source files
SRC					=	\
						main.c \
						command.c \
						path.c \
						path_utils.c \
						pipe.c \
						error.c \
						redirection.c \
						execution.c \
						init.c \

# Object files
OBJ					=	$(SRC:%.c=obj/%.o)

# Dependency files
DEP					=	$(SRC:%.c=dep/%.d)

# Make flags
MFLAGS				=	 --no-print-directory -C

# Build all targets
all: lib $(NAME)

# Link mandatory object files
$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LIB) -o $@
	@echo "$(NAME) has been built"

# Build libraries
lib:
	@make $(MFLAGS) ./lib/elibft

# Compile mandatory object files
obj/%.o: %.c | obj_dir dep_dir
	@$(CC) $(CFLAGS) dep/$(@:obj/%.o=%.d) $(INCLUDE) -c $< -o $@ && printf "Compiling: $(notdir $< \n)"

# Create mandatory object directories
obj_dir:
	@mkdir -p obj

# Create mandatory dependency directories
dep_dir:
	@mkdir -p dep

# Clean build files
clean:
	@$(RM) obj
	@$(RM) dep
	@make clean $(MFLAGS) ./lib/elibft
	@echo "$(NAME) has been cleaned"

# Clean build files and executables
fclean: clean
	@make fclean $(MFLAGS) ./lib/elibft
	@$(RM) $(NAME)

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re lib
.DEFAULT_GOAL := all

# Include the dependency files
-include $(DEP)

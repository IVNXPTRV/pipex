# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/02 16:48:06 by ipetrov           #+#    #+#              #
#    Updated: 2024/12/13 13:41:54 by ipetrov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -g -MMD -MF
RM					=	rm -rf

# Executable names
NAME				=	\
						unlink

# Include directories
INCLUDE_DIRS		=	\
						./include \
						../pipex/lib/elibft/include \

# Source directories
VPATH				=	\
						./src:\
						./src/unlink:\

# Include flags
INCLUDE				=	$(addprefix -I, $(INCLUDE_DIRS))

# Source files
SRC					:= 	\
						unlink.c \


# Libraries
LIB					=	../pipex/lib/elibft/elibft.a \

# Object files
OBJ					=	$(SRC:%.c=obj/%.o)

# Dependency files
DEP					=	$(SRC:%.c=dep/%.d)

# Make flags
MFLAGS				= 	--no-print-directory -C

# Default target
a: all
	@./test_elibft

# Build all targets
all: $(NAME) lib

lib:
	@make  $(MFLAGS) ../pipex/lib/elibft/

# Link mandatory object files
$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LIB) -o $@
	@echo "$(NAME) has been built"

# Compile mandatory object files
obj/%.o: %.c | dep_dir obj_dir
	@$(CC) $(CFLAGS) dep/$(@:obj/%.o=%.d) $(INCLUDE) -c $< -o $@

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

# Clean build files and executables
fclean: clean
	@$(RM) $(NAME)
	@echo "Cleaned"

# Rebuild everything
re: fclean a

# Phony targets
.PHONY: all clean fclean re lib
.DEFAULT_GOAL := all

# Include the dependency files
-include $(DEP)
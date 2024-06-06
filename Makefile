NAME = minishell
FILES = redirections.c
LIBFT = libft/libft.a
OBJ_FILES = $(FILES:.c=.o)
CFLAGS =  -Wall -Wextra -Werror 

$(NAME): $(OBJ_FILES) 
	cc $(OBJ_FILES) $(LIBFT) -o $(NAME)

all:$(NAME)

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all


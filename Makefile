NAME = minishell
SOURCE_FILES =  execution/builtin_exec.c execution/echo_cd_pwd.c\
				execution/env_exit.c execution/env_functions.c\
				execution/error_functions.c execution/exec_helpers.c\
				execution/export.c execution/mem_free.c\
				execution/general_helpers.c execution/here_doc.c\
				execution/export_helpers.c execution/pipes.c\
				execution/starting_point.c execution/unset.c\
				execution/extra_cases.c execution/signals_handlers.c\
				parsing/ft_expansion.c parsing/ft_expansion_utils_2.c\
				parsing/ft_expansion_utils.c parsing/ft_free.c\
				parsing/get_list_and_cmds.c parsing/get_list_and_cmds_utils.c\
				parsing/parsing.c parsing/parsing_utils.c\
				parsing/quotes_cases.c parsing/quotes_cases_utils.c\
				main.c\

LIBFT = libft/libft.a -lreadline
OBJ_FILES = $(SOURCE_FILES:.c=.o)
CFLAGS =  #-Wall -Wextra -Werror 

$(NAME): $(OBJ_FILES) 
	cc $(OBJ_FILES) $(LIBFT) -o $(NAME)

all:$(NAME)

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug:
	cc -g3 -fsanitize=address main.c execution/*.c\
		parsing/*.c libft/libft.a -lreadline -o minishell
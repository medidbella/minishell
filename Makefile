NAME = minishell
SOURCE_FILES =  execution/builtin_exec.c execution/echo_cd_pwd.c\
				execution/env_exit.c execution/env_functions.c\
				execution/error_functions.c execution/exec_helpers.c\
				execution/export.c execution/mem_free.c\
				execution/general_helpers.c execution/here_doc.c\
				execution/export_helpers.c execution/pipes.c\
				execution/starting_point.c execution/unset.c\
				execution/extra_cases.c execution/signals_handlers.c\
				execution/expand_new_line.c\
				parsing/parsing.c parsing/ft_free.c parsing/get_list_and_cmds.c \
				parsing/parsing_utils.c parsing/get_list_and_cmds_utils.c \
				parsing/quotes_cases.c parsing/quotes_cases_utils.c \
				parsing/ft_expansion.c parsing/ft_expansion_utils_1.c \
				parsing/ft_expansion_utils_2.c parsing/ft_expansion_utils_3.c \
				parsing/errors.c parsing/errors_utils.c parsing/return_value.c \
				parsing/remove_quotes.c parsing/spliting.c parsing/spliting_utils.c \
				parsing/swap_args.c parsing/swap_args_utils.c main.c\

LIBFT = libft/libft.a 
READ_LINE = -lreadline
OBJ_FILES = $(SOURCE_FILES:.c=.o)
CFLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJ_FILES)
	make bonus -C libft/ && cc $(OBJ_FILES) $(LIBFT) $(READ_LINE) -o $(NAME) 

all:$(NAME)

clean:
	rm -f $(OBJ_FILES) && make clean -C libft

fclean: clean
	rm -f $(NAME) && make fclean -C libft

re: fclean all 

debug:
	cc -g3 -fsanitize=address main.c execution/*.c\
		parsing/*.c libft/libft.a -lreadline -o minishell

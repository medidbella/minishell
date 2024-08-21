NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
FILES = \
        ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_memset.c \
		ft_strchr.c ft_strlen.c ft_strncmp.c \
		ft_strnstr.c ft_strjoin.c ft_substr.c \
		ft_tolower.c ft_striteri.c ft_strlcpy.c \
		ft_putchar_fd.c ft_putendl_fd.c \
		ft_strrchr.c ft_toupper.c ft_bzero.c \
		ft_atoi.c ft_strlcat.c ft_memcpy.c \
		ft_memchr.c ft_memcmp.c ft_strdup.c \
		ft_calloc.c ft_memmove.c ft_split.c \
		ft_itoa.c ft_strmapi.c ft_putstr_fd.c \
		ft_putnbr_fd.c ft_strtrim.c \

BONUS_FILES = \
		ft_lstnew_bonus.c ft_lstadd_front_bonus.c\
		ft_lstsize_bonus.c ft_lstlast_bonus.c\
		ft_lstadd_back_bonus.c ft_lstdelone_bonus.c\
		ft_lstclear_bonus.c ft_lstiter_bonus.c\

FILES_O = $(FILES:%.c=%.o)
BONUS_O = $(BONUS_FILES:%.c=%.o)
all: $(NAME)

$(NAME): $(FILES_O)
	ar -rc $(NAME) $(FILES_O)

bonus: $(BONUS_O) $(FILES_O)
	ar -rc $(NAME) $?

clean:
	rm -f $(FILES_O) $(BONUS_O)

fclean: clean
	rm -f $(NAME)

re: fclean all


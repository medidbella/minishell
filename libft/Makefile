NAME = libft.a
MONDATORY = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memset.c ft_strchr.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strjoin.c ft_substr.c ft_tolower.c ft_striteri.c ft_putchar_fd.c ft_putendl_fd.c\
ft_strrchr.c ft_toupper.c ft_strlcpy.c ft_atoi.c ft_strlcat.c ft_bzero.c ft_memcpy.c ft_memchr.c ft_memcmp.c ft_strdup.c ft_calloc.c ft_memmove.c ft_split.c ft_itoa.c ft_strmapi.c ft_putstr_fd.c ft_putnbr_fd.c ft_strtrim.c
BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c
MONDATORY_o = $(MONDATORY:.c=.o)
CFLAGS = -Wall -Wextra -Werror
BONUS_o = $(BONUS:.c=.o)
CC = cc

all: $(NAME)

$(NAME): $(MONDATORY_o)

$(MONDATORY_o):
	$(CC) $(CFLAGS) $(MONDATORY) -c
	ar -rc $(NAME) $(MONDATORY_o)

$(BONUS_o) : $(BONUS)
	$(CC) $(CFLAGS) $(BONUS) -c
	ar -rc $(NAME) $(BONUS_o)

bonus:  $(BONUS_o)

clean:
	rm -f $(MONDATORY_o) $(BONUS_o)

fclean: clean
	rm -f $(NAME)

re: fclean all


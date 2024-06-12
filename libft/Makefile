SRC	= 	ft_isalpha.c	\
		ft_isdigit.c	\
		ft_isalnum.c	\
		ft_isascii.c	\
		ft_isprint.c	\
		ft_strlen.c		\
		ft_toupper.c	\
		ft_tolower.c	\
		ft_strchr.c		\
		ft_strrchr.c	\
		ft_strncmp.c	\
		ft_strlcpy.c	\
		ft_strlcat.c	\
		ft_strnstr.c	\
		ft_memset.c		\
		ft_bzero.c		\
		ft_memchr.c		\
		ft_memcpy.c		\
		ft_memcmp.c		\
		ft_memmove.c	\
		ft_calloc.c		\
		ft_strdup.c		\
		ft_atoi.c		\
		ft_substr.c		\
		ft_strjoin.c	\
		ft_strtrim.c	\
		ft_strmapi.c	\
		ft_striteri.c	\
		ft_split.c		\
		ft_putchar_fd.c	\
		ft_putstr_fd.c	\
		ft_putendl_fd.c	\
		ft_putnbr_fd.c	\
		ft_itoa.c		\
		ft_printf.c		\
		parser.c		\
		render_num.c	\
		render_arg.c	\
		print_num.c		\
		utils.c			\
		get_next_line.c	\
		get_next_line_utils.c

OBJS	= ${SRC:.c=.o}

HEAD	= .libft.h

NAME	= libft.a

AR	= ar rcs

RM	= rm -f

LIB	= ranlib

GCC	= gcc

CFLAGS	= -Wall -Wextra -Werror

all:	${NAME}

.c.o:
	${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}
	
$(NAME):	${OBJS}
		${AR} ${NAME} ${OBJS}
		${LIB} ${NAME}
		
clean:
	rm -f ${OBJS}
	
fclean:	clean
	rm -f ${NAME}
	
re:	fclean all

.PHONY:	all clean fclean re

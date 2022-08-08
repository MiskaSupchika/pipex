NAME		=	pipex 

SRCS		=	main.c process.c\

OBJS		=	$(SRCS:.c=.o)

HEADER		=	pipex.h

CFLAGS		=	-Werror -Wall -Wextra

CC			=	gcc

LIBFT		=	./libft/libft.a

all: $(NAME)

$(NAME):	$(OBJS) $(HEADER)
			${MAKE} -C ./libft/
			${CC} -g ${OBJS} ${LIBFT}

.c.o:
			${CC} -g ${CFLAGS} -c $< -o ${<:.c=.o}
		

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all 

.PHONY: all, clean, fclean, re

NAME  = pipex

SRCS	= ./srcs/main.c \
			./srcs/check_cmd.c \
			./srcs/process.c \
			./lib_cub/ft_strchr.c \
			./lib_cub/ft_strdup.c \
			./lib_cub/ft_substr.c \
			./lib_cub/ft_strjoin.c \
			./lib_cub/ft_strcmp.c \
			./lib_cub/ft_split.c \
			./lib_cub/ft_strlen.c \
			./lib_cub/ft_lstclear.c \
			./lib_cub/ft_lstnew.c \
			./lib_cub/ft_lstadd_back.c \
			./lib_cub/malloc_lst.c \
			./lib_cub/ft_putchar_fd.c \
			./lib_cub/ft_putstr_fd.c \

SRCS_BONUS	= ./srcs_bonus/main.c \
			./srcs_bonus/check_cmd.c \
			./srcs_bonus/process.c \
			./lib_cub/ft_strchr.c \
			./lib_cub/ft_strdup.c \
			./lib_cub/ft_substr.c \
			./lib_cub/ft_strjoin.c \
			./lib_cub/ft_strcmp.c \
			./lib_cub/ft_split.c \
			./lib_cub/ft_strlen.c \
			./lib_cub/ft_lstclear.c \
			./lib_cub/ft_lstnew.c \
			./lib_cub/ft_lstadd_back.c \
			./lib_cub/malloc_lst.c \
			./lib_cub/ft_putchar_fd.c \
			./lib_cub/ft_putstr_fd.c \

OBJS= $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

INC	=	-I inc

CC	=	clang

CFLAGS	=	-Wall -Werror -Wextra -g -fsanitize=address

.c.o	:
			${CC} ${CFLAGS} ${INC} -c $< -o ${<:.c=.o}

all : ${NAME}

$(NAME) :	${OBJS}
			${CC} $(CFLAGS) -o $(NAME) $(OBJS)

bonus :	${OBJS_BONUS}
			${CC} $(CFLAGS) -o $(NAME) $(OBJS_BONUS)


clean	:	
			rm -rf ${OBJS}

fclean	:	clean
			rm -rf ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re

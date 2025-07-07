# **************************************************************************** #
#                                  VARIABLES                                   #
# **************************************************************************** #

NAME        = pipex
SRC_DIR     = src
INC_DIR     = includes
LIBFT_DIR   = Libft
LIBFT_A     = $(LIBFT_DIR)/libft.a

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR)

SRC         = $(wildcard $(SRC_DIR)/*.c)
OBJ         = $(SRC:.c=.o)

# **************************************************************************** #
#                                  RULES                                       #
# **************************************************************************** #

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT_A)

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJ)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

NAME = philosophers
CC = cc
# -Wall -Wextra -Werror
OBJ_DIR = obj
CFLAGS = -MMD -g -I.
VPATH = core globals threads actions
SRC = main.c functions_in_main.c actions.c end.c threads.c threads_setup.c globals.c
OBJ = $(SRC:%.c=obj/%.o)
DEP = $(SRC:%.c=obj/%.d)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MF $(@:.o=.d) -c $< -o $@


clean:
	rm -f $(OBJ) $(DEP)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re

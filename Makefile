NAME		= ft_script

SRCS		= main.c
SRCS_BONUS	=
LIBS		= libft

OBJ_DIR		= objs
SRC_DIR		= srcs
INC_DIR		= inc

CC			= clang
CFLAGS		= -Wall -Wextra -g3

OBJS		:= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))
OBJS_BONUS	:= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS_BONUS))
DEP			:= $(patsubst %.o,%.d,$(OBJS))
DEP			+= $(patsubst %.o,%.d,$(OBJS_BONUS))
INCLUDES	:= -I$(INC_DIR) $(patsubst %,-I %,$(LIBS))

all: 			$(NAME)

$(NAME):		$(OBJS) $(foreach L,$(LIBS),$L/$L.a)
	$(CC) $(CFLAGS) $^ -o $@

-include $(DEP)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

libft/libft.a:
	@echo "Building libft"
	@$(MAKE) -C libft

clean:
	@$(foreach L, $(LIBS), $(MAKE) -C $L clean;)
	$(RM) -r $(OBJ_DIR)

fclean:	clean
	$(RM) $(NAME) $(foreach L,$(LIBS),$L/$L.a)
	$(RM) -r $(OBJ_DIR)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all bonus clean fclean re

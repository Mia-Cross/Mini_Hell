NAME = minishell

SRCDIR = srcs

OBJDIR = .obj

SRCS =	builtin.c \
		echo.c \
		env.c \
		minishell.c

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

DPDCS = $(OBJS:.o=.d)

INCLUDES = -I include/ -I libft/include/

LIB = libft/libft.a

CFLAGS = -Wall -Wextra -Werror

LIBFT_FLAGS = 	-Llibft -lft

opti:
	@make -j all

all : 
	@printf "[libft] " && make -C libft
	@make $(NAME)

-include $(DPDCS)

$(NAME) : $(OBJS) $(LIB)
	@printf "[$(NAME)] "
	gcc $(CFLAGS) -o $(NAME) ${OBJS} $(LIB)
	@echo Compiled $(NAME) successfully !
	@echo $(NAME) > .gitignore

$(OBJDIR)/%.o : $(SRCDIR)/%.c | $(OBJDIR)
	gcc $(CFLAGS) -MMD -c $< -o $@

$(OBJDIR) :
	@mkdir -p .obj 

norme :
	#@make norme -C libft
	@(norminette -R CheckForbiddenSourceHeader srcs/*.c)
	@(norminette -R CheckForbiddenSourceHeader include/*.h

clean :
	@(rm -rf $(OBJDIR))
	@(make clean -C libft)

cleanlib :
	@(make fclean -C libft)

fclean : cleanlib clean
	@(rm -rf $(NAME))
	@(rm -f libft.a)
	@(rm -rf a.out.dSYM)
	@(rm -f a.out)

re :
	@make fclean
	@make opti
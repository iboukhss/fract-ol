NAME = fractol

MLX_DIR := minilibx-linux

CFLAGS := -Wall -Wextra -Werror
#CFLAGS += -g3 -fsanitize=address,undefined -MMD
#CFLAGS += -pg
CFLAGS += -I$(MLX_DIR)

LDLIBS  := -L$(MLX_DIR)
LDFLAGS := -lmlx -lX11 -lXext -lm

SRCS := f_main.c f_events.c f_render.c f_mandelbrot.c
SRCS += ft_printf.c ft_strcmp.c ft_atof.c
INCS := fractol.h libft.h

OBJS := $(SRCS:.c=.o)
DEPS := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS) $(MLX_DIR)/libmlx.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDLIBS) $(LDFLAGS)

$(MLX_DIR)/libmlx.a: $(MLX_DIR)/.git
	$(MAKE) -C $(MLX_DIR)

$(MLX_DIR)/.git:
	git submodule update --init --recursive

norm:
	-norminette $(SRCS) $(INCS)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re

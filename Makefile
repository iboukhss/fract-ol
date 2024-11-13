NAME = fractol

MLX_DIR = minilibx-linux

CFLAGS = -Wall -Wextra
CFLAGS += -g3 -fsanitize=address,undefined -MMD
CFLAGS += -pg
CFLAGS += -I$(MLX_DIR)

LDLIBS = -L$(MLX_DIR)
LDFLAGS = -lmlx -lX11 -lXext -lm

SRCS = f_main.c f_events.c f_render.c f_mandelbrot.c
INCS = fractol.h

OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS) $(LDFLAGS)

norm:
	-norminette $(SRCS) $(INCS)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re

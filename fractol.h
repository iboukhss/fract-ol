/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:52:57 by iboukhss          #+#    #+#             */
/*   Updated: 2024/11/12 13:57:14 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WIDTH 1600
# define HEIGHT 1200

# define MIN_RE -2.0
# define MAX_RE 1.0
# define MIN_IM -1.2
# define MAX_IM 1.2
# define MAX_ITER 100
# define ESCAPE_RADIUS 4.0

# define KEY_ESCAPE 65307

# define COLOR_BLACK 0x000000

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

double	map_to_complex(int pixel, int size, double min, double max);
int		mandelbrot(double real, double imag, int max_iter);
int		get_color(int iter, int max_iter);

int		key_press(int keycode, t_data *data);
int		close_window(t_data *data);

void	render_pixel(t_data *img, int x, int y);
int		render_fractal(t_data *img);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:56:50 by iboukhss          #+#    #+#             */
/*   Updated: 2024/11/12 12:40:27 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

// Buffered pixel drawing for increased performance (instead of mlx_pixel_put).
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

// Maps pixel coordinates to the complex plane.
double	map_to_complex(int pixel, int size, double min, double max)
{
	return (min + ((double)pixel / size) * (max - min));
}

// Computes the number of iterations for a point on the Mandrelbrot set.
// This function checks if a point with complex coordinates (real, imag)
// diverges up to max_iter and returns the iteration count as a result to
// be processed for coloring.
int	mandelbrot(double real, double imag, int max_iter)
{
	double	z_re;
	double	z_im;
	int		iter;
	double	temp_re;

	z_re = real;
	z_im = imag;
	iter = 0;
	while ((z_re * z_re + z_im * z_im <= ESCAPE_RADIUS) && iter < max_iter)
	{
		temp_re = z_re * z_re - z_im * z_im + real;
		z_im = 2 * z_re * z_im + imag;
		z_re = temp_re;
		iter++;
	}
	return (iter);
}

// Generates a grayscale color value based on iteration count.
// As the iteration count gets closer to max_iter, the color gets lighter.
int	get_color(int iter, int max_iter)
{
	int	color_intensity;

	if (iter == max_iter)
	{
		return (COLOR_BLACK);
	}
	color_intensity = (255 * iter) / max_iter;
	return ((color_intensity << 16) | (color_intensity << 8) | color_intensity);
}

// Key event handler.
int	key_press(int keycode, t_data *data)
{
	printf("Key pressed: %d\n", keycode);
	if (keycode == KEY_ESCAPE)
	{
		close_window(data);
	}
	return (0);
}

int	close_window(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

void	render_pixel(t_data *img, int x, int y)
{
	double	real;
	double	imag;
	int		iter;
	int		color;

	real = map_to_complex(x, WIDTH, MIN_RE, MAX_RE);
	imag = map_to_complex(y, HEIGHT, MIN_IM, MAX_IM);
	iter = mandelbrot(real, imag, MAX_ITER);
	color = get_color(iter, MAX_ITER);
	my_mlx_pixel_put(img, x, y, color);
}

void	render_fractal(t_data *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			render_pixel(img, x, y);
			x++;
		}
		y++;
	}
}

int	main(void)
{
	t_data	img;

	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, WIDTH, HEIGHT, "Fract'ol");
	img.img = mlx_new_image(img.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);

	render_fractal(&img);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);

	mlx_key_hook(img.win, key_press, &img);
	mlx_hook(img.win, 17, 0, close_window, &img);
	mlx_loop(img.mlx);
	return (0);
}

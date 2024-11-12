/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:56:50 by iboukhss          #+#    #+#             */
/*   Updated: 2024/11/12 15:35:15 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

int	get_color(int iter, int max_iter)
{
	int	red;
	int	green;
	int	blue;

	red = (iter * 255) / max_iter;
	green = (iter * 128) / max_iter;
	blue = (iter * 64) / max_iter;
	return ((red << 16) | (green << 8) | blue);
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
	exit(EXIT_SUCCESS);
	return (0);
}

void	render_pixel(t_data *img, int x, int y)
{
	double	real;
	double	imag;
	int		iter;
	int		color;

	real = map_to_complex(x, WIDTH, img->min_re, img->max_re);
	imag = map_to_complex(y, HEIGHT, img->min_im, img->max_im);
	iter = mandelbrot(real, imag, MAX_ITER);
	color = get_color(iter, MAX_ITER);
	my_mlx_pixel_put(img, x, y, color);
}

int	render_fractal(t_data *img)
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
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	return (0);
}

int	zoom_fractal(int button, int x, int y, t_data *data)
{
	double	zoom_center_re;
	double	zoom_center_im;

	zoom_center_re = map_to_complex(x, WIDTH, data->min_re, data->max_re);
	zoom_center_im = map_to_complex(y, HEIGHT, data->min_im, data->max_im);
	printf("Mouse event at: (%d, %d), button: %d\n", x, y, button);
	printf("Zoom center: re = %f, im = %f\n", zoom_center_re, zoom_center_im);
	if (button == 4)
	{
		printf("Zooming in\n");
		data->zoom_factor *= ZOOM_FACTOR;
		data->min_re = zoom_center_re + (data->min_re - zoom_center_re) / ZOOM_FACTOR;
		data->max_re = zoom_center_re + (data->max_re - zoom_center_re) / ZOOM_FACTOR;
		data->min_im = zoom_center_im + (data->min_im - zoom_center_im) / ZOOM_FACTOR;
		data->max_im = zoom_center_im + (data->max_im - zoom_center_im) / ZOOM_FACTOR;
	}
	if (button == 5)
	{
		printf("Zooming out\n");
		data->zoom_factor /= ZOOM_FACTOR;
		data->min_re = zoom_center_re + (data->min_re - zoom_center_re) * ZOOM_FACTOR;
		data->max_re = zoom_center_re + (data->max_re - zoom_center_re) * ZOOM_FACTOR;
		data->min_im = zoom_center_im + (data->min_im - zoom_center_im) * ZOOM_FACTOR;
		data->max_im = zoom_center_im + (data->max_im - zoom_center_im) * ZOOM_FACTOR;
	}
	printf("Zooming at: min_re: %lf, max_re: %lf, min_im: %lf, max_im: %lf\n", data->min_re, data->max_re, data->min_im, data->max_im);
	render_fractal(data);
	return (0);
}

int	main(void)
{
	t_data	img;

	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, WIDTH, HEIGHT, "Fract'ol");
	img.img = mlx_new_image(img.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);

	img.min_re = MIN_RE;
	img.max_re = MAX_RE;
	img.min_im = MIN_IM;
	img.max_im = MAX_IM;
	img.zoom_factor = 1.0;

	render_fractal(&img);

	mlx_key_hook(img.win, key_press, &img);
	mlx_hook(img.win, 17, 0, close_window, &img);
	mlx_mouse_hook(img.win, zoom_fractal, &img);
	mlx_expose_hook(img.win, render_fractal, &img);

	mlx_loop(img.mlx);
	return (0);
}

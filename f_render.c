/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 03:22:38 by iboukhss          #+#    #+#             */
/*   Updated: 2024/11/13 03:23:38 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#include <mlx.h>

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

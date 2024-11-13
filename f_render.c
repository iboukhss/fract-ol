/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 03:22:38 by iboukhss          #+#    #+#             */
/*   Updated: 2024/11/13 11:55:04 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#include <mlx.h>
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

// Function to generate a color with psychedelic rainbow cycling. We are using
// sine waves to create a rainbow-like effect.
int	get_color(int iter, int max_iter)
{
	double	t;
	int		red;
	int		green;
	int		blue;

	if (iter == max_iter)
	{
		return (COLOR_BLACK);
	}
	t = (double)iter / (double)max_iter;
	red = (int)(255 * (0.5 * sin(PI * (t + 0.0)) + 0.5));
	green = (int)(255 * (0.5 * sin(PI * (t + 0.33)) + 0.5));
	blue = (int)(255 * (0.5 * sin(PI * (t + 0.67)) + 0.5));
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
	if (img->frac_type == MANDELBROT)
	{
		iter = mandelbrot(real, imag, MAX_ITER);
	}
	else
	{
		iter = julia(real, imag, img->j_real, img->j_imag, MAX_ITER);
	}
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

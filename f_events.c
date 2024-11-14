/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_events.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 03:20:52 by iboukhss          #+#    #+#             */
/*   Updated: 2024/11/14 18:11:51 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#include <mlx.h>
#include <stdlib.h>

int	key_press(int keycode, t_data *data)
{
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
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

// Calculates the zoom center point on the complex plane.
int	zoom_fractal(int button, int x, int y, t_data *data)
{
	double	zoom_re;
	double	zoom_im;

	zoom_re = map_to_complex(x, WIDTH, data->min_re, data->max_re);
	zoom_im = map_to_complex(HEIGHT - y, HEIGHT, data->min_im, data->max_im);
	if (button == 4)
	{
		data->zoom_factor *= ZOOM_FACTOR;
		data->min_re = zoom_re + (data->min_re - zoom_re) / ZOOM_FACTOR;
		data->max_re = zoom_re + (data->max_re - zoom_re) / ZOOM_FACTOR;
		data->min_im = zoom_im + (data->min_im - zoom_im) / ZOOM_FACTOR;
		data->max_im = zoom_im + (data->max_im - zoom_im) / ZOOM_FACTOR;
	}
	if (button == 5)
	{
		data->zoom_factor /= ZOOM_FACTOR;
		data->min_re = zoom_re + (data->min_re - zoom_re) * ZOOM_FACTOR;
		data->max_re = zoom_re + (data->max_re - zoom_re) * ZOOM_FACTOR;
		data->min_im = zoom_im + (data->min_im - zoom_im) * ZOOM_FACTOR;
		data->max_im = zoom_im + (data->max_im - zoom_im) * ZOOM_FACTOR;
	}
	render_fractal(data);
	return (0);
}

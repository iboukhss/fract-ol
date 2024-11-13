/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_events.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 03:20:52 by iboukhss          #+#    #+#             */
/*   Updated: 2024/11/13 03:25:24 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

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

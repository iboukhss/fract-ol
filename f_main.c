/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 03:08:01 by iboukhss          #+#    #+#             */
/*   Updated: 2024/11/13 11:01:03 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void	parse_arguments(int argc, char **argv, t_data *img)
{
	if (argc == 1)
	{
		img->frac_type = MANDELBROT;
		img->min_re = -2.0;
		img->max_re = 1.0;
		img->min_im = -1.5;
		img->max_im = 1.5;
	}
	else if (argc == 4 && strcmp(argv[1], "-j") == 0)
	{
		img->frac_type = JULIA;
		img->j_real = atof(argv[2]);
		img->j_imag = atof(argv[3]);
		img->min_re = -1.5;
		img->max_re = 1.5;
		img->min_im = -1.5;
		img->max_im = 1.5;
	}
	else
	{
		printf("Usage: %s -j <real> <imag>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	t_data	img;

	parse_arguments(argc, argv, &img);

	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, WIDTH, HEIGHT, "Fract'ol");
	img.img = mlx_new_image(img.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);

	img.zoom_factor = 1.0;

	render_fractal(&img);

	mlx_key_hook(img.win, key_press, &img);
	mlx_hook(img.win, 17, 0, close_window, &img);
	mlx_mouse_hook(img.win, zoom_fractal, &img);
	mlx_expose_hook(img.win, render_fractal, &img);

	mlx_loop(img.mlx);
	return (0);
}

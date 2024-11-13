/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 03:08:01 by iboukhss          #+#    #+#             */
/*   Updated: 2024/11/13 03:25:42 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#include <mlx.h>
#include <stdlib.h>
#include <math.h>

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

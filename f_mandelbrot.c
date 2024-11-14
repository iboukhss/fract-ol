/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_mandelbrot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 03:23:57 by iboukhss          #+#    #+#             */
/*   Updated: 2024/11/14 18:00:13 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Maps pixel coordinates to the complex plane.
double	map_to_complex(int pixel, int size, double min, double max)
{
	return (min + ((double)pixel / size) * (max - min));
}

// Computes the number of iterations for a point on the Mandrelbrot set.
// This function checks if a point with complex coordinates (real, imag)
// diverges up to max_iter and returns the iteration count as a result to
// be processed for coloring.
int	mandelbrot(double real, double imag)
{
	double	z_re;
	double	z_im;
	int		iter;
	double	temp_re;

	z_re = real;
	z_im = imag;
	iter = 0;
	while ((z_re * z_re + z_im * z_im <= ESCAPE_RADIUS) && iter < MAX_ITER)
	{
		temp_re = z_re * z_re - z_im * z_im + real;
		z_im = 2 * z_re * z_im + imag;
		z_re = temp_re;
		iter++;
	}
	return (iter);
}

int	julia(double real, double imag, double c_re, double c_im)
{
	double	z_re;
	double	z_im;
	int		iter;
	double	temp_re;

	z_re = real;
	z_im = imag;
	iter = 0;
	while ((z_re * z_re + z_im * z_im <= ESCAPE_RADIUS) && iter < MAX_ITER)
	{
		temp_re = z_re * z_re - z_im * z_im + c_re;
		z_im = 2 * z_re * z_im + c_im;
		z_re = temp_re;
		iter++;
	}
	return (iter);
}

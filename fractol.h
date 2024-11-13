/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:52:57 by iboukhss          #+#    #+#             */
/*   Updated: 2024/11/13 11:20:59 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

// General settings
# define WIDTH 800
# define HEIGHT 800
# define ASPECT_RATIO ((double)WIDTH / (double)HEIGHT)
# define ZOOM_FACTOR 1.25

// Magic numbers
# define PI 3.14159265358979323846
# define KEY_ESCAPE 65307
# define COLOR_BLACK 0x000000

// Fractal options
# define MAX_ITER 100
# define ESCAPE_RADIUS 4.0

# define MANDELBROT 0
# define JULIA 1

typedef struct s_data
{
	// MLX data
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	// Fractal stuff
	int		frac_type;
	double	min_re;
	double	max_re;
	double	min_im;
	double	max_im;
	double	j_real;
	double	j_imag;
	double	zoom_factor;
}	t_data;

// Window events
int		key_press(int keycode, t_data *data);
int		close_window(t_data *data);
int		zoom_fractal(int button, int x, int y, t_data *data);

// Fractal
int		mandelbrot(double real, double imag, int max_iter);
int		julia(double real, double imag, double c_re, double c_im, int max_iter);
double	map_to_complex(int pixel, int size, double min, double max);

// Rendering
int		render_fractal(t_data *img);
int		get_color(int iter, int max_iter);
void	render_pixel(t_data *img, int x, int y);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif

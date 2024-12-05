/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:36:23 by lpolizzi          #+#    #+#             */
/*   Updated: 2024/10/21 15:43:15 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * Computes the Mandelbrot set iteration for a given point.
 *
 * @param pr  The real part of the point in the complex plane.
 * @param pi  The imaginary part of the point in the complex plane.
 * @return    The number of iterations before the point escapes the Mandelbrot
 * set or reaches MAX_ITERATIONS.
 */
static int	mandelbrot(double pr, double pi)
{
	int		n;
	double	zr;
	double	zi;
	double	tmp;

	n = 0;
	zr = 0;
	zi = 0;
	while (n < MAX_ITERATIONS)
	{
		if ((zi * zi + zr * zr) > 4.0)
			break ;
		tmp = 2 * zr * zi + pi;
		zr = zr * zr - zi * zi + pr;
		zi = tmp;
		n++;
	}
	return (n);
}

/**
 * Computes the Julia set iteration for a given point.
 *
 * @param fractdata  A pointer to a structure containing Julia set parameters
 * (c_real, c_imaginary).
 * @param zr         The real part of the initial point in the complex plane.
 * @param zi         The imaginary part of the initial point in the complex
 * plane.
 * @return           The number of iterations before the point escapes the
 * Julia set or reaches MAX_ITERATIONS.
 */
static int	julia(t_fractdata *fractdata, double zr, double zi)
{
	int		n;
	double	tmp;
	double	c_imaginary;
	double	c_real;

	c_imaginary = fractdata->c_imaginary;
	c_real = fractdata->c_real;
	n = 0;
	while (n < MAX_ITERATIONS)
	{
		if ((zi * zi + zr * zr) > 4.0)
			break ;
		tmp = 2 * zr * zi + c_imaginary;
		zr = zr * zr - zi * zi + c_real;
		zi = tmp;
		n++;
	}
	return (n);
}

/**
 * Computes the Burning Ship fractal iteration for a given point.
 *
 * @param cr  The real part of the point in the complex plane.
 * @param ci  The imaginary part of the point in the complex plane.
 * @return    The number of iterations before the point escapes the Burning
 * Ship fractal or reaches MAX_ITERATIONS.
 */
static int	burning_ship(double cr, double ci)
{
	int		n;
	double	zr;
	double	zi;
	double	tmp;

	zr = 0;
	zi = 0;
	n = 0;
	while (n < MAX_ITERATIONS)
	{
		if ((zr * zr + zi * zi) > 4.0)
			break ;
		zr = fabs(zr);
		zi = fabs(zi);
		tmp = 2 * zr * zi + ci;
		zr = zr * zr - zi * zi + cr;
		zi = tmp;
		n++;
	}
	return (n);
}

/**
 * Determines which fractal to calculate.
 *
 * @param fractdata A pointer to a structure containing values to calculate
 * each fractal.
 * @param pr Real par of the current pixels position in the complex plane.
 * @param pi Imaginary par of the current pixels position in the complex plane.
 * @return The number of iterations it took to reach zr^2 + zi^2 > 4.0.
 */
static int	calculate_which_fractal(t_fractdata *fractdata, double pr,
		double pi)
{
	int	nb_iter;

	nb_iter = 0;
	if (fractdata->type == MANDELBROT)
		nb_iter = mandelbrot(pr, pi);
	else if (fractdata->type == JULIA)
		nb_iter = julia(fractdata, pr, pi);
	else if (fractdata->type == BURNING_SHIP)
		nb_iter = burning_ship(pr, pi);
	return (nb_iter);
}

/**
 * Chooses a color for each pixel in the frame and renders them.
 *
 * Calculates if a pixel is in the desired fractal set and based on the
 * number of iterations needed to reach zr^2 + zi^2 > 4.0,
 * determines a color for each pixel using the palette.
 *
 * @param data A pointer to a data structure.
 */
void	render(t_data *data)
{
	int		x;
	int		y;
	double	pr;
	double	pi;
	int		nb_iter;

	mlx_clear_window(data->mlxdata.mlx, data->mlxdata.mlx_win);
	y = -1;
	while (++y < WIN_SIZE_Y)
	{
		x = -1;
		while (++x < WIN_SIZE_X)
		{
			pr = data->fractdata.min_r + (double)x * (data->fractdata.max_r
					- data->fractdata.min_r) / WIN_SIZE_X;
			pi = data->fractdata.max_i + (double)y * (data->fractdata.min_i
					- data->fractdata.max_i) / WIN_SIZE_Y;
			nb_iter = calculate_which_fractal(&data->fractdata, pr, pi);
			((int *)data->imgdata.addr)[y * WIN_SIZE_X
				+ x] = data->fractdata.palette[nb_iter];
		}
	}
	mlx_put_image_to_window(data->mlxdata.mlx, data->mlxdata.mlx_win,
		data->imgdata.img, 0, 0);
}

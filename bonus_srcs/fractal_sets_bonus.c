/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_sets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:03:29 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/03/22 14:04:07 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

/**
 * Computes the Mandelbrot set iteration for a given point.
 *
 * @param pr  The real part of the point in the complex plane.
 * @param pi  The imaginary part of the point in the complex plane.
 * @return    The number of iterations before the point escapes the Mandelbrot
 * set or reaches MAX_ITERATIONS.
 */
int	mandelbrot(double pr, double pi)
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
int	julia(t_fractdata *fractdata, double zr, double zi)
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
int	burning_ship(double cr, double ci)
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
int	calculate_which_fractal(t_fractdata *fractdata, double pr, double pi)
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

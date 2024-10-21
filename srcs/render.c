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

static int	julia(t_fractdata *fractdata, double zr, double zi)
{
	int		n;
	double	tmp;

	n = 0;
	while (n < MAX_ITERATIONS)
	{
		if ((zi * zi + zr * zr) > 4.0)
			break ;
		tmp = 2 * zr * zi + fractdata->c_imaginary;
		zr = zr * zr - zi * zi + fractdata->c_real;
		zi = tmp;
		n++;
	}
	return (n);
}

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

static int	calculate_fractal(t_fractdata *fractdata, double pr, double pi)
{
	int	nb_iter;

	if (fractdata->type == MANDELBROT)
		nb_iter = mandelbrot(pr, pi);
	else if (fractdata->type == JULIA)
		nb_iter = julia(fractdata, pr, pi);
	else if (fractdata->type == BURNING_SHIP)
		nb_iter = burning_ship(pr, pi);
	return (nb_iter);
}

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
			nb_iter = calculate_fractal(&data->fractdata, pr, pi);
			set_pixel(data, x, y, data->fractdata.palette[nb_iter]);
		}
	}
	mlx_put_image_to_window(data->mlxdata.mlx, data->mlxdata.mlx_win,
		data->imgdata.img, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:36:23 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/03/22 14:04:11 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

/**
 * Chooses a color for each pixel in the frame and renders them.
 *
 * Calculates if a pixel is in the desired fractal set and based on the
 * number of iterations needed to reach zr^2 + zi^2 > 4.0,
 * determines a color for each pixel using the palette.
 *
 * @param data A pointer to a data structure.
 */

void	*render_horizontal_section(void *arg)
{
	t_thread_data	*thread_data;
	t_data			*d;
	int				x;
	int				y;
	int				nb_iter;

	thread_data = (t_thread_data *)arg;
	d = thread_data->data;
	y = thread_data->start_y - 1;
	while (++y < thread_data->end_y)
	{
		x = -1;
		while (++x < WIN_SIZE_X)
		{
			nb_iter = calculate_which_fractal(&d->fractdata, d->fractdata.min_r
					+ (double)x * (d->fractdata.max_r - d->fractdata.min_r)
					/ WIN_SIZE_X, d->fractdata.max_i + (double)y
					* (d->fractdata.min_i - d->fractdata.max_i) / WIN_SIZE_Y);
			((int *)d->imgdata.addr)[y * WIN_SIZE_X
				+ x] = d->fractdata.palette[nb_iter];
		}
	}
	return (NULL);
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
	pthread_t		threads[NUM_THREADS];
	t_thread_data	thread_data[NUM_THREADS];
	int				stripe_height;
	int				i;

	stripe_height = WIN_SIZE_Y / NUM_THREADS;
	mlx_clear_window(data->mlxdata.mlx, data->mlxdata.mlx_win);
	i = -1;
	while (++i < NUM_THREADS)
	{
		thread_data[i].data = data;
		thread_data[i].start_y = i * stripe_height;
		if (i == NUM_THREADS - 1)
			thread_data[i].end_y = WIN_SIZE_Y;
		else
			thread_data[i].end_y = (i + 1) * stripe_height;
		pthread_create(&threads[i], NULL, render_horizontal_section,
			&thread_data[i]);
	}
	i = -1;
	while (++i < NUM_THREADS)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(data->mlxdata.mlx, data->mlxdata.mlx_win,
		data->imgdata.img, 0, 0);
}

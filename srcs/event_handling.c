/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:07:10 by lpolizzi          #+#    #+#             */
/*   Updated: 2024/10/21 13:36:05 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	zoom(t_data *data, double zoom_factor, double mouse_x,
		double mouse_y)
{
	double	center_r;
	double	center_i;
	double	offset_r;
	double	offset_i;

	center_r = data->fractdata.max_r - data->fractdata.min_r;
	center_i = data->fractdata.max_i - data->fractdata.min_i;
	offset_r = data->fractdata.min_r + (mouse_x / WIN_SIZE_X) * center_r;
	offset_i = data->fractdata.max_i - (mouse_y / WIN_SIZE_Y) * center_i;
	data->fractdata.min_r = offset_r - (offset_r - data->fractdata.min_r)
		* zoom_factor;
	data->fractdata.max_r = offset_r + (data->fractdata.max_r - offset_r)
		* zoom_factor;
	data->fractdata.min_i = offset_i - (offset_i - data->fractdata.min_i)
		* zoom_factor;
	data->fractdata.max_i = offset_i + (data->fractdata.max_i - offset_i)
		* zoom_factor;
}

static void	move(t_data *data, double distance, char direction)
{
	double	center_r;
	double	center_i;

	center_r = data->fractdata.max_r - data->fractdata.min_r;
	center_i = data->fractdata.max_i - data->fractdata.min_i;
	if (direction == 'R')
	{
		data->fractdata.min_r += center_r * distance;
		data->fractdata.max_r += center_r * distance;
	}
	else if (direction == 'L')
	{
		data->fractdata.min_r -= center_r * distance;
		data->fractdata.max_r -= center_r * distance;
	}
	else if (direction == 'D')
	{
		data->fractdata.min_i -= center_i * distance;
		data->fractdata.max_i -= center_i * distance;
	}
	else if (direction == 'U')
	{
		data->fractdata.min_i += center_i * distance;
		data->fractdata.max_i += center_i * distance;
	}
}

int	mouse_event(int keycode, int x, int y, t_data *data)
{
	if (keycode == MOUSE_WHEEL_UP || keycode == KEY_MINUS)
	{
		zoom(data, 0.9, x, y);
	}
	else if (keycode == MOUSE_WHEEL_DOWN || keycode == KEY_PLUS)
	{
		zoom(data, 1.1, x, y);
	}
	render(data);
	return (0);
}

int	key_event(int keycode, t_data *data)
{
	double	move_speed;

	move_speed = 0.025;
	if (keycode == KEY_ESC)
	{
		end_fractol(data);
		return (0);
	}
	else if (keycode == KEY_UP || keycode == KEY_W)
		move(data, move_speed, 'U');
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		move(data, move_speed, 'D');
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		move(data, move_speed, 'L');
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
		move(data, move_speed, 'R');
	render(data);
	return (0);
}

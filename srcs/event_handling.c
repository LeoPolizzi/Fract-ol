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

/**
 * zoom - Zooms in or out of the fractal depending on the input data.
 */
static void	zoom(t_data *data, const float zoom_factor, const float mouse_x,
		const float mouse_y)
{
	float	center_r;
	float	center_i;
	float	offset_r;
	float	offset_i;

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

/**
 * move - Moves the rendering view.
 *
 * 	Direction depends on input data.
 */
static void	move(t_data *data, const float distance, const char direction)
{
	float	center_r;
	float	center_i;

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

/**
 * mouse_event - Function registered as a mouse hook.
 *
 * 	Calls the function "zoom" if key Plus/Minus is pressed or
 * 	if Scroll Up/Down. Values passed to the function depends
 * 	if you zoom in/out.
 * @param keycode Input sent by mouse hook.
 * @param x X coordinates of the mouse cursor.
 * @param y Y coordinates of the mouse cursor.
 * @param data Pointer to a data structure.
 *
 * @return Returns 0.
 */
int	mouse_event(int keycode, int x, int y, t_data *data)
{
	if (keycode == MOUSE_WHEEL_UP)
	{
		zoom(data, 0.9, x, y);
	}
	else if (keycode == MOUSE_WHEEL_DOWN)
	{
		zoom(data, 1.1, x, y);
	}
	render(data);
	return (0);
}

/**
 * key_event - Function registered as a key hook.
 *
 * Calls function "end_fractol" in case of an input of Escape.
 * Calls function "move" in case of an input of WASD/Up,Down,Right,Left.
 * Calls function "color_shift" in case of an input of SpaceBar.
 * Re-renders the frame after the function call.
 *
 * @param keycode Input sent by key hook.
 * @param data Pointer to data structure.
 *
 * @return Returns 0.
 */
int	key_event(int keycode, t_data *data)
{
	float	move_speed;

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
	else if (keycode == KEY_SPC)
		color_shift(data);
	render(data);
	return (0);
}

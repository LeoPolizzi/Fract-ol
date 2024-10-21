/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:07:28 by lpolizzi          #+#    #+#             */
/*   Updated: 2024/10/21 15:43:09 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_pixel(t_data *data, int x, int y, int color)
{
	data->imgdata.addr[x * 4 + y * WIN_SIZE_X * 4] = color;
	data->imgdata.addr[x * 4 + y * WIN_SIZE_X * 4 + 1] = color >> 8;
	data->imgdata.addr[x * 4 + y * WIN_SIZE_X * 4 + 2] = color >> 16;
	data->imgdata.addr[x * 4 + y * WIN_SIZE_X * 4 + 3] = color >> 24;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:07:28 by lpolizzi          #+#    #+#             */
/*   Updated: 2024/10/24 12:09:27 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * set_pixel - Sets the current pixel's color to a given color.
 *
 *		AA : color >> 24	:	Alpha channel
 *		RR : color >> 16	:	Red channel
 *		GG : color >> 8		:	Green channel
 *		BB : color >> 0		:	Blue channel
 */
void	set_pixel(t_data *data, int x, int y, int color)
{
	data->imgdata.addr[x * 4 + y * WIN_SIZE_X * 4] = color >> 0;
	data->imgdata.addr[x * 4 + y * WIN_SIZE_X * 4 + 1] = color >> 8;
	data->imgdata.addr[x * 4 + y * WIN_SIZE_X * 4 + 2] = color >> 16;
	data->imgdata.addr[x * 4 + y * WIN_SIZE_X * 4 + 3] = color >> 24;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:07:21 by lpolizzi          #+#    #+#             */
/*   Updated: 2024/10/24 12:09:37 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * clean_init - Initialize a t_data structure with empty values.
 */
void	clean_init(t_data *data)
{
	data->mlxdata.mlx = NULL;
	data->mlxdata.mlx_win = NULL;
	data->imgdata.img = NULL;
	data->imgdata.addr = NULL;
	data->fractdata.min_r = 0;
	data->fractdata.max_r = 0;
	data->fractdata.min_i = 0;
	data->fractdata.max_i = 0;
	data->fractdata.c_real = 0;
	data->fractdata.c_imaginary = 0;
	data->fractdata.type = -1;
	data->fractdata.color = 0;
	data->fractdata.palette = NULL;
	data->fractdata.max_iterations = MAX_ITERATIONS;
}

/**
 * ft_atod - Converts a string into a float
 */
float	ft_atod(char *str)
{
	int		i;
	float	nb;
	int		sign;
	float	div;

	nb = 0;
	div = 0.1;
	sign = 1;
	i = 0;
	if (str[i++] == '-')
		sign *= -1;
	while (str[i] && ft_isdigit(str[i]) && str[i] != '.')
		nb = (nb * 10.0) + (str[i++] - '0');
	if (str[i] == '.')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		nb = nb + ((str[i++] - '0') * div);
		div *= 0.1;
	}
	if (str[i] && !ft_isdigit(str[i]))
		return (-42);
	return (nb * sign);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:07:21 by lpolizzi          #+#    #+#             */
/*   Updated: 2024/10/21 13:35:56 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	data->fractdata.z_real = 0;
	data->fractdata.z_imaginary = 0;
	data->fractdata.type = -1;
	data->fractdata.color = 0;
	data->fractdata.palette = NULL;
}

double	ft_atod(char *str)
{
	int		i;
	double	nb;
	int		is_neg;
	double	div;

	nb = 0;
	div = 0.1;
	is_neg = 1;
	i = skip_space_sign(str, &is_neg);
	while (str[i] && ft_isdigit(str[i]) && str[i] != '.')
	{
		nb = (nb * 10.0) + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		nb = nb + ((str[i] - '0') * div);
		div *= 0.1;
		i++;
	}
	if (str[i] && !ft_isdigit(str[i]))
		return (-42);
	return (nb * is_neg);
}

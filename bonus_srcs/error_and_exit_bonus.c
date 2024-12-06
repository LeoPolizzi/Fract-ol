/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:43:21 by lpolizzi          #+#    #+#             */
/*   Updated: 2024/10/21 15:43:23 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int	msg(char *str1, char *str2, int errno)
{
	ft_putstr_fd("Fractol: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putendl_fd(str2, 2);
	return (errno);
}

void	clean_exit(int exit_code, t_data *data)
{
	if (!data)
		exit(exit_code);
	if (data->fractdata.palette)
		free(data->fractdata.palette);
	if (data->imgdata.img)
		mlx_destroy_image(data->mlxdata.mlx, data->imgdata.img);
	if (data->mlxdata.mlx_win && data->mlxdata.mlx)
		mlx_destroy_window(data->mlxdata.mlx, data->mlxdata.mlx_win);
	if (data->mlxdata.mlx)
	{
		mlx_loop_end(data->mlxdata.mlx);
		mlx_destroy_display(data->mlxdata.mlx);
		free(data->mlxdata.mlx);
	}
	exit(exit_code);
}

int	end_fractol(t_data *data)
{
	clean_exit(0, data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:35:49 by lpolizzi          #+#    #+#             */
/*   Updated: 2024/10/23 22:08:40 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * init_palette - Creates a gradient of colors from a starting color.
 */
void	init_palette(t_fractdata *fractdata)
{
	int	i;
	int	start_color;
	int	end_color;
	int	color_step;

	i = 0;
	start_color = fractdata->color;
	end_color = 0x000000;
	color_step = (start_color - end_color) / (MAX_ITERATIONS + 1);
	while (i < MAX_ITERATIONS)
	{
		fractdata->palette[i] = start_color - (i * color_step);
		i++;
	}
}

/**
 * init_img - Initializes an image with the minilibx.
 * 
 * Also calls the init_palette function to get a gradient of colors.
 */
static void	init_img(t_data *data)
{
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	char	*buf;

	data->fractdata.palette = ft_calloc((MAX_ITERATIONS + 1), sizeof(int));
	if (!(data->fractdata.palette))
		clean_exit(msg("Color: ", "Error creating a color palette.", 1), data);
	init_palette(&data->fractdata);
	data->imgdata.img = mlx_new_image(data->mlxdata.mlx, WIN_SIZE_X,
			WIN_SIZE_Y);
	if (!(data->imgdata.img))
		clean_exit(msg("Image: ", "Error creating an image buffer.", 1), data);
	buf = mlx_get_data_addr(data->imgdata.img, &pixel_bits, &line_bytes,
			&endian);
	data->imgdata.addr = buf;
}

/**
 * get_starting_complex - Gets the starting values for each fractal set.
 * 
 * If set is not Julia or if there are only 2 args, use default values.
 * If there are only 3 args for Julia, output help message.
 * If incorrect values are passed in the args, output help message.
 */
void	get_starting_complex(t_data *data, int ac, char **av)
{
	t_fractdata	*fdata;

	fdata = &data->fractdata;
	if (fdata->type != JULIA || ac == 2)
	{
		fdata->c_real = DEFAULT_C_REAL;
		fdata->c_imaginary = DEFAULT_C_IMAGINARY;
		return ;
	}
	if (ac < 4)
	{
		help_msg(data);
	}
	if (!ft_strchr(av[2], '.') || !ft_strchr(av[3], '.'))
	{
		help_msg(data);
	}
	fdata->c_real = ft_atod(av[2]);
	fdata->c_imaginary = ft_atod(av[3]);
	if (fdata->c_real > 2.0 || fdata->c_real < -2.0 || fdata->c_imaginary > 2.0
		|| fdata->c_imaginary < -2.0)
		help_msg(data);
}

/**
 * get_complex_plane - Get the right complex plane for each fractal set.
 */
void	get_complex_plane(t_data *data)
{
	t_fractdata	*fdata;

	fdata = &data->fractdata;
	if (fdata->type == JULIA)
	{
		fdata->min_r = -2.0;
		fdata->max_r = 2.0;
		fdata->min_i = -2.0;
		fdata->max_i = fdata->min_i + (fdata->max_r - fdata->min_r) * WIN_SIZE_Y
			/ WIN_SIZE_X;
	}
	else
	{
		fdata->min_r = -2.0;
		fdata->max_r = 1.0;
		fdata->max_i = -1.5;
		fdata->min_i = fdata->max_i + (fdata->max_r - fdata->min_r) * WIN_SIZE_Y
			/ WIN_SIZE_X;
	}
}

/**
 * init - Initializes an MLX instance and calls other init functions.
 */
void	init(t_data *data)
{
	data->mlxdata.mlx = mlx_init();
	if (!data->mlxdata.mlx)
		clean_exit(msg("MLX: ", "Error initializing mlx instance.", 1), data);
	data->mlxdata.mlx_win = mlx_new_window(data->mlxdata.mlx, WIN_SIZE_X,
			WIN_SIZE_Y, "Fract'ol");
	if (!data->mlxdata.mlx_win)
		clean_exit(msg("MLX: ", "Error creating an mlx window.", 1), data);
	init_img(data);
	get_complex_plane(data);
}

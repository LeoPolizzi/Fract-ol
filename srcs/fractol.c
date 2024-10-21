/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:39:09 by lpolizzi          #+#    #+#             */
/*   Updated: 2024/10/20 23:43:06 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	get_set(t_data *data, char **av)
{
	char	first;

	first = av[1][0];
	if ((first == 'm' || first == 'M') && ft_strlen(av[1]) == 1)
		data->fractdata.type = MANDELBROT;
	else if ((first == 'j' || first == 'J') && ft_strlen(av[1]) == 1)
		data->fractdata.type = JULIA;
	else if ((first == 'b' || first == 'B') && ft_strlen(av[1]) == 1)
		data->fractdata.type = BURNING_SHIP;
	else
		help_msg(data);
}

static void	handle_args(t_data *data, int ac, char **av)
{
	get_set(data, av);
	if (data->fractdata.type != JULIA && ac > 3)
		help_msg(data);
	else if (data->fractdata.type == JULIA && ac > 5)
		help_msg(data);
	get_starting_complex(data, ac, av);
	get_color(data, ac, av);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 2)
	{
		ft_putendl_fd("\n+====================================================+",
			1);
		ft_putendl_fd("|                     FRACT'OL                       |",
			1);
		ft_putendl_fd("+====================================================+\n",
			1);
		print_fractal_options();
		print_color_options();
		exit(1);
	}
	clean_init(&data);
	handle_args(&data, ac, av);
	init(&data);
	render(&data);
	print_controls();
	mlx_hook(data.mlxdata.mlx_win, CLOSE_BTN, 0, end_fractol, &data);
	mlx_key_hook(data.mlxdata.mlx_win, key_event, &data);
	mlx_mouse_hook(data.mlxdata.mlx_win, mouse_event, &data);
	mlx_loop(data.mlxdata.mlx);
}

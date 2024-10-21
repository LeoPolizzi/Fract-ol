/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:35:33 by lpolizzi          #+#    #+#             */
/*   Updated: 2024/10/21 15:43:47 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	ft_atox_color(t_data *data, char *color)
{
	int	i;
	int	j;
	int	ret;

	ret = 0;
	i = skip_space_sign_0x(color);
	j = 0;
	while (color[i] && ft_ishexdigit(color[i]))
	{
		if (ft_isdigit(color[i]))
			ret = (ret * 16) + (color[i] - '0');
		else
			ret = (ret * 16) + (ft_toupper(color[i]) - 'A' + 10);
		i++;
		j++;
	}
	if (j == 6 && !color[i])
		return (ret);
	else
		help_msg(data);
	return (-1);
}

void	get_color(t_data *data, int ac, char **av)
{
	t_fractdata	*fractdata;
	int			color;

	fractdata = &data->fractdata;
	if (fractdata->type == JULIA && ac == 5)
	{
		color = ft_atox_color(data, av[4]);
		if (color != -1)
			fractdata->color = color;
		else
			fractdata->color = DEFAULT_COLOR;
	}
	else if (fractdata->type != JULIA && ac == 3)
	{
		color = ft_atox_color(data, av[2]);
		if (color != -1)
			fractdata->color = color;
		else
			fractdata->color = DEFAULT_COLOR;
	}
	if (ac == 2 || (fractdata->type == JULIA && ac == 4))
		fractdata->color = DEFAULT_COLOR;
}

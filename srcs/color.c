/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:35:33 by lpolizzi          #+#    #+#             */
/*   Updated: 2024/10/21 18:36:47 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * ft_ishexdigit - Check if a char is an hex digit (0123456789abcdef).
 * @param c  The char to check.
 *
 * @return 1 if the char is an hex digit, 0 otherwise.
 */
static int	ft_ishexdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	c = ft_toupper(c);
	if (c >= 'A' && c <= 'F')
		return (1);
	else
		return (0);
}

/**
 * ft_atox_color - Converts a string containing an hex
 * representation of an int into an int.
 * @param color  The string to convert.
 *
 * @return The int representation of the string.
 */
static int	ft_atox_color(char *color)
{
	int	i;
	int	ret;

	ret = 0;
	i = -1;
	while (color[++i] && ft_ishexdigit(color[i]))
	{
		if (ft_isdigit(color[i]))
			ret = (ret * 16) + (color[i] - '0');
		else
			ret = (ret * 16) + (ft_toupper(color[i]) - 'A' + 10);
	}
	if (i == 6 && !color[i])
		return (ret);
	else
		help_msg(data);
	return (-1);
}

/*
 * get_color - Gets a color from the args passed from the main.
 *
 * 		Defaults to "DEFAULT_COLOR" if the color isn't valid.
 */
void	get_color(t_data *data, int ac, char **av)
{
	t_fractdata	*fractdata;
	int			color;

	fractdata = &data->fractdata;
	if (fractdata->type == JULIA && ac == 5)
	{
		color = ft_atox_color(av[4]);
		if (color != -1)
			fractdata->color = color;
		else
			fractdata->color = DEFAULT_COLOR;
	}
	else if (fractdata->type != JULIA && ac == 3)
	{
		color = ft_atox_color(av[2]);
		if (color != -1)
			fractdata->color = color;
		else
			fractdata->color = DEFAULT_COLOR;
	}
	if (ac == 2 || (fractdata->type == JULIA && ac == 4))
		fractdata->color = DEFAULT_COLOR;
}

/**
 * color_shift - Applies a shift in the color to generate a different palette.
 */
void	color_shift(t_data *data)
{
	data->fractdata.color = data->fractdata.color - DEFAULT_COLOR_SHIFT;
	init_palette(&data->fractdata);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_msg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:43:29 by lpolizzi          #+#    #+#             */
/*   Updated: 2024/10/21 15:44:09 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	print_fractal_options(void)
{
	ft_putendl_fd("+===============  Available Fractals  ===============+", 1);
	ft_putendl_fd("Which fractal would you like to view?", 1);
	ft_putendl_fd("\tM - Mandelbrot", 1);
	ft_putendl_fd("\tJ - Julia", 1);
	ft_putendl_fd("\tB - Burning Ship", 1);
	ft_putendl_fd("\e[36mUsage example:\t./fractol_bonus <type>", 1);
	ft_putendl_fd("\t\t./fractol_bonus M\e[0m", 1);
	ft_putstr_fd("\nFor Julia, you may specify starting values for the\n", 1);
	ft_putstr_fd("initial fractal shape. Values must be between\n", 1);
	ft_putendl_fd("-2.0 and 2.0 and must contain a decimal point.", 1);
	ft_putendl_fd("\e[36mUsage example:\t./fractol_bonus J", 1);
	ft_putendl_fd("\t\t./fractol_bonus J 0.285 0.01\e[0m", 1);
}

void	print_color_options(void)
{
	ft_putendl_fd("\n+================   Color Display   =================+",
		1);
	ft_putendl_fd("Pick a display color by providing a hexadecimal code.", 1);
	ft_putendl_fd("The hex color code must be formatted as RRGGBB:", 1);
	ft_putstr_fd("\e[38;2;255;255;255m\tWhite:\tFFFFFF", 1);
	ft_putendl_fd("\t\e[38;2;128;128;128mBlack:\t000000\e[0m", 1);
	ft_putstr_fd("\e[38;2;255;0;0m\tRed:\tFF0000", 1);
	ft_putendl_fd("\t\e[38;2;0;255;0mGreen:\t00FF00\e[0m", 1);
	ft_putstr_fd("\e[38;2;0;0;255m\tBlue:\t0000FF", 1);
	ft_putendl_fd("\t\e[38;2;255;255;0mYellow:\tFFFF00\e[0m", 1);
	ft_putendl_fd("Other interesting colors:", 1);
	ft_putstr_fd("\e[38;2;153;51;255m\tPurple:\t9933FF", 1);
	ft_putendl_fd("\t\e[38;2;204;102;0mOrange:\tCC6600\e[0m", 1);
	ft_putstr_fd("\e[38;2;255;51;153m\tPink:\tFF3399", 1);
	ft_putendl_fd("\t\e[38;2;0;255;128mTurquoise: 00FF80\e[0m", 1);
	ft_putstr_fd("\e[36mUsage example:\t", 1);
	ft_putendl_fd("./fractol_bonus <type> <color>", 1);
	ft_putendl_fd("\t\t./fractol_bonus M 133742\e[0m", 1);
	ft_putendl_fd("\nFor Julia, you can only specify colors after", 1);
	ft_putendl_fd("the starting values.", 1);
	ft_putstr_fd("\e[36mUsage example:\t", 1);
	ft_putendl_fd("./fractol_bonus J 0.285 0.01 424242\e[0m", 1);
	ft_putendl_fd("+====================================================+\n",
		1);
}

void	print_controls(void)
{
	ft_putendl_fd("\n+====================  Controls  ====================+",
		1);
	ft_putendl_fd("WASD or arrow keys\t\tmove view.", 1);
	ft_putendl_fd("Space bar\t\t\tchange colors.", 1);
	ft_putendl_fd("Scroll wheel\t\t\tzoom in and out.", 1);
	ft_putendl_fd("ESC or close window\t\tquit fract'ol.", 1);
	ft_putendl_fd("+====================================================+\n",
		1);
}

void	help_msg(t_data *data)
{
	ft_putendl_fd("\n+====================================================+",
		1);
	ft_putendl_fd("|                     FRACT'OL                       |", 1);
	ft_putendl_fd("+====================================================+\n",
		1);
	print_fractal_options();
	print_color_options();
	clean_exit(EXIT_FAILURE, data);
}

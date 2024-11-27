/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:40:47 by lpolizzi          #+#    #+#             */
/*   Updated: 2024/10/19 16:24:41 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "keymap.h"
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

/**
 * Macros for default values.
 */
# define WIN_SIZE_X 600
# define WIN_SIZE_Y 600
# define MAX_ITERATIONS 150
# define MAX_C_VALUE 2
# define MIN_C_VALUE -2
# define DEFAULT_C_REAL -0.7
# define DEFAULT_C_IMAGINARY 0.3
# define DEFAULT_COLOR 0xFF421337
# define END_COLOR 0x000000
# define MANDELBROT 0
# define BURNING_SHIP 1
# define JULIA 2
# define COLOR_ERROR 1
# define FRACTAL_TYPE_ERROR 2
# define DEFAULT_COLOR_SHIFT 512

/**
 * t_mlxdata - Structure holding MLX instance data.
 *
 *		mlx: Pointer to the mlx instance.
 *		mlx_win: Pointer to the mlx window.
 */
typedef struct s_mlxdata
{
	void		*mlx;
	void		*mlx_win;
}				t_mlxdata;

/**
 * t_imgdata - Structure holding image data.
 *
 *		img: Pointer to the image buffer.
 *		addr: Pointer to the start of the pixel data for the image.
 *		bits_per_pixel: Number of bits used for the color of each pixel.
 *		line_length: Number of bytes in each row of the image.
 *		endian: Indicates the byte order of the pixel data.
 */
typedef struct s_imgdata
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_imgdata;

/**
 * t_fractdata - Structure holding data for the calculation of a fractal.
 *
 *		c_real: Real part of the coordinates in the complex plane.
 *		c_imaginary: Imaginary part of the coordinates in the complex plane.
 *		min_r: Minimal real value of the complex plane.
 *		max_r: Maximal real value of the complex plane.
 *		min_i: Minimal imaginary value of the complex plane.
 *		max_i: Maximal imaginary value of the complex plane.
 *		type: Defines wich fractal to print.
 *		color: The main color to base the palette around.
 *		palette: Range of colors used to simulate depth.
 */
typedef struct s_fractdata
{
	double		c_real;
	double		c_imaginary;
	double		min_r;
	double		max_r;
	double		min_i;
	double		max_i;
	int			type;
	int			color;
	int			*palette;
}				t_fractdata;

/**
 * t_data - Main data structure for the application.
 *
 *	mlxdata: MLX instance data.
 *
 *		mlx: Pointer to the mlx instance.
 *		mlx_win: Pointer to the mlx window.
 *
 *	imgdata: Image data.
 *
 *		img: Pointer to the image buffer.
 *		addr: Pointer to the start of the pixel data for the image.
 *		bits_per_pixel: Number of bits used for the color of each pixel.
 *		line_length: Number of bytes in each row of the image.
 *		endian: Indicates the byte order of the pixel data.
 */
typedef struct s_data
{
	t_mlxdata	mlxdata;
	t_imgdata	imgdata;
	t_fractdata	fractdata;
}				t_data;

// Color functions

void			get_color(t_data *data, int ac, char **av);
void			color_shift(t_data *data);
void			init_palette(t_fractdata *fractdata);

// Event handling functions

int				mouse_event(int keycode, int x, int y, t_data *data);
int				key_event(int keycode, t_data *data);

// Error/Exit handling and help message functions

void			clean_exit(int exit_code, t_data *data);
int				end_fractol(t_data *data);
void			help_msg(t_data *data);
int				msg(char *str1, char *str2, int errno);
void			print_controls(void);
void			print_color_options(void);
void			print_fractal_options(void);

// Initialization functions

void			clean_init(t_data *data);
void			init(t_data *data);
void			get_starting_complex(t_data *data, int ac, char **av);
void			get_complex_plane(t_data *data);
double			ft_atod(char *str);

// Rendering functions

void			render(t_data *data);
void			set_pixel(t_data *data, int x, int y, int color);

#endif

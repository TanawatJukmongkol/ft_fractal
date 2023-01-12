/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:20:41 by tjukmong          #+#    #+#             */
/*   Updated: 2023/01/12 20:59:09 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

// Standard headers
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

// X display server headers
# include <X11/X.h>
# include <mlx.h>
# include <mlx_int.h>

// Keymaps
# if __MACH__
#  include "OSXKeycodes.h"
# else
#  include <X11/keysymdef.h>
# endif

typedef struct s_mlx {
	void	*mlx_ptr;
	void	*win_ptr;
	int		win_width;
	int		win_height;
	float	win_ratio;
}	t_mlx;

typedef struct s_cam {
	float	x;
	float	y;
	float	zoom;
}	t_cam;

typedef struct s_image
{
	t_mlx	mlx;
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	void	*ptr;
	char	*buff;
}	t_image;

typedef struct s_cmplx
{
	float	re;
	float	im;
}	t_cmplx;

typedef struct s_shader
{
	int		x;
	int		y;
	int		ittr;
	int		is_in_set;
}	t_shader;

typedef struct s_vars {
	t_mlx			mlx;
	t_cam			cam;
	unsigned int	keys;
	t_image			image;
	int				*colors;
	int				*schemes[10];
	int				scheme;
	int				scheme_len;
	void			*renderers[10];
	int				renderer;
	int				renderer_len;
	int				max_ittr;
	int				draw_ittr;
	int				draw_offset;
	void			(*update)(struct s_vars *vars, int draw_ittr);
	void			(*fractol)(t_cmplx *cmplx_nbr, int max_ittr,
			int *ittr, int *is_in_set);
}	t_vars;

// 0 = no key assigned
// kdef_ = key defines
// kmod_ = moded key combinations
enum	e_keydef {
	kdef_term	= XK_Escape,
	kdef_mod	= XK_Control_L,
	kdef_up		= XK_Up,
	kdef_down	= XK_Down,
	kdef_left	= XK_Left,
	kdef_right	= XK_Right,

	kmod_origin	= XK_o,
	kmod_color	= XK_Shift_L
};

enum	e_keybit {
	kbit_mod	= 0b00000001,
	kbit_up		= 0b00000010,
	kbit_down	= 0b00000100,
	kbit_left	= 0b00001000,
	kbit_right	= 0b00010000,

	kbit_origin	= 0b00100000,
	kbit_color	= 0b01000000
};

// MiniLibX extra functions (reversed engineered by tjukmong)
void	mlx_int_size_limit(t_mlx *mlx, int w, int h, int max);

// Complex numbers
void	cartesian_to_cmplx(t_vars *vars, t_cmplx *cmplx_nbr, int *x, int *y);

// Event listeners
int		key_event(int code, t_vars *vars);
int		mod_key(int code, t_vars *vars);
int		key_released(int code, t_vars *vars);
int		mouse_event(int code, int x, int y, t_vars *vars);
int		resize_window(t_vars *vars);
int		close_window(t_vars *vars);

// Graphics API
void	ft_init_image(t_vars *vars, t_image *img, int w, int h);
void	ft_draw_point(t_image *img, int x, int y, unsigned int color_hex);
void	ft_put_image(t_image *img, int x, int y);
void	mlx_error(t_vars *vars, char *msg);

// Shaders
void	shader_1(t_vars *vars, int draw_ittr);
void	shader_2(t_vars *vars, int draw_ittr);

//	Fractol functions
void	mandelbrot_set(t_cmplx *cmplx_nbr,
			int max_ittr, int *ittr, int *is_in_set);
void	julia_set(t_cmplx *cmplx_nbr,
			int max_ittr, int *ittr, int *is_in_set);
void	burning_ship(t_cmplx *cmplx_nbr, int max_ittr,
			int *ittr, int *is_in_set);

#endif
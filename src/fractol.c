/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:03:40 by tjukmong          #+#    #+#             */
/*   Updated: 2023/01/07 00:34:53 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//////////////////////////////////////////////////////////////////////
//	Program shortcuts:												//
//		[ Arrow keys ]: Pans the camera								//
//		[ Ctrl ] [ Up / down ]										//
//			or														//
//		[ Ctrl ] [ Scroll ]: Zoom in / out (locked to center).		//
//		[ Scroll ]: Zoom in / out (follows the curser)				//
//		[ Ctrl ] [ Shift ] [ Up / down ]: Change color scheme		//
//		[ Ctrl ] [ O ]: Go back to origin (0, 0).					//
//		[ Esc ]: Exit application									//
//																	//
//	Or change the shortcuts defined in e_keydef at fractol.h!		//
//////////////////////////////////////////////////////////////////////

#include "fractol.h"
#include <stdint.h>

// int	loop(t_vars *vars)
// {
// 	t_image	image;

// 	image.ptr = NULL;
// 	ft_init_image(vars, &image, 69, 69);
// 	for (int y = 0; y < 69; ++y) {
// 		for (int x = 0; x < 69; ++x) {
// 			ft_draw_point(&image, x, y, 0xffffff);
// 		}
// 	}
// 	ft_put_image(&image, 69, 69);
// 	ft_put_image(&image, 42, 42);
// 	return (0);
// }

void	cartesian_to_cmplx(t_vars *vars, t_cmplx *cmplx_nbr, int *x, int *y)
{
	cmplx_nbr->re = (*x - (float)vars->mlx.win_width / 2)
		* ((float)4 / vars->mlx.win_width)
		* (vars->mlx.win_ratio / vars->cam.zoom)
		+ vars->cam.x;
	cmplx_nbr->im = (*y - (float)vars->mlx.win_height / 2)
		* ((float)4 / vars->mlx.win_height)
		* (1 / vars->cam.zoom)
		+ vars->cam.y;
}

void	calculate_point(t_cmplx cmplx_nbr, int *ittr, int *is_in_set)
{
	t_cmplx	z0;

	z0.re = 0;
	z0.im = 0;
	*ittr = 0;
	*is_in_set = 1;
	while (*ittr < 50)
	{
		z0.re = (z0.re * z0.re) - (z0.im * z0.im) + cmplx_nbr.re;
		z0.im = (2 * z0.re * z0.im) + cmplx_nbr.im;
		if (sqrt((z0.re * z0.re) + (z0.im * z0.im)) > 2)
		{
			*is_in_set = 0;
			break ;
		}
		(*ittr)++;
	}
}

void	update(t_vars *vars)
{
	t_cmplx	complex;
	int		ittr;
	int		is_in_set;

	ft_init_image(vars, &vars->image, vars->mlx.win_width, vars->mlx.win_height);
	for (int y = 0; y < vars->mlx.win_height; y += 8) {
		for (int x = 0; x < vars->mlx.win_width; x += 8) {
			cartesian_to_cmplx(vars, &complex, &x, &y);
			calculate_point(complex, &ittr, &is_in_set);
			if (is_in_set)
				ft_draw_point(&vars->image, x, y, 0x00000000);
			else
				ft_draw_point(&vars->image, x, y, vars->colors[ittr % 7]);
		}
	}
	ft_put_image(&vars->image, 0, 0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx.mlx_ptr = mlx_init();
	vars.mlx.win_ptr = mlx_new_window(vars.mlx.mlx_ptr, 400, 400, "ft_fractal");
	vars.keys = 0;
	vars.cam.x = 0;
	vars.cam.y = 0;
	vars.cam.zoom = 1;
	vars.image.ptr = NULL;
	vars.update = &update;
	vars.colors = (int [7]){0xff0000ff, 0xffa500ff, 0xffff00ff,
		0x008000ff, 0x0000ffff, 0x4b0082ff, 0xee82eeff};
	mlx_int_size_limit(&vars.mlx, 400, 400, 0);
	mlx_int_size_limit(&vars.mlx, 900, 900, 1);
	mlx_hook(vars.mlx.win_ptr, DestroyNotify, 0L, close_window, &vars);
	mlx_hook(vars.mlx.win_ptr, 0, StructureNotifyMask, NULL, &vars);
	mlx_hook(vars.mlx.win_ptr, ConfigureNotify, 0L, resize_window, &vars);
	mlx_hook(vars.mlx.win_ptr, ButtonPress, ButtonPressMask, mouse_event,
		&vars);
	mlx_hook(vars.mlx.win_ptr, KeyPress, KeyPressMask, key_event, &vars);
	mlx_hook(vars.mlx.win_ptr, KeyRelease, KeyReleaseMask, key_released, &vars);
	// mlx_loop_hook(vars.mlx.mlx_ptr, loop, &vars);
	mlx_loop(vars.mlx.mlx_ptr);
	return (0);
}

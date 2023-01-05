/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:03:40 by tjukmong          #+#    #+#             */
/*   Updated: 2023/01/05 22:07:51 by tjukmong         ###   ########.fr       */
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

int	loop(t_vars *vars)
{
	t_image	image;

	image.ptr = NULL;
	ft_init_image(vars, &image, 69, 69);
	for (int y = 0; y < 69; ++y) {
		for (int x = 0; x < 69; ++x) {
			ft_draw_point(&image, x, y, 0xffffff);
		}
	}
	ft_put_image(&image, 69, 69);
	ft_put_image(&image, 42, 42);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx.mlx_ptr = mlx_init();
	vars.mlx.win_ptr = mlx_new_window(vars.mlx.mlx_ptr, 690, 420, "ft_fractal");
	vars.keys = 0;
	vars.cam.x = 0;
	vars.cam.y = 0;
	vars.cam.zoom = 1;
	mlx_int_size_limit(&vars.mlx, 620, 350, 0);
	mlx_int_size_limit(&vars.mlx, 1380, 840, 1);
	mlx_hook(vars.mlx.win_ptr, DestroyNotify, 0L, close_window, &vars);
	mlx_hook(vars.mlx.win_ptr, 0, StructureNotifyMask, NULL, &vars);
	mlx_hook(vars.mlx.win_ptr, ConfigureNotify, 0L, resize_window, &vars);
	mlx_hook(vars.mlx.win_ptr, ButtonPress, ButtonPressMask, mouse_event,
		&vars);
	mlx_hook(vars.mlx.win_ptr, KeyPress, KeyPressMask, key_event, &vars);
	mlx_hook(vars.mlx.win_ptr, KeyRelease, KeyReleaseMask, key_released, &vars);
	mlx_loop_hook(vars.mlx.mlx_ptr, loop, &vars);
	mlx_loop(vars.mlx.mlx_ptr);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:03:40 by tjukmong          #+#    #+#             */
/*   Updated: 2023/01/03 11:43:34 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	loop(t_vars	vars)
{
	//
}

int	main(void)
{
	t_vars	vars;

	vars.mlx.mlx_ptr = mlx_init();
	vars.mlx.win_ptr = mlx_new_window(vars.mlx.mlx_ptr,
			690, 420,
			"ft_fractal");
	mlx_int_size_limit(&vars.mlx, 620, 350, 0);
	mlx_int_size_limit(&vars.mlx, 1380, 840, 1);
	mlx_hook(vars.mlx.win_ptr, DestroyNotify, 0L, close_window, &vars);
	mlx_hook(vars.mlx.win_ptr, 0, StructureNotifyMask, NULL, &vars);
	mlx_hook(vars.mlx.win_ptr, ConfigureNotify, 0L, resize_window, &vars);
	mlx_hook(vars.mlx.win_ptr, ButtonPress, ButtonPressMask, mouse_event, &vars);
	mlx_hook(vars.mlx.win_ptr, KeyPress, KeyPressMask, key_event, &vars);
	loop(vars);
	mlx_loop(vars.mlx.mlx_ptr);
	return (0);
}

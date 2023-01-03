/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:19:03 by tjukmong          #+#    #+#             */
/*   Updated: 2023/01/03 11:46:31 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_event(int code)
{
	printf("\033[A\33[2KKeyEvent [%d]\n", code);
	return (0);
}

int	mouse_event(int code, int x, int y)
{
	printf("\033[A\33[2KMouseEvent [%d] (%d, %d)\n", code, x, y);
	return (0);
}

int	resize_window(t_vars *vars)
{
	XWindowAttributes	attr;

	XGetWindowAttributes((
			(t_xvar *)vars->mlx.mlx_ptr)->display, (
			(t_win_list *)vars->mlx.win_ptr)->window, &attr);
	printf("\033[A\33[2KResized! [%dx%d]\n", attr.width, attr.height);
	vars->mlx.win_width = attr.width;
	vars->mlx.win_height = attr.height;
	return (0);
}

int	close_window(t_vars *vars)
{
	printf("Bye bye!\n");
	mlx_destroy_window(vars->mlx.mlx_ptr, vars->mlx.win_ptr);
	mlx_destroy_display(vars->mlx.mlx_ptr);
	free(vars->mlx.mlx_ptr);
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:19:03 by tjukmong          #+#    #+#             */
/*   Updated: 2023/01/04 02:20:54 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_event(int code, t_vars *vars)
{
	if (code == kdef_mod)
		vars->keys |= kbit_mod;
	else if (code == kdef_up)
		vars->keys |= kbit_up;
	else if (code == kdef_down)
		vars->keys |= kbit_down;
	else if (code == kdef_left)
		vars->keys |= kbit_left;
	else if (code == kdef_right)
		vars->keys |= kbit_right;
	if (vars->keys & kbit_mod)
		return (mod_key(code, vars));
	vars->cam.x += ((vars->keys & kbit_right) != 0)
		- ((vars->keys & kbit_left) != 0);
	vars->cam.y += ((vars->keys & kbit_down) > 0)
		- ((vars->keys & kbit_up) > 0);
	printf("\033[A\33[2K[%f, %f]\n", vars->cam.x, vars->cam.y);
}

int	mod_key(int code, t_vars *vars)
{
	if (code == kmod_win)
		vars->keys |= kbit_win;
	else if (code == kmod_color)
		vars->keys |= kbit_color;
	if (vars->keys == (kbit_mod | kbit_win))
		close_window(vars);
	else if (vars->keys == (kbit_mod | kbit_up))
		printf("\033[A\33[2KZoom in!\n");
	else if (vars->keys == (kbit_mod | kbit_down))
		printf("\033[A\33[2KZoom out!\n");
	else if (vars->keys == (kbit_mod | kbit_color | kbit_up))
		printf("change to next color...\n");
	else if (vars->keys == (kbit_mod | kbit_color | kbit_down))
		printf("change to previous color...\n");
	return (0);
}

int	key_released(int code, t_vars *vars)
{
	if (code == kdef_mod)
		vars->keys &= ~kbit_mod;
	else if (code == kdef_up)
		vars->keys &= ~kbit_up;
	else if (code == kdef_down)
		vars->keys &= ~kbit_down;
	else if (code == kdef_left)
		vars->keys &= ~kbit_left;
	else if (code == kdef_right)
		vars->keys &= ~kbit_right;
	else if (code == kmod_win)
		vars->keys &= ~kbit_win;
	else if (code == kmod_color)
		vars->keys &= ~kmod_color;
	return (0);
}

int	mouse_event(int code, int x, int y, t_vars *vars)
{
	if (vars->keys == kbit_mod && code == 4)
		printf("\033[A\33[2KZoom in!\n");
	else if (vars->keys == kbit_mod && code == 5)
		printf("\033[A\33[2KZoom out!\n");
	return (0);
}

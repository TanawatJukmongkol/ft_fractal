/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:19:03 by tjukmong          #+#    #+#             */
/*   Updated: 2023/01/04 17:05:39 by tjukmong         ###   ########.fr       */
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
	else if (code == kdef_term)
		close_window(vars);
	if (vars->keys & kbit_mod)
		return (mod_key(code, vars));
	vars->cam.x += ((vars->keys & kbit_right) != 0)
		- ((vars->keys & kbit_left) != 0);
	vars->cam.y += ((vars->keys & kbit_down) > 0)
		- ((vars->keys & kbit_up) > 0);
	printf("\033[A\33[2K[%f, %f]\n", vars->cam.x, vars->cam.y);
	return (0);
}

int	mod_key(int code, t_vars *vars)
{
	if (code == kmod_origin)
		vars->keys |= kbit_origin;
	else if (code == kmod_color)
		vars->keys |= kbit_color;
	if (vars->keys == (kbit_mod | kbit_up))
		printf("\033[A\33[2KZoom in shortcut (locked to screen center)!\n");
	else if (vars->keys == (kbit_mod | kbit_down))
		printf("\033[A\33[2KZoom out shortcut (locked to screen center)!\n");
	else if (vars->keys == (kbit_mod | kbit_origin))
	{
		vars->cam.x = 0;
		vars->cam.y = 0;
		vars->cam.zoom = 1;
		printf("\033[A\33[2KSet origin!\n");
	}
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
	else if (code == kmod_origin)
		vars->keys &= ~kbit_origin;
	else if (code == kmod_color)
		vars->keys &= ~kmod_color;
	return (0);
}

int	mouse_event(int code, int x, int y, t_vars *vars)
{
	if (code == 4)
	{
		if (vars->keys == kbit_mod)
			printf("\033[A\33[2KZoom in (locked to screen center)!\n");
		else
			printf("\033[A\33[2KZoom in! (follows curser)\n");
	}
	else if (code == 5)
	{
		if (vars->keys == kbit_mod)
			printf("\033[A\33[2KZoom out (locked to screen center)!\n");
		else
			printf("\033[A\33[2KZoom out! (follows curser)\n");
	}
	return (0);
}

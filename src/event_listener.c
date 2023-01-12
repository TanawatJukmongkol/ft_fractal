/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:19:03 by tjukmong          #+#    #+#             */
/*   Updated: 2023/01/12 15:51:32 by tjukmong         ###   ########.fr       */
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
	vars->cam.x += 0.4 * (((vars->keys & kbit_right) != 0)
			- ((vars->keys & kbit_left) != 0)) / (vars->cam.zoom * 4);
	vars->cam.y -= 0.4 * (((vars->keys & kbit_down) > 0)
			- ((vars->keys & kbit_up) > 0)) / (vars->cam.zoom * 4);
	// printf("\033[A\33[2K[%f, %f]\n", vars->cam.x, vars->cam.y);
	return (0);
}

void	change_color_scheme(int code, t_vars *vars) {
	if (vars->keys == (kbit_mod | kbit_color | kbit_up))
	{
		if (vars->scheme++ >= vars->scheme_len)
			vars->scheme = 0;
		vars->colors = vars->schemes[vars->scheme];
	}
	else if (vars->keys == (kbit_mod | kbit_color | kbit_down))
	{
		if (vars->scheme-- <= 0)
			vars->scheme = vars->scheme_len;
		vars->colors = vars->schemes[vars->scheme];
	}
	else if (vars->keys == (kbit_mod | kbit_color | kbit_left))
	{
		if (vars->renderer++ >= vars->renderer_len)
			vars->renderer = 0;
		vars->update = vars->renderers[vars->renderer];
	}
	else if (vars->keys == (kbit_mod | kbit_color | kbit_right))
	{
		if (vars->renderer-- <= 0)
			vars->renderer = vars->renderer_len;
		vars->update = vars->renderers[vars->renderer];
	}
}

int	mod_key(int code, t_vars *vars)
{
	if (code == kmod_origin)
		vars->keys |= kbit_origin;
	else if (code == kmod_color)
		vars->keys |= kbit_color;
	if (vars->keys == (kbit_mod | kbit_up) && vars->cam.zoom < 2000)
		vars->cam.zoom *= 1.08;
	else if (vars->keys == (kbit_mod | kbit_down) && vars->cam.zoom > 0.08)
		vars->cam.zoom /= 1.08;
	else if (vars->keys == (kbit_mod | kbit_origin))
	{
		vars->cam.x = 0;
		vars->cam.y = 0;
		vars->cam.zoom = 1;
	}
	else
		change_color_scheme(code, vars);
	return (0);
}

int	key_released(int code, t_vars *vars)
{
	vars->update(vars);
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
	// t_cmplx	cmplx_nbr;

	// cartesian_to_cmplx(vars, &cmplx_nbr, &x, &y);
	// printf("[%d, %d] => (%f, %fi)\n", x, y, cmplx_nbr.re, cmplx_nbr.im);
	if (code == 4 && vars->cam.zoom < 2000)
	{
		vars->cam.zoom *= 1.08;
		if (vars->keys != kbit_mod)
		{
			vars->cam.x += ((float)x - (vars->mlx.win_width >> 1))
				/ (vars->mlx.win_width >> 1)
				/ vars->cam.zoom * 0.4;
			vars->cam.y -= ((float)y - (vars->mlx.win_height >> 1))
				/ (vars->mlx.win_height >> 1)
				/ vars->cam.zoom * 0.4;
		}
	}
	else if (code == 5 && vars->cam.zoom > 0.08)
		vars->cam.zoom /= 1.08;
	vars->update(vars);
	return (0);
}

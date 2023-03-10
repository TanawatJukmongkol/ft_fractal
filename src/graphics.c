/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:12:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/01/19 05:10:23 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_init_image(t_vars *vars, t_image *img, int w, int h)
{
	if (img->ptr)
		return ;
	img->ptr = mlx_new_image(vars->mlx.mlx_ptr, w, h);
	if (!img->ptr)
		mlx_error(vars, "Failed to initialize image ptr.");
	img->buff = mlx_get_data_addr(img->ptr, &img->pixel_bits,
			&img->line_bytes, &img->endian);
	img->mlx = vars->mlx;
}

void	ft_draw_point(t_image *img, int x, int y, unsigned int color_hex)
{
	int	pixel;

	pixel = (y * img->line_bytes) + (x * 4);
	if (img->pixel_bits != 32)
		color_hex = mlx_get_color_value(img->mlx.mlx_ptr, color_hex);
	if (img->endian == 0)
	{
		img->buff[pixel] = (color_hex) & 0xff;
		img->buff[pixel + 1] = (color_hex >> 8) & 0xff;
		img->buff[pixel + 2] = (color_hex >> 16) & 0xff;
		img->buff[pixel + 3] = (color_hex >> 24);
	}
	else
	{
		img->buff[pixel] = (color_hex >> 24);
		img->buff[pixel + 1] = (color_hex >> 16) & 0xff;
		img->buff[pixel + 2] = (color_hex >> 8) & 0xff;
		img->buff[pixel + 3] = (color_hex) & 0xff;
	}
}

void	ft_put_image(t_image *img, int x, int y)
{
	mlx_put_image_to_window(img->mlx.mlx_ptr, img->mlx.win_ptr, img->ptr, x, y);
}

void	change_color_scheme(int code, t_vars *vars)
{
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

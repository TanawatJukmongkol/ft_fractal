/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MLXTras.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:34:07 by tjukmong          #+#    #+#             */
/*   Updated: 2023/01/03 11:41:17 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mlx_int_size_limit(t_mlx *mlx, int w, int h, int max)
{
	XSizeHints	hints;
	long		toto;

	XGetWMNormalHints((
			(t_xvar *)mlx->mlx_ptr)->display, (
			(t_win_list *)mlx->win_ptr)->window, &hints, &toto);
	hints.width = w;
	hints.height = h;
	if (max)
	{
		hints.max_width = w;
		hints.max_height = h;
	}
	else
	{
		hints.min_width = w;
		hints.min_height = h;
	}
	hints.flags = PPosition | PSize | PMinSize | PMaxSize;
	XSetWMNormalHints((
			(t_xvar *)mlx->mlx_ptr)->display, (
			(t_win_list *)mlx->win_ptr)->window, &hints);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:48:29 by jeshin            #+#    #+#             */
/*   Updated: 2024/07/26 18:30:54 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_rgb(char ***rgb, char *path)
{
	int	i;
	int	j;

	*rgb = ft_split(path, ',');
	i = -1;
	while ((*rgb)[++i])
	{
		j = -1;
		while ((*rgb)[i][++j])
		{
			if (ft_isdigit((*rgb)[i][j]) == 0)
				err("Error: elements: rgb\n");
		}
	}
	if (i != 3)
		err("Error: elements: rgb\n");
}

static void	save_rgb(char **rgb, int *where)
{
	int	tmp;
	int	i;

	i = -1;
	while (rgb[++i])
	{
		tmp = ft_atoi(rgb[i]);
		if (tmp < 0 || tmp > 255)
			err("Error: elements: rgb\n");
		*where |= tmp << (-(8 * i) + 16);
	}
}

void	check_rgb(char *path, t_data *data, int where)
{
	char	**rgb;

	get_rgb(&rgb, path);
	if (where == 0 && !(data->map_info->elem & (1 << 4)))
	{
		data->map_info->elem |= (1 << 4);
		save_rgb(rgb, &(data->rgb->f));
	}
	else if (where && !(data->map_info->elem & (1 << 5)))
	{
		data->map_info->elem |= (1 << 5);
		save_rgb(rgb, &(data->rgb->c));
	}
	else
		err("Error: elements\n");
	free_tab(rgb);
}

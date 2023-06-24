/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrimah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 08:13:42 by yrimah            #+#    #+#             */
/*   Updated: 2023/06/24 08:13:50 by yrimah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/cub3d.h"

char	*ft_strjoinf(char *str, char *buff)
{
	char	*temporaneo;

	if (!buff)
		return (str);
	temporaneo = ft_strjoin(str, buff);
	free(str);
	return (temporaneo);
}

char	*ft_get_map(char *path_cub)
{
	int		fd;	
	char	*str;		
	char	*buff;
	int		index;

	if (help(&fd, &index, path_cub, &str))
		return (NULL);
	while (1)
	{
		buff = get_next_line(fd);
		if (buff == NULL)
		{
			close(fd);
			free(buff);
			break ;
		}
		index = 1;
		str = ft_strjoinf(str, buff);
		free(buff);
	}
	if (!index)
		return (NULL);
	return (str);
}

char	*ft_delete_spaces(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] != ' ')
			tmp[j++] = str[i];
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

void	ft_load_instr(t_game *data, char **tmp)
{
	int		i;
	char	**array;
	char	*tmp1;

	array = malloc(sizeof(char *) * 7);
	i = 0;
	while (i < 6)
	{
		tmp1 = ft_delete_spaces(tmp[i]);
		array[i] = ft_strdup(tmp1);
		free(tmp1);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		data->instr[i] = ft_strdup(&array[i][2]);
		i++;
	}
	while (i < 6)
	{
		data->instr[i] = ft_strdup(&array[i][1]);
		i++;
	}
	ft_free_array(array);
}

void	ft_divide_map(t_game *data, char **tmp)
{
	int	j;
	int	i;

	i = 0;
	ft_load_instr(data, tmp);
	while (tmp[i])
		i++;
	data->map = ft_calloc(sizeof(char *), (i - 5));
	j = 0;
	i = 6;
	while (tmp[i])
	{
		data->map[j] = ft_strdup(tmp[i]);
		i++;
		j++;
	}
	ft_free_map(tmp);
}

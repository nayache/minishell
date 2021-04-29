/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_array_strings.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:25:39 by nayache           #+#    #+#             */
/*   Updated: 2021/04/29 13:56:05 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

int		tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

char	**ft_tabndup(char **src, int n)
{
	char	**tab;
	int		size;
	int		i;

	if (src == NULL)
		return (NULL);
	size = tablen(src);
	if ((tab = (char **)malloc(sizeof(char *) * (size + n + 1))) == NULL)
		return (NULL);
	i = 0;
	while (src[i] != NULL)
	{
		if ((tab[i] = ft_strdup(src[i])) == NULL)
		{
			free_tab(tab);
			return (NULL);
		}
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	print_tab(char **tab)
{
	while (*tab != NULL)
	{
		ft_putstr(*tab);
		if (*(tab + 1) != NULL)
			ft_putchar(' ');
		tab++;
	}
	ft_putchar('\n');
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_array_strings.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:25:39 by nayache           #+#    #+#             */
/*   Updated: 2021/03/25 11:25:43 by nayache          ###   ########.fr       */
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

char	**ft_tabdup(char **src)
{
	char	**tab;
	int		size;
	int		i;

	if (src == NULL)
		return (NULL);
	size = tablen(src);
	if ((tab = (char **)malloc(sizeof(char *) * (size + 1))) == NULL)
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
		ft_putchar('\n');
			tab++;
	}
}

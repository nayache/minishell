/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:32:13 by nayache           #+#    #+#             */
/*   Updated: 2021/04/28 18:15:19 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(t_cmd *list)
{
	int i;

	ft_putstr("-----------------------print-cmd----------------------------\n");
	if (list->argv == NULL)
		ft_putstr("No cmd.\n");
	while (list != NULL)
	{
		i = 0;
		if (list->argv != NULL)
		{
			while (list->argv[i] != NULL)
			{
				printf("[%s] ", list->argv[i]);
				i++;
			}
			printf("\n");
		}
		list = list->next;
	}
	ft_putstr("------------------------------------------------------------\n");
}

t_btree		*init_node(void)
{
	t_btree *node;
	
	if ((node = (t_btree *)malloc(sizeof(t_btree))) == NULL)
		return (NULL);
	node->argv = NULL;
	node->left = NULL;
	node->right = NULL;
	node->flux = NULL;
	return (node);
}

void	free_cmd(t_cmd *list)
{
	t_cmd *head;
	t_cmd *tmp;

	head = list;
	while (list != NULL)
	{
		if (list->argv != NULL)
			free_tab(list->argv);
		tmp = list;
		list = list->next;
		free(tmp);
	}
	head = NULL;
}

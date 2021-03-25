/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:32:13 by nayache           #+#    #+#             */
/*   Updated: 2021/03/25 11:50:15 by nayache          ###   ########.fr       */
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

t_cmd	*init_cmd(char **insert)
{
	t_cmd *cmd;
	
	if ((cmd = (t_cmd *)malloc(sizeof(t_cmd))) == NULL)
		return (NULL);
	if (insert == NULL)
		cmd->argv = NULL;
	else
		if ((cmd->argv = ft_tabdup(insert)) == NULL)
			return (NULL);
	cmd->next = NULL;
	return (cmd);
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

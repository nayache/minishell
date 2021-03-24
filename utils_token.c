/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:56:05 by nayache           #+#    #+#             */
/*   Updated: 2021/03/24 19:15:53 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *list)
{
	ft_putstr("----------------------print-token---------------------------\n");
	if (list->data == NULL)
		ft_putstr("No tokens.\n");
	while (list != NULL)
	{
		if (list->data != NULL)
		{
			printf("[%s]\n", list->data);
		}
		list = list->next;
	}
	ft_putstr("------------------------------------------------------------\n");
}

t_token	*init_token(void)
{
	t_token *token;
	
	if ((token = malloc(sizeof(t_token))) == NULL)
		return (NULL);
	token->data = NULL;
	token->next = NULL;
	return (token);
}

int		add_token(t_token *list, char *item, int size)
{
	t_token *new;
	char	tmp;
	
	tmp = item[size];
	item[size] = '\0';
	if (list->data == NULL)
	{
		if ((list->data = ft_strdup(item)) == NULL)
			return (-1);
		item[size] = tmp;
		return (0);
	}
	if ((new = (t_token *)malloc(sizeof(t_token))) == NULL)
		return (-1);
	while (list->next != NULL)
		list = list->next;
	list->next = new;
	if ((new->data = ft_strdup(item)) == NULL)
		return (-1);
	new->next = NULL;
	item[size] = tmp;
	return (0);
}

void	free_token(t_token *list)
{
	t_token *tmp;

	while (list != NULL)
	{
		if (list->data != NULL)
			free(list->data);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

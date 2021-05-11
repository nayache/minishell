/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 12:54:05 by nayache           #+#    #+#             */
/*   Updated: 2021/05/11 15:48:14 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_btree			*build_cmd(t_token *token)
{
	t_btree		*new;
	t_tokentype old_type;

	if ((new = init_node()) == NULL)
		return (NULL);
	while (token != NULL && is_operator(token->type) == 0)
	{
		if (adjust_type(token->type) == Text)
		{
			new->argv = build_argv(new->argv, token, old_type);
			if (new->argv == NULL)
				return (NULL);
		}
		old_type = token->type;
		token = token->next;
	}
	return (new);
}

t_btree			*build_operator(t_btree *current, char *operator)
{
	if (current->flux != NULL)
	{
		current->left = init_node();
		if (current->left == NULL)
			return (NULL);
		current = current->left;
	}
	if ((current->flux = ft_strdup(operator)) == NULL)
		return (NULL);
	return (current);
}

t_btree			*build_last_node(t_btree *head, t_btree *current, t_token *lst)
{
	if (current->flux == NULL)
	{
		if ((current = build_cmd(lst)) == NULL)
			return (NULL);
		free(head);
		return (current);
	}
	if ((current->left = build_cmd(lst)) == NULL)
		return (NULL);
	return (head);
}

t_btree			*build(t_btree *current, t_token *token)
{
	t_btree *tmp;

	if ((current = build_operator(current, token->data)) == NULL)
		return (NULL);
	if ((current->right = build_cmd(token->next)) == NULL)
		return (NULL);
	if (token->type == End_cmd)
	{
		tmp = current->right;
		current->right = NULL;
		tmp->flux = current->flux;
		current->flux = NULL;
		current->argv = tmp->argv;
		tmp->argv = NULL;
		current->left = tmp;
		return (current->left);
	}
	return (current);
}

t_btree			*build_btree(t_btree *btree, t_token *token)
{
	t_btree		*current;

	current = btree;
	token = get_last_token(token);
	while (token->prev != NULL)
	{
		if (is_operator(token->type) == 1 && token->next != NULL)
		{
			current = build(current, token);
			if (token->prev != NULL && *token->prev->data == '>')
			{
				free(current->flux);
				if ((current->flux = ft_strdup(">>")) == NULL)
					return (NULL);
				token = token->prev;
			}
		}
		token = token->prev;
	}
	btree = build_last_node(btree, current, token);
	return (btree);
}

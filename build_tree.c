/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 12:54:05 by nayache           #+#    #+#             */
/*   Updated: 2021/04/29 13:47:03 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		remove_whitespace(t_btree *tree)
{
	t_btree *prev;
	int		size;

	while (tree != NULL)
	{
		if (tree->argv == NULL && tree->flux == NULL)
		{
			free(tree);
			prev->right = NULL;
			return (0);
		}
		size = tablen(tree->argv);
		if (is_empty_str(tree->argv[size - 1]) == 1)
		{
			free(tree->argv[size - 1]);
			tree->argv[size - 1] = NULL;
		}
		prev = tree;
		tree = tree->right;
	}
	return (0);
}

static int		dissociate_operators(t_btree *tree)
{
	t_btree *new_node;

	while (tree != NULL)
	{
		if (tree->flux != NULL)
		{
			if ((new_node = init_node()) == NULL)
				return (-1);
			new_node->argv = tree->argv;
			tree->argv = NULL;
			tree->left = new_node;
		}
		tree = tree->right;
	}
	return (0);
}

static t_btree	*add_node(t_btree *tree, t_token *token)
{
	t_btree *new_node;

	if ((new_node = init_node()) == NULL)
		return (NULL);
	tree->right = new_node;
	tree = tree->right;
	if (token->type != End_cmd)
		if ((tree->flux = ft_strdup(token->data)) == NULL)
			return (NULL);
	return (tree);
}

static t_btree	*build(t_btree *current, t_token *token, t_tokentype old_type)
{
	if (adjust_type(token->type) == Text || token->type == Whitespace)
	{
		if (!(token->type == Whitespace && is_operator(old_type)))
		{
			current->argv = build_argv(current->argv, token, old_type);
			if (current->argv == NULL)
				return (NULL);
		}
	}
	else if (token->type == Dirout && old_type == Dirout)
	{
		free(current->flux);
		if ((current->flux = ft_strdup(">>")) == NULL)
			return (NULL);
	}
	else
		if ((current = add_node(current, token)) == NULL)
			return (NULL);
	return (current);
}

t_btree			*build_btree(t_btree *btree, t_token *token)
{
	t_btree		*current;
	t_tokentype old_type;

	current = btree;
	while (token != NULL)
	{
		if ((current = build(current, token, old_type)) == NULL)
			return (NULL);
		old_type = token->type;
		token = token->next;
	}
	if (remove_whitespace(btree) == -1 || dissociate_operators(btree) == -1)
		return (NULL);
	return (btree);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 09:56:45 by nayache           #+#    #+#             */
/*   Updated: 2021/05/03 13:24:49 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env		*init_env(void)
{
	t_env *new;

	if ((new = malloc(sizeof(t_env))) == NULL)
		return (NULL);
	new->var = NULL;
	new->value = NULL;
	new->enabled = 1;
	new->next = NULL;
	return (new);
}

void		free_env(t_env *env)
{
	t_env *tmp;

	while (env != NULL)
	{
		if (env->var != NULL)
			free(env->var);
		if (env->value != NULL)
			free(env->value);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}

void		push_back(t_env *head, t_env *root)
{
	while (head->next != NULL)
		head = head->next;
	head->next = root;
}

static int	copy_var(t_env *root, char *line)
{
	char	*tmp;
	
	tmp = ft_strchr(line, '=');
	*tmp = '\0';
	if ((root->var = ft_strdup(line)) == NULL)
		return (-1);
	if ((root->value = ft_strdup(tmp + 1)) == NULL)
		return (-1);
	root->enabled = 1;
	*tmp = '=';
	return (0);
}

int			copy_env(char **env, t_env *dst)
{
	t_env	*new;
	t_env	*root;

	root = dst;
	while (*env != NULL)
	{
		if (root->var != NULL)
		{
			if ((new = init_env()) == NULL || copy_var(new, *env) == -1)
			{
				free_env(dst);
				return (-1);
			}
			push_back(dst, new);
		}
		else
		{
			if (copy_var(root, *env) == -1)
			{
				free_env(dst);
				return (-1);
			}
		}
		env++;
	}
	return (0);
}

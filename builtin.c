/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:49:49 by nayache           #+#    #+#             */
/*   Updated: 2021/05/07 12:00:05 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int			echo(t_btree *head, char **argv, t_env *env, int fd)
{
	int		new_line;

	new_line = 1;
	if (*argv != NULL && ft_strcmp(*argv, "-n") == 0)
	{
		argv++;
		new_line = 0;
	}
	while (*argv != NULL)
	{
		ft_putstr_fd(*argv, fd);
		argv++;
		if (*argv != NULL)
			ft_putchar_fd(' ', fd);
	}
	if (new_line == 1)
		ft_putchar_fd('\n', fd);
	return (0);
}


int			pwd(t_btree *head, char **argv, t_env *env, int fd)
{
	char	buffer[20000];

	getcwd(buffer, 20000);
	if (buffer == NULL)
	{
		ft_putstr_fd("minishell: pwd: ", 2);
		error();
	}
	else
	{
		ft_putstr_fd(buffer, fd);
		ft_putchar_fd('\n', fd);
	}
	return (0);
}

static int	add_var(t_env *env, char *arg)
{
	char	*tmp;
	t_env 	*new;

	if ((new = init_env()) == NULL)
		return (-1);
	if ((tmp = ft_strchr(arg, '=')) == NULL)
	{
		if ((new->var = ft_strdup(arg)) == NULL)
			return (-1);
	}
	else
	{
		*tmp = '\0';
		if ((new->var = ft_strdup(arg)) == NULL)
			return (-1);
		if ((new->value = ft_strdup(tmp + 1)) == NULL)
			return (-1);
		*tmp = '=';
	}
	push_back(env, new);
	return (0);
}

int		export_var(t_btree *head, char **argv, t_env *env, int fd)
{
	while (*argv != NULL)
	{
		if (is_alpha(**argv) == 0)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(*argv, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else
		{
			if (add_var(env, *argv) == -1)
			{
				error();
				return (-1);
			}
		}
		argv++;
	}
	return (0);
}

int		unset(t_btree *head, char **argv, t_env *env, int fd)
{
	t_env	*tmp;

	while (*argv != NULL)
	{
		if ((tmp = get_var(env, *argv)) != NULL)
		{
			free(tmp->value);
			tmp->value = NULL;
			tmp->enabled = 0;
		}
		argv++;
	}
	return (0);
}

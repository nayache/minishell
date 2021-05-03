/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:52:18 by nayache           #+#    #+#             */
/*   Updated: 2021/05/03 15:01:20 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			print_env(t_env *env)
{
	while (env != NULL)
	{
		if (env->enabled == 1)
		{
			ft_putstr(env->var);
			ft_putchar('=');
			if (env->value != NULL)
				ft_putstr(env->value);
			ft_putchar('\n');
		}
		env = env->next;
	}
}

int			env_display(t_btree *head, char **argv, t_env *env)
{
	print_env(env);
	return (0);
}

int			exit_shell(t_btree *head, char **argv, t_env *env)
{
	free_btree(head);
	free_env(env);
	exit(EXIT_SUCCESS);
}

t_env		*get_var(t_env *env, char *name)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->var, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

static void	refresh_var(t_env *env)
{
	char	current_dir[20000];
	t_env	*pwd;
	t_env	*old;

	old = get_var(env, "OLDPWD");
	pwd = get_var(env, "PWD");
	if (old != NULL)
	{
		free(old->value);
		if (pwd->enabled == 1)
			old->value = ft_strdup(pwd->value);
		else
			old->value = NULL;
	}
	if (pwd != NULL)
	{
		free(pwd->value);
		pwd->value = ft_strdup(getcwd(current_dir, 20000));
	}
}

int			cd(t_btree *head, char **argv, t_env *env)
{
	t_env	*tmp;
	char	*path;

	if (tablen(argv) > 1)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (0);
	}
	if (tablen(argv) == 0)
	{
		if ((tmp = get_var(env, "HOME")) == NULL || tmp->value == NULL)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (0);
		}
	}
	path = tablen(argv) == 0 ? tmp->value : *argv;
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		error();
		ft_putstr_fd(path, 2);
		return (0);
	}
	refresh_var(env);
	return (0);
}

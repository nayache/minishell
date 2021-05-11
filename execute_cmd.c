/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 10:48:39 by nayache           #+#    #+#             */
/*   Updated: 2021/05/11 16:03:31 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_builtin(char *str)
{
	const char	builtin[7][7] = {"echo", "cd", "pwd", "export", "unset",
		"env", "exit"};
	int			index;

	index = 0;
	while (index < 7)
	{
		if (ft_strcmp(str, (char *)builtin[index]) == 0)
			return (index);
		index++;
	}
	return (-1);
}

int		lst_size(t_env *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

char	*save_var_env(t_env *env)
{
	char	*str;
	int		size;
	
	size = ft_strlen(env->var);
	if (env->value != NULL)
		size += ft_strlen(env->value);
	if ((str = (char *)malloc(size + 2)) == NULL)
		return (NULL);
	ft_strcpy(str, env->var);
	ft_strcat(str, "=");
	if (env->value != NULL)
		ft_strcat(str, env->value);
	return (str);
}

char	**lst_to_tab(t_env *lst)
{
	char	**tab;
	int		size;
	int		i;

	size = lst_size(lst);
	if ((tab = (char **)malloc(sizeof(char *) * (size + 1))) == NULL)
		return (NULL);
	i = 0;
	while (lst != NULL)
	{
		if (lst->enabled == 1)
		{
			if ((tab[i++] = save_var_env(lst)) == NULL)
			{
				free_tab(tab);
				return (NULL);
			}
		}
		lst = lst->next;
	}
	tab[i] = NULL;
	return (tab);
}

char	**get_path(t_env *path)
{
	char	**tab;

	if (path == NULL || path->value == NULL)
		return (NULL);
	if ((tab = ft_split(path->value, ":")) == NULL)
		return (NULL);
	return (tab);
}

char	*test_path(char **path, char *bin)
{
	struct stat buf;
	char		tmp[10000];
	char		*new_path;

	while (*path != NULL)
	{
		bzero(tmp, 10000);
		ft_strcpy(tmp, *path);
		if (tmp[ft_strlen(tmp) - 1] != '/')
			ft_strcat(tmp, "/");
		ft_strcat(tmp, bin);
		if (stat(tmp, &buf) != -1)
		{
			if ((new_path = ft_strdup(tmp)) == NULL)
			{
				error();
				return (NULL);
			}
			return (new_path);
		}
		path++;
	}
	return (NULL);
}

char	*search_binary(char *bin, t_env *env)
{
	char		**path;
	char		*new_path;
	struct stat	buf;
	
	if (stat(bin, &buf) != -1)
	{
		if ((new_path = ft_strdup(bin)) == NULL)
			return (NULL);
		return (new_path);
	}
	if (ft_strncmp(bin, "./", 2) == 0)
	{
		if ((new_path = ft_strdup(bin + 2)) == NULL)
		{
			error();
			return (NULL);
		}
		return (new_path);
	}
	if ((path = get_path(get_var(env, "PATH"))) == NULL)
		return (NULL);
	new_path = test_path(path, bin);
	free_tab(path);
	return (new_path);
}

int		pipe_process(char **av, char **av2, t_env *env, char *operator)
{
/*
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
	close(pfd[0]);
	execve(path, av, env);*/
	return (0);
}

int		exec_process(char *path, char **av, char **env)
{
	pid_t	pid;
	int		pfd[2];

	if (pipe(pfd) == -1 || (pid = fork()) == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	if (pid == 0)
		execve(path, av, env);
	wait(NULL);
	return (0);
}

int		binary_process(t_btree *cmd, char **argv, t_env *env, int fd)
{
	char	**envp;
	char	*path;

	if ((path = search_binary(argv[0], env)) == NULL)
	{
		printf("%s: command not found\n", argv[0]);
		return (127);
	}
	if ((envp = lst_to_tab(env)) == NULL)
	{
		free(path);
		return (-1);
	}
	exec_process(path, argv, envp);
	free(path);
	free_tab(envp);
	return (0);
}

int		execute_cmd(t_btree *cmd, char **argv, t_env *env, int fd)
{
	int		(*builtin[7])(t_btree *cmd, char **argv, t_env *env, int fd);
	int		index;

	builtin[0] = echo;
	builtin[1] = cd;
	builtin[2] = pwd;
	builtin[3] = export_var;
	builtin[4] = unset;
	builtin[5] = env_display;
	builtin[6] = exit_shell;
	index = is_builtin(argv[0]);
	if (index != -1)
		return (builtin[index](cmd, argv + 1, env, fd));
	return (binary_process(cmd, argv, env, fd));
}

int		tree_process(t_btree *head, t_btree *cmd, t_env *env, int fd)
{
	if (cmd == NULL)
		return (0);

	if (cmd->left != NULL)
		tree_process(head, cmd->left, env, fd);
	if (cmd->argv != NULL)
		execute_cmd(head, cmd->argv, env, fd);
	return (0);
}

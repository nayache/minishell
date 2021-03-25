/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:11:51 by nayache           #+#    #+#             */
/*   Updated: 2021/03/25 11:43:04 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "libft/libft.h"

# define QUOTE 39
# define DQUOTE 34
# define OPEN_ROUND '('
# define CLOSE_ROUND ')'
# define DOLLAR '$'
# define DIR_IN '<'
# define DIR_OUT '>'
# define PIPE '|'
# define END_CMD ';'
# define EQUAL_ASSIGN '='

typedef struct	s_token
{
	char			*data;
	struct s_token	*next;
}				t_token;

typedef struct	s_cmd
{
	char			**argv;
	struct s_cmd	*next;
}				t_cmd;

void			print_token(t_token *list);
void			free_token(t_token *list);
t_token			*init_token(char *insert);
int				add_token(t_token *list, char *item, int size);
void			lst_push_back(t_token *list, t_token *new_token);
void			free_token(t_token *list);
int				check_special_char(char c);
void			print_cmd(t_cmd *list);
t_cmd			*init_cmd(char **insert);
void			free_cmd(t_cmd *list);
int				is_space(char c);
int				lexing(char *buf, t_token *token);
void			free_buf(char **buffer);
void			free_tab(char **tab);
int				tablen(char **tab);
void			print_tab(char **tab);
char			**ft_tabdup(char **src);
#endif

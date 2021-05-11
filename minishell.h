/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:11:51 by nayache           #+#    #+#             */
/*   Updated: 2021/05/11 16:11:23 by nayache          ###   ########.fr       */
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

# define BACKSLASH '\\'
# define QUOTE '\''
# define DQUOTE '"'
# define DIRIN '<'
# define DIROUT '>'
# define PIPE '|'
# define OPEN_ROUND '('
# define CLOSE_ROUND ')'
# define DOLLAR '$'
# define QUEST '?'
# define EQUAL_ASSIGN '='
# define END_CMD ';'

typedef enum	e_tokentype
{
	Text,
	Whitespace,
	Dirin,
	Dirout,
	Pipe,
	End_cmd,
	Escape,
	Quote_text,
	Dquote_text
}				t_tokentype;

typedef	enum	e_state
{
	START,
	EAT,
	INPUT,
	OUTPUT,
	ERROR
}				t_state;

typedef struct	s_token
{
	t_tokentype		type;
	char			*data;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct	s_env
{
	char			*var;
	char			*value;
	int				enabled;
	struct s_env	*next;
}				t_env;

typedef	struct	s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	char			**argv;
	char			*flux;
	char			*result;
	int				file;

}				t_btree;

void			error(void);
void			print_token(t_token *list);
void			free_token(t_token *list);
t_token			*init_token(char *insert);
int				add_token(t_token *list, char *item, char first, int size);
void			lst_push_back(t_token *list, t_token *new_token);
void			free_token(t_token *list);
t_token			*get_last_token(t_token *token);
t_tokentype		get_type(char c);	
int				check_special_char(char c);
void			print_cmd(t_cmd *list);
t_btree			*init_node(void);
void			free_cmd(t_cmd *list);
t_env			*init_env(void);
void			print_env(t_env *env, int fd);
void			free_env(t_env *env);
void			push_back(t_env *head, t_env *root);
int				copy_env(char **env, t_env *dst);
int				is_space(char c);
int				is_alpha(char c);
int				is_text(char c);
int				is_empty_str(char *str);
int				is_operator(t_tokentype type);
int				lexing(char *buf, t_token *token);
int				manage_backslash(t_token *token);
void			free_buf(char **buffer);
void			free_tab(char **tab);
void			free_btree(t_btree *tree);
int				tablen(char **tab);
void			print_tab(char **tab);
char			**ft_tabndup(char **src, int n);
char			**ft_tabcat(char **src1, char **src2);
int				parsing(t_token *token);
int				adjust_type(t_tokentype type);
char			**build_argv(char **argv, t_token *token, t_tokentype old_type);
t_btree			*build_btree(t_btree *btree, t_token *token);
int				env_display(t_btree *head, char **argv, t_env *env, int fd);
int				exit_shell(t_btree *head, char **argv, t_env *env, int fd);
t_env			*get_var(t_env *env, char *name);
int				cd(t_btree *head, char **argv, t_env *env, int fd);
int				export_var(t_btree *head, char **argv, t_env *env, int fd);
int				unset(t_btree *head, char **argv, t_env *env, int fd);
int				pwd(t_btree *head, char **argv, t_env *env, int fd);
int				echo(t_btree *head, char **argv, t_env *env, int fd);
int				tree_process(t_btree *head, t_btree *cmd, t_env *env, int fd);
#endif

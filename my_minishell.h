/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:48:57 by jgarlic           #+#    #+#             */
/*   Updated: 2021/12/02 22:49:01 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MINISHELL_H
# define MY_MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "signal.h"
# include <sys/wait.h>
# include <errno.h>

typedef struct s_shell {
	char	**env;
	int		i;
	char	**path;
	int		fd_pipe;
	int		last_code;
}	t_shell;

typedef enum e_pipe_state {
	Dis,
	File,
	Input,
	Write,
	Append,
}	t_pipe_state;

typedef struct s_command {
	char			**args;
	t_pipe_state	input_state;
	char			*input_arg;
	int				input_fd;
	t_pipe_state	output_state;
	char			*output_arg;
	int				output_fd;
	int				push_pipe;
}	t_command;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_parser {
	t_list			*list;
	char			*cmd;
	char			*str;
	char			*newline;
	int				i;
	int				bword;
	int				quote;
	int				updated;
	t_pipe_state	status;
}	t_parser;

typedef struct s_remove_split {
	char	**new_split;
	int		size;
	int		i;
	int		offset;
	int		del_size;
}	t_remove_split;

typedef struct s_executor {
	t_command	*cmd;
	int			pid;
	int			fd[2];
	int			fd_input_pipe;
}	t_executor;

typedef struct s_var_helper {
	int		i;
	int		j;
	char	tempc;
	char	*vr;
}	t_var_helper;

char			**ft_split(char const *s, char c);
char			*ft_strdup(char *src);
char			*ft_itoa(int n);
int				ft_atoi(char *str);
char			*ft_strchr(const char *s, int c);
void			my_cmd_controller(char *cmd, t_shell *shell);
void			my_print_split(char **split);
__SIZE_TYPE__	ft_strlen(const char *s);
char			**my_split_path(char **env);
char			*my_env_find(char **env, char *find, int last_code);
int				my_env_check(char **env, char *find);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_strncmp(char *s1, char *s2, __SIZE_TYPE__ n);
int				my_check_builtin(t_command *cmd, t_shell *shell, int can_exit);
char			**my_init_split(char **split);
char			**my_add_split(char **split, char *new_elem);
char			**my_remove_split(char **split, char *del_elem);
void			my_free_split(char **split);
int				my_split_size(char **split);
t_list			*my_cmd_parser(char *cmd, t_shell *shell);
void			my_ss(t_parser *p, char *arg,
					int pipe, t_pipe_state new_status);
void			my_str_append(char **str, char *append);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_back(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
void			ft_lstclear(t_list **lst, void (*del)(void *));
t_list			*ft_lstlast(t_list *lst);
void			my_input_solver_part2(char *str);
void			my_builtin_cd(char **args, t_shell *shell, int can_exit);
void			my_builtin_exit(char **args);
void			my_free_cmd(void *content);
void			my_exec_error(t_command *cmd);
void			my_cmd_parser_part5(t_parser *p, t_shell *shell);
void			my_cmd_parser_part3(t_parser *p);
void			my_cut_char(char **str, int index);
char			*my_st(char *str, int index, int *bword);
t_command		*my_init_cmd(char **args, int pipe);
int				my_is_spec(char c);
char			*my_var_solver(char *str, int i, t_shell *shell, int quotes);
int				my_global_static(int mode, int value);
#endif

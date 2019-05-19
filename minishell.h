/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 20:00:35 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/19 02:04:54 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <signal.h>
# include <readline/readline.h>
# include "libft/libft.h"

# define PATH_BUILTIN "./src/builtins:"

typedef void		(*t_sighandler)(int);

typedef struct		s_minishell
{
	char			**envp;
	char			**tab_cmd;
	t_sighandler	old;
	char			*cmd;
	pid_t			pid;
	int				status;
	int				last;
	int				sig_int;
	int				sig_bonus;
}					t_minishell;

typedef struct		s_echo
{
	int				n:1;
	int				e:1;
	int				cap_e:1;
}					t_echo;

typedef struct		s_env
{
	int				i:1;
	int				u:1;
	int				null:1;
	int				start_var;
	int				start_cmd;
	char			**tab;
}					t_env;

typedef struct		s_printenv
{
	char			**tab;
	int				null:1;
	int				ret;
}					t_printenv;

void				handler_sigint(int sig);
void				msg_error(char *msg, int n);
pid_t				create_process(void);
void				display_prompt(char **envp);
char				**cmdsplit(const char *str);
char				**ft_split_quote(char *tab);
char				**ft_split_invquote(char *tab);
int					well_quoted(char *str);
void				show_env(char **envp);
void				affect_chars(char **s1, char **s2, char *val1, char *val2);
void				set_oldpath(char ***envp, char	*val);
/*
**  exec command:   ---------------------------------------------------
*/
int					cmd_lancher(t_minishell *ms);
int					builtin_parent(t_minishell *ms);
int					builtin_child(t_minishell *ms);
int					exec_cmd(t_minishell *ms);
int					cmd_user(char ***tab, char **envp, char **fullpath);
/*
**		builtins:   ---------------------------------------------------
*/
int					ft_echo(char **av, t_minishell *ms);
int					ft_cd(t_minishell *ms);
int					ft_env(t_minishell *ms);
int					ft_setenv(t_minishell *ms);
int					ft_unsetenv(t_minishell *ms);
int					ft_printenv(t_minishell *ms);
int					ft_dollarenv(t_minishell *ms);
int					ft_exec(t_minishell *ms);
/*
**		 usages:    ----------------------------------------------------
*/
void				usage_env(char *f_msg);
int					fork_error(void);
void				msg_cmd_nfound(char *str);
int					msg_usrerr(char *cmd, int n);
int					msg_type(mode_t mode, char *cmd);
/*
**                  ----------------------------------------------------
*/
/*
**		ms tools:   ----------------------------------------------------
*/
void				init_minishell(t_minishell *ms, char **envp,
							int ac, char **av);
void				fill_new_ms(t_minishell *new_ms, t_minishell ms);
void				free_ms(t_minishell *ms, char *cmd);
/*
**                  ----------------------------------------------------
*/
int					exit_val(int stats);
void				gest_signal(t_minishell *ms);
void				ft_swap_env(char **env1, char **env2);
int					fill_env(t_env *env, char *cmd);
int					adv_show_env(char **envp, t_env *env, int len_t);
void				ft_setpwd(char ***envp, char *value);
char				*ft_getpwd(char **envp);
int					check_fx(char *str);
void				to_relative(char **a_path, char *home);
void				fix_path(char **envp, char ***tab);
int					is_relative(char *path);
void				rel_to_abs(char **r_path);
void				ft_print_sbslch(char *str);
int					print_var(char **envp, char *var, int last);
void				print_ee(char *str, t_echo echo);
int					quote_affiche(char **tab, t_echo echo);
int					found_env(char **envp, char *var);
void				qclean_tab(char **tab);
char				**clean_cmds(char *cmd);
int					fail_qtest(char *cmd);
void				free_ms(t_minishell *ms, char *str);
void				init_env(t_env *env);

#endif

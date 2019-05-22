/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <obelouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 20:00:35 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/22 21:18:11 by obelouch         ###   ########.fr       */
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
# include "libft/libft.h"

# define PATH_BUILTIN "./src/builtins:"

typedef void		(*t_sighandler)(int);

typedef struct		s_dicstr
{
	char			*var;
	char			*value;
}					t_dicstr;

typedef struct		s_minishell
{
	char			**envp;
	char			**tab_cmd;
	t_dicstr		*tab_var;
	int				cmd_freable;
	char			*cmd;
	pid_t			pid;
	t_sighandler	old;
	int				status;
	int				last;
	int				sig_int;
	int				sig_bonus;
	char			*home;
	char			*user;
}					t_minishell;

typedef struct		s_echo
{
	int				n:1;
	int				e:1;
	int				cap_e:1;
	char			**tab;
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

/*
**        splits:   ---------------------------------------------------
*/
char				**cmdsplit(const char *str);
char				**ft_split_quote(char *tab);
char				**ft_split_invquote(char *tab);
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
int					ft_echo(t_minishell *ms);
int					ft_cd(t_minishell *ms);
int					ft_env(t_minishell *ms);
int					ft_setenv(t_minishell *ms);
int					ft_unsetenv(t_minishell *ms);
int					ft_printenv(t_minishell *ms);
int					ft_exec(t_minishell *ms);
void				ft_exit(t_minishell *ms);
/*
**	 expansions:    ----------------------------------------------------
*/
int					affect_vars(t_minishell *ms);
void				replace_dollar(t_minishell *ms);
/*
**		 usages:    ----------------------------------------------------
*/
void				obsh_version(void);
void				usage_env(char *f_msg);
int					fork_error(void);
void				msg_cmd_nfound(char *str);
int					msg_usrerr(char *cmd, int n);
int					msg_type(mode_t mode, char *cmd);
/*
**		ms tools:   ----------------------------------------------------
*/
void				init_minishell(t_minishell *ms, char **envp,
							int ac, char **av);
void				fill_new_ms(t_minishell *new_ms, t_minishell ms);
int					free_ms(t_minishell *ms, char *cmd);
void				free_mscmd(t_minishell *ms);
/*
**       prints:    ----------------------------------------------------
*/
void				print_sbslch(char *str);
int					print_var(char **envp, char *var, int last);
void				print_ee(char *str, t_echo echo);
/*
**          env:    ----------------------------------------------------
*/
int					fill_env(t_env *env, char *cmd);
int					found_env(char **envp, char *var);
int					adv_show_env(char **envp, t_env *env, int len_t);
void				show_env(char **envp);
/*
**     wildcard:     ----------------------------------------------------
*/
int					ft_wildcard(char **str, char *path);
int					wildcard(t_minishell *ms);
int					manage_mid(char **str, char **b_star, char **a_star);
void				new_verify(char ***tab, char *str);
int					is_fine_a(char *str, char *after);
int					is_fine_b(char *str, char *before);
void				join_tab_snull(char ***tab, char **str);
int					is_allstar(char *str);
char				*first_w(char *str);
char				*last_w(char *str);
/*
**		dicstr		-----------------------------------------------------
*/
int					len_dicstr(t_dicstr *tab);
void				free_dicstr(t_dicstr **tab);
t_dicstr			*copy_2_dicstr(t_dicstr *tab);
void				add_2_dicstr(t_dicstr **tab, char *var, char *value);
/*
**					-----------------------------------------------------
*/
char				*home_path(char **envp);
char				*user_name(char **envp);
int					is_exit(char *str);
void				set_oldpath(char ***envp, char	*val);
void				ft_setpwd(char ***envp, char *value);
char				*ft_getpwd(char **envp);
int					exit_val(int stats);
pid_t				create_process(void);
int					check_fx(char *str);
void				to_relative(char **a_path, char *home);
int					fail_qtest(char *cmd);
void				handler_sigint(int sig);
void				gest_signal(t_minishell *ms);
void				msg_error(char *msg, int n);
void				display_prompt(char **envp);
int					tab_well_quoted(char **tab);
int					well_quoted(char *str);
void				affect_chars(char **s1, char **s2, char *v1, char *v2);
char				**clean_cmds(char *cmd, int mode);

#endif

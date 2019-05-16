/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 20:00:35 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/16 02:01:34 by obelouch         ###   ########.fr       */
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

typedef void (*sighandler_t)(int);

typedef struct	s_minishell
{
	char		**cmd;
	pid_t		pid;
	int			status;
	int			last_ret;
	int			i;
}				t_minishell;

typedef struct	s_echo
{
	int			n:1;
	int			e:1;
	int			cap_e:1;
}				t_echo;

typedef struct	s_env
{
	int			i:1;
	int			u:1;
	int			null:1;
	int			start_var;
	int			start_cmd;
	char		**tab;
}				t_env;

int				len_tab(char **tab);
void			msg_error(char *msg, int n);
pid_t			create_process(void);
void			display_prompt(char **envp);
void			free_tabstr(char ***tab);
char			**cmdsplit(const char *str);
int				cmd_user(char **tab, char **envp);
int				cmd_mybuilt(char *cmd, char **envp, int *last);
int				exec_cmd(char *cmd, char **envp);
char			**ft_split_quote(char *tab);
char			**ft_split_invquote(char *tab);
int				well_quoted(char *str);
void			show_env(char **envp);
void			set_oldpath(char ***envp, char	*val);
int				ft_echo(int ac, char **av, char **envp, int *last);
int				ft_cd(char *cmd, char **envp, int *last);
int				ft_env(char **envp, char *cmd, int *last);
int				ft_setenv(char **envp, char *cmd, int *last);
int				ft_unsetenv(char **envp, char *cmd, int *last);
void			triple_free(char **s1, char **s2, char **s3);
int				exit_val(int stats);
void			gest_signal(t_minishell *ms, int ac, char **av);
void			ft_swap_env(char **env1, char **env2);
int				fill_env(t_env *env, char *cmd);
int				adv_show_env(char **envp, t_env *env, int len_t);
void			ft_setpwd(char **envp, char *value);
char			*ft_getpwd(char **envp);
int				check_fx(char *str);
void			to_relative(char **a_path, char *home);
void			fix_path(char **envp, char **tab);
int				is_relative(char *path);
void			rel_to_abs(char **r_path);
void			ft_print_sbslch(char *str);
int				print_var(char **envp, char *var, int *last);
void			print_ee(char *str, t_echo echo);
int				quote_affiche(char **tab, t_echo echo);


#endif

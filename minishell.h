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
void			display_prompt(char *envp[]);
void			free_tabstr(char ***tab);
char			**cmdsplit(const char *str);
int				cmd_user(char **tab, char *envp[]);
int				cmd_mybuilt(char *cmd, char **envp, char **prev_cd);
int				exec_cmd(char *cmd, char **envp, int status);
int				ft_echo(int ac, char **av, char **envp, int status);
void			ft_cd(char *cmd, char *envp[], char **prev_cd);
char			**ft_split_quote(char *tab);
char			**ft_split_invquote(char *tab);
int				well_quoted(char *str);
void			show_env(char **envp);
void			ft_env(char **envp, char *cmd);
void			ft_setenv(char **envp, char *cmd);
void			ft_unsetenv(char **envp, char *cmd);
void			triple_free(char **s1, char **s2, char **s3);

#endif

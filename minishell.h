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

typedef struct	s_echo
{
	int			n:1;
	int			e:1;
	int			cap_e:1;
}				t_echo;

pid_t			create_process(void);
void			free_tabstr(char **tab);
char			**cmdsplit(const char *str);
void			display_prompt(char *envp[]);
int				cmd_user(char **tab, char *envp[]);
int				ft_echo(char **tab, char *envp[]);
void			ft_cd(char **tab, char *envp[]);
void			ft_exit(char **tab, char *envp[]);

#endif

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include "libft/libft.h"

pid_t	create_process(void);
void	free_tabstr(char **tab);
char	**cmdsplit(const char *str);
void	display_prompt(char *envp[]);
int	cmd_user(char ***tab, char *envp[]);
void	ft_cd(char ***tab, char *envp[]);
void	ft_echo(char ***tab, char *envp[]);
void	ft_exit(char ***tab, char *envp[]);

#endif

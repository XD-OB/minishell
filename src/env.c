#include "minishell.h"

void	ft_env(char **envp, char **tab)
{
	int		i;

	i = -1;
	while (envp[++i])
		ft_putendl(envp[i]);
}

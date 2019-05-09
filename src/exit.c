#include "minishell.h"

int		ft_exit(char ***tab, char *envp[])
{
	int		n;

	n = ((*tab)[1]) ? ft_atoi((*tab)[1]) : 0;
	free_tabstr(*tab);
	kill(0, SIGINT);
	return (n);
}

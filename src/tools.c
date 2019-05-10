#include "minishell.h"

void	free_tabstr(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

pid_t	create_process(void)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid != -1)
		return (child_pid);
	write(2, "fork: Error\n", 12);
	exit(EXIT_FAILURE);
}

int			well_quoted(char *str)
{
	int		d_quote;
	int		s_quote;
	int		i;

	i = 0;
	d_quote = 0;
	s_quote = 0;
	while (str[i])
	{
		if (str[i] == 34)
			d_quote++;
		if (str[i] == 39)
			s_quote++;
		i++;
	}
	if (!(s_quote % 2) && !(d_quote % 2))
		return (1);
	return (0);
}

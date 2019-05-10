#include "minishell.h"

void	ft_unsetenv(char **envp, char *var, char *value)
{
	char	*tmp;
	int		len_var;
	int		start;
	int		i;

	i = 0;
	start = -5;
	len_var = ft_strlen(var);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, len_var))
		{
			start = i;
			break ;
		}
		i++;
	}
	if (start == -5)
		return ;
	i = start;
	while (envp[i])
	{
		envp[i] = envp[i + 1];
		i++;
	}
}

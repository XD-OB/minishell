#include "minishell.h"

void	ft_setenv(char **envp, char *var, char *value)
{
	char	*new;
	int		len_var;
	int		i;

	i = 0;
	new = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, len_var))
		{
			new = ft_strjoin(var, "=");
			ft_strcombin(&new, value);
			envp[i] = new;
			return ;
		}
		i++;
	}
	if (!new)
	{
		new = ft_strjoin(var, "=");
		ft_strcombin(&new, value);
		envp[i] = new;
		envp[i + 1] = NULL;
	}
}

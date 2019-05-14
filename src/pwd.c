#include "minishell.h"

void		ft_setpwd(char **envp, char *value)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PWD=", 4))
		{
			new = ft_strjoin("PWD=", value);
			ft_strclr(envp[i]);
			ft_strcpy(envp[i], new);
			break ;
		}
		i++;
	}
	if (!new)
	{
		new = ft_strjoin("PWD=", value);
		ft_strclr(envp[i]);
		ft_strcpy(envp[i], new);
		envp[++i] = NULL;
	}
	free(new);
}

char		*ft_getpwd(char **envp)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PWD=", 4))
		{
			path = ft_strdup(&envp[i][4]);
			break ;
		}
		i++;
	}
	if (!path)
	{
		path = ft_strnew(500);
		getcwd(path, 500);
	}
	return(path);
}

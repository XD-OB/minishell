#include "minishell.h"

static void	user_home(char *envp[], int *u, int *h)
{
	int	i;

	i = -1;
	*u = -5;
	*h = -5;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "USER=", 5))
			*u = i;
		if (!ft_strncmp(envp[i], "HOME=", 5))
			*h = i;
	}
}

/*
** len:		0: len	1: len_a_path	2: len_home
*/

static void	to_relative(char **a_path, char *home)
{
	char	*r_path;
	int	len[3];
	int	i;
	int	j;

	len[1] = ft_strlen(*a_path);
	len[2] = ft_strlen(home);
	len[0] = len[1] - len[2] + 1;
	r_path = ft_strnew(len[0]);
	i = 0;
	j = len[2] - 1;
	r_path[i] = '~';
	while (++j < len[1])
		r_path[++i] = (*a_path)[j];
	free(*a_path);
	*a_path = r_path;
}

void		display_prompt(char *envp[])
{
	char	*curr_dir;
	char	*user;
	char	*home;
	int	u;
	int	h;

	curr_dir = ft_strnew(500);
	user_home(envp, &u, &h);
	user = ft_strdup((u == -5) ? "user" : &envp[u][5]);
	home = ft_strdup((h == -5) ? "" : &envp[h][5]);
	getcwd(curr_dir, 500);
	if (ft_strcmp(home, ""))
		to_relative(&curr_dir, home);
	ft_printf("%{GREEN}%s%{eoc}", user);
	ft_printf("%{RED}:%{cyan} %s%{eoc}$ ", curr_dir);
	free(curr_dir);
	free(user);
	free(home);
}

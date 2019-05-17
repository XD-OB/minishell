/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 16:18:53 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/17 07:14:19 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t		create_process(void)
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

void		set_oldpath(char ***envp, char *val)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_strjoin("OLDPWD=", val);
	while ((*envp)[i] && ft_strncmp((*envp)[i], "OLDPWD=", 7))
		i++;
	if (!(*envp)[i])
		add_2_tab(envp, new);
	else
	{
		free((*envp)[i]);
		(*envp)[i] = new;
	}
}

int			found_env(char **envp, char *var)
{
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(var);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, len))
			return (1);
		i++;
	}
	return (0);
}

void		affect_chars(char **s1, char **s2, char *val1, char *val2)
{
	*s1 = ft_strdup(val1);
	*s2 = ft_strdup(val2);
}

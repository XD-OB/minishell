/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 16:18:53 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/19 00:40:28 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		init_env(t_env *env)
{
	env->i = 0;
	env->u = 0;
	env->null = 0;
	env->start_var = 0;
	env->start_cmd = 0;
	env->tab = NULL;
}

void		affect_chars(char **s1, char **s2, char *val1, char *val2)
{
	*s1 = ft_strdup(val1);
	*s2 = ft_strdup(val2);
}

pid_t		create_process(void)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid != -1)
		return (child_pid);
	ft_dprintf(2, "%{red}-obsh%{CYAN}fork%{eoc}: error\n");
	return (-1);
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

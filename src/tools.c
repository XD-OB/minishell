/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <obelouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 16:18:53 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/20 22:28:29 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			obsh_version(void)
{
	ft_printf("\n%{CYAN}----------- OBSH ");
	ft_printf("--------------%{eoc}\n");
	ft_printf("           V.1.0.1\n");
	ft_printf(" Developed by:   %{GREEN}obelouch%{eoc}");
	ft_printf(" 2019\n\n");
	return (0);
}

int			fail_qtest(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i] && cmd[i + 1])
	{
		if ((cmd[i] == 34 || cmd[i] == 39) && cmd[i + 1] == '-')
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

pid_t		create_process(void)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid != -1)
		return (child_pid);
	ft_dprintf(2, "%{red}-obsh%{CYAN}fork%{eoc}: error\n");
	return (-1);
}

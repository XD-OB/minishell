/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:14:17 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/16 21:23:42 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				handler_sigint(int sig)
{
	char			*user;
	char			*pwd;

	if (sig == SIGINT)
	{
		pwd = getenv("PWD");
		if (!pwd)
		{
			pwd = ft_strnew(500);
			getcwd(pwd, 500);
		}
		else
			pwd = ft_strdup(pwd);
		to_relative(&pwd, getenv("HOME"));
		user = getenv("USER");
		user = ft_strdup((!user) ? "user" : user);
		ft_putchar('\n');
		ft_printf("%{red}[%{GREEN}%s%{eoc}", user);
		ft_printf("%{RED}:%{cyan} %s%{red}]%{eoc}", pwd);
		ft_printf("%{RED}$%{eoc} ");
		free(user);
		free(pwd);
	}
}

static int			cmd_lancher(int ac, char **av, t_minishell *ms, char **envp)
{
	if (cmd_builtin(ms->cmd[ms->i], envp, &(ms->last_ret)) == -1)
	{
		if ((ms->pid = create_process()) == -1)
		{
			ft_dprintf(2, "%{red}-obsh%{eoc}: ");
			ft_dprintf(2, "%{CYAN}fork%{eoc}: error\n");
			return (1);
		}
		if (ms->pid == 0)
		{
			signal(SIGINT, ms->old);
			exec_cmd(ms->cmd[ms->i], envp);
		}
		else
		{
			waitpid(ms->pid, &(ms->status), 0);
			if (ac == 2 && !ft_strcmp(av[1], "--signals"))
				gest_signal(ms);
			else
				ms->last_ret = exit_val(ms->status);
		}
	}
	return (0);
}

int					main(int ac, char **av, char **envp)
{
	t_minishell		ms;
	char			*line;

	set_oldpath(&envp, "");
	ms.status = 0;
	ms.last_ret = 0;
	ms.old = signal(SIGINT, handler_sigint);
	while (ac)
	{
		display_prompt(envp);
		get_next_line(0, &line);
		ft_trimstr(&line);
		ms.cmd = cmdsplit(line);
		free(line);
		ms.i = -1;
		while (ms.cmd[++(ms.i)])
			if (cmd_lancher(ac, av, &ms, envp))
				return (1);
		free_tabstr(&(ms.cmd));
	}
	return (EXIT_SUCCESS);
}

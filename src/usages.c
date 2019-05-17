/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usages.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 07:31:50 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/17 07:32:16 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		usage_env(void)
{
	ft_dprintf(2, "usage: env [-i0] [-u name]\n");
	ft_dprintf(2, "options: -   -i  --ignore-environment\n");
	ft_dprintf(2, "         -0  --null-separator\n");
	ft_dprintf(2, "         -u  --unset\n");
}

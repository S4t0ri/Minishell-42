/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inbuilt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:51:46 by shaas             #+#    #+#             */
/*   Updated: 2022/04/23 16:51:42 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_inbuilt(t_exec_block *i_exec)
{
	if (ft_strcmp(i_exec->cmd, "echo") == 0
		|| ft_strcmp(i_exec->cmd, "cd") == 0
		|| ft_strcmp(i_exec->cmd, "pwd") == 0
		|| ft_strcmp(i_exec->cmd, "export") == 0
		|| ft_strcmp(i_exec->cmd, "unset") == 0
		|| ft_strcmp(i_exec->cmd, "env") == 0
		|| ft_strcmp(i_exec->cmd, "exit") == 0)
		return (true);
	else
		return (false);
}

void	handle_inbuilt(t_exec_block *i_exec)
{
	if (ft_strcmp(i_exec->cmd, "echo") == 0)
		cmd_echo(i_exec);
	if (ft_strcmp(i_exec->cmd, "cd") == 0)
		cmd_cd(i_exec);
	if (ft_strcmp(i_exec->cmd, "env") == 0)
		cmd_env(i_exec);
	if (ft_strcmp(i_exec->cmd, "pwd") == 0)
		cmd_pwd(i_exec);
	if (ft_strcmp(i_exec->cmd, "export") == 0)
		cmd_export(i_exec);
	if (ft_strcmp(i_exec->cmd, "unset") == 0)
		cmd_unset(i_exec);
	if (ft_strcmp(i_exec->cmd, "exit") == 0)
		cmd_exit(i_exec);
}

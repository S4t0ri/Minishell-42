/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_creator_free_exit.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:18:50 by shaas             #+#    #+#             */
/*   Updated: 2022/05/01 23:10:48 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_parser_blocks_only_redir(t_parser_block *parser_blocks)
{
	t_parser_block	*free_blocks;

	while (parser_blocks != NULL)
	{
		free_blocks = parser_blocks;
		parser_free_redir(parser_blocks->redir);
		parser_blocks = parser_blocks->next;
		free(free_blocks);
	}
}

void	exec_free_args(t_arg *args)
{
	t_arg	*free_args;

	free_args = args;
	while (args != NULL)
	{
		free(args->value);
		args = args->next;
		free(free_args);
		free_args = args;
	}
}

void	free_close_exec_blocks(t_exec_block *exec_blocks)
{
	t_exec_block	*free_blocks;

	free_blocks = exec_blocks;
	while (exec_blocks != NULL)
	{
		free(exec_blocks->cmd);
		exec_free_args(exec_blocks->arg);
		if (exec_blocks->in_fd > STDERR_FILENO)
			close(exec_blocks->in_fd);
		if (exec_blocks->out_fd > STDERR_FILENO)
			close(exec_blocks->out_fd);
		exec_blocks = exec_blocks->next;
		free(free_blocks);
		free_blocks = exec_blocks;
	}
}

void	redir_creator_fail_exit1(t_parser_block *parser_blocks,
		t_exec_block *exec_blocks)
{
	free_parser_blocks(parser_blocks);
	free_close_exec_blocks(exec_blocks);
	free_env();
	exit(EXIT_FAILURE);
}

void	redir_creator_fail_exit2(t_parser_block *parser_blocks,
		t_exec_block *exec_blocks)
{
	free_parser_blocks_only_redir(parser_blocks);
	free_close_exec_blocks(exec_blocks);
	free_env();
	exit(EXIT_FAILURE);
}

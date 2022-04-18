/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_creator_free_exit.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:18:50 by shaas             #+#    #+#             */
/*   Updated: 2022/04/18 11:56:32 by shaas            ###   ########.fr       */
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
		if (exec_blocks->pp_in > STDERR_FILENO)
			close(exec_blocks->pp_in);
		if (exec_blocks->pp_out > STDERR_FILENO)
			close(exec_blocks->pp_out);
		if (exec_blocks->heredoc_pp_in > STDERR_FILENO)
			close(exec_blocks->heredoc_pp_in);
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

void	read_heredoc_fail_exit(int *heredoc_pp, t_parser_block *parser_blocks,
		t_exec_block *exec_blocks)
{
	close(heredoc_pp[PIPE_READ]);
	close(heredoc_pp[PIPE_WRITE]);
	free(heredoc_pp);
	redir_creator_fail_exit2(parser_blocks, exec_blocks);
}

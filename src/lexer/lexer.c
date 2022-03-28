/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:16:05 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/28 21:35:43 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*lexer_collect_string(t_lexer *lexer, t_command_block *first)
{
	char	*str;
	char	*c;
	char	quote_type;

	quote_type = lexer->c;
	str = ft_strdup("");
	if (str == NULL)
		command_blocks_fail_exit(first);
	while (true)
	{
		c = lexer_get_current_char_as_string(lexer, first);
		str = ft_strjoin_free(str, c);
		if (str == NULL)
			command_blocks_fail_exit(first);
		if (lexer->c == quote_type && ft_strlen(str) != 1)
			break ;
		lexer_advance(lexer);
	}
	return (str);
}

void	lexer_collect_id(t_lexer *lexer, t_command_block *first, t_command_block *curr)
{
	char	*s;
	char	*value;

	value = ft_strdup("");
	if (value == NULL)
		command_blocks_fail_exit(first);
	while (!is_seperator(lexer->c))
	{
		if ((lexer->c == '"' || lexer->c == '\'') && lexer_quote_is_closed(lexer))
			s = lexer_collect_string(lexer, first);
		else
			s = lexer_get_current_char_as_string(lexer, first);
		lexer_advance(lexer);
		value = ft_strjoin_free(value, s);
		if (value == NULL)
			command_blocks_fail_exit(first);
	}
	add_token(TOKEN_ID, value, curr, first);
}

void	lexer_advance_with_token(t_lexer *lexer, int token_len)
{
	int i;

	i = 0;
	while (i < token_len)
	{
		lexer_advance(lexer);
		i++;
	}
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0')
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	check_for_tokens(t_lexer *lexer, t_command_block **iter, t_command_block *first)
{
	if (lexer_peek_string(lexer, "|"))
	{
		lexer_advance(lexer);
		*iter = add_command_block(*iter, first);
	}
	else if (lexer_peek_string(lexer, "<<"))
		lexer_advance_with_token(lexer, add_token(TOKEN_INPUT_HEREDOC, NULL, *iter, first));
	else if (lexer_peek_string(lexer, "<"))
		lexer_advance_with_token(lexer, add_token(TOKEN_INPUT_FILE, NULL, *iter, first));
	else if (lexer_peek_string(lexer, ">>"))
		lexer_advance_with_token(lexer, add_token(TOKEN_OUTPUT_APPEND, NULL, *iter, first));
	else if (lexer_peek_string(lexer, ">"))
		lexer_advance_with_token(lexer, add_token(TOKEN_OUTPUT_REPLACE, NULL, *iter, first));
	else
		lexer_collect_id(lexer, first, *iter);
}

t_command_block	*lexer(t_lexer *lexer)
{
	t_command_block	*first;
	t_command_block	*iter;

	first = init_command_block(NULL, lexer->contents);
	iter = first;
	while (lexer->c != '\0')
	{
		lexer_skip_whitespace(lexer);
		if (lexer->c == '\0')
			break ;
		check_for_tokens(lexer, &iter, first);
	}
	return (first);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:37:18 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/28 20:56:58 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "structs.h"
# include <stdbool.h>

/*============LEXER=============*/

void			init_lexer(t_lexer *lexer);
void			lexer_advance_with_token(t_lexer *lexer, int token_len);
void			lexer_advance(t_lexer *lexer);
void			command_blocks_fail_exit(t_command_block *command_blocks);
void			lexer_skip_whitespace(t_lexer *lexer);
void			free_command_blocks(t_command_block *command_blocks);
void			lexer_collect_id(t_lexer *lexer, t_command_block *first,
					t_command_block *curr);
void			check_for_tokens(t_lexer *lexer, t_command_block **iter,
					t_command_block *first);
int				add_token(int type, char *value, t_command_block *curr,
					t_command_block *first);
char			*lexer_collect_string(t_lexer *lexer, t_command_block *first);
char			*lexer_get_current_char_as_string(t_lexer *lexer,t_command_block *first);
char			*ft_strjoin_free(char *s1, char *s2);
bool			is_seperator(char c);
bool			lexer_quote_is_closed(t_lexer *lexer);
bool			lexer_peek_string(t_lexer *lexer, char *str);
t_token			*init_token(int type, char *value, t_command_block *first);
t_command_block	*lexer(t_lexer *lexer);
t_command_block	*add_command_block(t_command_block *prev,
					t_command_block *first);
t_command_block	*init_command_block(t_command_block *first,
					char *block_contents);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:08:46 by shaas             #+#    #+#             */
/*   Updated: 2022/04/01 00:17:19 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*============PARSER===============*/

t_parser_block	*parser(t_lexer_block *lexer_block);
void			free_parser_blocks(t_parser_block *parser_blocks);
void			parser_fail_exit(t_lexer_block *lexer_blocks, t_parser_block *parser_blocks);
void			parser_free_redir(t_redir *redir);
void			parser_free_args(t_arg *args);
int	get_lexer_block_num(t_lexer_block *lexer_blocks);
t_parser_block	*init_parser_block(t_lexer_block *lexer_blocks, t_parser_block *first);
t_parser_block	*add_parser_block(t_parser_block *first, t_parser_block *prev,
t_lexer_block	*lexer_blocks);
#endif

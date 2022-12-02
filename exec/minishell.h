/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:11:00 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/02 16:46:38 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

struct s_cmd
{
	char		**cmd;
	char		**env;
	char		*outfile;
	int			append;
	char		*infile;
	char		*herdoc;
	struct s_cmd	*next;
	struct s_cmd	*prev;
};

int	exec(struct s_cmd *cmd);

#endif // MINISHELL_H

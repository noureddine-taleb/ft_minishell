/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:11:00 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/05 16:12:36 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include <unistd.h>

#define INPUT_HEREDOC 1
#define INPUT_FILE 2
struct s_cmd
{
	char		**cmd;
	char		**env;
	char		*outfile;
	int			append;
	int			input;
// union {
	char		*infile;
	char		*heredoc;
// }
	struct s_cmd	*next;
	struct s_cmd	*prev;

	pid_t			__pid;
};

int		exec(struct s_cmd *cmd);
void	die(char *msg, int status);

#endif // MINISHELL_H

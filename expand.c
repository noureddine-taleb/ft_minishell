/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:22:22 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/29 12:40:49 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*ft_expand(char *word, t_lexer *lexer, t_data **data)
{
	char	*ptr;
	char	**env;
	char	*str;
	char	*found;
	int		i;
	
	i = 1;
	found = NULL;
	env = (*data)->env;
	ptr = &lexer->command_ling[lexer->index + 1];
	while (env)
	{
		str = *env;
		while (*ptr && *ptr == *str && *str != '=')
		{
			ptr++;
			str++;
			i++;
		}
		if (*str == '=')
		{
			str++;
			found = ft_strjoin(word, str);
			while(i--)
				get_next_char(lexer);
			break ;
		}
		else
			ptr = &lexer->command_ling[lexer->index + 1];
		env++;
	}
	if (!found)
		return (NULL);
	else
		return (found);
}
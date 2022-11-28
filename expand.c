/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:22:22 by kadjane           #+#    #+#             */
/*   Updated: 2022/11/28 19:03:22 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*ft_expand(char **word, t_lexer *lexer, t_data **data)
{
	char	*ptr;
	char	**env;
	int		bool;
	char	*found;
	
	(void)word;
	bool = 0;
	found = NULL;
	env = (*data)->env;
	ptr = &lexer->command_ling[lexer->index + 1];
	while (env)
	{
	// 	while (*ptr && *ptr == **env && **env != '=')
	// 	{
	// 		ptr++;
	// 		(*env)++;
	// 	}
	// 	if (**env == '=')
	// 	{
	// 		(*env)++;
	// 		found = ft_strjoin(*word, *env);
	// 		break ;
	// 	}
	// 	env++;
	}
	// if (!found)
	while(env && *env && **env != '=')
	{
		// printf("-------- %c\n", *ptr++);
		while(**env != '=')
		{
			printf("%c\n", **env);
			(*env)++;
		}
		env++;
	}
	// printf("******* %c\n", lexer->c);
	return (NULL);
	// else
	// 	return (found);
}
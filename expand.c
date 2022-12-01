/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:22:22 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/01 18:15:34 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*expand_digit(t_lexer *lexer, char *word)
{
	char	*ptr;
	char	*found_digit;
	char	*str;
	char	*found;
	
	found_digit = NULL;
	found = NULL;
	ptr = &lexer->command_ling[lexer->index + 1];
	if (ft_isdigit(*ptr))
	{

		get_next_char(lexer);
		get_next_char(lexer);
		while(ft_isdigit(lexer->c))
		{
			str = char_convert_string(lexer->c);
			found_digit = ft_strjoin(found_digit, str);
			get_next_char(lexer);
			ft_free(&str);
		}
		found = ft_strjoin(word, found_digit);
		ft_free(&found_digit);
		return (found);
	}
	if(*ptr == '$')
	{
		get_next_char(lexer);
		get_next_char(lexer);
		return (ft_strjoin(word, "$$"));
	}
	return (NULL);
}

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
	if(ft_isalnum(lexer->command_ling[lexer->index + 1])
		|| lexer->command_ling[lexer->index + 1] == '$')
	{
		found = expand_digit(lexer, word);
		if (found)
			return(found);
		else
		{
			while (env && *env)
			{
				str = *env;
				ptr = &lexer->command_ling[lexer->index + 1];
				while (*ptr && *ptr == *str && *str != '=')
				{
					ptr++;
					str++;
					i++;
				}
				if (*str == '=' && !ft_isalnum(*ptr))
				{
					str++;
					found = ft_strjoin(word, str);
					while(i--)
						get_next_char(lexer);
					break ;
				}
				env++;
			}
			if (!found)
				return (NULL);
			else
				return (found);
		}
	}
	else
	{
		get_next_char(lexer);
		return(ft_strjoin(word, "$"));
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:22:22 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/02 02:56:14 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*expand_digit_2(t_lexer *lexer, char *word)
{
	char	*str;
	char	*found;
	char	*found_digit;
	
	found = NULL;
	found_digit = NULL;
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

char	*expand_digit(t_lexer *lexer, char *word)
{
	char	*ptr;
	
	ptr = &lexer->command_ling[lexer->index + 1];
	if (ft_isdigit(*ptr))
		return(expand_digit_2(lexer, word));
	if(*ptr == '$')
	{
		get_next_char(lexer);
		get_next_char(lexer);
		return (ft_strjoin(word, "$$"));
	}
	return (NULL);
}

int	ft_expand_2(t_lexer *lexer, char **str, char **ptr, char **env)
{
	int	i;
	
	i = 1;
	*str = *env;
	*ptr = &lexer->command_ling[lexer->index + 1];
	while (**ptr && **ptr == **str && **str != '=')
	{
		(*ptr)++;
		(*str)++;
		i++;
	}
	return (i);
}

void	ft_expand_3(t_lexer *lexer, char **str, char **ptr, char **env)
{
	int	i;
	
	while (env && *env)
	{
		i = ft_expand_2(lexer, str, ptr, env);
		if (**str == '=' && !ft_isalnum(**ptr))
		{
			(*str)++;
			while(i--)
				get_next_char(lexer);
			// found = ft_strjoin(word, str);
			break ;
		}
		env++;
	}
}

char	*ft_expand(char *word, t_lexer *lexer, t_data **data)
{
	char	*ptr;
	char	*str;
	char	*found;
	char	**env;
	int		i;
	
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
			// found
			// ft_expand_3(lexer, &str, &ptr, env);
			// printf("--->%s\n",ft_strjoin(word, str));
			// return(ft_strjoin(word, str));
			while (env && *env)
			{
				i = ft_expand_2(lexer, &str, &ptr, env);
				if (*str == '=' && !ft_isalnum(*ptr))
				{
					str++;
					while(i--)
						get_next_char(lexer);
					found = ft_strjoin(word, str);
					break ;
				}
				env++;
			}
			return (found);
		}
	}
	else
	{
		get_next_char(lexer);
		return(ft_strjoin(word, "$"));
	}
}
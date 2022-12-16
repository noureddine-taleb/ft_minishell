/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadjane <kadjane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:22:22 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/16 21:19:25 by kadjane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*expand_digit_2(t_lexer *lexer, char *word)
{
	// char	*str;
	char	*found;
	char	*found_digit;

	found = NULL;
	found_digit = NULL;
	get_next_char(lexer);
	get_next_char(lexer);
	while (ft_isdigit(lexer->c))
	{
		// str = char_convert_string(lexer->c);
		found_digit = ft_strjoin(found_digit, &lexer->c);
		get_next_char(lexer);
		// ft_free(&str);
	}
	found = ft_strjoin(word, found_digit);
	ft_free(&found_digit);
	return (found);
}

char	*expand_digit(t_lexer *lexer, char *word, t_data **data)
{
	char	*ptr;

	ptr = &lexer->command_ling[lexer->index + 1];
	if (ft_isdigit(*ptr))
	{
		(*data)->sign_exp_digit = 1;
		return (expand_digit_2(lexer, word));
	}
	if (*ptr == '$')
	{
		get_next_char(lexer);
		get_next_char(lexer);
		return (ft_strjoin(word, "$$"));
	}
	return (NULL);
}

int	ft_expand_3(t_lexer *lexer, char **str, char **ptr, char **env)
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

char	*ft_expand_2(char *word, t_lexer *lexer)
{
	char	*ptr;
	char	*str;
	char	**env;
	int		i;

	env = g_env;
	while (env && *env)
	{
		i = ft_expand_3(lexer, &str, &ptr, env);
		if (*str == '=' && !ft_isalnum(*ptr))
		{
			str++;
			while (i--)
				get_next_char(lexer);
			return (ft_strjoin(word, str));
		}
		env++;
	}
	return (NULL);
}

char	*ft_expand(char *word, t_lexer *lexer, t_data **data)
{
	char	*found;

	found = NULL;
	if (ft_isalnum(lexer->command_ling[lexer->index + 1])
		|| lexer->command_ling[lexer->index + 1] == '$')
	{
		found = expand_digit(lexer, word, data);
		if (found)
			return (found);
		else
			return (ft_expand_2(word, lexer));
	}
	else
	{
		get_next_char(lexer);
		return (ft_strjoin(word, "$"));
	}
}

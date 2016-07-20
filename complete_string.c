/*
** complete_string.c for  in /home/fernan_w/Téléchargements/backup/parser
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:58:42 2016
** Last update Sun Jun  5 19:14:54 2016 retyt
*/

#include <stdlib.h>
#include "parser.h"
#include "tools.h"
#include "readline.h"
#include "my.h"

static int	is_quote_missing(char *str)
{
  int		i;
  int		is_string;
  int		tmp;

  is_string = 0;
  i = 0;
  if (str == NULL)
    return (0);
  while (str[i])
    {
      tmp = i;
      pass_var(str, &i);
      if (i == tmp + 1 || (tmp != i && str[i - 1] != '"' && str[i - 1] != '`'
			   && str[i - 1] != '\'' && str[i - 1] != ')'))
	return (-1);
      if ((i > 0 && str[i] == '"' && str[i - 1] != '\\')
	  || (i == 0 && str[i] == '"'))
	is_string += 1;
      if (str[i])
	i += 1;
    }
  if (is_string % 2 == 1)
    return (-1);
  return (0);
}

static int	is_little_quote_missing(char *str)
{
  int		i;
  int		is_string;

  is_string = 0;
  i = 0;
  if (str == NULL)
    return (0);
  while (str[i])
    {
      pass_var(str, &i);
      if ((i > 0 && str[i] == '\'' && str[i - 1] != '\\')
	  || (i == 0 && str[i] == '\''))
	is_string += 1;
      if (str[i])
	i += 1;
    }
  if (is_string % 2 == 1)
    return (-1);
  return (0);
}

static int	is_var_missing(char *str)
{
  int		i;

  i = 0;
  while (str && str[i])
    {
      if (my_strncmp(str + i, "$(", 2) == 0)
	{
	  pass_var(str, &i);
	  if (i > 1 && str[i] == 0 && str[i - 1] != ')')
	    return (-1);
	}
      else
	i += 1;
    }
  return (0);
}

static int	is_magic_missing(char *str)
{
  int		i;

  i = 0;
  while (str && str[i])
    {
      if (str[i] == '`')
	{
	  pass_var(str, &i);
	  if (i > 0 && str[i - 1] != '`')
	    return (-1);
	}
      else
	i += 1;
    }
  return (0);
}

char	*complete_string(char *str, char **env, char ***files_completition)
{
  char	*tmp;
  char	*to_rm;
  int	what;
  int	loop;

  what = 0;
  loop = 0;
  while ((is_quote_missing(str) == -1 || (what = is_var_missing(str)) == -1
  	  || (what = is_magic_missing(str)) == -1
	  || is_little_quote_missing(str) == -1) && (loop++ < 50))
    {
      if ((tmp = read_line(0, files_completition, env, "> ")) == NULL)
	return (str);
      if (what == 0)
	if ((str = str_cat(str, "\n")) == NULL)
	  return (NULL);
      to_rm = str;
      if ((str = str_cat(str, tmp)) == NULL)
	return (NULL);
      if (loop > 0)
	free(to_rm);
      free(tmp);
    }
  return (str);
}

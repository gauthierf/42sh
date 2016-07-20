/*
** check_str.c for  in /home/fernan_w/Téléchargements/backup/parser
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:56:50 2016
** Last update Sun Jun  5 19:55:07 2016 retyt
*/

#include <stdlib.h>
#include "readline.h"
#include "parser.h"
#include "tools.h"
#include "my.h"
static int	check_str_redi(char *str)
{
  unsigned int	i;

  i = 0;
  while (str[i])
    {
      if ((str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
	  || (str[i] == '>' && str[i + 1] == ' ' && str[i + 2] == '>'))
	return (my_putstr("error: expression expected near '>'.\n", 2));
      if ((str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
	  || (str[i] == '<' && str[i + 1] == ' ' && str[i + 2] == '<'))
	return (my_putstr("error: expression expected near '<'.\n", 2));
      if ((str[i] == '>' || str[i] == '<')
	  && (str[i + 1] == '|' || str[i + 1] == '\0'
	      || (str[i + 1] == ' '
		  && (str[i + 2] == '\0' || str[i + 2] == '|'))))
	return (my_putstr("error: expression expected near '<' or '>'.\n", 2));
      if ((str[i] == '>' && str[i + 1] == '<')
	  || (str[i] == '<' && str[i + 1] == '>'))
	return (my_putstr("error: expression expected near '<' or '>'.\n", 2));
      i += 1;
    }
  return (0);
}

static int	check_pipe(char *str)
{
  int		i;
  int		error;

  i = 0;
  error = 0;
  if (str[0] == '|')
    error = -1;
  while (str[i])
    {
      if (str[i] == '|' && str[i + 1] && str[i + 2] == '|')
	error = -1;
      else if ((str[i] == '|' && str[i + 1] == ';')
	       || (str[i] == '|' && str[i + 1] && str[i + 2] == ';'))
	error = -1;
      else if ((str[i] == '|' && str[i + 1] == '&')
	       || (str[i] == '|' && str[i + 1] && str[i + 2] == '&'))
	error = -1;
      i += 1;
    }
  if (i > 0 && str[i - 1] == '|')
    error = -1;
  if (error == -1)
    if ((my_putstr("error: expression expected near '|'.\n", 2)) == -1)
      return (-1);
  return (error);
}

static int	check_semicolon(char *str)
{
  int		i;
  int		error;

  i = 0;
  error = 0;
  if (str[0] == ';')
    error = -1;
  while (str[i])
    {
      if ((str[i] == ';' && str[i + 1] && str[i + 2] == ';')
	  || (str[i] == ';' && str[i + 1] == ';'))
	error = -1;
      else if ((str[i] == ';' && str[i + 1] == '|')
	       || (str[i] == ';' && str[i + 1] && str[i + 2] == '|'))
	error = -1;
      else if ((str[i] == ';' && str[i + 1] == '&')
	       || (str[i] == ';' && str[i + 1] && str[i + 2] == '&'))
	error = -1;
      i += 1;
    }
  if (error == -1)
    if ((my_putstr("error: expression expected near ';'.\n", 2)) == -1)
      return (-1);
  return (error);
}

static int	check_and(char *str)
{
  int		i;
  int		error;

  i = 0;
  error = 0;
  if (str[0] == '&')
    error = -1;
  while (str[i])
    {
      if (str[i] == '&' && str[i + 1] == ' ' && str[i + 2] == '&')
	error = -1;
      else if ((str[i] == '&' && str[i + 1] == '|')
	       || (str[i] == '&' && str[i + 1] == ' ' && str[i + 2] == '|'))
	error = -1;
      else if ((str[i] == '&' && str[i + 1] == ';')
      	       || (str[i] == '&' && str[i + 1] == ' ' && str[i + 2] == ';'))
      	error = -1;
      if (my_strncmp(str + i, "&&&", 3) == 0)
	error = -1;
      i += 1;
    }
  if (error == -1 || (i > 1 && str[i - 1] == '&' && str[i - 2] == '&'))
    if ((my_putstr("error: expression expected near '&'.\n", 2)) == -1)
      return (-1);
  return (error);
}

int	check_str(char *to_check)
{
  char	*str;

  if (to_check == NULL)
    return (0);
  if ((str = my_strdup(to_check)) == NULL)
    return (-1);
  clean_str(str);
  if ((check_str_redi(str) == -1)
      || (check_pipe(str) == -1)
      || (check_semicolon(str) == -1)
      || (check_and(str) == -1))
    return (0);
  free(str);
  return (1);
}

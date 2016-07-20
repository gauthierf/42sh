/*
** clean_redirections.c for  in /home/fernan_w/Téléchargements/backup/parser
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:57:30 2016
** Last update Sun Jun  5 19:51:57 2016 retyt
*/

#include <stdlib.h>
#include "parser.h"
#include "tools.h"
#include "my.h"

void	clean_this_redirection(char *str)
{
  int	i;

  i = 0;
  while (str[i] && (str[i] == '>' || str[i] == '<'))
    {
      str[i] = ' ';
      i += 1;
    }
  while (str[i] && str[i] == ' ')
    i += 1;
  while (str[i] && str[i] != ' ' && str[i] != '|' && str[i] != '&'
	 && str[i] != ';')
    {
      str[i] = ' ';
      i += 1;
    }
}

void	clean_redirections(char *str)
{
  int	i;
  int	size;

  i = 0;
  size = my_strlen(str);
  while (str[i])
    {
      pass_var(str, &i);
      if (str[i] == '>' || str[i] == '<')
	clean_this_redirection(str + i);
      if (i >= size)
	return ;
      if (str[i])
	i += 1;
    }
}

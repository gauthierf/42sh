/*
** clean_str.c for  in /home/fernan_w/Téléchargements/backup/parser
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:58:09 2016
** Last update Sun Jun  5 19:13:50 2016 retyt
*/

#include "my.h"

static void	last_clean(char *str, int i)
{
  i -= 1;
  while (i > 0 && str[i] == ' ')
    {
      str[i] = 0;
      i -= 1;
    }
}

char	*clean_str(char *str)
{
  int	i;
  int	j;

  i = 0;
  while (str[i])
    {
      j = i;
      if (str[i] == '\t')
	str[i] = ' ';
      if ((str[i] == ' ' && (str[i + 1] == ' ' || str[i + 1] == '\t'))
	  || (i == 0 && str[i] == ' '))
	{
	  while (str[j])
	    {
	      str[j] = str[j + 1];
	      j += 1;
	    }
	  i -= 1;
	}
      i += 1;
    }
  last_clean(str, i);
  return (str);
}

int	is_bad_character(char *str)
{
  int	i;

  i = 0;
  while (str && str[i])
    {
      if (str[i] < 32 || str[i] > 126)
	if (str[i] != '\n' && str[i] != '\t')
	  return (str[i]);
      i += 1;
    }
  return (0);
}

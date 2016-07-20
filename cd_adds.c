/*
** cd_tools.c for  in /home/fernan_w/Téléchargements/backup/builtins
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:51:05 2016
** Last update Sun Jun  5 19:13:05 2016 retyt
*/

#include "tools.h"
#include "my.h"

char	*my_strcat_spe(char *var, char *str)
{
  int	i;
  int	n;

  i = my_strlen(str) + my_strlen(var) - 1;
  str[i + 1] = '\0';
  n = my_strlen(str) - 1;
  while (n >= 0)
    str[i--] = str[n--];
  n = 0;
  i = 0;
  while (var[n])
    str[i++] = var[n++];
  return (str);
}

int	char_only(char *str, char c)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (str[i] != c)
	return (0);
      ++i;
    }
  return (1);
}

void	fill_new_cd(char *new, char *str)
{
  int	i;
  int	n;

  i = 2;
  n = 2;
  new[0] = '.';
  new[1] = '.';
  while (str[i])
    {
      new[n++] = '/';
      new[n++] = '.';
      new[n++] = '.';
      ++i;
    }
  new[n] = '\0';
}

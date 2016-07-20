/*
** echo_tools.c for  in /home/fernan_w/Téléchargements/backup/builtins
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:51:27 2016
** Last update Sun Jun  5 19:50:23 2016 retyt
*/

#include <stdlib.h>
#include "my.h"

char	*clean_var(char *str)
{
  int	index;
  int	count;
  int	cursor;
  char	*temp;

  index = 0;
  if (!str)
    return (NULL);
  while (str && str[index] && str[index] != '=')
    index++;
  count = index + 1;
  while (str && str[index])
    index++;
  if (!(temp = malloc(sizeof(char) * (index - count + 1))))
    return (NULL);
  cursor = 0;
  while (str[count])
    temp[cursor++] = str[count++];
  temp[cursor] = '\0';
  return (temp);
}

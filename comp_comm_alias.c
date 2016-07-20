/*
** replace_alias.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:18:28 2016
** Last update Sun Jun  5 19:14:34 2016 retyt
*/

#include <stdlib.h>
#include "readline.h"
#include "tools.h"
#include "my.h"

char	*replace_alias(char *str, int cur, char *found)
{
  char	*new;
  int	i;
  int	j;

  if ((new = (char*)malloc(my_strlen(str) + my_strlen(found) + 2)) == NULL)
    return ((void*)(unsigned long)my_putstr("error: could not alloc\n", 1));
  i = 0;
  while (str[i] && i < cur)
    {
      new[i] = str[i];
      i += 1;
    }
  j = 0;
  while (found[j])
    new[i++] = found[j++];
  j = cur;
  while (str[j] && str[j] != ' ' && str[j] != ';' && str[j] != '|'
	 && str[j] != '&')
    j += 1;
  while (str[j])
    new[i++] = str[j++];
  new[i] = 0;
  free(str);
  return (new);
}

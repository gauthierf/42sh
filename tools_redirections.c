/*
** tools_redirections.c for  in /home/fernan_w/Téléchargements/backup/parser
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:59:00 2016
** Last update Sun Jun  5 19:54:14 2016 retyt
*/

#include <stdlib.h>
#include "parser.h"
#include "tools.h"
#include "readline.h"
#include "my.h"

char	*realloc_me_that(char *dest, char *src)
{
  char	*new_str;
  int	i;
  int	j;

  if ((new_str = (char*)malloc(my_strlen(dest) + my_strlen(src) + 2)) == NULL)
    {
      if ((my_putstr("error: could not alloc\n", 2)) == -1)
	return (NULL);
      return (NULL);
    }
  i = 0;
  j = 0;
  while (dest && dest[i])
    {
      new_str[i] = dest[i];
      i += 1;
    }
  if (dest || (src == NULL && dest != NULL))
    new_str[i++] = '\n';
  while (src && src[j++])
    new_str[i + j - 1] = src[j - 1];
  new_str[i + j - ((src != NULL) ? (1) : (0))] = '\0';
  free(dest);
  free(src);
  return (new_str);
}

int	is_same_strings(char *str, char *good_string)
{
  int	i;
  int	j;

  i = 0;
  if (str == NULL)
    return (0);
  while (str[i])
    i += 1;
  i -= 2;
  while (i > 0 && str[i] != '\n')
    i -= 1;
  i += 1;
  j = 0;
  while (str[i + j] && str[i + j] == good_string[j])
    j += 1;
  if (good_string[j] == '\0')
    return (1);
  return (0);
}

char	*rm_good_string(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    i += 1;
  i -= 2;
  while (i > 0 && str[i] != '\n')
    i -= 1;
  i += 1;
  while (str[i])
    {
      str[i] = '\0';
      i += 1;
    }
  return (str);
}

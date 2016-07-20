/*
** get_alias.c for  in /home/fernan_w/Téléchargements/backup/start
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:02:54 2016
** Last update Sun Jun  5 19:43:11 2016 retyt
*/

#include <stdlib.h>
#include "readline.h"
#include "tools.h"
#include "my.h"

static int	get_nb_stock(char **alias)
{
  int		nb;

  nb = 0;
  while (alias && alias[nb])
    nb += 1;
  return (nb);
}

static char	**get_alias(char *str, char **alias)
{
  char		**new;
  int		nb_stock;
  int		i;

  nb_stock = get_nb_stock(alias);
  if ((new = (char**)malloc(sizeof(char*) * (nb_stock + 2))) == NULL)
    {
      my_putstr("error: could not alloc\n", 2);
      return (NULL);
    }
  i = 0;
  while (alias && alias[i])
    {
      new[i] = alias[i];
      i += 1;
    }
  if ((new[i++] = my_strdup(str)) == NULL)
    return (NULL);
  new[i] = NULL;
  if (alias)
    free(alias);
  alias = new;
  return (alias);
}

int	check_alias(char *str)
{
  int	i;
  int	j;

  i = 0;
  while (str[i] && str[i] != '=')
    i += 1;
  if (i == 0 || str[i] == '\0')
    return (-1);
  i += 1;
  j = i;
  while (str[i])
    i += 1;
  if (j == i)
    return (-1);
  return (0);
}

char	*return_alias(char **alias, char *str)
{
  int	i;
  int	j;
  int	size;
  int	s_alias;

  i = 0;
  while (alias && alias[i] && str)
    {
      size = 0;
      s_alias = 0;
      j = 0;
      while (str[size] && str[size] != ' ' && str[size] != '|'
	     && str[size] != '&' && str[size] != ';')
	size += 1;
      while (alias[i][s_alias] && alias[i][s_alias] != '=')
	s_alias += 1;
      if (s_alias == size && my_strncmp(alias[i], str, size) == 0)
	{
	  while (alias[i][j] && alias[i][j] != '=')
	    j += 1;
	  return (&(alias[i][j + 1]));
	}
      i += 1;
    }
  return (NULL);
}

char		*alias(char *str, int is_init)
{
  static char	**alias = NULL;

  if (is_init == -1)
    {
      free_tab(alias);
      alias = NULL;
    }
  else if (is_init == 1)
    {
      if ((alias = get_alias(str, alias)) == NULL)
	return (NULL);
      return ("");
    }
  else
    return (return_alias(alias, str));
  return (NULL);
}

/*
** path_processing.c for  in /home/fernan_w/Téléchargements/backup/process
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:01:36 2016
** Last update Sun Jun  5 19:51:01 2016 retyt
*/

#include <stdlib.h>
#include "tools.h"
#include "my.h"

static int	next_single_path_len(char *path)
{
  int		i;

  i = 0;
  while (path[i])
    if (path[i++] == ':')
      return (i);
  return (i);
}

static int	path_len(char *path)
{
  int		i;
  int		len;

  i = 0;
  len = 0;
  while (path && path[i])
    if (path[i++] == ':')
      len++;
  return (len);
}

static char	**path_loop(char **res, char *path_str, int *x, int *j)
{
  int		i;

  i = 0;
  while (path_str[i])
    {
      if (path_str[i] == ':')
	{
	  if (res[*j][*x - 1] != '/')
	    res[*j][(*x)++] = '/';
	  res[*j][*x] = '\0';
	  *x = 0;
	  if (!(res[++(*j)] = malloc(next_single_path_len(path_str + ++i) + 2)))
	    return (NULL);
	}
      res[*j][(*x)++] = path_str[i++];
    }
  return (res);
}

char	**process_path(char **env)
{
  int	i;
  int	j;
  int	x;
  char	**res;
  char	*path_str;

  j = 0;
  x = 0;
  i = 0;
  if (!(path_str = find_str_in_tab("PATH", env))
      || !(res = malloc(sizeof(char *) * (path_len(path_str) + 2)))
      || !(res[j] = malloc(next_single_path_len(path_str) + 2)))
    return (NULL);
  while (path_str[i] && path_str[i++] != '=');
  res = path_loop(res, path_str + i, &x, &j);
  if (res[j][x - 1] != '/')
    res[j][x++] = '/';
  res[j][x] = '\0';
  res[++j] = NULL;
  return (res);
}

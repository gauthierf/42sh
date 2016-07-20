/*
** search_in_env.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:19:45 2016
** Last update Sun Jun  5 19:42:27 2016 retyt
*/

#include <stdlib.h>
#include "readline.h"
#include "tools.h"
#include "my.h"

char	*search_in_env(char **env, char *var)
{
  int	i;
  int	j;
  char	*value;
  int	size_var;

  i = 0;
  j = 0;
  value = NULL;
  if (env == NULL || env[0] == NULL)
    return (NULL);
  if ((size_var = my_strlen(var)) == 0)
    return (NULL);
  while (env && env[i] && my_strncmp(var, env[i], size_var) != 0)
    i += 1;
  if (env[i] == NULL)
    return (NULL);
  while (env[i] && env[i][j] && env[i][j] != '=')
    j += 1;
  j += 1;
  value = &(env[i][j]);
  return (value);
}

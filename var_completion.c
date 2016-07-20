/*
** var_completition.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:21:03 2016
** Last update Wed Jun  8 10:34:21 2016 
*/

#include <stdlib.h>
#include "readline.h"
#include "my.h"
#include "tools.h"

static int	get_size_var(char *var)
{
  int		size;

  size = 0;
  while (var[size] && var[size] != '=')
    size += 1;
  return (size);
}

static char	*copy_var(char *var)
{
  char		*tmp;
  int		size;
  int		i;

  size = get_size_var(var);
  if ((tmp = (char*)malloc(size + 2)) == NULL)
    return ((void*)(unsigned long)my_putstr("error: could not alloc\n", 2));
  tmp[0] = '$';
  i = 1;
  while (var[i - 1] && var[i - 1] != '=')
    {
      tmp[i] = var[i - 1];
      i += 1;
    }
  tmp[i] = 0;
  return (tmp);
}

int	search_var_env(char **env, t_completion **list, char *word)
{
  char	*tmp;
  int	i;

  i = 0;
  while (env && env[i])
    {
      if ((tmp = copy_var(env[i])) == NULL)
	return (-1);
      if (my_strncmp(tmp, word, my_strlen(word)) == 0)
	if ((push_completition(list, tmp)) == -1)
	  return (-1);
      free(tmp);
      i += 1;
    }
  return (0);
}

int	complete_history(t_rdd *reader, char *word, char *buf)
{
  int	i;
  char	tmp[2];

  i = my_strlen(word);
  tmp[1] = 0;
  while (i >= 0 && i < 7)
    {
      tmp[0] = buf[i];
      if ((get_char(reader, tmp)) == -1)
	return (-1);
      i += 1;
    }
  return (0);
}

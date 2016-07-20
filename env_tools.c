/*
** env_tools.c for  in /home/fernan_w/Téléchargements/backup/builtins
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:53:16 2016
** Last update Wed Jun  8 10:03:19 2016 
*/

#include <stdlib.h>
#include "tools.h"

void	add_str_end_env(t_mini *shell, char *str)
{
  int	index;
  int	val;

  val = my_tablen(shell->env);
  if (!(shell->env = realloc(shell->env, sizeof(char *) * (val + 2))))
    return ;
  shell->env[val + 1] = NULL;
  if (!(shell->env[val] = malloc(sizeof(char) * (my_strlen(str) + 1))))
    return ;
  index = 0;
  while (str[index])
    {
      shell->env[val][index] = str[index];
      index++;
    }
  shell->env[val][index] = '\0';
}

void	remplace_str_in_env(t_mini *shell, char *str, char *var)
{
  int	index;
  int	count;
  char	*ptr;

  count = 0;
  index = 0;
  ptr = find_str_in_tab(var, shell->env);
  while (shell->env[index] != ptr)
    index++;
  free(shell->env[index]);
  if (!(shell->env[index] = malloc(sizeof(char) * (my_strlen(str) + 1))))
    return ;
  while (str[count])
    {
      shell->env[index][count]= str[count];
      count++;
    }
  shell->env[index][count] = '\0';
}

int	get_new_size(int i, char **tab)
{
  int	size;

  size = 0;
  while (tab[++i])
    size += my_strlen(tab[i]) + 1;
  return (size);
}

void	get_new_cmd(char *new, int i, char **tab)
{
  int	n;
  int	j;

  n = 0;
  while (tab[i])
    {
      j = 0;
      while (tab[i][j])
	new[n++] = tab[i][j++];
      new[n++] = (tab[i + 1] != NULL) ? (' ') : ('\0');
      ++i;
    }
  return ;
}

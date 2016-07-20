/*
** remake_argv.c for  in /home/fernan_w/Téléchargements/backup/parser
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:58:30 2016
** Last update Wed Jun  8 10:09:18 2016 
*/

#include <stdlib.h>
#include "tools.h"
#include "shell.h"
#include "my.h"

void	rm_backslash_n(char *str)
{
  int	size;
  int	i;

  i = 0;
  while (str[i] && i < 512)
    {
      if (str[i] == '\n')
	str[i] = ' ';
      i += 1;
    }
  if ((size = my_strlen(str)) > 0 && str[size - 1] == '\n')
    str[size - 1] = 0;
}

static int	get_size_tab(char **arraw)
{
  int		size;

  size = 0;
  while (arraw && arraw[size])
    size += 1;
  return (size);
}

static void	get_ptr_argv(char **argv_new, t_process *proc, char **tab_new,
			     int cur)
{
  int		i;
  int		j;

  i = 0;
  while (i < cur)
    {
      argv_new[i] = proc->cmd_argv[i];
      i += 1;
    }
  j = 0;
  while (tab_new && tab_new[j])
    {
      argv_new[i] = tab_new[j];
      i += 1;
      j += 1;
    }
  j = cur + 1;
  while (proc->cmd_argv[j])
    {
      argv_new[i] = proc->cmd_argv[j];
      i += 1;
      j += 1;
    }
  argv_new[i] = NULL;
}

char		**remake_argv(t_process *proc, int cur, char *new)
{
  char		**argv_new;
  char		**tab_new;
  int		size;

  rm_backslash_n(new);
  if ((tab_new = my_str_to_wordtab(new)) == NULL)
    return (NULL);
  size = get_size_tab(proc->cmd_argv);
  size += get_size_tab(tab_new) + 1;
  if ((argv_new = (char**)malloc(sizeof(char*) * size)) == NULL)
    return (NULL);
  get_ptr_argv(argv_new, proc, tab_new, cur);
  free(tab_new);
  free(new);
  return (argv_new);
}

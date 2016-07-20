/*
** do_globbing.c for  in /home/fernan_w/Téléchargements/backup/process
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:00:41 2016
** Last update Wed Jun  8 10:14:31 2016 
*/

#include <glob.h>
#include <stdlib.h>
#include "shell.h"
#include "tools.h"
#include "my.h"

static char	**put_tab_end(char **res, char **proc_tab, int i, int p_len)
{
  while (proc_tab && proc_tab[++p_len])
    {
      res[i] = my_strdup(proc_tab[p_len]);
      ++i;
    }
  res[i] = NULL;
  return (res);
}

static char	**put_glob_res(char **gl_tab, char **proc_tab,
			       int gl_len, int p_len)
{
  int		i;
  int		j;
  char		**res;

  i = 0;
  j = 0;
  if (!(res = malloc(sizeof(char *) * (my_tablen(proc_tab) + gl_len + 1))))
    return (NULL);
  while (proc_tab && proc_tab[i] && i < p_len)
    {
      res[i] = my_strdup(proc_tab[i]);
      ++i;
    }
  while (gl_tab && gl_tab[j] && j < gl_len)
    {
      res[i] = my_strdup(gl_tab[j]);
      ++j;
      ++i;
    }
  res = put_tab_end(res, proc_tab, i, p_len);
  free_tab(proc_tab);
  return (res);
}

int		put_glob(t_process *proc, int *i)
{
  int		err;
  glob_t	globbuf;

  if ((err = glob(proc->cmd_argv[(*i)], MYGLOBFLAG, NULL, &globbuf) != 0))
    return (FAILURE);
  if (!(proc->cmd_argv = put_glob_res(globbuf.gl_pathv, proc->cmd_argv,
				      globbuf.gl_pathc, (*i))))
    return (FAILURE);
  (*i) += globbuf.gl_pathc;
  globfree(&globbuf);
  return (SUCCESS);
}

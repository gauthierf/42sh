/*
** builtins.c for  in /home/fernan_w/Téléchargements/backup/builtins
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:52:08 2016
** Last update Wed Jun  8 10:55:26 2016 
*/

#include <string.h>
#include "tools.h"
#include "builtins.h"
#include "my.h"

static const t_opec	g_bul[] =
   {
     {"exit", &my_exit},
     {"cd", &my_cd},
     {"fg", &my_fg},
     {"bg", &my_bg},
     {"jobs", &my_jobs},
     {"unset", &my_unset},
     {"export", &my_export},
     {"disown", &my_disown},
     {"source", &my_source},
     {"env", &my_env},
     {"echo", &my_echo},
     {NULL, NULL},
   };

int	builtins(t_mini *shell, t_process *proc)
{
  if (g_bul[proc->is_builtin].str)
    return (g_bul[proc->is_builtin].funct(shell, proc));
  else
    return (my_egal_env(shell, proc));
}

int	check_builtins(t_process *proc)
{
  int	index;

  index = 0;
  proc->is_builtin = -1;
  while (g_bul[index].str)
    {
      if (proc->cmd && strcmp(proc->cmd, g_bul[index].str) == 0)
	{
	  proc->is_builtin = index;
	  return (SUCCESS);
	}
      index++;
    }
  if (is_in_str(proc->cmd, '=') == SUCCESS)
    {
      proc->is_builtin = index;
      return (SUCCESS);
    }
  return (FAILURE);
}

int	built_no_fork(t_process *proc, t_mini *shell)
{
  if (proc->is_builtin < MAX_BUILT_FORK - 1)
    return (g_bul[proc->is_builtin].funct(shell, proc));
  else
    return (builtins(shell, proc));
}

/*
** exit.c for  in /home/fernan_w/Téléchargements/backup/builtins
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:54:26 2016
** Last update Wed Jun  8 09:26:28 2016 
*/

#include <unistd.h>
#include "jobs.h"
#include "builtins.h"
#include "my.h"

static int	wave_goodbye_to_the_kids()
{
  int		i;

  i = 0;
  while (i < g_background.max_job_count)
    {
      if (g_background.active_jobs[i]
	  && g_background.active_jobs[i]->disowned == FAILURE)
	if (kill(g_background.active_jobs[i]->pid, SIGHUP) == -1)
	  return (FAILURE);
      i++;
    }
  return (SUCCESS);
}

static int	pre_exit_check()
{
  char		c;

  if (g_background.active_jobs_count > 0)
    {
      my_print_error("You have suspended jobs, exit? [y/N] ");
      if (read(0, &c, 1) == 1)
	{
	  if (c == 'Y' || c == 'y')
	    return (wave_goodbye_to_the_kids());
	  else
	    return (FAILURE);
	}
      my_print_error("\n");
    }
  return (SUCCESS);
}

int	my_exit(t_mini *shell, t_process *proc)
{
  int	nb;

  (void)shell;
  if (pre_exit_check() == FAILURE)
    return (SUCCESS);
  if (!(proc->cmd_argv[1]))
    shell->need_exit = 0;
  else
    {
      nb = my_getnbr(proc->cmd_argv[1]);
      nb = (unsigned char)nb;
      shell->need_exit = nb;
    }
  return (SUCCESS);
}

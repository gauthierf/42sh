/*
** jobs.c for  in /home/fernan_w/Téléchargements/backup/builtins
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:54:59 2016
** Last update Wed Jun  8 10:01:09 2016 
*/

#include <stdlib.h>
#include "jobs.h"
#include "builtins.h"
#include "my.h"

static void	simple_job_list()
{
  int		i;

  i = 0;
  while (i < g_background.max_job_count)
    {
      if (g_background.active_jobs[i])
	my_printf("[%d] running %s\n", i, g_background.active_jobs[i]->cmd);
      ++i;
    }
}

static void	precise_info(int job_id)
{
  my_printf("[%d] %d running  %s\n",
	    job_id, g_background.active_jobs[job_id]->pid,
            g_background.active_jobs[job_id]->cmd);
}

int	my_jobs(t_mini *shell, t_process *proc)
{
  int	job_id;

  (void)shell;
  proc->status = 0;
  if (!(proc->cmd_argv[1]))
    simple_job_list();
  else if (proc->cmd_argv[1] && (job_id = my_getnbr(proc->cmd_argv[1])) >= 0
	   && job_id < g_background.active_jobs_count)
    precise_info(job_id);
  else if (proc->cmd_argv[1])
    {
      proc->status = 1;
      my_print_error("jobs: no such job [%s]\n", proc->cmd_argv[1]);
      return (SUCCESS);
    }
  return (SUCCESS);
}

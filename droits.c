/*
** disown.c for  in /home/fernan_w/Téléchargements/backup/builtins
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:52:41 2016
** Last update Wed Jun  8 09:17:19 2016 
*/

#include "jobs.h"
#include "my.h"

int	my_disown(t_mini *shell, t_process *proc)
{
  int	job_id;

  (void)shell;
  proc->status = 0;
  job_id = -1;
  if (g_background.active_jobs_count == 0)
    {
      my_print_error("disown: no jobs to disown\n");
      proc->status = 1;
      return (SUCCESS);
    }
  if (!(proc->cmd_argv[1]) && g_background.active_jobs_count > 0
      && g_background.active_jobs[g_background.active_jobs_count - 1])
    job_id = g_background.active_jobs_count - 1;
  else if (proc->cmd_argv[1] && ((job_id = my_getnbr(proc->cmd_argv[1])) < 0
				 || job_id >= g_background.active_jobs_count))
    my_print_error("disown: no such job [%s]\n", proc->cmd_argv[1]);
  if (job_id > -1 && job_id < g_background.active_jobs_count)
    g_background.active_jobs[job_id]->disowned = SUCCESS;
  return (SUCCESS);
}

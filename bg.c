/*
** bg.c for  in /home/fernan_w/Téléchargements/backup/builtins
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:50:50 2016
** Last update Wed Jun  8 09:16:08 2016 
*/

#include "jobs.h"
#include "my.h"

static int	no_jobs(t_process *proc)
{
  my_print_error("bg: no jobs to resume\n");
  proc->status = 1;
  return (SUCCESS);
 }

int	my_bg(t_mini *shell, t_process *proc)
{
  int	job_id;

  (void)shell;
  job_id = -1;
  proc->status = 0;
  if (g_background.active_jobs_count == 0)
    return (no_jobs(proc));
  if (!(proc->cmd_argv[1]) && g_background.active_jobs_count > 0
      && g_background.active_jobs[g_background.active_jobs_count - 1])
    job_id = g_background.active_jobs_count - 1;
  else if (proc->cmd_argv[1] && ((job_id = my_getnbr(proc->cmd_argv[1])) < 0
				 || job_id >= g_background.active_jobs_count))
    my_print_error("42sh: no such job [%s]\n", proc->cmd_argv[1]);
  if (job_id > -1 && job_id < g_background.active_jobs_count)
    {
      g_background.active_jobs[job_id]->mode = BACKGROUND;
      if (put_to_background(g_background.active_jobs[job_id], 0) == FAILURE)
	my_print_error("bg: putting to background failed\n");
    }
  return (SUCCESS);
}

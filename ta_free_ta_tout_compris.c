/*
** free_proc.c for  in /home/fernan_w/Téléchargements/backup/process
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:00:10 2016
** Last update Wed Jun  8 10:58:01 2016 
*/

#include <stdlib.h>
#include "shell.h"
#include "tools.h"
#include "my.h"

static t_output	*copy_output(t_process *proc)
{
  t_output	*newout;

  if (!(newout = malloc(sizeof(t_output))))
    return (FAILURE);
  newout->is_pipe = proc->output->is_pipe;
  newout->file = NULL;
  newout->append_or_not = FAILURE;
  newout->next = NULL;
  return (newout);
}

t_process	*proc_copy(t_process *proc)
{
  t_process	*p_copy;

  if (!(p_copy = malloc(sizeof(t_process))))
    return (NULL);
  p_copy->cmd = my_strdup(proc->cmd);
  p_copy->cmd_argv = my_tab_copy(proc->cmd_argv);
  p_copy->path_cmd = my_strdup(proc->path_cmd);
  p_copy->pid = proc->pid;
  p_copy->pgid = proc->pgid;
  p_copy->outfd = proc->outfd;
  p_copy->infd = proc->infd;
  p_copy->mode = proc->mode;
  p_copy->status = proc->status;
  p_copy->disowned = proc->disowned;
  p_copy->output = NULL;
  if (proc->output && proc->output->is_pipe == SUCCESS)
    p_copy->output = copy_output(proc);
  p_copy->input = NULL;
  p_copy->next = NULL;
  p_copy->prev = NULL;
  return (p_copy);
}

void		free_proc(t_process *proc)
{
  t_input	*tmpin;
  t_input	*tmpin1;

  if (proc->cmd_argv)
    free_tab(proc->cmd_argv);
  free(proc->cmd);
  free(proc->path_cmd);
  tmpin = proc->input;
  while (tmpin)
    {
      if (tmpin->file)
	free(tmpin->file);
      if (tmpin->heredoc)
	free(tmpin->heredoc);
      tmpin1 = tmpin;
      tmpin = tmpin->next;
      free(tmpin1);
    }
  if (proc->output)
    {
      if (proc->output->file)
	free(proc->output->file);
      free(proc->output);
    }
}

t_process	*super_proc(t_process *proc)
{
  t_process	*temp;

  temp = proc->next;
  free_proc(proc);
  free(proc);
  return (temp);
}

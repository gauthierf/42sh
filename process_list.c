/*
** list_proc.c for  in /home/fernan_w/Téléchargements/backup/parser
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:57:14 2016
** Last update Wed Jun  8 10:19:11 2016 
*/

#include <stdlib.h>
#include "readline.h"
#include "parser.h"
#include "tools.h"
#include "my.h"

static int	select_mode(char *mode)
{
  if (my_strncmp(mode, "&&", 2) == 0)
    return (IF_OK);
  else if (my_strncmp(mode, "&", 1) == 0)
    return (BACKGROUND);
  else if (my_strncmp(mode, "||", 2) == 0)
    return (IF_ERR);
  return (FAILURE);
}

static t_process	*create_proc(char *cmd, char *mode, t_process *prev)
{
  t_process		*new;

  if ((new = (t_process*)malloc(sizeof(*new))))
    {
      new->cmd = cmd;
      new->cmd_argv = NULL;
      new->path_cmd = NULL;
      new->pid = FAILURE;
      new->pgid = FAILURE;
      new->outfd = FAILURE;
      new->infd = FAILURE;
      new->mode = select_mode(mode);
      new->status = FAILURE;
      new->disowned = FAILURE;
      new->output = NULL;
      new->input = NULL;
      new->next = NULL;
      new->prev = prev;
    }
  else
    if ((my_putstr("error: could not alloc\n", 2)) == -1)
      return (NULL);
  return (new);
}

int		push_proc(t_process **proc, char *cmd, char *mode,
			  t_process **tmp_proc)
{
  t_process	*tmp;

  tmp = *proc;
  if (tmp)
    {
      while (tmp->next)
	tmp = tmp->next;
      if ((tmp->next = create_proc(cmd, mode, tmp)) == NULL)
	return (-1);
      tmp = tmp->next;
    }
  else
    {
      if ((*proc = create_proc(cmd, mode, NULL)) == NULL)
	return (-1);
      tmp = *proc;
    }
  if ((my_strcmp(mode, "|")) == 0)
    if (push_output(&(tmp->output), NULL, 0, SUCCESS) == -1)
      return (-1);
  if (tmp->prev && tmp->prev->output && tmp->prev->output->is_pipe == SUCCESS)
    if (push_input(&(tmp->input), NULL, NULL, SUCCESS) == -1)
      return (-1);
  *tmp_proc = tmp;
  return (0);
}

/*
** cd.c for  in /home/fernan_w/Téléchargements/backup/builtins
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:53:46 2016
** Last update Wed Jun  8 09:41:52 2016 
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "builtins.h"
#include "tools.h"
#include "my.h"

static int	change_dir(char *arg, t_mini *shell, char *old)
{
  char		*str;
  int		i;

  str = NULL;
  if (arg == NULL)
    if ((str = get_homedir()) == NULL)
      return (my_print_error("42sh: cd: HOME not set\n") - 1);
  if (arg && strcmp(arg, "-") == 0)
    if ((str = clean_var(find_str_in_tab("OLDPWD", shell->env))) == NULL)
      return (my_print_error("42sh: cd: OLDPWD not set\n") - 1);
  if (access((str != NULL) ? (str) : (arg), F_OK) == -1)
    i = my_print_error("42sh: cd: No such file or directory\n") - 1;
  else if (access((str != NULL) ? (str) : (arg), R_OK) == -1)
    i = my_print_error("42sh: cd: Permission denied\n") - 1;
  else
    i = chdir((str != NULL) ? (str) : (arg));
  if (str)
    free(str);
  if (i == -1)
    free(old);
  return (i);
}

static int	new_value(t_mini *shell, char *str, char *var, char *new_var)
{
  int		size;

  size = my_strlen(str) + my_strlen(new_var) + 1;
  if ((str = realloc(str, size * sizeof(*str))) == NULL)
    return (-1);
  if (!(find_str_in_tab(var, shell->env)))
    add_str_end_env(shell, str = my_strcat_spe(new_var, str));
  else
    remplace_str_in_env(shell, str = my_strcat_spe(new_var, str), var);
  free(str);
  return (0);
}

static char	*change_cd_path(char *str)
{
  int		size;
  char		*new;

  if (char_only(str, '.') == 0)
    return (str);
  if ((size = my_strlen(str)) == 2 || size == 1)
    return (str);
  size = my_strlen(str) - 2;
  size = 2 + (size * 3) + 1;
  if ((new = malloc(size * sizeof(*new))) == NULL)
    return (NULL);
  fill_new_cd(new, str);
  free(str);
  return (new);
}

static int	my_baby_cd(t_mini *shell, t_process *proc)
{
  char		*new;
  char		*old;

  proc->status = 1;
  if (proc->cmd_argv[1] != NULL &&
      (proc->cmd_argv[1] = change_cd_path(proc->cmd_argv[1])) == NULL)
    return (EXIT_FAILURE);
  if ((old = getcwd(NULL, 0)) == NULL)
    return (EXIT_FAILURE);
  if (change_dir(proc->cmd_argv[1], shell, old) == -1)
    return (EXIT_FAILURE);
  if ((new = getcwd(NULL, 0)) == NULL ||
      new_value(shell, new, "PWD", "PWD=") == -1 ||
      new_value(shell, old, "OLDPWD", "OLDPWD=") == -1)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int	my_cd(t_mini *shell, t_process *proc)
{
  proc->status = my_baby_cd(shell, proc);
  return (SUCCESS);
}

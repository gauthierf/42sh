/*
** replace_var_in_str.c for  in /home/fernan_w/Téléchargements/backup/process
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:01:15 2016
** Last update Wed Jun  8 10:00:01 2016 
*/

#include <stdlib.h>
#include "builtins.h"
#include "tools.h"
#include "shell.h"
#include "my.h"

static char	*get_var_name(char *str, int nb)
{
  int		index;
  char		*name;

  index = nb;
  while (str && str[index] && str[index] != ' ' && str[index] != '/'
	 && str[index] != '$' &&  str[index] != '=' && str[index] != ':')
    index++;
  if (!(name = malloc(sizeof(char *) * (index - nb + 1))))
    return (NULL);
  name[index - nb] = '\0';
  index = 0;
  while (str && str[nb] && str[nb] != ' ' && str[nb] != '='
	 && str[nb] != '$' && str[nb] != ':' && str[nb] != '/')
    name[index++] = str[nb++];
  return (name);
}

static char	*get_var_replace(char *name, t_mini *shell)
{
  char		*ptr;

  if (!(ptr = find_str_in_tab(name, shell->env)))
    if (!(ptr = find_str_in_tab(name, shell->secret_env)))
      return (NULL);
  return (clean_var(ptr));
}

static char	*replace_val_in_str(char *str, char *name, char *val, int nb)
{
  char		*temp;
  int		index;
  int		cursor;

  if (!( temp = malloc(sizeof(char *) *(my_strlen(str) + my_strlen(val) + 1
					- my_strlen(name)))))
    return (NULL);
  index = 0;
  cursor = 0;
  while (index < nb)
    temp[index++] = str[cursor++];
  nb = 0;
  while (val && val[nb])
    temp[index++] = val[nb++];
  cursor += my_strlen(name) + 1;
  while (str && str[cursor])
    temp[index++] = str[cursor++];
  temp[index] = '\0';
  free(name);
  free(val);
  free(str);
  return (temp);
}

char	*replace_var_in_str(char *str, t_mini *shell)
{
  int	nb;
  char	*name;
  char	*val;

  while (str && (nb = have_var(str)) != -1)
    {
      name = get_var_name(str, nb + 1);
      val = get_var_replace(name, shell);
      str = replace_val_in_str(str, name, val, nb);
    }
  return (str);
}

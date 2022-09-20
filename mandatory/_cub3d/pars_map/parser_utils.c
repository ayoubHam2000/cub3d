#include "cub3d.h"

// print data

void print_data_h(t_prog **data)
{
    printf ("res---> {%p} \n", (data));
    int i = 0;
    t_prog *tmp = *data;
    printf ("================ text =================\n");
    while (i < 4)
    {
        printf("{%s}\n", tmp->tex[i]->tex);
        i++;
    }
       printf ("res---> {%s} \n", (*data)->player.map[0]); 
    printf ("=============== floor =============== \n");
    i = 0;
    while (i < 2)
    {
        printf ("{%d}\n", tmp->floor[i]);
        i++;
    }
    printf ("============== map ==================\n");
    printf ("{%s}\n", tmp->player.map[0]);
}

// put data
void free_and_alloc (char **tmp)
{
    char *new;
    if (*tmp != NULL)
        free (*tmp);
    new = malloc (sizeof (char) * 1);
    new[0] = '\0';
    *tmp = new;
}

// change the char to string
char *change_char_to_string (char c)
{
    char *tmp;
    tmp = ft_malloc (sizeof(char) * 2);
    if (tmp == NULL)
        return (NULL);
    tmp[0] = c;
    tmp[1] = '\0';
    return (tmp);
}

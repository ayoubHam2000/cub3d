#include "cub3d.h"

// read the file 
char *parse_file_to_string (int fd)
{
    char *new;
    char *tmp;
    char  *line;
    
    new = ft_malloc (sizeof (char));
    new[0] = '\0';
    line = get_next_line (fd);
    while (line != NULL)
    {
        tmp = line;
        new = ft_strjoin (new, tmp);
        free (line);
        line = get_next_line(fd);
    }
    return (new);
}

void parse_floor(t_prog **data, char *line, int *i)
{
    int j = 0;
    char *tmp;
    printf ("res---> {%d}\n", *i);
    while (j < 2)
    {
        free_and_alloc (&tmp);
        while (line[*i] != '\n')
        {
            if (line[*i] != ' ')
                tmp = ft_strjoin (tmp, change_char_to_string (line[*i]));
            (*i)++;
        }
        (*data)->floor[j] = ft_atoi(tmp);
        *i += 2;
        j++;
    }
    while (line[++(*i)] == '\n');
}

void parse_map (t_prog **data, char *line, int *i)
{
    char *tmp = NULL;

    free_and_alloc (&tmp);
    while (line[*i])
    {
        if (line[*i] == '\n' && line[*i + 1] == '\n')
        {
            printf("Error \n");
            return ;
        }
        tmp = ft_strjoin(tmp, change_char_to_string (line[*i]));
        (*i)++;
    }
    ft_addrs_exclude (tmp);
    (*data)->player.map = &tmp;
}

void parser_textrure (t_prog **data, char *line, int *i)
{
    char *tmp;
    t_tex  *tex = malloc (sizeof(t_tex));
    int j = 0;
    tmp = NULL;
    while (j < 4)
    {
        free_and_alloc (&tmp);
        while (line[*i]  != '\n')
        {
            if (line[*i] != ' '){
                tmp = ft_strjoin (tmp, change_char_to_string(line[*i]));
            }
            (*i)++;
        }
        (*data)->tex[j] = put_texture (*data, tmp);
        while (line[++(*i)] == '\n') ;
        *i += 2;
        j++;
    }
}

void parse_file(t_prog *data, char *s)
{
    char *line;
    int i = 2;
    int fd = open (s, O_RDONLY);
    if (fd == -1) 
        return ;
    line = parse_file_to_string(fd);
    parser_textrure (&data, line, &i);
    parse_floor (&data, line, &i);
    parse_map (&data, line, &i);
    print_data_h (&data);
}
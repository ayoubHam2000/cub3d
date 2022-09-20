#include "cub3d.h"
t_tex *put_texture (t_prog *data, char *path)
{
    t_tex *tex;
    if (path == NULL)
        return (NULL) ;
    tex = malloc (sizeof (t_tex));
    if (tex == NULL)
        return (NULL);
    tex->tex = mlx_xpm_file_to_image (data->mlx, path, &tex->width, &tex->height);
    if (tex->tex == NULL)
        return (NULL);
    tex->ptr = mlx_get_data_addr (tex->tex, &tex->bpp, &tex->size_line, &tex->endian);
    if (tex->ptr == NULL)
        return (NULL);

    return (tex);
}

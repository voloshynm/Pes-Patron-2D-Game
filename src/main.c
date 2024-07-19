/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:33:00 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/06/12 19:33:07 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/so_long.h"

int	main(int argc, char **argv)
{
	t_game	g;

	g.game_name = WINDOW_NAME;
	g.sprite_size = SPRITE_SIZE;
	init_game(&g, argc, argv);
	while (g.state == IN_PLAY)
		update_game(&g);
	game_over(&g);
	free_game(&g);
/*	(void) argc;
	(void) argv;

    char cwd[1024];
    void *mlx_ptr;
    void *img;
    int sprite_size = 32;

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working directory: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }

    mlx_ptr = mlx_init();
    if (mlx_ptr == NULL) {
        fprintf(stderr, "Error: mlx_init failed.\n");
        return 1;
    }

    printf("Trying to load image from: %s\n", "2.xpm");
    img = mlx_xpm_file_to_image(mlx_ptr, "2.xpm", &sprite_size, &sprite_size);
    if (img == NULL) {
        fprintf(stderr, "Error: mlx_xpm_file_to_image failed.\n");
        return 1;
    }

    printf("Image loaded successfully.\n");
    return 0;
*/
}

# cub3d
![Passed Cub3D with 115](https://github.com/byaliego/42-project-badges/blob/main/badges/cub3dm.png)

Passed with **115**/100

cub3d is a project that challenges you to recreate game history. Your goal is to build a simple pseudo-3D-game using an approach called ray casting. This has been pioneered in 1993 by id Software with the title [Wolfenstein 3D](https://github.com/id-Software/wolf3d) (depending on your age you might know its successors [Return to Castle Wolfenstein](https://github.com/id-Software/RTCW-SP), Wolfenstein: New Order or even its predecessor Castle Wolfenstein).

Ray casting allows you to render 2D images of simple 3D scenes. For the full explanation, have a look at the linked tutorials in the resources section.

The project requires you to use the [minilibx](https://github.com/42Paris/minilibx-linux) library by 42 Paris. There's an improved (and better documented) version by Codam (42 Amsterdam) called [MLX42](https://github.com/codam-coding-college/MLX42), but if it's allowed to use is up to your local Bocal (ask them if you're not sure). There's only a limited set of functions permitted in general:

- all functions of miniLibX and math library

- system functions for files: open, close, read, write

- functions for printing output (mainly used for error handling): printf, perror, strerror

- functions for memory management and process termination: malloc, free and exit



## Resources

[Lode's tutorial on Raycasting](https://lodev.org/cgtutor/raycasting.html): probably the best tutorial on raycasting out there, with code examples step by step (links provided as list here, part 4 is linked on the [main page](https://lodev.org/cgtutor/), but somehow not on part 3)

- [Part 1: basics, untextured and textured walls](https://lodev.org/cgtutor/raycasting.html)

- [Part 2: floor and ceiling](https://lodev.org/cgtutor/raycasting2.html)

- [Part 3: sprites](https://lodev.org/cgtutor/raycasting3.html)

- [Part 4: important for bonus, directional sprites, doors, enemies and more](https://lodev.org/cgtutor/raycasting4.html)

Could also be useful for some, if you haven't worked with it on so_long: [Lode's tutorial on floodfill](https://lodev.org/cgtutor/floodfill.html). Many colleagues from other campuses recommended the [Permadi tutorial on Raycasting](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/), but it uses only the angle instead of vectors for the looking direction, which I found harder to use.

I highly recommend the [Game Engine Black Book: Wolfenstein 3D, 2nd Edition](https://fabiensanglard.net/gebbwolf3d/) by Fabien Sanglard, which documents the whole development process of Wolfenstein 3D from a technical perspective. Additionally, if you're into game history, read [DOOM Guy: Life in First Person](https://romero.com/shop/p/doomguy) by John Romero, written by one of the founders of id Software.

[Coding Train](https://www.youtube.com/watch?v=vYgIKn7iDH8) has a helpful explanation how raycasting works, but his code examples are in JS. The video series by [3DSage](https://www.youtube.com/watch?v=gYRrGTC7GtA) is closer to the subject of cub3d because it uses C and OpenGL. There's also a [course by Pikuma](https://pikuma.com/courses/raycasting-engine-tutorial-algorithm-javascript) which has been highly recommended, but it's 60 USD for enrolling.

## MLX specific resources

- [Notions mathématiques du projet Cub3D](https://docs.google.com/document/d/1tdNYHg3Mfqf8dr8W6Ajs3seUugwtmaQizZ7BzimkXog/edit): found on Slack, wonderful explanation of raycasting as required for this project, unfortunately only in french
- [42 specific resources for mlx and 3D projects](https://github.com/qst0/ft_libgfx)
- [FdF cookbook, contains a lot of information on hooks](https://stackoverflowteams.com/c/42network/questions/164)
- [Getting started with mlx](https://aurelienbrabant.fr/blog/getting-started-with-the-minilibx): basic, but very helpful if you haven't worked with mlx in a while
- [Blog post on using animated sprites in mlx](http://pulgamecanica.herokuapp.com/posts/mlx-animations)


## Testers

- [Cub3D Leaks Maps Tester](https://github.com/mlaraki/cub3D_leaks_maps_tester): outdated, but contains some test maps that can be repurposed (but remove the resolution line at the top)

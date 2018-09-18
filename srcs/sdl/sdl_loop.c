#include "../../includes/wolf3d.h"

static void catch_event(t_sdl *sdl)
{
    while (SDL_PollEvent(&(sdl->event)))
    {
        if (sdl->event.type == SDL_QUIT)
            sdl->quit = 0;
        if (sdl->event.type == SDL_KEYDOWN)
        {
            sdl->input.key = SDL_GetKeyboardState(NULL);
        }
    }
}

static void render(t_sdl *sdl)
{
    draw(sdl);
    SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255);
    SDL_RenderClear(sdl->renderer);
	SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
	SDL_RenderPresent(sdl->renderer);
    if (sdl->texture)
    {
        SDL_DestroyTexture(sdl->texture);
        sdl->texture = NULL;
    }
   }

static void update_logic(t_sdl *sdl, double dt)
{
    if (sdl->input.key)
    {
        if (sdl->input.key[SDL_GetScancodeFromKey(SDLK_LEFT)])
            rotate_player(sdl, dt, ROT_LEFT);
        if (sdl->input.key[SDL_GetScancodeFromKey(SDLK_RIGHT)])
            rotate_player(sdl, dt, ROT_RIGHT);
        if (sdl->input.key[SDL_GetScancodeFromKey(SDLK_UP)])
            move_player(sdl, dt);
    }
    raycast(sdl);
}

void     start_loop(int enableshowfps, t_sdl *sdl)
{
    t_sdl_loop loop;

    ft_bzero(&loop, sizeof(t_sdl_loop));
    loop.current_time = (double)clock();
    loop.dt = 1.0 / LOGIC_STEP;
    while (sdl->quit)
    {
        catch_event(sdl);
        loop.new_time = clock();
        loop.frametime = (double)(loop.new_time - loop.current_time) / CLOCKS_PER_SEC;
        if (loop.frametime > 0.25)
            loop.frametime = 0.25;
        loop.current_time = loop.new_time;
        loop.accumulator += loop.frametime;
        while (loop.accumulator >= loop.dt)
        {
            update_logic(sdl, loop.dt);
            loop.accumulator -= loop.dt;
        }
        if (enableshowfps)
        {
            system("clear");
            printf("FPS : %d\n", (int)(1.0 / loop.frametime));
        }
        render(sdl);
    }
    exitprogram_evt(sdl);
}

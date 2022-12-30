#include "Functions/motion.hpp"
#include "Functions/Initialize.hpp"
#include "Functions/values.hpp"

int main(int argv, char **args)
{
    // Initializations
    init_please();
    SDL_Renderer *rend = SDL_CreateRenderer(o, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    Mix_PlayMusic(music, -1);

    // render Game Over texture
    CreateRect(ScoreBoardRect, 50, 50, 0, 0);

    make_it(rend);

    while (game_running == true and i)
    {
        Game_Menu.render_menu(rend);

        myDeclare(i);

        while (i)
        {
            SDL_Delay(15);
            SDL_RenderCopy(rend, bg_texture, NULL, NULL);
            spaceship_game.border_limits();
            kahini_1();
            bulleter_kahini(rend);
            final_kahini(rend);
            SDL_RenderClear(rend);

            if (player_dead == true)
            {
                break;
            }
        }

        if (i)
        {
            GameOver.print_final(rend);
        }
    }

    SDL_DestroyWindow(o);
    SDL_DestroyRenderer(rend);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
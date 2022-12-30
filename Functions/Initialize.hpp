#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
bool game_running = true;

SDL_Window *o;
SDL_Event e;
SDL_Rect ScoreBoardRect;
SDL_Rect GameOverScore;
SDL_Rect HighScoreRect;

SDL_Surface *surface;

SDL_Texture *bg_texture;
SDL_Texture *GameOver_texture;
SDL_Texture *bullet_texture;
SDL_Texture *explosion_texture;
SDL_Texture *asteroid_texture;
SDL_Texture *spaceship;
SDL_Texture *menu_img;
SDL_Texture *final_img;
SDL_Texture *FinalScoretexture;
SDL_Texture *HighScoreTexture;
SDL_Texture *instructions_screen;

spaceship_class spaceship_game;
bullet shot[shot_limit];
asteroid obstacle[asteroid_limit];
SDL_Rect SpaceshipRect;
int i = 1;
int j = 1;

Mix_Music *music;
TTF_Font *font;
SDL_Color white, white1;
char points[10];
char lives[10];

// if_else declaration
SDL_Texture *PointTexture;
SDL_Texture *LivesTexture;
SDL_Texture *ReloadingTexture;

bool player_dead = false;
int PlayerScoreGame = 0;

void CreateRect(SDL_Rect &a, int l1, int w1, int x1, int y1)
{
    a.x = x1;
    a.y = y1;
    a.h = l1;
    a.w = w1;
}

class game_over
{
public:
    void print_final(SDL_Renderer *rend)
    {
        SDL_RenderCopy(rend, final_img, NULL, NULL);
        j = 1;
        i = 1;

        CreateRect(GameOverScore, 50, 40, 300, 85);
        CreateRect(HighScoreRect, 50, 40, 300, 180);

        white1 = {255, 255, 255, 255};
        char score[20];
        char highscore[20];
        snprintf(score, sizeof(score), "%d", PlayerScoreGame);
        cout << PlayerScoreGame << endl;

        FILE *file = fopen("High_Score.txt", "r");
        if (file == NULL)
        {
            cout << "chudi" << endl;
        }
        int high_score;
        fscanf(file, "%d", &high_score);
        fclose(file);
        cout << high_score << endl;
        // high score
        high_score = max(high_score, PlayerScoreGame);
        snprintf(highscore, sizeof(highscore), "%d", high_score);

        surface = TTF_RenderText_Solid(font, score, white1);
        FinalScoretexture = SDL_CreateTextureFromSurface(rend, surface);
        SDL_RenderCopy(rend, FinalScoretexture, NULL, &GameOverScore);
        SDL_FreeSurface(surface);

        surface = TTF_RenderText_Solid(font, highscore, white1);
        HighScoreTexture = SDL_CreateTextureFromSurface(rend, surface);
        SDL_RenderCopy(rend, HighScoreTexture, NULL, &HighScoreRect);
        SDL_FreeSurface(surface);

        SDL_RenderPresent(rend);
        SDL_Delay(3000);

        file = fopen("High_Score.txt", "w");
        fprintf(file, "%d", high_score);
        fclose(file);
    }
};

game_over GameOver;

class menu
{
public:
    void render_menu(SDL_Renderer *rend)
    {
        SDL_Delay(delay);
        SDL_RenderCopy(rend, menu_img, NULL, NULL);
        SDL_RenderPresent(rend);
        while (j)
        {
            while (SDL_PollEvent(&e) != 0 and j)
            {
                if (e.type == SDL_QUIT)
                {
                    j = 0;
                    i = 0;
                    game_running = false;
                    return;
                }

                // instructions
                else if (e.type == SDL_MOUSEBUTTONDOWN and e.motion.x >= 420 and e.motion.x <= 560 and e.motion.y >= 370 and e.motion.y <= 415)
                {
                    e.type = 0;
                    // instructions
                    surface = IMG_Load("images/rocket_instruction.png");
                    instructions_screen = SDL_CreateTextureFromSurface(rend, surface);
                    SDL_FreeSurface(surface);

                    SDL_RenderCopy(rend, instructions_screen, NULL, NULL);
                    SDL_RenderPresent(rend);
                    while (e.type != SDL_MOUSEBUTTONDOWN)
                    {
                        SDL_PollEvent(&e);
                    }
                    SDL_RenderCopy(rend, menu_img, NULL, NULL);
                    SDL_RenderPresent(rend);
                }

                else if (e.type == SDL_MOUSEBUTTONDOWN and e.motion.x >= 230 and e.motion.x <= 380 and e.motion.y >= 370 and e.motion.y <= 415)
                {
                    j = 0;
                    i = 1;
                    break;
                }
                else if (e.type == SDL_MOUSEBUTTONDOWN and e.motion.x >= 615 and e.motion.x <= 760 and e.motion.y >= 370 and e.motion.y <= 415)
                {
                    j = 0;
                    i = 0;
                    game_running = false;
                    return;
                }

                else if (e.type == SDL_KEYDOWN)
                {
                    switch (e.key.keysym.sym)
                    {

                    case SDLK_SPACE:
                    {
                        j = 0;
                        i = 1;
                        break;
                    };

                    case SDLK_ESCAPE:
                    {
                        j = 0;
                        i = 0;
                        game_running = false;
                        return;
                    };
                    }
                }
            }
        }
    }
};

menu Game_Menu;

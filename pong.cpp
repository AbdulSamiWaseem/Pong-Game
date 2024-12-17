
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <pthread.h>
#include <unistd.h>

using namespace std;

struct Ball
{
    float x, y;
    float velX, velY;
    int size;
};

struct Paddle
{
    float y;
    int width, height;
};

Ball ball;
Paddle paddle1, paddle2;
int score1, score2;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;

const float BALL_SPEED = 5;
const float PADDLE_SPEED = 10;

void *ballThread(void *arg)
{
    while (true)
    {
        ball.x += ball.velX;
        ball.y += ball.velY;

        if (ball.y - ball.size / 2 <= 0 || ball.y + ball.size / 2 >= 600)
        {
            ball.velY = -ball.velY;
        }

        if (ball.x - ball.size / 2 <= 55 + paddle1.width && ball.x - ball.size / 2 >= 50 && ball.y >= paddle1.y && ball.y <= paddle1.y + paddle1.height)
        {
            ball.velX = -ball.velX;
        }
        if (ball.x + ball.size / 2 >= 730 && ball.y >= paddle2.y && ball.y <= paddle2.y + paddle2.height)
        {
            ball.velX = -ball.velX;
        }

        if (ball.x - ball.size / 2 <= 0)
        {
            score2++;
            ball = {400, 300, BALL_SPEED, BALL_SPEED, 20};
        }
        else if (ball.x + ball.size / 2 >= 800)
        {
            score1++;
            ball = {400, 300, -BALL_SPEED, BALL_SPEED, 20};
        }

        usleep(50000);
    }
    return NULL;
}

void *paddle1Thread(void *arg)
{
    while (true)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_w && paddle1.y > 0)
                {
                    paddle1.y -= PADDLE_SPEED;
                }
                if (event.key.keysym.sym == SDLK_s && paddle1.y + paddle1.height < 600)
                {
                    paddle1.y += PADDLE_SPEED;
                }
            }
        }
        usleep(500);
    }
    return NULL;
}

void *paddle2Thread(void *arg)
{
    while (true)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_UP && paddle2.y > 0)
                {
                    paddle2.y -= PADDLE_SPEED;
                }
                if (event.key.keysym.sym == SDLK_DOWN && paddle2.y + paddle2.height < 600)
                {
                    paddle2.y += PADDLE_SPEED;
                }
            }
        }
        usleep(500);
    }
    return NULL;
}

void renderText(const string &text, int x, int y)
{
    SDL_Color textColor = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    int width = surface->w;
    int height = surface->h;

    int adjustedX = x - width / 2;

    SDL_Rect dstRect = {adjustedX, y, width, height};

    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cerr << "SDL initialization failed: " << SDL_GetError() << endl;
        return 1;
    }

    if (TTF_Init() < 0)
    {
        cerr << "SDL_ttf initialization failed: " << TTF_GetError() << endl;
        return 1;
    }

    window = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    font = TTF_OpenFont("/usr/share/fonts/truetype/abyssinica/AbyssinicaSIL-Regular.ttf", 24);

    if (font == NULL)
    {
        cerr << "Failed to load font: " << TTF_GetError() << endl;
        return 1;
    }

    ball = {400, 300, BALL_SPEED, BALL_SPEED, 20};
    paddle1 = {250, 20, 100};
    paddle2 = {250, 20, 100};
    score1 = 0;
    score2 = 0;

    pthread_t ball_tid, paddle1_tid, paddle2_tid;
    pthread_create(&ball_tid, NULL, ballThread, NULL);
    pthread_create(&paddle1_tid, NULL, paddle1Thread, NULL);
    pthread_create(&paddle2_tid, NULL, paddle2Thread, NULL);

    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    quit = true;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Rect paddle1Rect = {50, (int)paddle1.y, paddle1.width, paddle1.height};
        SDL_Rect paddle2Rect = {730, (int)paddle2.y, paddle2.width, paddle2.height};
        SDL_Rect ballRect = {(int)(ball.x - ball.size / 2), (int)(ball.y - ball.size / 2), ball.size, ball.size};

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &paddle1Rect);
        SDL_RenderFillRect(renderer, &paddle2Rect);
        SDL_RenderFillRect(renderer, &ballRect);

        string scoreText1 = to_string(score1);
        string scoreText2 = to_string(score2);
        int scoreTextWidth = 50;

        renderText(scoreText1, 200 - scoreTextWidth, 50);
        renderText(scoreText2, 650 - scoreTextWidth, 50);

        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

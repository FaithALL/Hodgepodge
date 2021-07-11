

#ifndef GAME_HPP
#define GAME_HPP

#include <array>
#include <random>
#include <memory>
#include <SDL2/SDL.h>

template <int, int> class lifeGame;

//图形展示
template<int WIDTH, int HEIGHT>
class Game {
public:
    Game() {
        SDL_Init(SDL_INIT_VIDEO);
        window.reset(SDL_CreateWindow("GameOfLife", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                      WIDTH * 16, HEIGHT * 16, SDL_WINDOW_SHOWN));
        renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED));
    }

    void draw() {
        constexpr int len = 15;
        constexpr int margin = 2;
        constexpr int boarder = 25;
        std::vector<SDL_Rect> aliveRect;
        std::vector<SDL_Rect> deadRect;
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                int x = j * len + margin + boarder;
                int y = i * len + margin + boarder;
                int rectLen = len - 2 * margin;
                if (world.alive(i, j)) aliveRect.push_back({x, y, rectLen, rectLen});
                else deadRect.push_back({x, y, rectLen, rectLen});
            }
        }
        SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 0);
        SDL_RenderClear(renderer.get());
        SDL_SetRenderDrawColor(renderer.get(), 9, 9, 9, 0);
        SDL_RenderFillRects(renderer.get(), &aliveRect[0], aliveRect.size());
        SDL_SetRenderDrawColor(renderer.get(), 230, 230, 230, 0);
        SDL_RenderFillRects(renderer.get(), &deadRect[0], deadRect.size());
        SDL_RenderPresent(renderer.get());
        world.next();
    }

    ~Game() {
        SDL_Quit();
    }

private:
    lifeGame<WIDTH, HEIGHT> world;
    std::unique_ptr<SDL_Window, void (*)(SDL_Window *)> window = {nullptr, SDL_DestroyWindow};
    std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)> renderer = {nullptr, SDL_DestroyRenderer};
};

//负责算法实现
template<int WIDTH, int HEIGHT>
class lifeGame {
public:
    lifeGame() {
        //初始随机化
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 1);
        for (auto &arr : matrix) {
            for (auto &x : arr) {
                x = dis(gen);
            }
        }
    }

    //算法实现
    void next() {
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                int count = livingCount(i, j);
                if (matrix[i][j] == 1) {
                    if (count == 2 || count == 3) matrix[i][j] += 2;
                } else {
                    if (count == 3) matrix[i][j] += 2;
                }
            }
        }

        for (auto &vec : matrix) {
            for (auto &x : vec) {
                x >>= 1;
            }
        }
    }

    //判断(x, y)位置处细胞是否存活
    bool alive(int x, int y) {
        return matrix.at(x).at(y) == 1;
    }

private:
    std::array<std::array<int, WIDTH>, HEIGHT> matrix;

    //计算以(x,y)为中心的九宫格内活细胞的数目
    int livingCount(int x, int y) {
        int count = -matrix[x][y];
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int px = x + i;
                int py = y + j;
                if (0 <= px && px < HEIGHT &&
                    0 <= py && py < WIDTH &&
                    matrix[px][py] % 2 == 1) {
                    ++count;
                }
            }
        }
        return count;
    }
};

#endif //GAME_HPP

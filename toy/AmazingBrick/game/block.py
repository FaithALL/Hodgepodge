import pygame

import game.game_config as config


class Block:
    def __init__(self, x, y, color):
        self.x = x
        self.y = y
        self.color = color

    def draw(self, screen):
        pygame.draw.rect(screen, self.color, (self.x, self.y,
                                              config.BLOCK_LEN, config.BLOCK_LEN))

    def get_points(self):
        return [(self.x, self.y), (self.x + config.BLOCK_LEN, self.y),
                (self.x + config.BLOCK_LEN, self.y + config.BLOCK_LEN),
                (self.x, self.y + config.BLOCK_LEN)]

    def move_y_pos(self, y):
        self.y -= y


class Pipe(Block):
    def __init__(self, x, y, w, color):
        super().__init__(x, y, color)
        self.w = w
        self.scored = False

    def draw(self, screen):
        pygame.draw.rect(screen, self.color, (self.x, self.y,
                                              self.w, config.PIPE_HEIGHT))

    def get_points(self):
        return [(self.x, self.y), (self.x + self.w, self.y), (self.x + self.w, self.y + config.PIPE_HEIGHT),
                (self.x, self.y + config.PIPE_HEIGHT)]


class Player(Block):
    def __init__(self, x, y, color):
        super().__init__(x, y, color)
        self.vx = 0
        self.vy = 0
        self.g = config.GRAVITY
        self.ax = config.ACC_X
        self.ay = config.ACC_Y

    def get_points(self):
        points = [(self.x + config.PLAYER_LEN, self.y), (self.x, self.y + config.PLAYER_LEN),
                  (self.x - config.PLAYER_LEN, self.y), (self.x, self.y - config.PLAYER_LEN)]
        return points

    def draw(self, screen):
        points = self.get_points()
        pygame.draw.polygon(screen, self.color, points)

    def no_move(self):
        self.vy += self.g
        self.__move()

    def move_left(self):
        self.vx = 0
        self.vy = 0
        self.vx -= self.ax
        self.vy -= (self.ay - self.g)
        self.__move()

    def move_right(self):
        self.vx = 0
        self.vy = 0
        self.vx += self.ax
        self.vy -= (self.ay - self.g)
        self.__move()

    def __move(self):
        self.x += self.vx
        self.y += self.vy
        if self.x - config.PLAYER_LEN < 0:
            self.x = config.PLAYER_LEN
        elif self.x + config.PLAYER_LEN > config.WINDOW_WIDTH:
            self.x = config.WINDOW_WIDTH - config.PLAYER_LEN

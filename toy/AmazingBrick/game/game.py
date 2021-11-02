import random

import pygame

import game.game_config as config
from game.block import Block, Pipe, Player
from pygame_colliders import ConvexCollider

pygame.init()

SCREEN = pygame.display.set_mode((config.WINDOW_WIDTH, config.WINDOW_HEIGHT), pygame.NOFRAME)


class Game:
    def __init__(self):
        self.score = 0
        self.colorId = 0
        self.pipes = []
        self.blocks = []
        self.player = Player(config.WINDOW_WIDTH / 2,
                             config.WINDOW_HEIGHT / 2, config.PLAYER_COLOR)
        self.start = False
        self.__draw()

    def reset(self):
        self.__init__()

    def frame_step(self, action):
        if action == config.ACTION.NOTHING:
            if self.start:
                self.player.no_move()
        elif action == config.ACTION.LEFT:
            self.start = True
            self.player.move_left()
        elif action == config.ACTION.RIGHT:
            self.start = True
            self.player.move_right()

        self.__handle_pipe_blocks()
        self.__move_y_pos()
        self.__calculate_score()
        self.__draw()
        return self.__is_collision()

    def __handle_pipe_blocks(self):
        n = len(self.pipes)
        if n == 0:
            gap_y = -config.PIPE_HEIGHT
            gap_x = self.__create_pipe(gap_y)
            self.__create_block(gap_x, gap_y)
        elif n < 6:
            gap_y = self.pipes[n - 1].y - config.WINDOW_HEIGHT / 2
            gap_x = self.__create_pipe(gap_y)
            self.__create_block(gap_x, gap_y, True)
        else:
            pipe = self.pipes[0]
            if pipe.y >= config.WINDOW_HEIGHT:
                self.pipes.pop(0)
                self.pipes.pop(0)

        while self.blocks[0].y >= config.WINDOW_HEIGHT:
            self.blocks.pop(0)

    def __create_pipe(self, y):
        gap_x = random.randint(config.PIPE_GAP_X[0], config.PIPE_GAP_X[1])
        self.pipes.append(Pipe(0, y, gap_x, config.COLORS[self.colorId]))
        self.pipes.append(
            Pipe(gap_x + config.PIPE_GAP_LEN, y, config.WINDOW_WIDTH - gap_x - config.PIPE_GAP_LEN,
                 config.COLORS[self.colorId]))
        return gap_x

    def __create_block(self, gap_x, gap_y, two=False):
        mid_x = gap_x + config.PIPE_GAP_LEN / 2
        mid_y = gap_y + config.PIPE_HEIGHT / 2
        if two:
            dx = random.randint(int(config.BLOCK_AREA_WIDTH[0]), int(config.BLOCK_AREA_WIDTH[1]))
            dy = random.randint(int(config.BLOCK_AREA_HEIGHT[0]), int(config.BLOCK_AREA_HEIGHT[1]))
            self.blocks.append(Block(mid_x + dx, mid_y + dy, config.COLORS[self.colorId]))
        dx = random.randint(int(config.BLOCK_AREA_WIDTH[0]), int(config.BLOCK_AREA_WIDTH[1]))
        dy = random.randint(int(config.BLOCK_AREA_HEIGHT[0]), int(config.BLOCK_AREA_HEIGHT[1]))
        self.blocks.append(Block(mid_x + dx, mid_y - dy, config.COLORS[self.colorId]))

    def __move_y_pos(self):
        t = self.player.y - config.WINDOW_HEIGHT / 2
        if t < 0:
            self.player.move_y_pos(t)
            for pipe in self.pipes:
                pipe.move_y_pos(t)
            for block in self.blocks:
                block.move_y_pos(t)

    def __draw(self):
        SCREEN.fill(config.BACKGROUND_COLOR)
        for pipe in self.pipes:
            pipe.draw(SCREEN)
        for block in self.blocks:
            block.draw(SCREEN)
        self.player.draw(SCREEN)
        pygame.display.update()

    def __is_collision(self):
        if self.player.y + config.PLAYER_LEN >= config.WINDOW_HEIGHT:
            return True
        player_points = self.player.get_points()
        collider_player = ConvexCollider(player_points)
        for pipe in self.pipes:
            if pipe.y + config.PIPE_HEIGHT < self.player.y - config.PLAYER_LEN:
                break
            else:
                pipe_points = pipe.get_points()
                collider_pipe = ConvexCollider(pipe_points)
                if collider_player.collide(collider_pipe):
                    return True

        for block in self.blocks:
            if block.y + config.BLOCK_LEN < self.player.y - config.PLAYER_LEN:
                break
            else:
                block_points = block.get_points()
                collider_block = ConvexCollider(block_points)
                if collider_player.collide(collider_block):
                    return True

        return False

    def __calculate_score(self):
        for pipe in self.pipes:
            if not pipe.scored:
                if pipe.y >= config.WINDOW_HEIGHT / 2:
                    self.score += 0.5
                    pipe.scored = True
                else:
                    break
        self.colorId = int(self.score) // len(config.COLORS) % len(config.COLORS)

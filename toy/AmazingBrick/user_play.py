from game.game import Game
from game.game_config import FPS
from game.game_config import ACTION
import pygame

game_state = Game()

fps_clock = pygame.time.Clock()

run = True
while run:
    action = ACTION.NOTHING
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_LEFT:
                action = ACTION.LEFT
            elif event.key == pygame.K_RIGHT:
                action = ACTION.RIGHT
            elif event.key == pygame.K_ESCAPE:
                run = False

    done = game_state.frame_step(action)
    if done:
        print(game_state.score)
        game_state.reset()

    fps_clock.tick(FPS)

pygame.quit()

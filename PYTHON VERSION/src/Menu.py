# Tank Game:
# A game with tanks and stuff.
#
# by Erkalys & Florimond Manca
#
# Menu loop


## Imports

import pygame
from pygame.locals import *
from pygame.font import *
import math

import Tank
import Utils
import Bullet_Cursor
from paths import *
from Walls import *
from Init_AI import init_AI
from Level_Loop import main
from Importation import get_level
from Level_Selection import level_selection_menu
from Options import *
import Level_Editor


def run_game() :
    pygame.init()
    Utils.update_music_menu()
    clickSound = pygame.mixer.Sound(join(MUSIC_PATH,"click_sound.wav"))
    pygame.font.init()  # module de pygame qui gère le texte

    size = Utils.get_size()
    pygame.display.set_mode(size)
    screen = pygame.display.get_surface()
    pygame.display.set_caption("Tank Game")
    walls_group, pits_group, _, data_AI, _ = get_level(MAIN_PATH,-1)
    icone = pygame.image.load(join(IMAGE_PATH, 'tank.png'))
    pygame.display.set_icon(icone)

    # get the AI data
    AI_group, _ = init_AI(data_AI)

    background = Utils.Background(-1)
    screen.blit(background.image, (0, 0))

    pygame.mouse.set_visible(False)
    curseur = Bullet_Cursor.Cursor(IMAGE_PATH)

    clock = pygame.time.Clock()
    running = 1

    font = pygame.font.SysFont("impact", 36)

    title = font.render("Tank Game", 1, (30, 30, 30))
    titlepos = title.get_rect(centerx=512, centery = 100)

    start_game = Utils.Button("Start Game", font, 512, 200, (200, 0, 0))
    level_select = Utils.Button("Level Selection", font, 512, 300, (200, 0, 0))
    exit_game = Utils.Button("Exit Game", font, 512, 600, (200, 0, 0))
    editor = Utils.Button("Level Editor",  font, 512, 400, (200, 0, 0))
    options = Utils.Button("Options", font, 512, 500, (200, 0, 0))

    while running:
        clock.tick(60) # on maximise le fps à 60
        screen.blit(background.image, (0, 0))
        screen.blit(title, titlepos)
        start_game.update(screen)
        exit_game.update(screen)
        editor.update(screen)
        level_select.update(screen)
        curseur.update(screen)
        options.update(screen)
        Utils.update_music_menu()

        for AI_sprite in AI_group:
            boulets = AI_sprite.update(curseur.rect.center,
                walls_group, pits_group, [], in_menu = True, bliton = screen)

        pygame.display.flip()

        for event in pygame.event.get():
            # if player wants to quit (using window buttons)
            if event.type == QUIT:
                running = 0
                pygame.mixer.music.fadeout(200)
                clock.tick(5)
                pygame.quit()

            # player clicked somewhere
            elif event.type == MOUSEBUTTONDOWN and event.button == 1:

                # player clicked on "Exit Game"
                if exit_game.highlighten:
                    running = 0
                    clickSound.play()
                    clock.tick(4)
                    pygame.quit()

                # player clicked on "Start Game"
                elif start_game.highlighten:
                    clickSound.play()
                    pygame.mixer.music.fadeout(200)
                    clock.tick(5)
                    n = 1
                    result = main(n, start=True)
                    while result:
                        n += 1
                        result = main(n)
                    if not pygame.mixer.get_init():
                        return
                    pygame.display.set_caption("Tank Game")

                # player clicked on "Level Selection"
                elif level_select.highlighten:
                    clickSound.play()
                    if not level_selection_menu():
                        running = 0
                        pygame.quit()
                    else:
                        pygame.display.set_caption("Tank Game")

                # player clicked on "Level Editor"
                elif editor.highlighten :
                    clickSound.play()
                    running = 0
                    pygame.quit()
                    Level_Editor.level_editor()

                # player clicked on "Options"
                elif options.highlighten:
                    clickSound.play()
                    if not options_menu():
                        return

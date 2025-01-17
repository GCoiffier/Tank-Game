# Tank Game:
# A game with tanks and stuff.
#
# by Erkalys & Florimond Manca
#
# Level selection menu


## Imports

import pygame
from pygame.locals import *
from pygame.font import *
import math
import sys
import os
import Tank
import Utils
import Bullet_Cursor
from paths import *
from AI_Player import *
from Level_Loop import main
from Importation import get_level, get_unlocked, overwrite_unlocked


def button_update(buttons, bliton = pygame.display.get_surface()):
    for b in buttons:
        b.update(bliton)

def level_selection_menu():
    """level_selection_menu(): launches the menu where the player can select
    levels, either normal or custom ones."""
    # some initialization
    pygame.font.init()  # pygame module for managing fonts
    size = Utils.get_size()
    screen = pygame.display.set_mode(size)
    background = Utils.Background(IMAGE_PATH, nlevel=-1)
    screen.blit(background.image, (0, 0))

    # replace the mouse with a cursor
    pygame.mouse.set_visible(False)
    curseur = Bullet_Cursor.Cursor(IMAGE_PATH)

    clickSound = pygame.mixer.Sound(join(MUSIC_PATH, "click_sound.wav"))

    clock = pygame.time.Clock()
    running = 1
    buttons = []
    unlocked = get_unlocked() # unlocked levels
    font_big = pygame.font.SysFont("impact", 36)
    font_medium = pygame.font.SysFont("impact", 18)
    font_buttons = pygame.font.SysFont("impact", 20)

    title = font_big.render("Select a level", 1, (30, 30, 30))
    titlepos = title.get_rect(centerx=512, centery=50)

    back = Utils.Button("Back" , font_big, 512, 590, (200, 0, 0))
    help_msg = font_medium.render("You can only select levels you've unlocked. To unlock a level, beat all the previous ones.", 1, (69, 52, 16))
    msgpos = help_msg.get_rect(centerx=512, centery=620)

    # load the buttons
    n, i, j = 1, 0, 0
    # first the buttons for the default levels
    while os.path.exists(join(LEVEL_PATH, "level"+str(n)+".txt")):
        if i > 500:
            i = 0
            j += 50
        buttons.append(Utils.Button("#{}".format(n), font_buttons,
            100 + j, 100 + i, (200, 0, 0)))
        i += 30
        n += 1
    n_customs = n - 1 # the identifier of the first custom level

    m, i, j = 1, 0, 0

    while os.path.exists(join(CLEVEL_PATH, "custom_level{}.txt".format(m))): #on charge les boutons des niveaux customs
        if i > 500:
            i = 0
            j += 50
        buttons.append(Utils.Button("#custom{}".format(m), font_buttons,
            900 + j, 100 + i, (200, 0, 0)))
        i += 30
        m += 1

    # On lance la boucle d'affichage
    while running:
        clock.tick(60)  # maximum fps is 60
        # blit the basic things
        screen.blit(background.image , (0, 0))
        screen.blit(title, titlepos)
        screen.blit(help_msg, msgpos)
        # update the entities
        back.update(screen)
        button_update(buttons,screen)
        curseur.update(screen)
        # update the music (to keep it running if it reaches the end)
        Utils.update_music_menu()
        pygame.display.flip()
        # deal with the events
        for event in pygame.event.get():
            if event.type ==  QUIT:
                clickSound.play()
                pygame.mixer.music.fadeout(200)
                clock.tick(5)
                running = 0
                return False
            elif event.type == MOUSEBUTTONDOWN and event.button == 1 :
                if back.highlighten :
                    clickSound.play()
                    running = 0
                    return True
                else :
                    for i, button in enumerate(buttons):
                        if button.highlighten:
                            if i >= n_customs : # si le niveau est un niveau custom :
                                clickSound.play()
                                pygame.mixer.music.fadeout(200)
                                clock.tick(5)
                                main(i - n_customs + 1, custom=True, start=True, from_selection=True)
                                if not pygame.mixer.get_init():
                                    return False
                                pygame.display.set_caption("Tank Game")
                            else:
                                if unlocked[i]:
                                    clickSound.play()
                                    pygame.mixer.music.fadeout(200)
                                    clock.tick(5)
                                    if main(i + 1, custom=False, start=True, from_selection=True):
                                        unlocked = get_unlocked()
                                    if not pygame.mixer.get_init():
                                        return False
                                    pygame.display.set_caption("Tank Game")

if __name__ == '__main__':
    level_selection_menu()

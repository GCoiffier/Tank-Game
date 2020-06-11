# Tank Game:
# A game with tanks and stuff.
#
# by Erkalys & Florimond Manca
#
# Defining AI and Player classes

## Imports

import pygame
from pygame.locals import *
import math
import sys
import os
from random import randint
from AI_Player import StillAI, StillPlusAI
from Tank import Tank
from Utils import *

path = os.getcwd()
join = os.path.join

## Class AdvancedIA

class AdvancedAI(StillAI,Tank):

    """
    An advanced IA for the game. Inherits from class Tank
    Uses a neural network to play the game.

    works more like a player that gives input to the game rather than other IA
    """

    def __init__(self,  pos, target_pos) :
        StillAI.__init__(self, 'tank_corps_dark.png', 'canon_dark.png', pos, (pos[0]-1, pos[1]))

        self.firesound = pygame.mixer.Sound(join(MUSIC_PATH,"shot_sound.wav"))
        v = get_volumes()[1]
        self.firesound.set_volume(v)

    def react(self, target_pos, walls_group, pits_group, bullets_group):
        """
        Updates the state of the AI. This function reads the game parameters (walls, enemy positions, bullets in flight, ...)
        and returns the reaction of the AI, in terms of input keys.
        """
        input_dict = {"left" : False,
                      "right" : False,
                      "up" : False,
                      "down" : False,
                      "mouse_move" : False,
                      "mouse_click" : False}

    def update(self, target_pos, walls_group, pits_group, bullets_group, in_menu=False, bliton = pygame.display.get_surface()):
        new_bullets = None
        inputs = self.react(target_pos, walls_group, pits_group, bullets_group)
        if not in_menu and self.alive:
            pass
        Tank.update(self, target_pos, bullets_group, bliton = bliton)
        return new_bullets





class AdvancedPlusAI(StillPlusAI,Tank):

    def __init__(self,  pos, target_pos) :
        StillPlusAI.__init__(self, 'tank_corps_dark.png', 'canon_darkPlus.png', pos, (pos[0]-1, pos[1]))

        self.firesound = pygame.mixer.Sound(join(MUSIC_PATH,"shot_sound.wav"))
        v = get_volumes()[1]
        self.firesound.set_volume(v)

    def react(self, target_pos, walls_group, pits_group, bullets_group):
        """
        Updates the state of the AI. This function reads the game parameters (walls, enemy positions, bullets in flight, ...)
        and returns the reaction of the AI, in terms of input keys.
        """
        input_dict = {"left" : False,
                      "right" : False,
                      "up" : False,
                      "down" : False,
                      "mouse_move" : False,
                      "mouse_click" : False}

    def update(self, target_pos, walls_group, pits_group, bullets_group, in_menu=False, bliton = pygame.display.get_surface()):
        new_bullets = None
        inputs = self.react(target_pos, walls_group, pits_group, bullets_group)
        if not in_menu and self.alive:
            pass
        Tank.update(self, target_pos, bullets_group, bliton = bliton)
        return new_bullets

# Tank Game:
# A game with tanks and stuff.
#
# by Erkalys & Florimond Manca
#
# Defining AI

## Imports

import pygame
from pygame.locals import *
import math
from queue import PriorityQueue # Priority Queue for A* algorithm
from random import randint
from Tank import *
from AI_Player import *
from Utils import *
from paths import *

## Classes Player, YellowAI, BlueAI, RedAI, PurpleAI, Spawner

class YellowAI(StillAI):
    def __init__(self, pos, target_pos) :
        StillAI.__init__(self, 'tank_corps_yellow.png', 'canon_yellow.png', pos, target_pos)


class YellowPlusAI(StillPlusAI):
    def __init__(self, pos, target_pos):
        StillPlusAI.__init__(self, 'tank_corps_yellow.png',
                             'canon_yellowPlus.png', pos, target_pos)


class BlueAI(PathAI):
    def __init__(self, pos, target_pos, points_list) :
        PathAI.__init__(self, 'tank_corps_blue.png',
                      'canon_blue.png' , pos, target_pos, points_list,1)


class BluePlusAI(PathPlusAI):
    def __init__(self, pos, target_pos, points_list) :
        PathPlusAI.__init__(self, 'tank_corps_blue.png',
                          'canon_bluePlus.png' , pos, target_pos, points_list,1)


class PurpleAI(PathAI):
    def __init__(self, pos, target_pos, points_list):
        PathAI.__init__(self, 'tank_corps_purple.png',
                          'canon_purple.png', pos, target_pos, points_list,3)


class PurplePlusAI(PathPlusAI):
    def __init__(self, pos, target_pos, points_list) :
        PathPlusAI.__init__(self, 'tank_corps_purple.png',
                               'canon_purplePlus.png', pos, target_pos, points_list,3)


class RedAI(RushAI):
    def __init__(self, pos, target_pos) :
        RushAI. __init__(self, 'tank_corps_red.png',
                    'canon_red.png', pos, target_pos)


class RedPlusAI(RushPlusAI):
    def __init__(self, pos, target_pos) :
        RushPlusAI. __init__(self, 'tank_corps_red.png',
                        'canon_redPlus.png', pos, target_pos)

class SpawnerSimple(Spawner):
    """SpawnerPlus : An AI that generates RedPlusAI's. 3 shots are needed to kill it."""
    def __init__(self, pos):
        Spawner.__init__(self, 'spawner.png', pos, max_shots = 1)

class SpawnerPlus(Spawner) :
    """SpawnerPlus : An AI that generates RedPlusAI's. 3 shots are needed to kill it."""
    def __init__(self, pos):
        Spawner.__init__(self, 'spawnerPlus.png', pos, enhanced = True, max_shots = 3)

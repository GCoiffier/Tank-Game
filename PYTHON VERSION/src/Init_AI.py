# Tank Game:
# A game with tanks and stuff.
#
# by Erkalys & Florimond Manca
#
# AI init Loop used in menu.py, level_loop.py and training.py

from AI_Player import *
from AI_Standard import *
from AI_Advanced import *

def init_AI(datas,points_list=[]):
    AI_group = []
    all_spawners = []
    for element in datas:
        name,pos = element[0],element[1]
        if name == 'yellow':
            yellow = YellowAI(pos,(0,0))
            AI_group.append(yellow)
        if name == 'yellowPlus':
            yellowp = YellowPlusAI(pos, (0,0))
            AI_group.append(yellowp)
        elif name == 'blue':
            try :
                path = points_list.pop()
            except :
                path = []
            blue = BlueAI(pos, (0,0), path)
            AI_group.append(blue)
        elif name == 'bluePlus':
            try :
                path = points_list.pop()
            except :
                path = []
            bluep = BluePlusAI(pos, (0,0), path)
            AI_group.append(bluep)
        elif name == 'red':
            red = RedAI(pos, (0,0))
            AI_group.append(red)
        elif name == 'redPlus':
            redp = RedPlusAI(pos, (0,0))
            AI_group.append(redp)
        elif name == 'purple':
            try :
                path = points_list.pop()
            except :
                path = []
            purple = PurpleAI(pos, (0,0), path)
            AI_group.append(purple)
        elif name == 'purplePlus':
            try :
                path = points_list.pop()
            except :
                path = []
            purplep = PurplePlusAI(pos , (0,0), path)
            AI_group.append(purplep)
        elif name == 'spawner' :
            spawner = SpawnerSimple(pos)
            all_spawners.append(spawner)
        elif name == 'spawnerPlus' :
            spawnerp = SpawnerPlus(pos)
            all_spawners.append(spawnerp)
        elif name == 'advanced' :
            adv = AdvancedAI(pos , (0,0))
            AI_group.append(adv)
        elif name== 'advancedPlus' :
            advp = AdvancedAI(pos , (0,0))
            AI_group.append(advp)
    return AI_group, all_spawners

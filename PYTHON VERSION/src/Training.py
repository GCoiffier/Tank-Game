# Tank Game:
# A game with tanks and stuff.
#
# by Erkalys & Florimond Manca
#
# Level loop


## Imports

import pygame
from pygame.locals import *
import math
import sys
import os

import Tank
import Utils
import Bullet_Cursor
from AI_Player import *
from AI_Standard import *
from AI_Advanced import *
from Walls import *
from Importation import get_level, get_unlocked, overwrite_unlocked

join = os.path.join
path = os.getcwd()


## Programme principal

def pause(screen, player, background, walls_group, AI_group, bullets_group, all_dead_IA ,all_spawners, all_dead_spawners ,all_spawned_IA) :
    global clickSound
    paused = True
    font = pygame.font.SysFont("impact", 36)
    resume= Utils.Button("Resume Game", font, 512 , 200 , (200,0,0))
    exit = Utils.Button("Return to Menu", font, 512, 300, (200,0,0))

    curseur_pause = Bullet_Cursor.Cursor(join(path, "images")) # par un curseur/pointeur
    c = pygame.time.Clock()

    while paused :
        c.tick(60)
        screen.blit( background.image , (0,0) )

        curseur_pause.update()

        screen.blit(player.body.image, player.body.rect)
        screen.blit(player.canon.image, player.canon.rect)

        for IA in AI_group :
            screen.blit(IA.body.image , IA.body.rect)
            screen.blit(IA.canon.image, IA.canon.rect)
        for IA in all_dead_IA :
            screen.blit(IA.body.image , IA.body.rect)
        for IA in all_spawners :
            screen.blit(IA.image , IA.rect)
        for IA in all_dead_spawners :
            screen.blit(IA.image , IA.rect)
        for bullet in bullets_group :
            screen.blit(bullet.image , bullet.rect)
        for IA in all_spawned_IA :
            screen.blit(IA.body.image , IA.body.rect)
            screen.blit(IA.canon.image, IA.canon.rect)
        for wall in walls_group :
            screen.blit(wall.image, wall.rect)

        for event in pygame.event.get():
            if event.type == MOUSEBUTTONDOWN and event.button == 1 and resume.highlighten :
                clickSound.play()
                return False
            if event.type == MOUSEBUTTONDOWN and event.button == 1 and exit.highlighten :
                clickSound.play()
                return True
            if event.type == QUIT: # le player choisit de quitter
                clickSound.play()
                pygame.mixer.music.fadeout(200)
                c.tick(5)
                pygame.quit()
                return True

        resume.update()
        exit.update()
        pygame.display.flip()

def run_training():
        """
        runs a dual between an advanced AI and another AI in order to train the
        advanced AI.
        """
        global clickSound
        pygame.init()
        size = Utils.get_size()
        screen = pygame.display.set_mode(size)
        pygame.display.set_caption("Training mode")
        clock = pygame.time.Clock()
        screen = pygame.display.get_surface()
        walls_group , pits_group, _ , pos_IA , point_list = get_level(path,-2,False)
        assert(None == None and len(pos_IA)==2) # 2 IA in a duel. No player

        pygame.mouse.set_visible( False )       # remplacement de la souris
        curseur = Bullet_Cursor.Cursor() # par un curseur/pointeur
        walls_pits = pygame.sprite.Group()
        unlocked = get_unlocked() #les niveaux disponibles
        font = pygame.font.SysFont("impact", 36)
        clickSound = pygame.mixer.Sound(join(MUSIC_PATH,"click_sound.wav"))
        v = Utils.get_volumes()[0]

        for elt in walls_group:
            walls_pits.add(elt)
        for elt in pits_group:
            walls_pits.add(elt)

        background = Utils.Background(1, False)

        pygame.font.init()
        font = pygame.font.SysFont("impact", 18)

        target = None
        other = None

        for element in pos_IA:
            if element[0] == 'yellow':
                yellow =  YellowAI('tank_corps_yellow.png' ,
                                    'canon_yellow.png' ,
                                    element[1] , (0,0) )
                other = yellow
            elif element[0] == 'yellowPlus':
                yellowp =  YellowPlusAI('tank_corps_yellowPlus.png' ,
                                   'canon_yellowPlus.png' ,
                                     element[1] , (0,0) )
                other = yellowp
            elif element[0] == 'blue':
                blue = BlueAI('tank_corps_blue.png',
                                   'canon_blue.png' ,
                                   element[1] , (0,0) , points_list.pop(0) )
                other = blue
            elif element[0] == 'bluePlus':
                bluep = BluePlusAI('tank_corps_blue.png',
                                   'canon_bluePlus.png' ,
                                   element[1] , (0,0) , points_list.pop(0) )
                other = bluep
            elif element[0] == 'red':
                red = RedAI('tank_corps_red.png',
                                 'canon_red.png' ,
                                 element[1] , (0,0) )
                other = red
            elif element[0] == 'redPlus':
                redp = RedPlusAI('tank_corps_red.png',
                                 'canon_redPlus.png' ,
                                 element[1] , (0,0) )
                other = redp
            elif element[0] == 'purple' :
                purple = PurpleAI('tank_corps_purple.png',
                                    'canon_purple.png' ,
                                    element[1] , (0,0), points_list.pop(0) )
                other = purple
            elif element[0] == 'purplePlus' :
                purplep = PurplePlusAI('tank_corps_purple.png',
                                    'canon_purplePlus.png' ,
                                    element[1] , (0,0), points_list.pop(0) )
                other = purplep
            elif element[0] == 'advanced' :
                adv = AdvancedAI('tank_corps_dark.png',
                                       'canon_dark.png',
                                       element[1] , (0,0))
                if target is None :
                    target = adv
                else :
                    other = adv
            elif element[0]== 'advancedPlus' :
                advp = AdvancedAI('tank_corps_dark.png',
                                  'canon_darkPlus.png',
                                   element[1] , (0,0))
                if target is None :
                    target = advp
                else :
                    other = advp
            else :
                print("AI " + element[0]+ " is not a correct training mode AI")

        target.target_pos = other.pos
        other.target_pos = target.pos

        bullets_group = pygame.sprite.Group()

        RUNNING = 1 # variable de boucle
        # On lance la boucle de jeu
        while RUNNING:
            clock.tick(60) # on maximise le fps à 60
            if (target.alive and other.alive): #if every AI is alive
                # 1/ Gestion d'évènements divers
                for event in pygame.event.get():
                    if event.type == QUIT: # le player choisit de quitter
                        RUNNING = 0
                        pygame.mixer.music.fadeout(200)
                        clock.tick(5)
                        pygame.quit()
                        return

                # 2/ On met à jour les sprites

                collisions_dict = pygame.sprite.groupcollide(bullets_group , walls_group, False , False, pygame.sprite.collide_rect)
                # on récupère sous forme d'un dictionnaire l'ensemble des boulets qui sont entrés en collision avec un mur, et quel mur a été percuté
                # (cf. l'aide de pygame.sprite.groupcollide)

                screen.blit( background.image , (0,0) )

                for bullet in bullets_group:
                    if bullet in collisions_dict:
                            bullet.kill()
                for elt in walls_pits:
                    screen.blit(elt.image , elt.rect)

                bullets_group.update()

                bullets = other.update(path , target.body.rect.center , walls_group, pits_group, bullets_group)
                if bullets != None:
                    for bullet in bullets:
                        bullets_group.add(bullet)

                bullets = target.update(path, other.body.rect.center , walls_group, pits_group, bullets_group)
                if bullets != None:
                    for bullet in bullets:
                        bullets_group.add(bullet)

                curseur.update(screen)

                # 4/ on met à jour l'ensemble de l'image
                pygame.display.flip()

            else:
                print("end of training")
                return

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

from paths import *
import Tank
import Utils
import Bullet_Cursor
from Init_AI import init_AI
from AI_Player import Player
from Walls import *
from Importation import get_level, get_unlocked, overwrite_unlocked

def pause(screen, player, background, walls_group, AI_group, bullets_group, all_dead_IA ,all_spawners, all_dead_spawners ,all_spawned_IA) :
    global clickSound
    paused = True
    font = pygame.font.SysFont("impact", 36)
    resume= Utils.Button("Resume Game", font, 512 , 200 , (200,0,0))
    exit = Utils.Button("Return to Menu", font, 512, 300, (200,0,0))

    curseur_pause = Bullet_Cursor.Cursor(IMAGE_PATH) # par un curseur/pointeur
    c = pygame.time.Clock()

    while paused :
        c.tick(60)
        screen.blit( background.image , (0,0) )

        curseur_pause.update(screen)

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

        resume.update(screen)
        exit.update(screen)
        pygame.display.flip()

def dead_menu(screen, player, background, walls_group, AI_group, bullets_group, all_dead_IA ,all_spawners, all_dead_spawners ,all_spawned_IA) :
    global clickSound
    paused = True
    font1 = pygame.font.SysFont("impact", 36)
    recommencer = Utils.Button("Try Again", font1, 512 , 220 , (200,0,0))
    quitter = Utils.Button("Return to Menu", font1, 512, 350, (200,0,0))
    font2 = pygame.font.SysFont("impact", 50)
    you_died = font2.render("You died!", 1, (200,0,0))
    you_died_pos = you_died.get_rect(centerx=512, centery=150)
    curseur_pause = Bullet_Cursor.Cursor(IMAGE_PATH) # par un curseur/pointeur
    c = pygame.time.Clock()
    deadimg = Utils.load_image(IMAGE_PATH,'tank_destroyed.png')[0]

    while paused :
        c.tick(60)
        screen.blit( background.image , (0,0) )

        curseur_pause.update(screen)

        screen.blit(deadimg, player.body.rect)

        for IA in AI_group :
            screen.blit(IA.body.image , IA.body.rect)
            screen.blit(IA.canon.image, IA.canon.rect)
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
            if event.type == MOUSEBUTTONDOWN and event.button == 1 and recommencer.highlighten :
                clickSound.play()
                pygame.mixer.fadeout(200)
                return True
            if event.type == MOUSEBUTTONDOWN and event.button == 1 and quitter.highlighten :
                clickSound.play()
                pygame.mixer.music.fadeout(200)
                return False
            if event.type == QUIT: # le player choisit de quitter
                clickSound.play()
                pygame.mixer.music.fadeout(200)
                c.tick(5)
                pygame.quit()
                return False
        screen.blit(you_died, you_died_pos)
        recommencer.update(screen)
        quitter.update(screen)
        pygame.display.flip()

def main(n,custom=False, start = False, from_selection=False): #n est le numéro du niveau qui va être joué. On va chercher un niveau custom si custom=True
        global clickSound
        pygame.display.set_caption("Level %d" %n)
        clock = pygame.time.Clock()
        screen = pygame.display.get_surface()
        walls_group , pits_group , pos_joueur , data_AI , points_list = get_level(LEVEL_PATH,n,custom)
        pygame.mouse.set_visible( False )       # remplacement de la souris
        curseur = Bullet_Cursor.Cursor() # par un curseur/pointeur
        walls_pits = pygame.sprite.Group()
        unlocked = get_unlocked() #les niveaux disponibles
        font = pygame.font.SysFont("impact", 36)
        recommencer = Utils.Button("Try again", font, 512-200 , 200 , (200,0,0))
        quitter = Utils.Button("Back to menu", font, 512+200 , 200 , (200,0,0))
        clickSound = pygame.mixer.Sound(join(MUSIC_PATH,"click_sound.wav"))
        v = Utils.get_volumes()[0]

        if start :  #Si on a lancé le niveau depuis le menu (pas de changement de musique lors de l'enchainement de deux niveaux)
            if sys.platform in ["win32", "linux"]:
                pygame.mixer.pre_init( 44100 , -16 , 2 , 2048 )
                pygame.mixer.init()
                pygame.mixer.music.load(join(MUSIC_PATH, "MainTheme.ogg"))
            else :
                pygame.mixer.pre_init( 44100 , -16 , 2 , 2048 )
                pygame.mixer.init()
                pygame.mixer.music.load(join(MUSIC_PATH, "MainTheme.wav"))
            pygame.mixer.music.set_volume(v)
            pygame.mixer.music.play(-1)

        for elt in walls_group:
            walls_pits.add(elt)
        for elt in pits_group:
            walls_pits.add(elt)

        background = Utils.Background(n, custom)

        pygame.font.init()
        font = pygame.font.SysFont("impact", 18)
        if (n== 1 or n == 2) and not custom :
            if n== 1 :
                help_msg1 = font.render("Use the mouse to control your cannon", 1, (69,52,16))
                msgpos1 = help_msg1.get_rect(centerx=800, centery = 600)
                help_msg2 = font.render("and press left click to fire a bullet.", 1, (69,52,16))
                msgpos2 = help_msg2.get_rect(centerx=800, centery = 630)
            else :
                help_msg1 = font.render("Use Z,Q,S,D or up, down, left and right to move.", 1, (69,52,16))
                msgpos1 = help_msg1.get_rect(centerx=700, centery = 600)
                help_msg2 = font.render("Press ESC to pause at any moment.", 1, (69,52,16))
                msgpos2 = help_msg2.get_rect(centerx=800, centery = 630)

        player = Player(pos_joueur)

        AI_group, all_spawners = init_AI(data_AI,points_list)
        all_dead_IA = []
        all_dead_spawners = []
        all_spawned_IA = []
        bullets_group = pygame.sprite.Group()

        RUNNING = 1 # variable de boucle
        # On lance la boucle de jeu
        chemin_musique = MUSIC_PATH
        if sys.platform in ["win32" , "linux"] :
            deadTheme = pygame.mixer.Sound(join(chemin_musique,"DeadTheme.ogg"))
        else:
            deadTheme = pygame.mixer.Sound(join(chemin_musique,"DeadTheme.wav"))
            deadTheme.set_volume(v)
        has_begun = False
        begin_msg = font.render("CLICK TO BEGIN !", 2, (200,0,0))
        begin_msg_rect = begin_msg.get_rect(centerx = player.body.rect.centerx,
                                            centery = player.body.rect.centery-50)

        while RUNNING:
            clock.tick(60) # on maximise le fps à 60
            if has_begun:
                if player.alive:
                    # 1/ Gestion d'évènements divers
                    for event in pygame.event.get():
                        if event.type == MOUSEBUTTONDOWN:
                            if event.button == 1 and len(player.bullets) < 4:
                                # si clic gauche, on crée un boulet
                                player.firesound.play()
                                pos = (event.pos[0] , event.pos[1])
                                blt = player.create_bullet(pos)
                                player.bullets.add(blt)
                                bullets_group.add(blt)
                            if event.type == QUIT: # le player choisit de quitter
                                RUNNING = 0
                                pygame.mixer.music.fadeout(200)
                                clock.tick(5)
                                pygame.quit()
                                return False
                    # 2/ On gère les déplacements du player
                    keys = pygame.key.get_pressed()
                    right, left, up, down = keys[K_RIGHT] or keys[K_d], keys[K_LEFT] or keys[K_q], keys[K_UP] or keys[K_z], keys[K_DOWN] or keys[K_s]

                    player.move(right , left , up , down)

                    if keys[K_ESCAPE] :
                        k = pause(screen, player, background,walls_pits, AI_group, bullets_group, all_dead_IA ,all_spawners, all_dead_spawners ,all_spawned_IA)
                        if k:
                            try:
                                pygame.mixer.music.fadeout(200)
                                clock.tick(5)
                                RUNNING = 0  #on retourne au menu
                                return False
                            except:
                                return False

                    # 3/ On met à jour les sprites

                    collisions_dict = pygame.sprite.groupcollide(bullets_group , walls_group, False , False, pygame.sprite.collide_rect)
                    # on récupère sous forme d'un dictionnaire l'ensemble des boulets qui sont entrés en collision avec un mur, et quel mur a été percuté
                    # (cf. l'aide de pygame.sprite.groupcollide)

                    screen.blit( background.image , (0,0) )

                    #affichage des messages d'aide dans les premiers niveaux

                    if (n == 1 or n == 2) and not custom :
                        screen.blit(help_msg1,msgpos1)
                        screen.blit(help_msg2,msgpos2)

                    # affichage des sprites morts
                    for IA in all_dead_IA:
                        screen.blit(IA.body.image, IA.body.rect)
                    for spawner in all_dead_spawners:
                        screen.blit(spawner.image, spawner.rect)

                    for bullet in bullets_group:
                        if bullet in collisions_dict:
                                bullet.kill()
                    for elt in walls_pits:
                        screen.blit(elt.image , elt.rect)

                    bullets_group.update()

                    player.update(pygame.mouse.get_pos() , bullets_group , walls_pits, bliton = screen)

                    for IA in AI_group:
                        if IA.alive:
                            bullets = IA.update(player.body.rect.center , walls_group, pits_group, bullets_group, AI_group+all_spawned_IA, bliton = screen)
                            if bullets != None:
                                for bullet in bullets:
                                    bullets_group.add(bullet)
                        else:
                            (x,y) = IA.body.rect.center
                            IA.body.image , IA.body.rect = Utils.load_image(IMAGE_PATH,'tank_destroyed.png')
                            IA.body.rect.center = (x,y)
                            all_dead_IA.append(IA)
                            AI_group.remove(IA)

                    for IA in all_spawned_IA:
                        if IA.alive:
                            bullets = IA.update(player.body.rect.center , walls_group, pits_group, bullets_group, AI_group+all_spawned_IA, bliton = screen)
                            if bullets != None:
                                for bullet in bullets:
                                    bullets_group.add(bullet)
                        else:
                            (x,y) = IA.body.rect.center
                            IA.body.image , IA.body.rect = Utils.load_image(IMAGE_PATH,'tank_destroyed.png')
                            IA.body.rect.center = (x,y)
                            all_dead_IA.append(IA)
                            IA.id.spawned = False #le spawner est de nouveau libre
                            all_spawned_IA.remove(IA)

                    for spawner in all_spawners:
                        if spawner.alive:
                            IAspawned = spawner.update(player.body.rect.center,bullets_group, bliton = screen)
                            if IAspawned != None:
                                    all_spawned_IA.append(IAspawned)
                        else:
                            all_spawners.remove(spawner)
                            center = spawner.rect.center
                            spawner.image, spawner.rect = Utils.load_image(IMAGE_PATH,'spawner_destroyed.png')
                            spawner.rect.center = center
                            all_dead_spawners.append(spawner)

                    curseur.update(screen)

                    if len(AI_group) == 0 and len(all_spawned_IA) == 0 and len(all_spawners) == 0 : # toutes les IA ont été détruites, on a gagné
                        if not unlocked[n] and not custom:
                            unlocked[n] = 1 #le niveau suivant est débloqué
                            overwrite_unlocked(unlocked) #on actualise le fichier unlocked
                        if from_selection:
                            pygame.mixer.music.fadeout(200)
                            clock.tick(5)
                        return True
                    # 4/ on met à jour l'ensemble de l'image
                    pygame.display.flip()

                else:   # le player est mort, on affiche la boite de dialogue
                    pygame.mixer.music.fadeout(10)
                    deadTheme.play()
                    k = dead_menu(screen, player, background,walls_pits, AI_group, bullets_group, all_dead_IA ,all_spawners, all_dead_spawners ,all_spawned_IA)
                    if k: # on veut recommencer
                        return main(n, custom, True, from_selection)
                    else:
                        try:
                            deadTheme.fadeout(200)
                            return False
                        except:
                            return False

            else: # on attend que le player clique
                for event in pygame.event.get():
                    if event.type == MOUSEBUTTONDOWN and event.button == 1:
                        clickSound.play()
                        has_begun = True
                    elif event.type == QUIT:
                        pygame.mixer.music.fadeout(200)
                        clock.tick(5)
                        pygame.quit()
                        return False
                    elif event.type == KEYDOWN and event.key == K_ESCAPE:
                        k = pause(screen, player, background, walls_pits, AI_group, bullets_group, all_dead_IA ,all_spawners, all_dead_spawners ,all_spawned_IA)
                        if k :
                            pygame.mixer.music.fadeout(200)
                            clock.tick(5)
                            RUNNING = 0  #on retourne au menu
                            return False
                screen.blit(background.image, (0,0))
                cible = pygame.mouse.get_pos()
                player.canon.update(player.body.rect.center,cible, bliton = screen)
                screen.blit(player.body.image, player.body.rect)
                screen.blit(player.canon.image, player.canon.rect)
                for IA in AI_group:
                    screen.blit(IA.body.image, IA.body.rect)
                    screen.blit(IA.canon.image, IA.canon.rect)
                for spawner in all_spawners:
                    screen.blit(spawner.image, spawner.rect)
                for x in walls_pits:
                    screen.blit(x.image, x.rect)
                if (n== 1 or n==2) and not custom :
                    screen.blit(help_msg1,msgpos1)
                    screen.blit(help_msg2,msgpos2)
                screen.blit(begin_msg, begin_msg_rect)
                curseur.update(screen)
                pygame.display.flip()

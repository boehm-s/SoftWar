from __future__ import print_function
import pygame, sys, os
from pygame.locals import *
import time
import zmq
import json
import pygame
pygame.init()

#Couleur
white = (255,255,255)
pink = (255,127,237)
green = (76,255,0)
blue = (0,38,255)
red = (255,0,0)

#Size
tailleMap = 1000
tailleServ = 5

#Tab des couleurs et des positions des informations
color = (("pink", pink), ("red",red), ("blue",blue), ("green", green))
information_position = ((40,0), (40,80),(520,0),(520,80))

#Variable global
l_object = None
game = False
old_data = None
color_player = {}


# Initialise écran
DISPLAYSURF = pygame.display.set_mode((tailleMap, tailleMap), RESIZABLE)
pygame.display.set_caption('Soft War')

#Initialise la map et les objet visuel
def init_game(tailleMap, tailleServ):
    #Initialisation du jeux
    l_object = []

    #Init object box and perso
    l_object = init_box_player(tailleMap, tailleServ)

    #Init the map
    create_map(int(tailleMap), int(tailleServ), l_object["box"])

    return  l_object



#Défini l'objet d'écriture
def text_objects(text, font, color):
    textSurface = font.render(text, True, color)
    return textSurface, textSurface.get_rect()


#Ecrit du text sur l'écran
def message_display(posx, posy, text, color):
    largeText = pygame.font.Font('freesansbold.ttf', 25)
    TextSurf, TextRect = text_objects(text, largeText, color)
    TextRect = (posx, posy)
    DISPLAYSURF.blit(TextSurf, TextRect)


#Positionne perssonage sur map
def create_perso(position_perso, personnage):
    DISPLAYSURF.blit(personnage, position_perso)
    return {"player" : personnage, "position_x" : position_perso[0], "position_y":position_perso[1]}

#Créer la map avec toutes les cases
def create_map(tailleMap, tailleServ, box):
    ibis = 1
    i = 0
    x = 100
    y = 0
    taillex = tailleMap / tailleServ
    tailley = tailleMap / tailleServ
    nbrCarre = taillex * tailley

    while i != tailleServ * tailleServ:
        DISPLAYSURF.blit(box, (x,y))
        x = x + taillex
        if ibis == tailleServ:
            ibis = 0
            x = 100
            y = y + tailley
        i = i + 1
        ibis = ibis + 1

#Créer un objet de perssonage avec une couleur
def init_perso(taille, color):
    personnage = pygame.image.load("data/perso_"+color+".png").convert_alpha()
    personnage = pygame.transform.scale(personnage, (int(taille), int(taille)))
    return personnage


#Créer le tableau d'objet avec tous les objet affiché sur l'écran
def init_box_player(tailleMap, tailleServ):
    taille = tailleMap / tailleServ
    box = pygame.image.load("data/image.png").convert()
    box = pygame.transform.scale(box, (int(taille), int(taille)))
    personnage_red = init_perso(taille, "red")
    personnage_blue = init_perso(taille, "blue")
    personnage_pink = init_perso(taille, "pink")
    personnage_green = init_perso(taille, "green")
    energy = pygame.image.load("data/energy.png").convert()
    energy = pygame.transform.scale(energy, (int(taille), int(taille)))
    return {"energy" : energy, "box" : box, "personnage_red" : personnage_red, "personnage_blue" : personnage_blue, "personnage_pink" : personnage_pink, "personnage_green" : personnage_green, "size" : taille}


"""
def event_handler(player, l_object):
    for event in pygame.event.get():
        if event.type == QUIT or (
             event.type == KEYDOWN and (
              event.key == K_ESCAPE or
              event.key == K_q
             )):
            pygame.quit()
            sys.exit()
            quit()
        if event.type == KEYDOWN:
            if event.key == K_DOWN:
                return move_player(player, l_object, "position_y", l_object["size"])
            if event.key == K_UP:
                return move_player(player, l_object, "position_y", -l_object["size"])
            if event.key == K_LEFT:
                return  move_player(player, l_object, "position_x", -l_object["size"])
            if event.key == K_RIGHT:
                return move_player(player, l_object, "position_x", l_object["size"])
    return player
"""

#Change l'objet image de place et met à son ancienne place un carré
"""
def move_player(player, l_object, to_change, change):
    for player in data["data"]["players"]:
        move_player((player["x"]*l_object["size"], player["y"]*l_object["size"]), l_object["personnage"])
    DISPLAYSURF.blit(l_object["box"], (player["position_x"], player["position_y"]))
    DISPLAYSURF.blit(l_object["personnage"], (player["position_x"], player["position_y"]))
    return player
"""

#Place les colonnes et le fond du bas
def fond_information():
    img = pygame.image.load("data/fond.jpg").convert_alpha()
    img = pygame.transform.scale(img, (1000, 200))
    DISPLAYSURF.blit(img, (0, 800))
    img = pygame.image.load("data/colonne.png").convert_alpha()
    img = pygame.transform.scale(img, (100, 800))
    DISPLAYSURF.blit(img, (0, 0))
    DISPLAYSURF.blit(img, (900, 0))


#Place les objets et perssonage
def move_player(data, old_data, l_object, color_plaver):
    if old_data != None:
        for player in old_data["data"]["players"]:
            posx = (player["x"]*l_object["size"]) - l_object["size"]
            posy = (player["y"]*l_object["size"]) - l_object["size"]
            DISPLAYSURF.blit(l_object["box"], (max(posx, 0)+100, max(posy, 0)))

    if old_data != None:
        for energy in old_data["data"]["energy_cells"]:
            posx = (energy["x"]*l_object["size"]) - l_object["size"]
            posy = (energy["y"]*l_object["size"]) - l_object["size"]
            DISPLAYSURF.blit(l_object["box"], (max(posx, 0)+100, max(posy, 0)))

    fond_information()
    for player in data["data"]["players"]:
            color = color_player[player["name"]]["color"]
            posx = (player["x"]*l_object["size"]) - l_object["size"]
            posy = (player["y"]*l_object["size"]) - l_object["size"]
            DISPLAYSURF.blit(l_object["personnage_"+color[0]], (max(posx, 0)+100, max(posy, 0)))
            posx_i =  color_player[player["name"]]["information"][0] + 100
            posy_i = color_player[player["name"]]["information"][1] + 820
            message_display(posx_i, posy_i, "Perssonage : "+player["name"], color[1])
            message_display(posx_i, posy_i  + 30, "Energie        : "+str(player["energy"]), color[1])
            DISPLAYSURF.blit(l_object["personnage_"+color[0]], (max(posx, 0)+100, max(posy, 0)))
            print (player)

    for energy in data["data"]["energy_cells"]:
            posx = (energy["x"]*l_object["size"]) - l_object["size"]
            posy = (energy["y"]*l_object["size"]) - l_object["size"]
            DISPLAYSURF.blit(l_object["energy"], (max(posx, 0)+100, max(posy, 0)))



#Création de la connexion à la PUB
context = zmq.Context()
socket = context.socket(zmq.SUB)
socket.setsockopt_string(zmq.SUBSCRIBE, '')
socket.connect("tcp://127.0.0.1:12345")

#Boucle d'affichage du jeu
index = 0
while True:
    msg = socket.recv_string()
    data = json.loads(msg)
    pygame.display.update()
    if game == False :
        l_object = init_game(800, data["data"]["map_size"])
        game = True
    if len(data["data"]["players"]) == 4 and color_player == {}:
        for player in data["data"]["players"]:
            try:
                color_player[player["name"]].update({"color": color[index], "information": information_position[index]})
            except KeyError:
                color_player[player["name"]] = {"color" : color[index], "information": information_position[index]}


            #color_player[player["name"]]["color"] = color[index]
            #color_player[player["name"]]["information"] = information_position[index]
            index = index + 1
    else:
        move_player(data, old_data, l_object, color_player)
    old_data = data

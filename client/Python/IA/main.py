from __future__ import print_function

import zmq
import time
import random



tab = [
        ["empty", "energy", "empty","#0x02"],
        ["empty", "empty", "empty", "empty"],
        ["energy", "empty", "empty", "empty"],
        ["empty", "empty", "energy", "empty"],
        ["energy", "empty", "energy", "empty"],
        ["empty", "empty", "empty", "energy"],
        ["empty", "energy", "empty", "#0x02"],
        ["empty", "empty", "empty", "empty"],
        ["energy", "empty", "empty", "empty"],
        ["empty", "empty", "energy", "empty"],
        ["energy", "empty", "energy", "empty"],
        ["empty", "empty", "empty", "energy"],
    ]

def action(socket, action) :
    print(action)
    socket.send_string(action)
    message = socket.recv()
    message = str(message)
    response = message.split("'")[1].split('|')
    #simulation reponse looking server
    if action == u"watch|null":
        rand = random.random() * 10000
        identity = int(str(rand)[:1])
        response[1] = tab[identity]
    return response

if __name__ == "__main__":
    context = zmq.Context()
    print("Connecting to hello world server")
    socket = context.socket(zmq.REQ)
    rand = random.random() * 10000
    identity = u"#0X"+str(rand)[:2]
    print(identity)
    socket.setsockopt_string(zmq.IDENTITY, identity)
    socket.connect("tcp://127.0.0.1:4242")
    turn = 1
    pos_energy = None
    next_move = False
    last_mouv = u"rightfwd|null"
    while (42):
        time.sleep(0.5)

        #Si on n'a pas de suite de mouvement logique à faire
        if next_move == False:

            #Regarde devant soi
            pos_energy = None
            response = action(socket, u"watch|null")
            print(response[1])
            if response[1].count("energy") != 0:
                incre_energy = 0
                for case in response[1]:
                    if case == "energy":
                        pos_energy = incre_energy
                        break
                    incre_energy = incre_energy + 1
            time.sleep(0.5)

            #Si on ne trouve pas d'energie
            if action(socket, u"selfstats|null")[1] > 90 or pos_energy == None:
               if action(socket, u"looking|null")[1] == 2:
                   response = action(socket, u"leftfwd|null")
               else:
                   response = action(socket, u"rightfwd|null")

            #Si on trouve de l'energie
            else:
               print (pos_energy)
               response = action(socket, u"forward|null")
               next_move = [u"gather|null"]
               if pos_energy > 0:
                   response = action(socket, u"forward|null")
               if pos_energy == 3:
                   next_move = [u"rightfwd|null"] + next_move
               if pos_energy == 1:
                   next_move = [u"leftfwd|null"] + next_move
               pos_energy = None

        #Si on à une suite de mouvement logique  à faire
        else:
            action(socket, next_move[0])
            if len(next_move) > 1:
                next_move.remove(next_move[0])
            else:
                next_move = False




#Bibliotheques d'interface
import tkinter
from tkinter import ttk
from tkinter import *
from tkinter.ttk import *
import time
import os

import subprocess
import random as rd
#import Robot
#import Main (si le main se declenche pas on met tout dans le main)


dirname = os.getcwd()

window = tkinter.Tk()#Creation d'une fenetre graphique tkinter
window.wm_title("Interface ARKTAUM néon") #Nom de la fenetre
window.minsize(1920,1000) #Dimension minimum
window.maxsize(1920,1000) #Dimension maximum (les deux sont egales, la fenetre n'est pas redimensionnable)


 #La frame est une facon plus pratique de gerer le placement des objets, c'est un "groupement"
#s=Style()
#s.configure('m.frame',background='red')
frame = ttk.Frame(window)
#frame.config()
frame.pack(fill="both",expand='yes')

robotList = dict()
orderList = dict()
mapList = dict()
interface = dict() #Dictionnaire qui va contenir l'interface non modulaire une fois connecte


OrdersData = [["frite","prep",9],["steak","Delivered",42]]
RobotsData = [["Heron","service","occupe"],["Robotino","service","batterie"],["turtlebot_2i","service","libre"],["Nyrio","preparateur","libre"],["Nyrio","preparateur","occupe"],["accueil","accueil","libre"]]

#Affichage du logo de l'entreprise en haut de l'ecran
#logo = tkinter.PhotoImage(file=os.path.join(dirname, 'app_data/logo.png'))

def purge(plist): #La fonction purge permet de vider tout les elements de la frame pour afficher un autre menu
    for i in range(len(plist)):
        if(not isinstance(plist[i],int)):
            plist[i].destroy()

def entry_point():
    purge(interface)
    os.system('screen -X quit')
    #interface[0] = ttk.Label(frame, image = logo)
    #interface[0].pack()
    #interface[1] = ttk.Button(frame, text = 'Connexion', command = lambda : main())
    #interface[1].pack()
   
    interface[0] = ttk.Label(frame, text = '"RestoBot, We go above and beyond the universe for you" - Gerard')
    interface[0].pack(side = 'bottom')
   
    interface[1] = tkinter.Button(frame, text = 'Keyboard control',height =5,width=200 ,font=("Courier",30), bg='RoyalBlue3', command =keyboard_control)
    interface[1].pack(expand=YES)

    interface[2] = tkinter.Button(frame, text = 'suivi personne/camera',height =5,width=200 ,font=("Courier",30),bg='RoyalBlue3',command=interface_client)
    interface[2].pack(expand=YES)
    
    interface[3] = tkinter.Button(frame, text = 'mode autonome',height =5,width=200 ,font=("Courier",30),bg='RoyalBlue3',command=interface_client)
    interface[3].pack(expand=YES)
    
    interface[4] = tkinter.Button(frame, text = 'camera',height =5,width=200 ,font=("Courier",30),bg='RoyalBlue3',command=gamera)
    interface[4].pack(expand=YES)

def interface_pro():
    purge(interface)
    interface[1] = ttk.Button(frame, text = "Retour", command = lambda : entry_point())
    interface[1].place(relx=.85, rely=.97)
    #interface[1] = ttk.Button(frame, text = "Retour", command = lambda : entry_point())
    #interface[1].place(relx=.65, rely=.95)
    interface[2] = tkinter.Button(frame, text = "suivi des robots",height =1,width=200,font=("Courier",30),bg='dark turquoise', command = lambda : suividesrobots())
    interface[2].pack(expand=YES)
    interface[3] = tkinter.Button(frame, text = "liste des robots",height =1,width=200,font=("Courier",30),bg='dark turquoise', command = lambda : listedesrobots())
    interface[3].pack(expand=YES)
    interface[4] = tkinter.Button(frame, text = "liste des articles",height =1,width=200,font=("Courier",30),bg='dark turquoise', command = lambda : listedesarticles())
    interface[4].pack(expand=YES)
    interface[5] = tkinter.Button(frame, text = "liste des commandes",height =1,width=200,font=("Courier",30),bg='dark turquoise', command = lambda : listedescommandes())
    interface[5].pack(expand=YES)
    interface[6] = tkinter.Button(frame, text = "ajout, modif article",height =1,width=200,font=("Courier",30),bg='dark turquoise', command = lambda : ajoutmodifarticle())
    interface[6].pack(expand=YES)
    interface[7] = tkinter.Button(frame, text = "envoie, appel robot",height =1,width=200,font=("Courier",30),bg='dark turquoise', command = lambda : envoieappelrobot())
    interface[7].pack(expand=YES)
    interface[8] = tkinter.Button(frame, text = "ajout des positions cles",height =1,width=200,font=("Courier",30),bg='dark turquoise', command = lambda : ajoutpositionscle())
    interface[8].pack(expand=YES)

def suividesrobots():#remplacee par main
    purge(interface)
    interface[1] = ttk.Button(frame, text = "Retour", command = lambda : interface_pro())
    interface[1].place(relx=.65, rely=.95)
    fmap= LabelFrame(frame, text="Map", padx=20, pady=20)
    interface[2] = fmap
    interface[2].pack(fill="both")
    MyMap(fmap)  


def ajoutpositionscle():
    purge(interface)
    interface[1] = ttk.Button(frame, text = "Retour", command = lambda : interface_pro())
    interface[1].place(relx=.65, rely=.95)

def listedesrobots():
    purge(interface)
    interface[1] = ttk.Button(frame, text = "Retour", command = lambda : interface_pro())
    interface[1].place(relx=.65, rely=.95)

    frobot= LabelFrame(frame, text="Liste de robot", padx=20, pady=20)
    interface[2] = frobot
    interface[2].pack(side='left',fill="both")
    robotspourliste(frobot)

def robotspourliste():
    result = Robot.get_all_Robot(mycursor)
    print("affichage des robots")
   

def listedesarticles():
    purge(interface)
    interface[1] = ttk.Button(frame, text = "Retour", command = lambda : interface_pro())
    interface[1].place(relx=.65, rely=.95)

def listedescommandes():
    purge(interface)
    interface[1] = ttk.Button(frame, text = "Retour", command = lambda : interface_pro())
    interface[1].place(relx=.65, rely=.95)
    forder= LabelFrame(frame, text="Liste des commandes", padx=20, pady=20)
    interface[2] = forder
    interface[2].pack(fill="both")
    MyOrders(forder)


def ajoutmodifarticle():
    purge(interface)
    interface[1] = ttk.Button(frame, text = "Retour", command = lambda : interface_pro())
    interface[1].place(relx=.65, rely=.95)
    interface[2] = tkinter.Button(frame, text = "ajout d'article",height =10,width=200, command = lambda : ajoutarticle())
    interface[2].pack(expand=YES)
    interface[3] = tkinter.Button(frame, text = "suppression d'article",height =10,width=200, command = lambda : supprimearticle())
    interface[3].pack(expand=YES)
    interface[4] = tkinter.Button(frame, text = "modifier article",height =10,width=200, command =lambda : modifarticle())
    interface[4].pack(expand=YES)

def envoieappelrobot():  
    purge(interface)
    interface[1] = ttk.Button(frame, text = "Retour", command = lambda : interface_pro())
    interface[1].place(relx=.65, rely=.95)
 

def ajoutarticle():
    purge(interface)
    interface[1] = ttk.Button(frame, text = "Retour", command = lambda : ajoutmodifarticle())
    interface[1].place(relx=.65, rely=.95)
def supprimearticle():
    purge(interface)
    interface[1] = ttk.Button(frame, text = "Retour", command = lambda : ajoutmodifarticle())
    interface[1].place(relx=.65, rely=.95)
def modifarticle():
    purge(interface)
    interface[1] = ttk.Button(frame, text = "Retour", command = lambda : ajoutmodifarticle())
    interface[1].place(relx=.65, rely=.95)
    
    
    
    
def keyboard_control():
    purge(interface)
    
    os.chdir('/home/pi/sketchbook')
    
    os.system('make upload monitor clean')
    os.system('lxterminal')
    interface[1] = tkinter.Button(frame, text = "Retour", command = lambda : entry_point())
    interface[1].place(relx=.65, rely=.95)


def gamera():
    purge(interface)
    os.system('guvcview')
    interface[1] = tkinter.Button(frame, text = "Retour", command = lambda : entry_point())
    interface[1].place(relx=.65, rely=.95)
    
    
    
    
    
def interface_client():
    purge(interface)
    interface[1] = ttk.Button(frame, text = "Retour", command = lambda : entry_point())
    interface[1].place(relx=.65, rely=.95)
    interface[2] = tkinter.Button(frame, text = "commande ",height =10,width=200, command = commande)
    interface[2].pack(expand=YES)
    interface[3] = tkinter.Button(frame, text = "appelserveur",height =10,width=200, command = appelserveur)
    interface[3].pack(expand=YES)

def commande():
    purge(interface)
    interface[1] = tkinter.Button(frame, text = "Retour", command = lambda : interface_client())
    interface[1].place(relx=.65, rely=.95)
    interface[2] = tkinter.Button(frame, text = "vers la commande",height =10,width=200, command = lambda : affichagecommande())
    interface[2].pack(expand=YES)

def appelserveur():
    purge(interface)
    interface[1] = tkinter.Button(frame, text = "Retour", command = lambda : interface_client())
    interface[1].place(relx=.65, rely=.95)
    interface[2] = ttk.Label(frame, text = "Un serveur a ete appele")
    interface[2].pack(expand=YES)

def affichagecommande():
    purge(interface)
    interface[1] = tkinter.Button(frame, text = "valider commande",height =10,width=200, command = interface_client)
    interface[1].pack(expand=YES)
    interface[2] = ttk.Button(frame, text = "retour", command = lambda : commande())
    interface[2].place(relx=.65, rely=.95)
   

def main():
    purge(interface)
   
    UserData = "RestoBot"#client.GetUserData()
       
    #Affichage du message de bienvenue
    welcomsg = "Suivi des robots"
    interface[0] = ttk.Label(frame, text = welcomsg)
    interface[0].pack()

    #Bouton avec sa frame pour le menu des commandes
    forder= LabelFrame(frame, text="Liste des commandes", padx=20, pady=20)
    frobot= LabelFrame(frame, text="Liste de robot", padx=20, pady=20)
    fmap= LabelFrame(frame, text="Map", padx=20, pady=20)
   
    interface[1] = frobot
    interface[1].pack(side='left',fill="both")
    MyRobots(frobot)
   
    interface[2] = forder
    interface[2].pack(side='right',fill="both")
    MyOrders(forder)

    interface[3] = ttk.Button(frame, text = "Retour", command = lambda : interface_pro())
    interface[3].place(relx=.65, rely=.95)

    interface[4] = fmap
    interface[4].pack(side='top',fill="both")
    MyMap(fmap)  


def MyOrders(forder):
    purge(orderList)
    blankspace = "           "

    for k in range(len(OrdersData)):
        orderList[k] = ttk.Label(forder, text = OrdersData[k][0] + blankspace)
        orderList[k+len(OrdersData)] = ttk.Label(forder, text = OrdersData[k][1]+"  ")
        if OrdersData[k][1] != "Delivered": #Si l'objet n'est pas encore livre, on ne peut pas le sortir de l'historique
            orderList[k+2*len(OrdersData)] = ttk.Button(forder, text = "Please wait")
        else:
            orderList[k+2*len(OrdersData)] = ttk.Button(forder, text = "Forget this", command = lambda a=k: clear_this(OrdersData,a))
       
        orderList[k].grid(row=k,column=0)
        orderList[k+len(OrdersData)].grid(row=k,column=1)
        orderList[k+2*len(OrdersData)].grid(row=k,column=2)
   
    orderList[3*len(OrdersData)] = ttk.Button(forder, text = "Refresh", command = lambda: MyOrders(forder))
    orderList[3*len(OrdersData)].place(relx=.7,rely=.98)
   
def MyRobots(frobot):
    purge(robotList)
    blankspace = "    "
    #robot=Robot.get_all_Robot(mycursor)
    for k in range(len(RobotsData)):
        robotList[k] = ttk.Label(frobot, text = RobotsData[k][0] + blankspace)
        imRob=tkinter.PhotoImage(file=os.path.join(dirname, 'app_data/'+RobotsData[k][1]+'.png')).subsample(3, 3)
        robotList[k+len(RobotsData)] = ttk.Label(frobot, image=imRob)
        robotList[k+len(RobotsData)].image = imRob
        robotList[k+2*len(RobotsData)] = ttk.Label(frobot, text = RobotsData[k][2]+"  ")
        robotList[k+3*len(RobotsData)] = ttk.Button(frobot, text = "Stat", command = lambda k=k: StatRobot(frobot,k))
       
        robotList[k].grid(row=k,column=0)
        robotList[k+len(RobotsData)].grid(row=k,column=1)
        robotList[k+2*len(RobotsData)].grid(row=k,column=2)
        robotList[k+3*len(RobotsData)].grid(row=k,column=3)

    b=len(robotList)
    robotList[b] = ttk.Button(frobot, text = "Refresh", command = lambda: MyRobots(frobot))
    robotList[b].place(relx=.01,rely=.98)

def StatRobot(frobot,k):
    purge(robotList)

    robotList[0] = ttk.Label(frobot, text = RobotsData[k][0])
    robotList[0].pack()

    imRob=tkinter.PhotoImage(file=os.path.join(dirname, 'app_data/'+RobotsData[k][0]+'.png')).subsample(2, 2)
    robotList[1] = ttk.Label(frobot, image=imRob)
    robotList[1].image = imRob
    robotList[1].pack()

    robotList[2] = ttk.Label(frobot, text = "Type :   "+RobotsData[k][1])
    robotList[2].pack()

    robotList[3] = ttk.Label(frobot, text = "Etat :   "+RobotsData[k][2])
    robotList[3].pack()
   
    robotList[4] = ttk.Button(frobot, text = "Retour", command = lambda: MyRobots(frobot))
    robotList[4].place(relx=.01,rely=.98)

   
def MyMap(fmap):
    purge(mapList)
   
    map1 = tkinter.PhotoImage(file=os.path.join(dirname, 'app_data/map.png')).zoom(2, 2)
    map1= map1.subsample(3,3)
    wi=map1.width()
    hi=map1.height()
    mapList[0] = Canvas(fmap,width=wi, height=hi)
    mapList[0].create_image(0, 0, anchor=NW, image=map1)
    mapList[0].image = map1
    mapList[0].pack(fill = "both", expand = "yes")

    color={'batterie':'red','libre':'green','occupe':'blue',}

    for i in range(len(RobotsData)):
        c=color.get(RobotsData[i][2],'black')
        x,y=rd.randint(0,wi),rd.randint(0,hi)
        mapList[2*i+1] = mapList[0].create_oval(x, y, x+10, y+10, outline=c, fill=c)
        mapList[2*i+2] = mapList[0].create_text(x-1-2*len(RobotsData[i][0]), y+8, anchor="nw",text=RobotsData[i][0])

    f=len(mapList)    
    mapList[f] = ttk.Button(fmap, text = "Refresh", command = lambda: MyMap(fmap))
    mapList[f].place(relx=.9,rely=.95)

def clear_this(data,j):  
      orderList[j].destroy()
      orderList[j+len(data)].destroy()
      orderList[j+2*len(data)].destroy()

def move(event):
    "Move the sprite image"
    if event.keysym == 'q':
        mapList[0].move(mapList[1], -10, 0)
        mapList[0].move(mapList[2], -10, 0)
    elif event.keysym == 'd':
        mapList[0].move(mapList[1], 10, 0)
        mapList[0].move(mapList[2], 10, 0)
    elif event.keysym == 'z':
        mapList[0].move(mapList[1], 0, -10)
        mapList[0].move(mapList[2], 0, -10)
    elif event.keysym == 's':
        mapList[0].move(mapList[1], 0, 10)
        mapList[0].move(mapList[2], 0, 10)
    elif event.keysym == 'Left':
        mapList[0].move(mapList[3], -10, 0)
        mapList[0].move(mapList[4], -10, 0)
    elif event.keysym == 'Right':
        mapList[0].move(mapList[3], 10, 0)
        mapList[0].move(mapList[4], 10, 0)
    elif event.keysym == 'Up':
        mapList[0].move(mapList[3], 0, -10)
        mapList[0].move(mapList[4], 0, -10)
    elif event.keysym == 'Down':
        mapList[0].move(mapList[3], 0, 10)
        mapList[0].move(mapList[4], 0, 10)
   

entry_point() #Appelle du point d'entree de la fenetre au demarrage

window.bind("<Key>", move)

window.mainloop() #Bouclage infini sur la fenetre principale

#client.stop() #On s'assure bien que le client quitte le serveur si il coup brusquement
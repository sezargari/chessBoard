import Tkinter as tk
from Tkinter import *
import os


#from stackoverflow on how to make tkinter fullscreen on python 2.7
class FullScreenApp(object):
    def __init__(self, master, **kwargs):
        self.master=master
        pad=3
        self._geom='200x200+0+0'
        master.geometry("{0}x{1}+0+0".format(
            master.winfo_screenwidth()-pad, master.winfo_screenheight()-pad))
        master.bind('<Escape>',self.toggle_geom)            
    def toggle_geom(self,event):
        geom=self.master.winfo_geometry()
        print(geom,self._geom)
        self.master.geometry(self._geom)
        self._geom=geom


root = tk.Tk()
app=FullScreenApp(root)


canvas = tk.Canvas(root, height = 480, width = 800, bg="white")
canvas.pack()

chessBoardView = tk.Frame(root, bg="grey")
chessBoardView.place(relwidth=0.6, relheight=0.85)

options = tk.Frame(root, bg="grey")
options.place(relwidth=0.6, relheight=0.85, relx=0.5)

compElo = Entry(options, width=34, borderwidth = 5)
compElo.grid(row=0, columnspan=2)

eloDown = tk.Button(options, text="Comp Elo Down", padx=48, pady=40, fg="white", bg="#263D42")
eloDown.grid(row=1, column=0);

eloUp = tk.Button(options, text="Comp Elo Up", padx=53, pady=40, fg="white", bg="#263D42")
eloUp.grid(row=1, column=1);

compGame = tk.Button(options, text="Start Game", padx=161, pady=70, fg="white", bg="#263D42")
compGame.grid(row=2, columnspan=2);

endGame = tk.Button(options, text="End Game", padx=165, pady=40, fg="white", bg="#263D42")
endGame.grid(row=4, columnspan=2);

root.mainloop()

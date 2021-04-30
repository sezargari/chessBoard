import Tkinter as tk
from Tkinter import *
import os

"""
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
"""

root = tk.Tk()
#app=FullScreenApp(root)


canvas = tk.Canvas(root, height = 480, width = 800, bg="#263D42")
canvas.pack()

options = tk.Frame(root, bg="white")
options.place(relwidth=0.4, relheight=0.8, relx=0.5, rely=0.1)

compElo = Entry(options, width=34, borderwidth = 5)
compElo.grid(row=0, columnspan=2)

eloDown = tk.Button(options, text="Comp Elo Down", padx=28, pady=30, fg="white", bg="#263D42")
eloDown.grid(row=1, column=0);

eloUp = tk.Button(options, text="Comp Elo Up", padx=33, pady=30, fg="white", bg="#263D42")
eloUp.grid(row=1, column=1);

compGame = tk.Button(options, text="1 Player Game", padx=108, pady=30, fg="white", bg="#263D42")
compGame.grid(row=2, columnspan=2);

userGame = tk.Button(options, text="2 Player Game", padx=108, pady=30, fg="white", bg="#263D42")
userGame.grid(row=3, columnspan=2);

root.mainloop()

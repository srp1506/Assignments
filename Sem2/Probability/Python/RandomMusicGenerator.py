import os
import numpy as np
import pygame
from tkinter import Tk, Button, Label, messagebox, filedialog, Listbox, Scrollbar, RIGHT, Y, END, VERTICAL

def PlayPreviousSong():
    if len(previousSongs) == 0:
        messagebox.showinfo("Random Song Player", "No previous songs.")
        return

    song = previousSongs.pop()
    currentSong = pygame.mixer.music.get_busy()

    try:
        pygame.mixer.music.load(song)
        pygame.mixer.music.play(start=currentSong)
        song_label.config(text="Now playing: " + os.path.basename(song))
    except pygame.error:
        messagebox.showerror("Random Song Player", "Failed to load the song.")

def PlayNextSong():
    if len(songs) == 0:
        if RepeatPlayback:
            ReshuffleSongs()
        else:
            messagebox.showinfo("Random Song Player", "All songs have been played.")
        return

    song = songs.pop(0)
    previousSongs.append(song)

    try:
        pygame.mixer.music.load(song)
        pygame.mixer.music.play()
        song_label.config(text="Now playing: " + os.path.basename(song))
    except pygame.error:
        messagebox.showerror("Random Song Player", "Failed to load the song.")

def PauseSong():
    pygame.mixer.music.pause()

def ResumeSong():
    pygame.mixer.music.unpause()

def SkipSong():
    pygame.mixer.music.stop()
    PlayNextSong()

def ReshuffleSongs():
    global songs, previousSongs
    songs = OriginalSongs[:]
    np.random.shuffle(songs)
    previousSongs = []
    messagebox.showinfo("Random Song Player", "Songs have been reshuffled.")
    song_listbox.delete(0, END)
    song_listbox.insert(END, *songs)
    PlayNextSong()

pygame.mixer.init()

window = Tk()
window.title("Random Song Player")

previous_button = Button(window, text="Previous", command=PlayPreviousSong)
play_button = Button(window, text="Play", command=PlayNextSong)
pause_button = Button(window, text="Pause", command=PauseSong)
resume_button = Button(window, text="Resume", command=ResumeSong)
skip_button = Button(window, text="Skip", command=SkipSong)
reshuffle_button = Button(window, text="Reshuffle", command=ReshuffleSongs)

song_label = Label(window, text="")

song_listbox = Listbox(window, width=50)
song_listbox.pack(pady=10)

scrollbar = Scrollbar(window, orient=VERTICAL, command=song_listbox.yview)
scrollbar.pack(side=RIGHT, fill=Y)
song_listbox.config(yscrollcommand=scrollbar.set)

previous_button.pack(pady=5)
play_button.pack(pady=5)
pause_button.pack(pady=5)
resume_button.pack(pady=5)
skip_button.pack(pady=5)
reshuffle_button.pack(pady=5)
song_label.pack(pady=5)

directory = "/home/soam/Desktop/Probability/Python/Music" 
OriginalSongs = []  
songs = []  
previousSongs = [] 
RepeatPlayback = True 

OriginalSongs = [os.path.join(directory, file) for file in os.listdir(directory) if file.endswith(".mp3")]
songs = OriginalSongs[:]
np.random.shuffle(songs)
song_listbox.insert(END, *songs)

window.mainloop()


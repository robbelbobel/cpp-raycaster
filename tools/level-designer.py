from tkinter import *

# Create Window
window = Tk()
window.title("LVL designer")
window.columnconfigure([0, 1, 2], weight=1, minsize=50)
window.rowconfigure([0, 1], weight=1, minsize=25)

#** WIDGETS & FRAMES **#
# Toolbar
frm_toolbar = Frame(window, background="black")
frm_toolbar.grid(row=0, column=0, sticky='n')

btn_open = Button(frm_toolbar, text="open")
btn_save = Button(frm_toolbar, text="save")
btn_reset = Button(frm_toolbar, text="reset")

btn_open.grid(row=0, column=0)
btn_save.grid(row=0, column=1)
btn_reset.grid(row=0, column=2)

# Main Frame
frm_main = Frame(window)
frm_main.grid(row=1, column=0)

# Name
Label(frm_main, text="Name: ").grid(row=0, column=0)
ent_name = Entry(frm_main)

ent_name.grid(row=0, column=1)

# Textures 
Label(frm_main, text="Texture File Path: ").grid(row=1, column=0)
ent_texture_path = Entry(frm_main)
ent_texture_path.grid(row=1, column=1)

# Map Layouts
btn_textures = Button(frm_main, text="Map Menu")
btn_textures.grid(row=1, column=1)

window.mainloop()
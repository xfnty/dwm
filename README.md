![dwm logo](dwm.png)

# dwm - dynamic window manager
[dwm](dwm.suckless.org) is an extremely fast, small, and dynamic window manager for X.
It is also has [page](https://wiki.archlinux.org/title/dwm) on Arch Wiki.


## Patches
No patches here. It's the original dwm source code.


## Theme
- Pallette: `#EB3232`, `#EB7547`, `#141414`
- Font: `Hack Nerd Font:size=9`
- Background: [link](https://rare-gallery.com/uploads/posts/924281-minimalism-red-simple-background-digital-art.png)


## Requirements
Arch Linux
```
sudo pacman -S base-devel libx11 libxft libxinerama freetype2 fontconfig ttf-hack-nerd
```


## Installation
Edit config.mk to match your local setup (dwm is installed into
the `/usr/local` namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):
```
sudo make clean install
```


## Running dwm
Add the following line to your `.xinitrc` to start dwm using startx:
```
exec dwm
```


## Configuration
The configuration of dwm is done by editing `config.def.h`
and (re)compiling the source code.

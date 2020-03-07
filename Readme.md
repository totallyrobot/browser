# Browser


# Building
## Dependecies
All you need to build this program is WebKit2GTK and GTK3.

Install on debian based systems (e.g. Debian, Ubuntu, Pop!OS, Elemantary):
> \# apt install libgtk-3-dev libwebkit2gtk-4.0-dev

On Arch based distros (e.g. Arch, Manjaro, Arco):
> \# pacman -S gtk3 webkit2gtk

And on Gentoo:
> \# emerge -a net-libs/webkit-gtk x11-libs/gtk+

## Actually building the program

Just run: 
> $ make

And to execute the built program run:
> $ ./browser
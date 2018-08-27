
Debian
====================
This directory contains files used to package dachcoind/dachcoin-qt
for Debian-based Linux systems. If you compile dachcoind/dachcoin-qt yourself, there are some useful files here.

## dachcoin: URI support ##


dachcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install dachcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your dachcoinqt binary to `/usr/bin`
and the `../../share/pixmaps/dachcoin128.png` to `/usr/share/pixmaps`

dachcoin-qt.protocol (KDE)


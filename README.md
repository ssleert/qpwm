# qpwm - quite powerful window manager for X <img src="https://github.com/0xMrNight/0xMrNight/blob/main/assets/wave.gif?raw=true" width="28px">
### 👉 it's small floating window manager from not a programmer 👍
#### if you have a multimonitor setup go [here](https://github.com/ssleert/qpwm/tree/qpwm2)
## some features 💪
- Floating only.
- Fullscreen toggle.
- Window centering.
- Mix of mouse and keyboard workflow.
- Focus with cursor.
## Dependencies for build 🧑‍💻
- `xlib` (*usually `libX11`*).
- `gcc` (*for compile*)
- `make` (*for make*)
## Installation of dependencies
### for Debian based <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/6/66/Openlogo-debianV2.svg/1200px-Openlogo-debianV2.svg.png?raw=true" width="20px"> (*like Ubuntu or mint*)
```fish
sudo apt install gcc make libx11-dev git
```
### for Arch based <img src="https://wiki.installgentoo.com/images/f/f9/Arch-linux-logo.png?raw=true" width="20px"> (*like Manjaro or EndeavourOS*)
```fish
sudo pacman -Sy gcc make libx11 git
```
### for RPM based <img src="https://avatars.githubusercontent.com/u/33972111?s=280&v=4?raw=true" width="20px"> (*like Fedora or OpenSUSE*)
#### for Fedora <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/3/3f/Fedora_logo.svg/1024px-Fedora_logo.svg.png?raw=true" width="20px">
```fish
sudo dnf install gcc make libX11-devel git
```
#### for OpenSUSE <img src="https://en.opensuse.org/images/4/44/Button-filled-colour.png?raw=true" width="20px">
```fish
sudo zypper install gcc make libX11-devel git
```
## Installation of qpwm 🕵️‍♂️
```fish
git clone https://github.com/ssleert/qpwm.git
cd qpwm
sudo make clean install
```
# How to configure? :tipping_hand_person:
### type ``make`` in qpwm dir
### next open ``config.h`` file in your text editor. And configure! :zap:
# :rocket: Running qpwm :rocket:
### add to `.xinitrc`
```fish
exec qpwm
```
If you use ``GDM``, ``SDDM``, ``LightDM`` оr anything other display manager 👤

Add it in /usr/share/xsessions/qpwm.desktop 
```desktop
[Desktop Entry]
Name=qpwm
Comment=This session runs qpwm as window manager 
Exec=qpwm
Type=Application
```
## Default Keybindings :space_invader:
**Window Management**
| combo                      | action                 |
| -------------------------- | -----------------------|
| `Mouse`                    | focus under cursor     |
| `win` + `Left Mouse`       | move window            |
| `win` + `Right Mouse`      | resize window          |
| `win` + `f`                | maximize toggle        |
| `win` + `c`                | center window          |
| `win` + `q`                | kill window            |
| `win` + `1-6`              | desktop swap           |
| `win` + `Shift` +`1-6`     | send window to desktop |
| `win` + `return` (*enter*) | open terminal (st)     |
| `ALT` + `TAB`.             | focus cycle            |
# Thanks!
| person          | action           |
| --------------- | -----------------|
| xZecora         | some fixes       |
| OpenSky         | screenshots      |
# :fire: Screenshots of qpwm :fire:
![qpwm1](https://cdn.discordapp.com/attachments/955362477137362954/957063386154295346/2022-03-26_02-12.png?raw=true)
![qpwm2](https://cdn.discordapp.com/attachments/955362477137362954/957119114235764746/2022-03-26_06-20.png?raw=true)
![qpwm3](https://cdn.discordapp.com/attachments/955362477137362954/957310037682946118/2022-03-26_19-01.png?raw=true)
![qpwm4](https://cdn.discordapp.com/attachments/955362477137362954/957797487303860255/2022-03-28_02-58.png?raw=true)
![qpwm5](https://cdn.discordapp.com/attachments/956938396520042566/957343080120471633/unknown.png?raw=true)
![qpwm6](https://cdn.discordapp.com/attachments/955362477137362954/955533886132215878/2022-03-21_21-30.png?raw=true)
![qpwm7](https://cdn.discordapp.com/attachments/955362477137362954/957434635103649832/unknown.png?raw=true)
![qpwm8](https://cdn.discordapp.com/attachments/955362477137362954/957437016541368420/unknown.png?raw=true)
## Thanks for code :speech_balloon:
- [tinywm](http://incise.org/tinywm.html)
- [dwm](https://dwm.suckless.org)
- [2bwm](https://github.com/venam/2bwm)
- [sowm](https://github.com/dylanaraps/sowm)

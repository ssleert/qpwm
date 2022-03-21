# qpwm - quite power window manager
### it's small floating window manager in ~220 lines of C
## Dependencies
- only `xlib` (*usually `libX11`*).
## Installation
```fish
sudo make clean install
```
# Running qpwm
### add to `.xinitrc`
```bash
exec qpwm
```
If you use GDM, SDDM, LightDM оr anything other display manager

Add it in /usr/share/xsessions/qpwm.desktop 
```
[Desktop Entry]
Name=qpwm
Comment=This session runs qpwm as window manager
Exec=qpwm
Type=Application
```
## Default Keybindings
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
| `win` + `return` (*enter*) | open terminal          |
| `ALT` + `TAB`.             | focus cycle            |
# Screenshots of qpwm
![sfowm](https://github.com/ssleert/qpwm/blob/main/5CqwsnNUOos.jpg?raw=true)

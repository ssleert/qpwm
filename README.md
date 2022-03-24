# qpwm - quite powerful window manager for X 
### 👉 it's small floating window manager from not a programmer 👍
## some features 💪
- Floating only.
- Fullscreen toggle.
- Window centering.
- Mix of mouse and keyboard workflow.
- Focus with cursor.
## Dependencies 🧑‍💻
- only `xlib` (*usually `libX11`*).
## Installation 🕵️‍♂️
```fish
sudo make clean install
```
# :rocket: Running qpwm :rocket:
### add to `.xinitrc`
```bash
exec qpwm
```
If you use GDM, SDDM, LightDM оr anything other display manager 👤

Add it in /usr/share/xsessions/qpwm.desktop 
```
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
# :fire: Screenshots of qpwm :fire:
![qpwm1](https://media.discordapp.net/attachments/955362477137362954/955362504656187392/5CqwsnNUOos.jpg?raw=true)
![qpwm2](https://cdn.discordapp.com/attachments/955362477137362954/955533886132215878/2022-03-21_21-30.png?raw=true)
![qpwm3](https://cdn.discordapp.com/attachments/955362477137362954/955543502110990476/2022-03-21_22-08_1.png?raw=true)
![qpwm4](https://cdn.discordapp.com/attachments/955362477137362954/955544733470580776/2022-03-21_22-13.png?raw=true)

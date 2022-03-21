# qpwm - quite power window manager
## it's small floating window manager in ~220 lines of C
## Installation
```bash
sudo make clean install
```
# Running qpwm
### add to .xinitrc
```bash
exec qpwm
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



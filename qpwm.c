// qpwm - quite power window manager.

#include <X11/XKBlib.h>
#include <X11/extensions/Xinerama.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define NUM_WS 10

#define win (client *t = 0, *c = list; c && t != list->prev; t = c, c = c->next)
#define ws_save(W) ws_list[W] = list
#define ws_sel(W) list = ws_list[ws = W]
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define win_size(W, gx, gy, gw, gh)                                            \
  XGetGeometry(d, W, &(Window){0}, gx, gy, gw, gh, &(unsigned int){0},         \
               &(unsigned int){0})

#define mod_clean(mask)                                                        \
  (mask & ~(numlock | LockMask) &                                              \
   (ShiftMask | ControlMask | Mod1Mask | Mod2Mask | Mod3Mask | Mod4Mask |      \
    Mod5Mask))

typedef struct {
  const char **com;
  const int i;
  const Window w;
} Arg;

struct key {
  unsigned int mod;
  KeySym keysym;
  void (*function)(const Arg arg);
  const Arg arg;
};

typedef struct client {
  struct client *next, *prev;
  int f, wx, wy;
  unsigned int ww, wh;
  Window w;
} client;

int multimonitor_action(int action);
void button_press(XEvent *e);
void button_release(XEvent *e);
void configure_request(XEvent *e);
void input_grab(Window root);
void key_press(XEvent *e);
void map_request(XEvent *e);
void mapping_notify(XEvent *e);
void notify_destroy(XEvent *e);
void notify_enter(XEvent *e);
void notify_motion(XEvent *e);
void run(const Arg arg);
void win_add(Window w);
void win_center(const Arg arg);
void win_del(Window w);
void win_fs(const Arg arg);
void win_focus(client *c);
void win_kill(const Arg arg);
void win_prev(const Arg arg);
void win_next(const Arg arg);
void win_to_ws(const Arg arg);
void ws_go(const Arg arg);
bool exists_win(Window w);
void quit(const Arg arg);

static int xerror() { return 0; }

static client *list = {0}, *ws_list[NUM_WS] = {0}, *cur;
static int ws = 1, sw, sh, wx, wy, numlock = 0, monitors;
static unsigned int ww, wh;

static Display *d;
static XButtonEvent mouse;
static Window root;
static int running = 1;

static void (*events[LASTEvent])(XEvent *e) = {
    [ButtonPress] = button_press,
    [ButtonRelease] = button_release,
    [ConfigureRequest] = configure_request,
    [KeyPress] = key_press,
    [MapRequest] = map_request,
    [MappingNotify] = mapping_notify,
    [DestroyNotify] = notify_destroy,
    [EnterNotify] = notify_enter,
    [MotionNotify] = notify_motion};

#include "config.h"

void win_focus(client *c) {
  cur = c;
  XSetInputFocus(d, cur->w, RevertToParent, CurrentTime);
}

void notify_destroy(XEvent *e) {
  win_del(e->xdestroywindow.window);

  if (list)
    win_focus(list->prev);
}

void notify_enter(XEvent *e) {
  while (XCheckTypedEvent(d, EnterNotify, e))
    ;

    for
      win if (c->w == e->xcrossing.window) win_focus(c);
}

void notify_motion(XEvent *e) {
  if (!mouse.subwindow || cur->f)
    return;

  while (XCheckTypedEvent(d, MotionNotify, e))
    ;

  int xd = e->xbutton.x_root - mouse.x_root;
  int yd = e->xbutton.y_root - mouse.y_root;

  XMoveResizeWindow(d, mouse.subwindow, wx + (mouse.button == 1 ? xd : 0),
                    wy + (mouse.button == 1 ? yd : 0),
                    MAX(1, ww + (mouse.button == 3 ? xd : 0)),
                    MAX(1, wh + (mouse.button == 3 ? yd : 0)));

	win_size(cur->w, &cur->wx, &cur->wx, &cur->ww, &cur->wh);
}

void key_press(XEvent *e) {
  KeySym keysym = XkbKeycodeToKeysym(d, e->xkey.keycode, 0, 0);

  for (unsigned int i = 0; i < sizeof(keys) / sizeof(*keys); ++i)
    if (keys[i].keysym == keysym &&
        mod_clean(keys[i].mod) == mod_clean(e->xkey.state))
      keys[i].function(keys[i].arg);
}

void button_press(XEvent *e) {
  if (!e->xbutton.subwindow)
    return;

  win_size(e->xbutton.subwindow, &wx, &wy, &ww, &wh);
  XRaiseWindow(d, e->xbutton.subwindow);
  mouse = e->xbutton;
}

void button_release(XEvent *e) { mouse.subwindow = 0; }

void win_add(Window w) {
  client *c;

  if (!(c = (client *)calloc(1, sizeof(client))))
    exit(1);

  c->w = w;

  if (list) {
    list->prev->next = c;
    c->prev = list->prev;
    list->prev = c;
    c->next = list;

  } else {
    list = c;
    list->prev = list->next = list;
  }

  ws_save(ws);
}

void win_del(Window w) {
  client *x = 0;

    for
      win if (c->w == w) x = c;

    if (!list || !x)
      return;
    if (x->prev == x)
      list = 0;
    if (list == x)
      list = x->next;
    if (x->next)
      x->next->prev = x->prev;
    if (x->prev)
      x->prev->next = x->next;

    free(x);
    ws_save(ws);
}

void win_kill(const Arg arg) {
  if (cur)
    XKillClient(d, cur->w);
}

int multimonitor_action (int action) { // action = 0 -> center; action = 1 -> fs
    if (!XineramaIsActive(d)) return 1;
    XineramaScreenInfo *si = XineramaQueryScreens(d, &monitors);
    for (int i = 0; i < monitors; i++) {
        if ((cur->wx + (cur->ww/2) >= (unsigned int)si[i].x_org
                && cur->wx + (cur->ww/2) < (unsigned int)si[i].x_org + si[i].width)
            && ( cur->wy + (cur->wh/2) >= (unsigned int)si[i].y_org
                && cur->wy + (cur->wh/2) < (unsigned int)si[i].y_org + si[i].height)) {
            if (action)
                XMoveResizeWindow(d, cur->w,
                                  si[i].x_org, si[i].y_org,
                                  si[i].width, si[i].height);
            else
                XMoveWindow(d, cur->w,
                            si[i].x_org + ((si[i].width - ww)/2),
                            si[i].y_org + ((si[i].height -wh)/2));
            break;
        }
    }
    return 0;
}

void win_center(const Arg arg) {
  if (!cur)
    return;

  win_size(cur->w, &(int){0}, &(int){0}, &ww, &wh);
    if (multimonitor_action(0)) {
        XMoveWindow(d, cur->w, (sw - ww) / 2, (sh - wh) / 2);
    }

    win_size(cur->w, &cur->wx, &cur->wy, &cur->ww, &cur->wh);
}

void win_fs(const Arg arg) {
  if (!cur)
    return;

  if ((cur->f = cur->f ? 0 : 1)) {
    win_size(cur->w, &cur->wx, &cur->wy, &cur->ww, &cur->wh);
        if(multimonitor_action(1)) {
          XMoveResizeWindow(d, cur->w, 0, 0, sw, sh);
        }

  } else {
    XMoveResizeWindow(d, cur->w, cur->wx, cur->wy, cur->ww, cur->wh);
  }
}

void win_to_ws(const Arg arg) {
  int tmp = ws;

  if (arg.i == tmp)
    return;

  ws_sel(arg.i);
  win_add(cur->w);
  ws_save(arg.i);

  ws_sel(tmp);
  win_del(cur->w);
  XUnmapWindow(d, cur->w);
  ws_save(tmp);

  if (list)
    win_focus(list);
}

void win_prev(const Arg arg) {
  if (!cur)
    return;

  XRaiseWindow(d, cur->prev->w);
  win_focus(cur->prev);
}

void win_next(const Arg arg) {
  if (!cur)
    return;

  XRaiseWindow(d, cur->next->w);
  win_focus(cur->next);
}

void ws_go(const Arg arg) {
  int tmp = ws;

  if (arg.i == ws)
    return;

  ws_save(ws);
  ws_sel(arg.i);

    for
      win XMapWindow(d, c->w);

    ws_sel(tmp);

    for
      win XUnmapWindow(d, c->w);

    ws_sel(arg.i);

    if (list)
      win_focus(list);
    else
      cur = 0;
}

void configure_request(XEvent *e) {
  XConfigureRequestEvent *ev = &e->xconfigurerequest;

  XConfigureWindow(d, ev->window, ev->value_mask,
                   &(XWindowChanges){.x = ev->x,
                                     .y = ev->y,
                                     .width = ev->width,
                                     .height = ev->height,
                                     .sibling = ev->above,
                                     .stack_mode = ev->detail});
}

bool exists_win(Window w) {
    int tmp = ws;
    for (int i = 0; i < NUM_WS; ++i) {
        if (i == tmp) continue;
        ws_sel(i);
        for win if (c->w == w) {
            ws_sel(tmp);
            return true;
        }
    }
    ws_sel(tmp);
    return false;
}

void map_request(XEvent *e) {
  Window w = e->xmaprequest.window;
	if (exists_win(w)) return;
  XSelectInput(d, w, StructureNotifyMask | EnterWindowMask);
  win_size(w, &wx, &wy, &ww, &wh);
  win_add(w);
  cur = list->prev;

  if (wx + wy == 0)
    win_center((Arg){0});

  XMapWindow(d, w);
  win_focus(list->prev);
}

void mapping_notify(XEvent *e) {
  XMappingEvent *ev = &e->xmapping;

  if (ev->request == MappingKeyboard || ev->request == MappingModifier) {
    XRefreshKeyboardMapping(ev);
    input_grab(root);
  }
}

void run(const Arg arg) {
  if (fork())
    return;
  if (d)
    close(ConnectionNumber(d));

  setsid();
  execvp((char *)arg.com[0], (char **)arg.com);
  	exit(111);
}

void input_grab(Window root) {
  unsigned int i, j, modifiers[] = {0, LockMask, numlock, numlock | LockMask};
  XModifierKeymap *modmap = XGetModifierMapping(d);
  KeyCode code;

  for (i = 0; i < 8; i++)
    for (int k = 0; k < modmap->max_keypermod; k++)
      if (modmap->modifiermap[i * modmap->max_keypermod + k] ==
          XKeysymToKeycode(d, 0xff7f))
        numlock = (1 << i);

  XUngrabKey(d, AnyKey, AnyModifier, root);

  for (i = 0; i < sizeof(keys) / sizeof(*keys); i++)
    if ((code = XKeysymToKeycode(d, keys[i].keysym)))
      for (j = 0; j < sizeof(modifiers) / sizeof(*modifiers); j++)
        XGrabKey(d, code, keys[i].mod | modifiers[j], root, True, GrabModeAsync,
                 GrabModeAsync);

  for (i = 1; i < 4; i += 2)
    for (j = 0; j < sizeof(modifiers) / sizeof(*modifiers); j++)
      XGrabButton(d, i, MOD | modifiers[j], root, True,
                  ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
                  GrabModeAsync, GrabModeAsync, 0, 0);

  XFreeModifiermap(modmap);
}

void quit(const Arg arg) {
  if (!arg.i) {
    running = 0;
  }
}

int main(void) {
  XEvent ev;

  if (!(d = XOpenDisplay(0)))
    exit(1);

  signal(SIGCHLD, SIG_IGN);
  XSetErrorHandler(xerror);

  int s = DefaultScreen(d);
  root = RootWindow(d, s);
  sw = XDisplayWidth(d, s);
  sh = XDisplayHeight(d, s);

  XSelectInput(d, root, SubstructureRedirectMask);
  XDefineCursor(d, root, XCreateFontCursor(d, 68));
  input_grab(root);

  while (running && !XNextEvent(d, &ev)) // 1 && will forever be here.
    if (events[ev.type])
      events[ev.type](&ev);
}

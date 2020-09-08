/***********************************************************************************
 * Universidad Nacional Arturo Jauretche                                           *
 * Autor: Rosatto Daniel                                                           *
 * Integrador 1: Mpi v2                                                            *
 * Archivo abstract_wm.h                                                          *
 ***********************************************************************************/
#ifndef __ABSTRACT_WM_H_INCLUDED__
#define __ABSTRACT_WM_H_INCLUDED__
  #ifndef NULL
  #define NULL 0
  #endif
  #ifndef FALSE
  #define FALSE 0
  #endif
  #ifndef TRUE
  #define TRUE 1
  #endif
  #include <stdio.h>
  #include <stdbool.h>
  #include <stdint.h>
  #include <unistd.h>
  #include <string.h>
  #include <signal.h>
  #include <xcb/randr.h>
  #include <xcb/xcb_keysyms.h>
  #include <xcb/xcb_icccm.h>
  #include <xcb/xcb_ewmh.h>
  #include <xcb/xcb_xrm.h>
  #include <X11/keysym.h>
  #include "list.h"
  #include "definitions.h"
  #include "types.h"

  ///---Internal Constants---///
  ///---Globals---///
  static xcb_generic_event_t *ev  = NULL;
  static void (*events[XCB_NO_OPERATION])(xcb_generic_event_t *e);
  static unsigned int numlockmask = 0;
  static bool is_sloppy = true;              // by default use sloppy focus
  int sigcode = 0;                           // Signal code. Non-zero if we've been interruped by a signal.
  xcb_connection_t *conn = NULL;             // Connection to X server.
  xcb_ewmh_connection_t *ewmh = NULL;        // Ewmh Connection.
  xcb_screen_t     *screen = NULL;           // Our current screen.
  int randrbase = 0;                         // Beginning of RANDR extension events.
  static uint8_t curws = 0;                  // Current workspace.
  struct client *focuswin = NULL;            // Current focus window.
  static xcb_drawable_t top_win=0;           // Window always on top.
  static struct item *winlist = NULL;        // Global list of all client windows.
  static struct item *monlist = NULL;        // List of all physical monitor outputs.
  static struct item *wslist[WORKSPACES];
  ///---Global configuration.---///
  static const char *atomnames[NB_ATOMS][1] = {
  	{"WM_DELETE_WINDOW"},
  	{"WM_CHANGE_STATE"}
  };

  xcb_atom_t ATOM[NB_ATOMS];
  ///---Functions prototypes---///
  static void run(void);
  static bool setup(int);
  static void install_sig_handlers(void);
  static void start(const Arg *);
  static void mousemotion(const Arg *);
  static void cursor_move(const Arg *);
  static void changeworkspace(const Arg *);
  static void changeworkspace_helper(const uint32_t);
  static void focusnext(const Arg *);
  static void focusnext_helper(bool);
  static void sendtoworkspace(const Arg *);
  static void sendtonextworkspace(const Arg *);
  static void sendtoprevworkspace(const Arg *);
  static void resizestep(const Arg *);
  static void resizestep_aspect(const Arg *);
  static void movestep(const Arg *);
  static void maxvert_hor(const Arg *);
  static void maxhalf(const Arg *);
  static void teleport(const Arg *);
  static void changescreen(const Arg *);
  static void grabkeys(void);
  static void twobwm_restart();
  static void twobwm_exit();
  static void centerpointer(xcb_drawable_t, struct client *);
  static void always_on_top();
  static bool setup_keyboard(void);
  static bool setupscreen(void);
  static int  setuprandr(void);
  static void arrangewindows(void);
  static void prevworkspace();
  static void nextworkspace();
  static void getrandr(void);
  static void raise_current_window(void);
  static void raiseorlower();
  static void setunfocus(void);
  static void maximize(const Arg *);
  static void fullscreen(const Arg *);
  static void unmaxwin(struct client *);
  static void maxwin(struct client *, uint8_t);
  static void maximize_helper(struct client *,uint16_t, uint16_t, uint16_t, uint16_t);
  static void hide();
  static void clientmessage(xcb_generic_event_t *);
  static void deletewin();
  static void unkillable();
  static void fix();
  static void check_name(struct client *);
  static void addtoclientlist(const xcb_drawable_t);
  static void configurerequest(xcb_generic_event_t *);
  static void buttonpress(xcb_generic_event_t *);
  static void unmapnotify(xcb_generic_event_t *);
  static void destroynotify(xcb_generic_event_t *);
  static void circulaterequest(xcb_generic_event_t *);
  static void newwin(xcb_generic_event_t *);
  static void handle_keypress(xcb_generic_event_t *);
  static xcb_cursor_t Create_Font_Cursor(xcb_connection_t *, uint16_t);
  static xcb_keycode_t *xcb_get_keycodes(xcb_keysym_t);
  static xcb_screen_t *xcb_screen_of_display(xcb_connection_t *, int);
  static struct client *setupwin(xcb_window_t);
  static struct client create_back_win(void);
  static void cleanup(void);
  static uint32_t getwmdesktop(xcb_drawable_t);
  static void addtoworkspace(struct client *, uint32_t);
  static void grabbuttons(struct client *);
  static void delfromworkspace(struct client *);
  static void unkillablewindow(struct client *);
  static void fixwindow(struct client *);
  static uint32_t getcolor(const char *);
  static void forgetclient(struct client *);
  static void forgetwin(xcb_window_t);
  static void fitonscreen(struct client *);
  static void getoutputs(xcb_randr_output_t *,const int, xcb_timestamp_t);
  static void arrbymon(struct monitor *);
  static struct monitor *findmonitor(xcb_randr_output_t);
  static struct monitor *findclones(xcb_randr_output_t, const int16_t, const int16_t);
  static struct monitor *findmonbycoord(const int16_t, const int16_t);
  static void delmonitor(struct monitor *);
  static struct monitor *addmonitor(xcb_randr_output_t, const int16_t, const int16_t, const uint16_t, const uint16_t);
  static void raisewindow(xcb_drawable_t);
  static void movelim(struct client *);
  static void movewindow(xcb_drawable_t, const int16_t, const int16_t);
  static struct client *findclient(const xcb_drawable_t *);
  static void setfocus(struct client *);
  static void resizelim(struct client *);
  static void resize(xcb_drawable_t, const uint16_t, const uint16_t);
  static void moveresize(xcb_drawable_t, const uint16_t, const uint16_t,const uint16_t, const uint16_t);
  static void mousemove(const int16_t,const int16_t);
  static void mouseresize(struct client *,const int16_t,const int16_t);
  static void setborders(struct client *,const bool);
  static void unmax(struct client *);
  static bool getpointer(const xcb_drawable_t *, int16_t *,int16_t *);
  static bool getgeom(const xcb_drawable_t *, int16_t *, int16_t *, uint16_t *,uint16_t *, uint8_t *);
  static void configwin(xcb_window_t, uint16_t,const struct winconf *);
  static void sigcatch(const int);
  static void ewmh_init(void);
  static xcb_atom_t getatom(const char *);
  static void getmonsize(int8_t, int16_t *, int16_t *, uint16_t *, uint16_t *,const struct client *);
  static void noborder(int16_t *,struct client *, bool);
  static void movepointerback(const int16_t, const int16_t, const struct client *);
  static void snapwindow(struct client *);
#endif

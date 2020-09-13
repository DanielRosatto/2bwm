/***********************************************************************************
 * Universidad Nacional Arturo Jauretche                                           *
 * Autor: Rosatto Daniel                                                           *
 * Archivo abstract_wm.h                                                           *
 ***********************************************************************************/
#ifndef __CONFIG_H_INCLUDED__
#define __CONFIG_H_INCLUDED__
	#include <stdio.h>
	#include <stdlib.h>
	// #include <stdbool.h>
	#include <sys/types.h>
	#include <unistd.h>
	#include <string.h>
	#include <xcb/randr.h>
	#include <xcb/xcb_ewmh.h>
	#include <xcb/xcb_icccm.h>
	// #include <xcb/xcb_keysyms.h>
	#include <X11/keysym.h>
	#include <signal.h>
	#include "definitions.h"
	// #include <xcb/xcb_icccm.h>
  #include <xcb/xcb_xrm.h>
  // #include <X11/keysym.h>
  #include "types.h"
  #include "list.h"
 /*********************************************************************************
  * Inicio de: Variables globales extraidas de abstract_wm.h                     *
  *********************************************************************************/
	///---Global configuration.---///
	 static const char *atomnames[NB_ATOMS][1] = {{"WM_DELETE_WINDOW"},{"WM_CHANGE_STATE"}};
   static xcb_connection_t *conn;             // Connection to X server.
   static xcb_ewmh_connection_t *ewmh;        // Ewmh Connection.
   static xcb_screen_t     *screen;           // Our current screen.
   static struct item *wslist[WORKSPACES];
	 static struct item *winlist;        // Global list of all client windows.
   #define LOOK_INTO "WM_NAME"
   static const char *ignore_names[] = {"bar", "xclock"};
   static uint8_t curws;                  // Current workspace.
   static xcb_drawable_t top_win;           // Window always on top.
   static xcb_atom_t ATOM[NB_ATOMS];
   static void (*events[XCB_NO_OPERATION])(xcb_generic_event_t *e);
   /* if this is set to true the inner border and outer borders colors will be swapped */
 	 static const bool inverted_colors = true;
   static bool is_sloppy;              // by default use sloppy focus
   static struct client *focuswin;            // Current focus window.
   static unsigned int numlockmask;
   static struct item *monlist;        // List of all physical monitor outputs.
   static int randrbase;                         // Beginning of RANDR extension events.
   static int sigcode;                           // Signal code. Non-zero if we've been interruped by a signal.
   static xcb_generic_event_t *ev;
  /*********************************************************************************
   * FIN de: Variables globales extraidas de config.h                     *
   *********************************************************************************/
 /*********************************************************************************
  * Inicio de: prototipos extraidos de abstract_wm.h                              *
  *********************************************************************************/
   extern void addtoclientlist(const xcb_drawable_t);
	 extern void addtoworkspace(struct client *, uint32_t);
   extern void always_on_top();
	 extern void arrangewindows(void);
	 extern void buttonpress(xcb_generic_event_t *);
   extern void centerpointer(xcb_drawable_t, struct client *);
   extern void check_name(struct client *);
   extern void circulaterequest(xcb_generic_event_t *);
   extern void cleanup(void);
   extern void clientmessage(xcb_generic_event_t *);
   extern void confignotify(xcb_generic_event_t *ev);
   extern void configurerequest(xcb_generic_event_t *);
   extern void configwin(xcb_window_t, uint16_t,const struct winconf *);
   extern xcb_cursor_t Create_Font_Cursor(xcb_connection_t *, uint16_t);
   extern void cursor_move(const Arg *arg);
   extern void changeworkspace(const Arg *arg);
   extern void changeworkspace_helper(const uint32_t);
   extern struct client create_back_win(void);
   extern void deletewin();
   extern void delfromworkspace(struct client *);
   extern void destroynotify(xcb_generic_event_t *);
   extern void enternotify(xcb_generic_event_t *ev);
   extern void ewmh_init(void);
   extern struct client *findclient(const xcb_drawable_t *);
   extern struct monitor *findclones(xcb_randr_output_t, const int16_t, const int16_t);
   extern struct monitor *findmonbycoord(const int16_t, const int16_t);
   extern void fitonscreen(struct client *);
   extern void fix();
   extern void fixwindow(struct client *);
	 extern void focusnext(const Arg *arg);
   extern void focusnext_helper(bool);
   extern void forgetclient(struct client *);
   extern void forgetwin(xcb_window_t);
   extern void fullscreen(const Arg *arg);
   extern uint32_t getcolor(const char *);
   extern xcb_atom_t getatom(const char *);
   extern bool get_unkil_state(xcb_drawable_t win);
   extern bool getgeom(const xcb_drawable_t *, int16_t *, int16_t *, uint16_t *,uint16_t *, uint8_t *);
   extern void getmonsize(int8_t, int16_t *, int16_t *, uint16_t *, uint16_t *,const struct client *);
   extern void getoutputs(xcb_randr_output_t *,const int, xcb_timestamp_t);
   extern bool getpointer(const xcb_drawable_t *, int16_t *,int16_t *);
   extern void getrandr(void);
   extern uint32_t getwmdesktop(xcb_drawable_t);
   extern void grabbuttons(struct client *);
   extern void grabkeys(void);
   extern void handle_keypress(xcb_generic_event_t *);
	 extern void maxvert_hor(const Arg *arg);
   extern void maxhalf(const Arg *arg);
   extern void maximize_helper(struct client *,uint16_t, uint16_t, uint16_t, uint16_t);
   extern void maximize(const Arg *arg);
   extern void maxwin(struct client *, uint8_t);
   extern void mousemotion(const Arg *arg);
   extern void mousemove(const int16_t,const int16_t);
   extern void mouseresize(struct client *,const int16_t,const int16_t);
   extern void moveresize(xcb_drawable_t, const uint16_t, const uint16_t,const uint16_t, const uint16_t);
   extern void movewindow(xcb_drawable_t, const int16_t, const int16_t);
   extern void movelim(struct client *);
   extern void movepointerback(const int16_t, const int16_t, const struct client *);
   extern void movestep(const Arg *arg);
   extern void newwin(xcb_generic_event_t *);
	 extern void new_config(void);
   extern void noborder(int16_t *,struct client *, bool);
   extern void changescreen(const Arg *arg);
   extern void raiseorlower();
   extern void raise_current_window(void);
   extern void raisewindow(xcb_drawable_t);
   extern void resizelim(struct client *);
   extern void resizestep(const Arg *arg);
   extern void resizestep_aspect(const Arg *arg);
   extern void sendtonextworkspace(const Arg *arg);
   extern void nextworkspace();
   extern void sendtoprevworkspace(const Arg *arg);
   extern void hide();
   extern void unkillable();
   extern void prevworkspace();
   extern void resize(xcb_drawable_t, const uint16_t, const uint16_t);
   extern void run(void);
   extern void sendtoprevworkspace(const Arg *arg);
   extern void sendtoworkspace(const Arg *arg);
   extern void setborders(struct client *,const bool);
   extern void setfocus(struct client *);
   extern void setunfocus(void);
   extern void snapwindow(struct client *);
   extern bool setup(int);
   extern bool setup_keyboard(void);
	 extern int  setuprandr(void);
   extern bool setupscreen(void);
   extern struct client *setupwin(xcb_window_t);
   extern void start(const Arg *arg);
   extern void teleport(const Arg *arg);
   extern void twobwm_restart();
   extern void twobwm_exit();
   extern void unkillablewindow(struct client *);
   extern void unmapnotify(xcb_generic_event_t *);
   extern void unmax(struct client *);
   extern void unmaxwin(struct client *);
   extern xcb_keycode_t *xcb_get_keycodes(xcb_keysym_t);
   extern xcb_keysym_t xcb_get_keysym(xcb_keycode_t keycode);
   extern xcb_screen_t *xcb_screen_of_display(xcb_connection_t *, int);
   extern void arrbymon(struct monitor *);
   extern struct monitor *findmonitor(xcb_randr_output_t);
   extern void delmonitor(struct monitor *);
   extern struct monitor *addmonitor(xcb_randr_output_t, const int16_t, const int16_t, const uint16_t, const uint16_t);
   extern void install_sig_handlers(void);
   extern void sigcatch(const int);
/*********************************************************************************
  * Fin De: prototipos extraidos de abstract_wm.h                                 *
  *********************************************************************************/
	extern void halfandcentered(const Arg *arg);
	extern void toggle_sloppy(const Arg *arg);
	extern void saveorigsize(struct client *client);
	extern void updateclientlist(void);
	///---User configurable stuff---///
	///---Modifiers---///
	#define MOD XCB_MOD_MASK_4       /* Super/Windows key  or check xmodmap(1) with -pm  defined in /usr/include/xcb/xproto.h */
	///--Speed---///
	/* Move this many pixels when moving or resizing with keyboard unless the window has hints saying otherwise.
	 *0)move step slow   1)move step fast
	 *2)mouse slow       3)mouse fast     */
	static const uint16_t movements[] = {20,40,15,400};
	/* resize by line like in mcwm -- jmbi */
	static const bool     resize_by_line          = true;
	/* the ratio used when resizing and keeping the aspect */
	static const float    resize_keep_aspect_ratio = 1.03;
	///---Offsets---///
	/*0)offsetx          1)offsety
	 *2)maxwidth         3)maxheight */
	static const uint8_t offsets[] = {0,0,0,0};
	///---Colors---///
	/*0)focuscol         1)unfocuscol
	 *2)fixedcol         3)unkilcol
	 *4)fixedunkilcol    5)outerbordercol
	 *6)emptycol         */
	static const char *colors[] = {"#35586c","#333333","#7a8c5c","#ff6666","#cc9933","#0d131a","#000000"};
	///---Cursor---///
	/* default position of the cursor:
	 * correct values are:
	 * TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, MIDDLE
	 * All these are relative to the current window. */
	#define CURSOR_POSITION MIDDLE
	///---Borders---///
	/*0) Outer border size. If you put this negative it will be a square.
	 *1) Full borderwidth    2) Magnet border size
	 *3) Resize border size  */
	static const uint8_t borders[] = {3,5,5,4};
	/* Windows that won't have a border.
	 * It uses substring comparison with what is found in the WM_NAME
	 * attribute of the window. You can test this using `xprop WM_NAME`
	 */
	///--Menus and Programs---///
	static const char *menucmd[] = { "", NULL };
	///--Custom foo---///
	// void halfandcentered(const Arg *arg)
	// {
	// 	Arg arg2 = {.i=TWOBWM_MAXHALF_VERTICAL_LEFT};
	// 	maxhalf(&arg2);
	// 	Arg arg3 = {.i=TWOBWM_TELEPORT_CENTER};
	// 	teleport(&arg3);
	// }
	///---Sloppy focus behavior---///
	/*
	 * Command to execute when switching from sloppy focus to click to focus
	 * The strings "Sloppy" and "Click" will be passed as the last argument
	 * If NULL this is ignored
	 */
	static const char *sloppy_switch_cmd[] = {};
	//const char *sloppy_switch_cmd[] = { "notify-send", "toggle sloppy", NULL };
	// void toggle_sloppy(const Arg *arg)
	// {
	// 	is_sloppy = !is_sloppy;
	// 	if (arg->com != NULL && LENGTH(arg->com) > 0) {
	// 		start(arg);
	// 	}
	// }
	///---Shortcuts---///
	/* Check /usr/include/X11/keysymdef.h for the list of all keys
	 * 0x000000 is for no modkey
	 * If you are having trouble finding the right keycode use the `xev` to get it
	 * For example:
	 * KeyRelease event, serial 40, synthetic NO, window 0x1e00001,
	 *  root 0x98, subw 0x0, time 211120530, (128,73), root:(855,214),
	 *  state 0x10, keycode 171 (keysym 0x1008ff17, XF86AudioNext), same_screen YES,
	 *  XLookupString gives 0 bytes:
	 *  XFilterEvent returns: False
	 *
	 *  The keycode here is keysym 0x1008ff17, so use  0x1008ff17
	 *
	 *
	 * For AZERTY keyboards XK_1...0 should be replaced by :
	 *      DESKTOPCHANGE(     XK_ampersand,                     0)
	 *      DESKTOPCHANGE(     XK_eacute,                        1)
	 *      DESKTOPCHANGE(     XK_quotedbl,                      2)
	 *      DESKTOPCHANGE(     XK_apostrophe,                    3)
	 *      DESKTOPCHANGE(     XK_parenleft,                     4)
	 *      DESKTOPCHANGE(     XK_minus,                         5)
	 *      DESKTOPCHANGE(     XK_egrave,                        6)
	 *      DESKTOPCHANGE(     XK_underscore,                    7)
	 *      DESKTOPCHANGE(     XK_ccedilla,                      8)
	 *      DESKTOPCHANGE(     XK_agrave,                        9)*
	 */
	#define DESKTOPCHANGE(K,N) \
	{  MOD ,             K,              changeworkspace, {.i=N}}, \
	{  MOD |SHIFT,       K,              sendtoworkspace, {.i=N}},
	// the last argument makes it a root window only event
	static key keys[] = {
			/* modifier           key            function           argument */
			// Focus to next/previous window
			{  MOD ,              XK_Tab,        focusnext,         {.i=TWOBWM_FOCUS_NEXT}},
			{  MOD |SHIFT,        XK_Tab,        focusnext,         {.i=TWOBWM_FOCUS_PREVIOUS}},
			// Kill a window
			{  MOD ,              XK_q,          deletewin,         {}},
			// Resize a window
			{  MOD |SHIFT,        XK_k,          resizestep,        {.i=TWOBWM_RESIZE_UP}},
			{  MOD |SHIFT,        XK_j,          resizestep,        {.i=TWOBWM_RESIZE_DOWN}},
			{  MOD |SHIFT,        XK_l,          resizestep,        {.i=TWOBWM_RESIZE_RIGHT}},
			{  MOD |SHIFT,        XK_h,          resizestep,        {.i=TWOBWM_RESIZE_LEFT}},
			// Resize a window slower
			{  MOD |SHIFT|CONTROL,XK_k,          resizestep,        {.i=TWOBWM_RESIZE_UP_SLOW}},
			{  MOD |SHIFT|CONTROL,XK_j,          resizestep,        {.i=TWOBWM_RESIZE_DOWN_SLOW}},
			{  MOD |SHIFT|CONTROL,XK_l,          resizestep,        {.i=TWOBWM_RESIZE_RIGHT_SLOW}},
			{  MOD |SHIFT|CONTROL,XK_h,          resizestep,        {.i=TWOBWM_RESIZE_LEFT_SLOW}},
			// Move a window
			{  MOD ,              XK_k,          movestep,          {.i=TWOBWM_MOVE_UP}},
			{  MOD ,              XK_j,          movestep,          {.i=TWOBWM_MOVE_DOWN}},
			{  MOD ,              XK_l,          movestep,          {.i=TWOBWM_MOVE_RIGHT}},
			{  MOD ,              XK_h,          movestep,          {.i=TWOBWM_MOVE_LEFT}},
			// Move a window slower
			{  MOD |CONTROL,      XK_k,          movestep,          {.i=TWOBWM_MOVE_UP_SLOW}},
			{  MOD |CONTROL,      XK_j,          movestep,          {.i=TWOBWM_MOVE_DOWN_SLOW}},
			{  MOD |CONTROL,      XK_l,          movestep,          {.i=TWOBWM_MOVE_RIGHT_SLOW}},
			{  MOD |CONTROL,      XK_h,          movestep,          {.i=TWOBWM_MOVE_LEFT_SLOW}},
			// Teleport the window to an area of the screen.
			// Center:
			{  MOD ,              XK_g,          teleport,          {.i=TWOBWM_TELEPORT_CENTER}},
			// Center y:
			{  MOD |SHIFT,        XK_g,          teleport,          {.i=TWOBWM_TELEPORT_CENTER_Y}},
			// Center x:
			{  MOD |CONTROL,      XK_g,          teleport,          {.i=TWOBWM_TELEPORT_CENTER_X}},
			// Top left:
			{  MOD ,              XK_y,          teleport,          {.i=TWOBWM_TELEPORT_TOP_LEFT}},
			// Top right:
			{  MOD ,              XK_u,          teleport,          {.i=TWOBWM_TELEPORT_TOP_RIGHT}},
			// Bottom left:
			{  MOD ,              XK_b,          teleport,          {.i=TWOBWM_TELEPORT_BOTTOM_LEFT}},
			// Bottom right:
			{  MOD ,              XK_n,          teleport,          {.i=TWOBWM_TELEPORT_BOTTOM_RIGHT}},
			// Resize while keeping the window aspect
			{  MOD ,              XK_Home,       resizestep_aspect, {.i=TWOBWM_RESIZE_KEEP_ASPECT_GROW}},
			{  MOD ,              XK_End,        resizestep_aspect, {.i=TWOBWM_RESIZE_KEEP_ASPECT_SHRINK}},
			// Maximize (ignore offset and no EWMH atom)
			{  MOD ,              XK_x,          maximize,          {}},
			// Full screen (disregarding offsets and adding EWMH atom)
			{  MOD |SHIFT ,       XK_x,          fullscreen,        {}},
			// Maximize vertically
			{  MOD ,              XK_m,          maxvert_hor,       {.i=TWOBWM_MAXIMIZE_VERTICALLY}},
			// Maximize horizontally
			{  MOD |SHIFT,        XK_m,          maxvert_hor,       {.i=TWOBWM_MAXIMIZE_HORIZONTALLY}},
			// Maximize and move
			// vertically left
			{  MOD |SHIFT,        XK_y,          maxhalf,           {.i=TWOBWM_MAXHALF_VERTICAL_LEFT}},
			// vertically right
			{  MOD |SHIFT,        XK_u,          maxhalf,           {.i=TWOBWM_MAXHALF_VERTICAL_RIGHT}},
			// horizontally left
			{  MOD |SHIFT,        XK_b,          maxhalf,           {.i=TWOBWM_MAXHALF_HORIZONTAL_BOTTOM}},
			// horizontally right
			{  MOD |SHIFT,        XK_n,          maxhalf,           {.i=TWOBWM_MAXHALF_HORIZONTAL_TOP}},
			//fold half vertically
			{  MOD |SHIFT|CONTROL,XK_y,          maxhalf,           {.i=TWOBWM_MAXHALF_FOLD_VERTICAL}},
			//fold half horizontally
			{  MOD |SHIFT|CONTROL,XK_b,          maxhalf,           {.i=TWOBWM_MAXHALF_FOLD_HORIZONTAL}},
			//unfold vertically
			{  MOD |SHIFT|CONTROL,XK_u,          maxhalf,           {.i=TWOBWM_MAXHALF_UNFOLD_VERTICAL}},
			//unfold horizontally
			{  MOD |SHIFT|CONTROL,XK_n,          maxhalf,           {.i=TWOBWM_MAXHALF_UNFOLD_HORIZONTAL}},
			// Next/Previous screen
			{  MOD ,              XK_comma,      changescreen,      {.i=TWOBWM_NEXT_SCREEN}},
			{  MOD ,              XK_period,     changescreen,      {.i=TWOBWM_PREVIOUS_SCREEN}},
			// Raise or lower a window
			{  MOD ,              XK_r,          raiseorlower,      {}},
			// Next/Previous workspace
			{  MOD ,              XK_v,          nextworkspace,     {}},
			{  MOD ,              XK_c,          prevworkspace,     {}},
			// Move to Next/Previous workspace
			{  MOD |SHIFT ,       XK_v,          sendtonextworkspace,{}},
			{  MOD |SHIFT ,       XK_c,          sendtoprevworkspace,{}},
			// Iconify the window
			{  MOD ,              XK_i,          hide,              {}},
			// Make the window unkillable
			{  MOD ,              XK_a,          unkillable,        {}},
			// Make the window appear always on top
			{  MOD,               XK_t,          always_on_top,     {}},
			// Make the window stay on all workspaces
			{  MOD ,              XK_f,          fix,               {}},
			// Move the cursor
			{  MOD ,              XK_Up,         cursor_move,       {.i=TWOBWM_CURSOR_UP_SLOW}},
			{  MOD ,              XK_Down,       cursor_move,       {.i=TWOBWM_CURSOR_DOWN_SLOW}},
			{  MOD ,              XK_Right,      cursor_move,       {.i=TWOBWM_CURSOR_RIGHT_SLOW}},
			{  MOD ,              XK_Left,       cursor_move,       {.i=TWOBWM_CURSOR_LEFT_SLOW}},
			// Move the cursor faster
			{  MOD |SHIFT,        XK_Up,         cursor_move,       {.i=TWOBWM_CURSOR_UP}},
			{  MOD |SHIFT,        XK_Down,       cursor_move,       {.i=TWOBWM_CURSOR_DOWN}},
			{  MOD |SHIFT,        XK_Right,      cursor_move,       {.i=TWOBWM_CURSOR_RIGHT}},
			{  MOD |SHIFT,        XK_Left,       cursor_move,       {.i=TWOBWM_CURSOR_LEFT}},
			// Start programs
			{  MOD ,              XK_w,          start,             {.com = menucmd}},
			// Exit or restart 2bwm
			{  MOD |CONTROL,      XK_q,          twobwm_exit,       {.i=0}},
			{  MOD |CONTROL,      XK_r,          twobwm_restart,    {.i=0}},
			{  MOD ,              XK_space,      halfandcentered,   {.i=0}},
			{  MOD ,              XK_s,          toggle_sloppy,     {.com = sloppy_switch_cmd}},
			// Change current workspace
				 DESKTOPCHANGE(     XK_1,                             0)
				 DESKTOPCHANGE(     XK_2,                             1)
				 DESKTOPCHANGE(     XK_3,                             2)
				 DESKTOPCHANGE(     XK_4,                             3)
				 DESKTOPCHANGE(     XK_5,                             4)
				 DESKTOPCHANGE(     XK_6,                             5)
				 DESKTOPCHANGE(     XK_7,                             6)
				 DESKTOPCHANGE(     XK_8,                             7)
				 DESKTOPCHANGE(     XK_9,                             8)
				 DESKTOPCHANGE(     XK_0,                             9)
	};
	static Button buttons[] = {
	    {  MOD        ,XCB_BUTTON_INDEX_1,     mousemotion,   {.i=TWOBWM_MOVE}, false},
	    {  MOD        ,XCB_BUTTON_INDEX_3,     mousemotion,   {.i=TWOBWM_RESIZE}, false},
	    {  0          ,XCB_BUTTON_INDEX_3,     start,         {.com = menucmd}, true},
	    {  MOD|SHIFT,  XCB_BUTTON_INDEX_1,     changeworkspace, {.i=0}, false},
	    {  MOD|SHIFT,  XCB_BUTTON_INDEX_3,     changeworkspace, {.i=1}, false},
	    {  MOD|ALT,    XCB_BUTTON_INDEX_1,     changescreen,    {.i=1}, false},
	    {  MOD|ALT,    XCB_BUTTON_INDEX_3,     changescreen,    {.i=0}, false}
	};
#endif

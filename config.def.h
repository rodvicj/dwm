/* See LICENSE file for copyright and license details. */


/* appearance */
static const unsigned int borderpx       = 1;        /* border pixel of windows */
static const unsigned int snap           = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 8;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;     /* 0 means no systray */
static const unsigned int gappih         = 0;       /* horiz inner gap between windows */
static const unsigned int gappiv         = 0;       /* vert inner gap between windows */
static const unsigned int gappoh         = 0;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 0;       /* vert outer gap between windows and screen edge */
static       int smartgaps               = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar                 = 1;        /* 0 means no bar */
static const int topbar                  = 1;        /* 0 means bottom bar */
static const char *fonts[]               = { "Source Code Pro Regular:size=13", "JoyPixels:pixelsize=14:antialias=true:autohint=true" };
static const char *upvol[] = {"amixer", "set", "Master", "2%+", NULL};
static const char *downvol[] = {"amixer", "set", "Master", "2%-", NULL};
static const char *mutevol[] = {"amixer", "set", "Master", "toggle", NULL};
// static const char *upvol[]               = { "/usr/bin/pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%",     NULL };
// static const char *downvol[]             = { "/usr/bin/pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%",     NULL };
// static const char *mutevol[]             = { "/usr/bin/pactl", "set-sink-mute",   "@DEFAULT_SINK@", "toggle",  NULL };
static const char col_gray1[]            = "#1f2227";
static const char col_gray2[]            = "#abb2bf";
static const char col_gray3[]            = "#abb2bf";
static const char col_gray4[]            = "#abb2bf";
static const char col_cyan[]             = "#88c0d0";
static const char col_purple[]           = "#B48EAD";
static const char col_red[]              = "#d54646";
static const char col_green[]            = "#23d18b";
static const char col_yellow[]           = "#d7ba7d";
static const char col_blue[]             = "#81a1c1";
static const char col_info_blue[]        = "#4fc1ff";
static const char col_magenta[]          = "#c586c0";
static const char col_white[]            = "#abb2bf";
static const char col_bg_alt[]           = "#212121";

static const char *colors[][3] = {
	/*               fg         bg         border   */
	[SchemeNorm]     = { col_gray4, col_gray1, col_gray2 },
	[SchemeSel]      = { col_gray4, col_blue,  col_blue  },
	[SchemeStatus]   = { col_gray4, col_gray1,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}

	[SchemeTagsSel]  = { col_info_blue, col_gray1,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
  [SchemeTagsNorm] = { col_gray3, col_gray1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}

  [SchemeInfoSel]  = { col_yellow, col_gray1,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
  [SchemeInfoNorm] = { col_yellow, col_gray1,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* staticstatus */
static const int statmonval = 0;

/* tagging */
static const char *tags[] = { " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 ", " 7 ", " 8 ", " 9 " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "./patches/vanitygaps.c"

/* #include "./patches/fibonacci.c" */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
  { "[\\]",     dwindle },
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ NULL,       NULL },
    /* { "H[]",      deck },*/
	/* { "TTT",      bstack }, */
 	/* { "[@]",      spiral }, */
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { "kitty", NULL };

#include <X11/XF86keysym.h>
#include "./patches/shiftview.c"
static Key keys[] = {
	/* modifier                     key             function        argument */
	{ MODKEY,                       XK_Return,      spawn,          {.v = termcmd } },
	{ MODKEY,			                  XK_b,           spawn,		      SHCMD("feh --bg-fill --randomize ~/Pictures/wallpapers/* &") },
	{ MODKEY|ShiftMask,             XK_b,           togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,           rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,           rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,           focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,           focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,           incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,           incnmaster,     {.i = -1 } },
	// { MODKEY_ALT,                   XK_h,           setmfact,       {.f = -0.05} },
	// { MODKEY_ALT,                   XK_l,           setmfact,       {.f = +0.05} },
	// { MODKEY_ALT,                   XK_j,           setmfact,       {.f = -0.05} },
	// { MODKEY_ALT,                   XK_k,           setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return,      zoom,           {0} },
	{ MODKEY,                       XK_q,           killclient,     {0} },
	{ MODKEY,			                  XK_s,           spawn,		      SHCMD("restream -p") },
	{ MODKEY,                       XK_space,       spawn,          SHCMD("dmenu_run") },
	{ MODKEY|ShiftMask,             XK_space,       setlayout,      {0} }, 
	{ MODKEY,			                  XK_e,           spawn,		      SHCMD("nautilus") },
	{ MODKEY,			                  XK_w,           spawn,		      SHCMD("$BROWSER") },
	{ MODKEY,			                  XK_r,           spawn,		      SHCMD("$TERMINAL -e ranger") },

  
    {MODKEY, XK_o, spawn, SHCMD("flameshot gui -p ~/Pictures/screenshots")},
    {0, XK_Print, spawn, SHCMD("flameshot full -p ~/Pictures/screenshots")},

	// { MODKEY,			                  XK_y,           spawn,		      SHCMD("flameshot gui -p ~/Pictures/screenshots") },
	// { MODKEY|ShiftMask,			        XK_y,           spawn,		      SHCMD("flameshot full -p ~/Pictures/screenshots") },
	{ MODKEY|ShiftMask,			        XK_v,           spawn,		      SHCMD("mpv --profile=low-latency /dev/video0") },
	{ MODKEY,                       XK_semicolon,   spawn,          SHCMD("skippy-xd") },
	{ MODKEY,                       XK_comma,       focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,      focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_l,           shiftview,      {.i = +1 } },
	{ MODKEY,                       XK_h,           shiftview,      {.i = -1 } },
	{ MODKEY,                       XK_t,           setlayout,      {.v = &layouts[0]} }, // tile
	{ MODKEY|ShiftMask,             XK_t,           setlayout,      {.v = &layouts[1]} }, // tile
	{ MODKEY,                       XK_f,           setlayout,      {.v = &layouts[2]} }, // float
	/* { MODKEY|ShiftMask,             XK_f,        setlayout,      {.v = &layouts[3]} }, // float */
	{ MODKEY|ShiftMask,             XK_f,           togglefloating, {0} },
	{ MODKEY,                       XK_c,           setlayout,      {.v = &layouts[4]} }, // monocle
  { MODKEY|ShiftMask,             XK_c,           setlayout,      {.v = &layouts[5]} }, // dwindle
	{ MODKEY,                       XK_g,           togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_g,           defaultgaps,    {0} },
	{ MODKEY|ControlMask,		        XK_comma,       cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period,      cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,       tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,      tagmon,         {.i = +1 } },
	// { MODKEY|ShiftMask,             XK_q,           quit,           {0} },


    {MODKEY | ShiftMask | ControlMask, XK_q, quit, {0}},

	{ MODKEY,                       XK_F2,          spawn,          SHCMD("screenkey -s small --scr 2 -p fixed -g 400x100+4700+25 --opacity .6 --font-color white") },
	{ MODKEY,                       XK_F3,          spawn,          SHCMD("killall screenkey") },
	TAGKEYS(                        XK_1,                           0)
	TAGKEYS(                        XK_2,                           1)
	TAGKEYS(                        XK_3,                           2)
	TAGKEYS(                        XK_4,                           3)
	TAGKEYS(                        XK_5,                           4)
	TAGKEYS(                        XK_6,                           5)
	TAGKEYS(                        XK_7,                           6)
	TAGKEYS(                        XK_8,                           7)
	TAGKEYS(                        XK_9,                           8)
	/* { MODKEY,                       XK_0,      view,           {.ui = ~0 } }, */
	/* { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } }, */
	{ 0,                            XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },
	{ 0,                            XF86XK_AudioMute, spawn, {.v = mutevol } },
	// { MODKEY,                       XK_minus, spawn, {.v = downvol } },
	// { MODKEY,                       XK_equal, spawn, {.v = upvol   } },
	// { MODKEY,                       XK_0, spawn, {.v = mutevol } },
  /* { MODKEY,                       XK_minus,       focusmon,       {.i = -1 } }, */
  /* { MODKEY,                       XK_equal,       focusmon,       {.i = +1 } }, */
  /* { MODKEY,                       XK_0,       focusmon,       {.i = +1 } }, */
  /* { MODKEY|ShiftMask,             XK_minus,       tagmon,         {.i = -1 } }, */
  /* { MODKEY|ShiftMask,             XK_equal,       tagmon,         {.i = +1 } }, */
};


/* bindsym $mod+F1		        restart */
/* bindsym $mod+F2		        exec --no-startup-id screenkey -s small --scr 1 -p fixed -g 600x100+2573+1330 --opacity .9 --font-color white */
/* bindsym $mod+F3	          exec --no-startup-id killall screenkey */
/* bindsym $mod+F12	        exec $term -e nmtui */

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


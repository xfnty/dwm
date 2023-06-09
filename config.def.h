/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=9", "Hack Nerd Font:size=9", "Symbols Nerd Font:size=9" };
static const char dmenufont[]       =   "monospace:size=9";
static const char col_ignore[]      = "#FF00D0";
static const char col_dark[]        = "#222222";
static const char col_gray[]        = "#444444";
static const char col_lightgray[]   = "#A8A8A8";
static const char col_light[]       = "#F5F5F5";
static const char col_primary[]     = "#EB3232";
static const char col_secondary[]   = "#FFAC4E";
static const char *colors[][3]      = {
	/*                     fg              bg           border */
	[SchemeNorm]       = { col_lightgray,  col_dark,    col_gray },
	[SchemeSel]        = { col_dark,       col_dark,    col_primary },
    [SchemeStatus]     = { col_secondary,  col_dark,    col_ignore  }, // Statusbar right {text,background,not used but cannot be empty}
    [SchemeTagsSel]    = { col_light,      col_primary, col_ignore  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]   = { col_lightgray,  col_dark,    col_ignore  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]    = { col_light,      col_dark,    col_ignore  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]   = { col_lightgray,  col_dark,    col_ignore  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

static const char *const autostart[] = {
    NULL,
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance    title       tags mask     isfloating   monitor */
	{ "waterfox",     NULL,       NULL,       1,            0,           -1 },
    { "sublime_text", NULL,       NULL,       2,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[]=",      tile },    /* first entry is default */
	// { "[M]",      monocle },
    { NULL,       NULL },    /* cyclelayout() stop */
};

/* key definitions */
// Mod1Mask - Left Win
// Mod4Mask - Left Alt
#define MODKEY Mod1Mask
#define APPKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_dark, "-nf", col_lightgray, "-sb", col_primary, "-sf", col_light, NULL };
static const char *filemgr[]  = { "kitty", "lf", NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *sublime_cmd[]  = { "sublime", NULL };
static const char *waterfox_cmd[]  = { "waterfox", NULL };

static const Key keys[] = {
	/* modifier             key            function        argument */
	{ APPKEY,               XK_Return,     spawn,          {.v = dmenucmd } },
	{ APPKEY,               XK_w,          spawn,          {.v = termcmd } },
    { APPKEY,               XK_f,          spawn,          {.v = sublime_cmd } },
    { APPKEY,               XK_b,          spawn,          {.v = waterfox_cmd } },
    { APPKEY,               XK_e,          spawn,          {.v = filemgr } },
	{ MODKEY,               XK_Tab,        focusstack,     {.i = +1 } },
	{ MODKEY,               XK_h,          setmfact,       {.f = -0.05} },
	{ MODKEY,               XK_l,          setmfact,       {.f = +0.05} },
	{ MODKEY,               XK_F4,         killclient,     {0} },
	{ MODKEY,               XK_q,          cyclelayout,      {.i = +1} },
	{ MODKEY,               XK_grave,      togglefloating, {0} },
	TAGKEYS(                XK_1,          0)
	TAGKEYS(                XK_2,          1)
	TAGKEYS(                XK_3,          2)
	TAGKEYS(                XK_4,          3)
	TAGKEYS(                XK_5,          4)
	TAGKEYS(                XK_6,          5)
	TAGKEYS(                XK_7,          6)
	TAGKEYS(                XK_8,          7)
	TAGKEYS(                XK_9,          8)
	{ MODKEY|ControlMask,   XK_BackSpace,  quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
    { ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
    { ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Terminess Nerd Font:size=12.2" };
/* static const char dmenufont[]       = "Terminess Nerd Font:size=10.5"; */

static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";

static const char sanker78[]     = "#78003c";
static const char sanker3c[]     = "#3c0078";
static const char sanker22[]     = "#220022";
static const char sankerFP[]     = "#ff00ff";
static const char sankerff[]     = "#ffffff";
static const char sanker0d[]     = "#0db9d7";

static const char *colors[][3]      = {
	/*                    fg         bg         border   */
	[SchemeNorm]      = { "#ff0000", sanker22,  sanker3c  },
	[SchemeSel]       = { sankerff,  sanker78,  sanker78  },
	[SchemeStatus]    = { sankerff,  sanker22,  "#000000" }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]   = { sankerFP,  sanker78,  "#000000" }, // Tagbar left selected {text,background,not used but cannot be empty} FP
	[SchemeTagsNorm]  = { sanker0d,  sanker22,  "#000000" }, // Tagbar left unselected {text,background,not used but cannot be empty} 0d
	[SchemeInfoSel]   = { sankerff,  sanker78,  "#000000" }, // infobar middle  selected {text,background,not used but cannot be empty}
	[SchemeInfoNorm]  = { sankerff,  sanker22,  "#000000" }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "1", "", "", "4", "5", "6", "", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating  isfullscreen monitor */
	{  NULL,     NULL, "OnTheSpot",       0,            1,          0,           -1 },
	{ "Xarchiver", NULL,      NULL,       0,            1,          0,           -1 },
	{ "qimgv",    NULL,       NULL,       0,            1,          0,           -1 },
	{ "vlc",      NULL,       NULL,       0,            1,          0,           -1 },
	{ "steam",    NULL,       NULL,       1 << 1,       0,          0,           -1 },
	{ "Spotify",   NULL,      NULL,       1 << 6,       0,          0,           -1 },
	{ "librewolf", NULL,      NULL,       1 << 2,       0,          0,           -1 },
	{ "librewolf", NULL, "Library",       0,            1,          0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 60;  /* refresh rate (per second) for client move/resize */

#include "horizgrid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "###",      horizgrid },
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/bin/sh", "-c", cmd, NULL } }

/* commands */
/* static char dmenumon[2] = "0"; */ /* component of dmenucmd, manipulated in spawn() */
/* static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL }; */
/* static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-l", "10", NULL }; */
static const char *dmenucmd[] = { "/usr/local/bin/dmenu_run", "-l", "10", NULL };
static const char *termcmd[] = { "/usr/local/bin/st", NULL };
static const char *stbtopcmd[] = { "/usr/local/bin/st", "btop", NULL };
static const char *pcmanfm[] = { "/usr/bin/pcmanfm", NULL };
static const char *clipmenu[] = { "/usr/bin/clipmenu", "-i", NULL };
static const char *librewolf[] = { "/usr/bin/librewolf", NULL };
static const char *maim1[] = { "/bin/sh", "-c", "/usr/bin/maim /home/sanker/Pictures/x11scr/$(date +%Y-%m-%d__%H-%M-%S).png", NULL };
static const char *maim2[] = { "/bin/sh", "-c", "/usr/bin/maim -so | /usr/bin/xclip -se c -t image/png", NULL };
static const char *flameshot[] = { "/usr/bin/flameshot", "gui", NULL };

/* XF86 SNK814 */
static const char *AudioPrev[] = { "/usr/bin/playerctl", "previous", NULL };
static const char *AudioNext[] = { "/usr/bin/playerctl", "next", NULL };
static const char *AudioPlay[] = { "/usr/bin/playerctl", "play-pause", NULL };
static const char *AudioRais[] = { "/usr/bin/wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "5%+", NULL };
static const char *AudioLowe[] = { "/usr/bin/wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "5%-", NULL };
static const char *AudioMute[] = { "/usr/bin/wpctl", "set-mute", "@DEFAULT_AUDIO_SINK@", "toggle", NULL };
static const char *AuMicMute[] = { "/usr/bin/wpctl", "set-mute", "@DEFAULT_AUDIO_SOURCE@", "toggle", NULL };
static const char *MonBrigUp[] = { "/usr/bin/brightnessctl", "s", "10%+", NULL };
static const char *MonBrigDo[] = { "/usr/bin/brightnessctl", "s", "10%-", NULL };
/* XF86 SNK814 */




#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_q,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = pcmanfm } },
	{ MODKEY,                       XK_v,      spawn,          {.v = clipmenu } },
	{ MODKEY,                       XK_b,      spawn,          {.v = librewolf } },
	{ 0,                        XK_Print,      spawn,          {.v = maim1 } },
	{ Mod1Mask|ShiftMask,           XK_s,      spawn,          {.v = maim2 } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = flameshot } },
	{ 0,                XF86XK_AudioPrev,      spawn,          {.v = AudioPrev } },
	{ 0,                XF86XK_AudioNext,      spawn,          {.v = AudioNext } },
	{ 0,                XF86XK_AudioPlay,      spawn,          {.v = AudioPlay } },
	{ 0,         XF86XK_AudioRaiseVolume,      spawn,          {.v = AudioRais } },
	{ 0,         XF86XK_AudioLowerVolume,      spawn,          {.v = AudioLowe } },
	{ 0,                XF86XK_AudioMute,      spawn,          {.v = AudioMute } },
	{ 0,             XF86XK_AudioMicMute,      spawn,          {.v = AuMicMute } },
	{ 0,          XF86XK_MonBrightnessUp,      spawn,          {.v = MonBrigUp } },
	{ 0,        XF86XK_MonBrightnessDown,      spawn,          {.v = MonBrigDo } },
	{ MODKEY|ShiftMask,             XK_v,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ Mod1Mask,                     XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
/*	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_n,      setlayout,      {0} }, */
	{ MODKEY|ControlMask,           XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  togglefloating, {0} },
	{ Mod1Mask|ShiftMask,           XK_f,      togglefullscr,  {0} },
/*	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } }, */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_t,                      5)
	TAGKEYS(                        XK_r,                      6)
	TAGKEYS(                        XK_f,                      7)
	TAGKEYS(                        XK_g,                      8)
	{ MODKEY|ShiftMask,             XK_l,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_p,      quit,           {1} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
/*	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} }, */
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = AudioPrev } },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = stbtopcmd } },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = AudioNext } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
/*	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} }, */
};

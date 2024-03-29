/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const char font[]            = "-*-terminus-medium-r-*-*-16-*-*-*-*-*-iso10646-*";
static const char normbordercolor[] = "#3F3F3F";
static const char normbgcolor[]     = "#3F3F3F";
static const char normfgcolor[]     = "#DCDCCC";
static const char selbordercolor[]  = "#6F6F6F";
static const char selbgcolor[]      = "#1E2320";
static const char selfgcolor[]      = "#F0DFAF";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = {
	"[ www /",  // 1
	"code /",   // 2
	"manage /",     // 3
	"msg /",    // 4
	"media /",  // 5
	"6 /",
	"7 /",
	"srv /",    // 8
	"sys ]"     // 9
};

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	/* { "Gimp",     NULL,       NULL,       0,            True,        -1 }, */
	{ NULL,  NULL,      "music",       1 << 4,       False,       -1 },
	{ NULL,  NULL,      "jabber",       1 << 3,       False,       -1 },
	{ "Google-chrome",  NULL,      NULL,    1,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[ tiled ][",      tile },    /* first entry is default */
	{ "[ float ][",      NULL },    /* no layout function means floating behavior */
	{ "[ _mono ][",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* volume control */
/* static const int master_vol = 50; */
static const char *volume_mute_cmd[] = { "amixer", "-q", "sset", "Master", "toggle", NULL };
static const char *volume_up_cmd[] = { "amixer", "-q", "sset", "Master", "5+", "unmute", NULL };
static const char *volume_down_cmd[] = { "amixer", "-q", "sset", "Master", "5-", "unmute", NULL };

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "urxvt256cc", NULL };
/* custom commands */
static const char *file_manager_cmd[] = { "urxvt256cc", "-e", "/usr/libexec/mc/mc-wrapper.sh", NULL };
static const char *audio_player_cmd[] = { "urxvt256cc", "--title", " music", "-e", "/bin/mocp", NULL };
static const char *jabber_client_cmd[] = { "urxvt256cc", "--title", "jabber", "-e", "/bin/mcabber", NULL };
static const char *browser_cmd[] = { "google-chrome", NULL };
/* power commands */
static const char *suspend_cmd[] = { "urxvt256cc", "-e", "sudo", "/usr/sbin/pm-suspend", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    /* Custom commands */
    { MODKEY|ShiftMask,             XK_b,      spawn,          {.v = browser_cmd } },
    { MODKEY|ShiftMask,             XK_i,      spawn,          {.v = jabber_client_cmd } },
    { MODKEY|ShiftMask,             XK_a,      spawn,          {.v = audio_player_cmd } },
    { MODKEY|ShiftMask,             XK_f,      spawn,          {.v = file_manager_cmd } },
    /* volume controls */
    { NULL,                         XF86XK_AudioMute,    spawn,  {.v = volume_mute_cmd } },
    { NULL,                         XF86XK_AudioRaiseVolume,    spawn,  {.v = volume_up_cmd } },
    { NULL,                         XF86XK_AudioLowerVolume,    spawn,  {.v = volume_down_cmd } },
    /* syspend */
    { NULL,                         XF86XK_Suspend,    spawn,     {.v = suspend_cmd } },
    /* Custom commands */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


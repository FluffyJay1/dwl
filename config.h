/* appearance */
static const int sloppyfocus        = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const int lockfullscreen     = 1;  /* 1 will force focus on the fullscreen window */
static const unsigned int gappih    = 8;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 8;       /* vert inner gap between windows */
static const unsigned int gappoh    = 8;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 8;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int monoclegaps        = 0;        /* 1 means outer gaps in monocle layout */
/* To conform the xdg-protocol, set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]  = {0.1, 0.1, 0.1, 1.0};
static const int smartborders       = 1;
// sometimes in smart gaps, we still want to leave a small outer gap for the bar
static const int smartbargaps = 1; // 1 = enable
static const int smartbargaptop = 0; // upper gap (pixels) if we in smartgaps mode
static const int smartbargapbot = 8; // lower gap (pixels) if we in smartgaps mode
static const char cursortheme[]     = "Future-cyan"; /* theme from /usr/share/cursors/xorg-x11 */
static const unsigned int cursorsize = 24;
static const int cursor_timeout = 5;
static const int mons_view_same_tag = 0; /* Whether changing which tag to view affects all monitors or just the current one */
static const int scratchmingapv = 64; /* min outer vertical gap for items brought from the scratchtray */
static const int scratchmingaph = 64; /* min outer horizontal gap for items brought from the scratchtray */

/* pointer constraints */
static const int allow_constrain      = 1;

/* tagging - TAGCOUNT must be no greater than 31 */
#define TAGCOUNT (9)

/* logging */
static int log_level = WLR_ERROR;

static const Rule rules[] = {
	/* app_id     title       tags mask     isfloating   monitor */
	/* examples:
	{ "Gimp",     NULL,       0,            1,           -1 },
	*/
	{ "firefox",  NULL,       1 << 8,       1,           -1 }, // make firefox (and all its popups) floating
	{ "firefox",  "Mozilla Firefox",       1 << 8,       0,           -1 }, // then unfloat the actual browser, leaving all popups floated
	{ "file-",  NULL, 0,       1,           -1 },  // gimp's export file prompt should float
	{ "pavucontrol-qt",  NULL, 0,       1,           -1 },
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* monitors */
static const MonitorRule monrules[] = {
	/* name       mfact nmaster scale layout       rotate/reflect                x    y */
	/* example of a HiDPI laptop monitor:
	{ "eDP-1",    0.5,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	*/
	/* defaults */
	{ NULL,       0.55, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
};

/*
 * Priority of monitors to focus upon starting up, apps in your startup script
 * will now launch in that monitor
 */
static const char* main_mon_priority[] = {
	"HDMI-A-1",
	"eDP-1",
};

static const SwallowRule swallowrules[] = {
	/* app_id, title, autoswallow */
	{ NULL, NULL, 1 },
};

static const TerminalRule termrules[] = {
	/* app_id, title, isterminal */
	{ "foot", NULL, 1 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/
	.options = NULL,
};

static const int repeat_rate = 25;
static const int repeat_delay = 300;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 1;
static const int disable_while_typing = 0;
static const int left_handed = 0;
static const int middle_button_emulation = 1; // left + right button at the same time
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT;
static const double accel_speed = 0.0;

/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the windows key change this to WLR_MODIFIER_LOGO */
#define MODKEY WLR_MODIFIER_LOGO
#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[] = { "foot", NULL }; // if we use footclient, swallowing doesn't work properly
static const char *menucmd[] = { "fuzzel",	NULL};
/* command that gets run when you focus a new monitor via keyboard, output name gets passed as the first argument */
static const char *focusmoncmd = "focusmon.sh";
/* command that accepts args from the describeclient function (configured mod + shift + lmb) */
static const char *describeclientcmd = "describeclient.sh";
/* dmenu-like command that accepts scratchtray names from stdin, lets you choose, and outputs the _index_ of the choice to stdout */
static const char *scratchtraymenucmd = "fuzzel --dmenu --index";

static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                  key                 function        argument */
	{ MODKEY,                    XKB_KEY_p,          spawn,          {.v = menucmd} },
	{ MODKEY,                    XKB_KEY_n,          spawn,          {.v = termcmd} },
	{ MODKEY,                    XKB_KEY_j,          focusstack,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_k,          focusstack,     {.i = -1} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_J,          movestack,      {.i = +1} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_K,          movestack,      {.i = -1} },
	{ MODKEY,                    XKB_KEY_i,          incnmaster,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_d,          incnmaster,     {.i = -1} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_H,          setmfact,       {.f = -0.05} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_L,          setmfact,       {.f = +0.05} },
	{ MODKEY,                    XKB_KEY_Return,     zoom,           {0} },
	{ MODKEY,                    XKB_KEY_Tab,        view,           {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_C,          killclient,     {0} },
	{ MODKEY,                    XKB_KEY_t,          setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                    XKB_KEY_f,          setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                    XKB_KEY_m,          setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                    XKB_KEY_space,      setlayout,      {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_space,      togglefloating, {0} },
	{ MODKEY,                    XKB_KEY_e,         togglefullscreen, {0} },
	{ MODKEY,                    XKB_KEY_0,          view,           {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_parenright, tag,            {.ui = ~0} },
	{ MODKEY,                    XKB_KEY_comma,      focusmon,       {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                    XKB_KEY_period,     focusmon,       {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_less,       tagmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_greater,    tagmon,         {.i = WLR_DIRECTION_RIGHT} },
	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                     0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_at,                         1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_numbersign,                 2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                     3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                    4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_asciicircum,                5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_ampersand,                  6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_asterisk,                   7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_parenleft,                  8),
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT, XKB_KEY_Escape, quit, {0} },
	{ MODKEY,                    XKB_KEY_s,          swallowspit,    {.i = 0} },
	{ MODKEY,                    XKB_KEY_backslash,  scratchtraymenu,{0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_bar,        sendtoscratchtray,{0} },

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),

	// custom keys
	// volume control w/ laptop keys, requires alsa
	{0, XKB_KEY_XF86AudioRaiseVolume, spawn, SHCMD("amixer -qR set Master 5%+")},
	{0, XKB_KEY_XF86AudioLowerVolume, spawn, SHCMD("amixer -qR set Master 5%-")},
	{WLR_MODIFIER_SHIFT, XKB_KEY_XF86AudioRaiseVolume, spawn, SHCMD("amixer -qR set Master 20%+")},
	{WLR_MODIFIER_SHIFT, XKB_KEY_XF86AudioLowerVolume, spawn, SHCMD("amixer -qR set Master 20%-")},
	{0, XKB_KEY_XF86AudioMute, spawn, SHCMD("amixer -qR set Master toggle")},

	// brightness control with laptop keys, requires acpilight and a changebrightness.sh script
	{0, XKB_KEY_XF86MonBrightnessUp, spawn, SHCMD("changebrightness.sh inc")},
	{0, XKB_KEY_XF86MonBrightnessDown, spawn, SHCMD("changebrightness.sh dec")},

	// screenshotting w/ prtscr button, requires prtscr, screenshot, snip scripts
	{0, XKB_KEY_Print, spawn, SHCMD("prtscr")},
	{WLR_MODIFIER_CTRL, XKB_KEY_Print, spawn, SHCMD("screenshot")},
	{WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT, XKB_KEY_Print, spawn, SHCMD("snip")},

	// sleep button = lock lol
	{0, XKB_KEY_XF86Sleep, spawn, SHCMD("lock")},
};

static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
	{ MODKEY|WLR_MODIFIER_SHIFT, BTN_LEFT, describeclient, {0} },
};

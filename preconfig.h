/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }
/* simple configuration settings that can be included early in dwl.c */
static const unsigned int borderpx[] = {2, 1, 1}; /* borders pixel of windows */
static const unsigned int borderpxsum = 4;
static const float rootcolor[]      = {0.0, 0.0, 0.0, 1.0};
static const float bordercolor[][4] = {
	{0.07, 0.08, 0.10, 0.8}, /* outer */
	{0.07, 0.09, 0.11, 1.0}, /* inner */
	{0.07, 0.10, 0.12, 1.0}, /* innerest */
};
static const float floatcolor[][4] = {
	{0.12, 0.12, 0.07, 0.8},
	{0.13, 0.13, 0.07, 1.0},
	{0.16, 0.16, 0.07, 1.0},
};
static const float focuscolor[][4] = {
	{0.07, 0.15, 0.15, 0.8},
	COLOR(0x4588b8ff),
	COLOR(0x30cca0ff),
};
static const float urgentcolor[][4] = {
	{0.2, 0.02, 0.0, 0.8},
	{1.0, 0.8, 0.0, 1.0},
	{1.0, 0.9, 0.1, 1.0},
};


/* simple configuration settings that can be included early in dwl.c */
static const unsigned int borderpx[] = {2, 2}; /* borders pixel of windows */
static const unsigned int borderpxsum = 2;
static const float rootcolor[]      = {0.3, 0.3, 0.3, 1.0};
static const float bordercolor[][4] = {
	{0.07, 0.08, 0.10, 0.8}, /* outer */
	{0.07, 0.09, 0.11, 1.0} /* inner */
};
static const float floatcolor[][4] = {
	{0.12, 0.12, 0.07, 0.8},
	{0.13, 0.13, 0.07, 1.0}
};
static const float focuscolor[][4] = {
	{0.07, 0.15, 0.15, 0.8},
	{0.27, 0.53, 0.72, 1.0},
};
static const float urgentcolor[][4] = {
	{0.2, 0.02, 0.0, 0.8},
	{1.0, 0.8, 0.0, 1.0},
};


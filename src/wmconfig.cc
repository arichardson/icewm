/*
 * IceWM
 *
 * Copyright (C) 1997-2002 Marko Macek
 */
#include "config.h"
#include "ykey.h"
#include "ylib.h"

#include "yprefs.h"

#define CFGDEF
#include "wmconfig.h"
#include "bindkey.h"
#include "default.h"

#include "wmoption.h"
#include "wmmgr.h"
#include "yaction.h"
#include "yapp.h"

#include "intl.h"

long workspaceCount = 0;
char *workspaceNames[MAXWORKSPACES];
YAction *workspaceActionActivate[MAXWORKSPACES];
YAction *workspaceActionMoveTo[MAXWORKSPACES];

void loadConfiguration(const char *fileName) {
    YApplication::loadConfig(icewm_preferences, fileName);
    YApplication::loadConfig(icewm_themable_preferences, fileName);
}

void loadThemeConfiguration(const char *fileName) {
    YApplication::loadConfig(icewm_themable_preferences, fileName);
}

void freeConfiguration() {
    freeConfig(icewm_preferences);
}

void addWorkspace(const char */*name*/, const char *value) {
    if (workspaceCount >= MAXWORKSPACES)
        return;
    workspaceNames[workspaceCount] = newstr(value);
    workspaceActionActivate[workspaceCount] = new YAction(); // !! fix
    workspaceActionMoveTo[workspaceCount] = new YAction();
    PRECONDITION(workspaceNames[workspaceCount] != NULL);
    workspaceCount++;
}

void setLook(const char */*name*/, const char *arg) {
#ifdef CONFIG_LOOK_WARP4
    if (strcmp(arg, "warp4") == 0)
        wmLook = lookWarp4;
    else
#endif
#ifdef CONFIG_LOOK_WARP3
    if (strcmp(arg, "warp3") == 0)
        wmLook = lookWarp3;
    else
#endif
#ifdef CONFIG_LOOK_WIN95
    if (strcmp(arg, "win95") == 0)
        wmLook = lookWin95;
    else
#endif
#ifdef CONFIG_LOOK_MOTIF
    if (strcmp(arg, "motif") == 0)
        wmLook = lookMotif;
    else
#endif
#ifdef CONFIG_LOOK_NICE
    if (strcmp(arg, "nice") == 0)
        wmLook = lookNice;
    else
#endif
#ifdef CONFIG_LOOK_PIXMAP
    if (strcmp(arg, "pixmap") == 0)
        wmLook = lookPixmap;
    else
#endif
#ifdef CONFIG_LOOK_METAL
    if (strcmp(arg, "metal") == 0)
        wmLook = lookMetal;
    else
#endif
#ifdef CONFIG_LOOK_GTK
    if (strcmp(arg, "gtk") == 0)
        wmLook = lookGtk;
    else
#endif
    {
        msg(_("Bad Look name"));
    }
}

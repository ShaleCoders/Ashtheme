/*
 * Copyright (c) 2003-2004 E. Will et al.
 * Copyright (c) 2005-2008 Atheme Development Group
 * Copyright (c) 2008-2010 ShadowIRCd Development Group
 * Copyright (c) 2013 PonyChat Development Group
 * Rights to this code are documented in doc/LICENSE.
 *
 * This file contains protocol support for ponychat-ircd.
 *
 */

#include "atheme.h"
#include "uplink.h"
#include "pmodule.h"
#include "protocol/shadowircd.h"

DECLARE_MODULE_V1("protocol/foxaircd", true, _modinit, NULL, PACKAGE_STRING, "foxaIRCd <root@foxatomic.net>");

/* *INDENT-OFF* */

ircd_t foxaircd = {
    "foxaircd",		            /* IRCd name */
    "$$",                           /* TLD Prefix, used by Global. */
    true,                           /* Whether or not we use IRCNet/TS6 UID */
    false,                          /* Whether or not we use RCOMMAND */
    true,                           /* Whether or not we support channel owners. */
    true,                           /* Whether or not we support channel protection. */
    true,                           /* Whether or not we support halfops. */
    false,				/* Whether or not we use P10 */
    false,				/* Whether or not we use vHosts. */
    CMODE_EXLIMIT | CMODE_PERM | CMODE_IMMUNE, /* Oper-only cmodes */
    CSTATUS_OWNER,                  /* Integer flag for owner channel flag. */
    CSTATUS_PROTECT,                  /* Integer flag for protect channel flag. */
    CSTATUS_HALFOP,                   /* Integer flag for halfops. */
    "+q",                           /* Mode we set for owner. */
    "+a",                           /* Mode we set for protect. */
    "+h",                           /* Mode we set for halfops. */
    PROTOCOL_SHADOWIRCD,		/* Protocol type */
    CMODE_PERM,                     /* Permanent cmodes */
    CMODE_IMMUNE,                   /* Oper-immune cmode */
    "beIy",                         /* Ban-like cmodes */
    'e',                            /* Except mchar */
    'I',                            /* Invex mchar */
    IRCD_CIDR_BANS | IRCD_HOLDNICK  /* Flags */
};

struct cmode_ foxaircd_mode_list[] = {
    { 'i', CMODE_INVITE },
    { 'm', CMODE_MOD    },
    { 'n', CMODE_NOEXT  },
    { 'p', CMODE_PRIV   },
    { 's', CMODE_SEC    },
    { 't', CMODE_TOPIC  },
    { 'c', CMODE_NOCOLOR},
    { 'r', CMODE_REGONLY},
    { 'u', CMODE_OPMOD  },
    { 'g', CMODE_FINVITE},
    { 'L', CMODE_EXLIMIT},
    { 'P', CMODE_PERM   },
    { 'F', CMODE_FTARGET},
    { 'Q', CMODE_DISFWD },
    { 'M', CMODE_IMMUNE },
    { 'C', CMODE_NOCTCP },
    { 'A', CMODE_ADMINONLY },
    { 'O', CMODE_OPERONLY },
    { 'S', CMODE_SSLONLY },
    { 'D', CMODE_NOACTIONS },
    { 'T', CMODE_NONOTICE },
    { 'G', CMODE_NOCAPS },
    { 'E', CMODE_NOKICKS },
    { 'N', CMODE_NONICKS },
    { 'K', CMODE_NOREPEAT },
    { 'J', CMODE_KICKNOREJOIN },
    { '\0', 0 }
};

struct cmode_ foxaircd_status_mode_list[] = {
    { 'q', CSTATUS_OWNER },
    { 'a', CSTATUS_PROTECT },
    { 'o', CSTATUS_OP    },
    { 'h', CSTATUS_HALFOP },
    { 'v', CSTATUS_VOICE },
    { '\0', 0 }
};

struct cmode_ foxaircd_prefix_mode_list[] = {
    { '~', CSTATUS_OWNER },
    { '&', CSTATUS_PROTECT },
    { '@', CSTATUS_OP    },
    { '%', CSTATUS_HALFOP },
    { '+', CSTATUS_VOICE },
    { '\0', 0 }
};

struct cmode_ foxaircd_user_mode_list[] = {
    { 'a', UF_ADMIN    },
    { 'i', UF_INVIS    },
    { 'o', UF_IRCOP    },
    { 'D', UF_DEAF     },
    { '\0', 0 }
};

/* *INDENT-ON* */
static void dakota_join_sts(channel_t *c, user_t *u, bool isnew, char *modes)
{
    if (isnew) {
        sts(":%s SJOIN %lu %s %s :%s", ME, (unsigned long)c->ts,
            c->name, modes, CLIENT_NAME(u));
        sts(":%s TMODE %lu %s +o %s", CLIENT_NAME(u),
            (unsigned long)c->ts, c->name,
            CLIENT_NAME(u), CLIENT_NAME(u));
    } else {
        sts(":%s SJOIN %lu %s + :%s", ME, (unsigned long)c->ts,
            c->name, CLIENT_NAME(u));
        sts(":%s TMODE %lu %s +o %s", CLIENT_NAME(u),
            (unsigned long)c->ts, c->name,
            CLIENT_NAME(u), CLIENT_NAME(u));
    }
}

static void dakota_chan_lowerts(channel_t *c, user_t *u)
{
    slog(LG_DEBUG, "ts6_chan_lowerts(): lowering TS for %s to %lu",
         c->name, (unsigned long)c->ts);
    sts(":%s SJOIN %lu %s %s :%s", ME, (unsigned long)c->ts, c->name,
        channel_modes(c, true), CLIENT_NAME(u));
    sts(":%s TMODE %lu %s +o %s", CLIENT_NAME(u),
        (unsigned long)c->ts, c->name,
        CLIENT_NAME(u), CLIENT_NAME(u));
    if (ircd->uses_uid)
        chanban_clear(c);
}

static bool dakota_is_valid_host(const char *host)

{
    return true;
}

void _modinit(module_t * m)
{
    MODULE_TRY_REQUEST_DEPENDENCY(m, "protocol/charybdis");

    mode_list = foxaircd_mode_list;
    user_mode_list = foxaircd_user_mode_list;
    join_sts = &dakota_join_sts;
    chan_lowerts = &dakota_chan_lowerts;
    status_mode_list = foxaircd_status_mode_list;
    prefix_mode_list = foxaircd_prefix_mode_list;
    is_valid_host = &dakota_is_valid_host;

    ircd = &foxaircd;

    m->mflags = MODTYPE_CORE;

    pmodule_loaded = true;
}

/* vim:cinoptions=>s,e0,n0,f0,{0,}0,^0,=s,ps,t0,c3,+s,(2s,us,)20,*30,gs,hs
 * vim:ts=8
 * vim:sw=8
 * vim:noexpandtab
 */

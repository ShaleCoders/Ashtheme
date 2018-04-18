/*
 * Copyright (c) 2014-2016 Xtheme Development Group (Xtheme.org)
 * Rights to this code are as documented in doc/LICENSE.
 *
 * This file contains code for the ChanServ MASS PROTECT function.
 *
 */

#include "atheme.h"

DECLARE_MODULE_V1
(
    "chanserv/mass_protect", false, _modinit, _moddeinit,
    PACKAGE_STRING,
    "Atheme Development Group <http://www.atheme.org>"
);

static void cs_cmd_mass_protect(sourceinfo_t *si, int parc, char *parv[]);

command_t cs_mass_protect = { "PROTECT", N_("Protects all channel users on a channel."),
                              AC_NONE, 2, cs_cmd_mass_protect, { .path = "cservice/mass_protect" }
                            };

mowgli_patricia_t **cs_mass_cmds;

void _modinit(module_t *m)
{
    if (ircd != NULL && !ircd->uses_protect) {
        slog(LG_INFO, "Module %s requires protect support, refusing to load.", m->name);
        m->mflags = MODTYPE_FAIL;
        return;
    }

    MODULE_TRY_REQUEST_SYMBOL(m, cs_mass_cmds, "chanserv/mass", "cs_mass_cmds");

    command_add(&cs_mass_protect, *cs_mass_cmds);
}

void _moddeinit(module_unload_intent_t intent)
{
    command_delete(&cs_mass_protect, *cs_mass_cmds);
}

static void cs_cmd_mass_protect(sourceinfo_t *si, int parc, char *parv[])
{
    channel_t *c;
    char *channel = parv[0];
    mychan_t *mc = mychan_find(channel);
    chanuser_t *cu, *origin_cu = NULL;
    mowgli_node_t *n, *tn;

    if (!mc) {
        command_fail(si, fault_nosuch_target, _("Channel \2%s\2 is not registered."), channel);
        return;
    }

    if (metadata_find(mc, "private:frozen:freezer")) {
        command_fail(si, fault_noprivs, _("\2%s\2 is frozen."), channel);
        return;
    }

    if (!(c = channel_find(channel))) {
        command_fail(si, fault_nosuch_target, _("\2%s\2 is currently empty."), channel);
        return;
    }

    if (!chanacs_source_has_flag(mc, si, CA_RECOVER)) {
        command_fail(si, fault_noprivs, _("You are not authorized to perform this operation."));
        return;
    }

    if (!chanacs_source_has_flag(mc, si, CA_USEPROTECT)) {
        command_fail(si, fault_noprivs, _("You are not authorized to perform this operation."));
        return;
    }

    if (metadata_find(mc, "private:close:closer")) {
        command_fail(si, fault_noprivs, _("\2%s\2 is closed."), channel);
        return;
    }

    /* protect everyone */
    MOWGLI_ITER_FOREACH(n, mc->chan->members.head) {
        cu = (chanuser_t *)n->data;
        if (is_internal_client(cu->user))
            ;
        else {
            modestack_mode_param(chansvs.nick, mc->chan, MTYPE_ADD, ircd->protect_mchar[1], CLIENT_NAME(cu->user));
            cu->modes &= ~ircd->protect_mode;
        }
    }

    logcommand(si, CMDLOG_DO, "MASS:PROTECT: \2%s\2", mc->name);

    command_success_nodata(si, _("Mass Protected channel users in \2%s\2."), channel);
}



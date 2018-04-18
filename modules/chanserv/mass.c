/*
 * Copyright (c) 2014-2016 Xtheme Development Group (Xtheme.org)
 * Rights to this code are as documented in doc/LICENSE.
 *
 * This file contains code for the CService MASS functions.
 *
 */

#include "atheme.h"

DECLARE_MODULE_V1
(
    "chanserv/mass", false, _modinit, _moddeinit,
    PACKAGE_STRING,
    "Atheme Development Group <http://www.atheme.org>"
);


static void cs_cmd_mass(sourceinfo_t *si, int parc, char *parv[]);
static void cs_help_mass(sourceinfo_t *si, const char *subcmd);

command_t cs_mass = { "MASS", N_("Channel removal toolkit."),
                      AC_NONE, 3, cs_cmd_mass, { .func = cs_help_mass }
                    };

mowgli_patricia_t *cs_mass_cmds;

void _modinit(module_t *m)
{
    service_named_bind_command("chanserv", &cs_mass);

    cs_mass_cmds = mowgli_patricia_create(strcasecanon);
}

void _moddeinit(module_unload_intent_t intent)
{
    service_named_unbind_command("chanserv", &cs_mass);

    mowgli_patricia_destroy(cs_mass_cmds, NULL, NULL);
}

static void cs_help_mass(sourceinfo_t *si, const char *subcmd)
{
    if (!subcmd) {
        command_success_nodata(si, _("***** \2%s Help\2 *****"), chansvs.me->disp);
        command_success_nodata(si, _("Help for \2MASS\2:"));
        command_success_nodata(si, " ");
        command_success_nodata(si, _("MASS allows you to perform MASS functions on a channel."));
        command_success_nodata(si, " ");
        command_help(si, cs_mass_cmds);
        command_success_nodata(si, " ");
        command_success_nodata(si, _("For more information, use \2/msg %s HELP MASS \37command\37\2."), chansvs.me->disp);
        command_success_nodata(si, _("***** \2End of Help\2 *****"));
    } else
        help_display(si, si->service, subcmd, cs_mass_cmds);
}

static void cs_cmd_mass(sourceinfo_t *si, int parc, char *parv[])
{
    char *chan;
    char *cmd;
    command_t *c;

    if (parc < 2) {
        command_fail(si, fault_needmoreparams, STR_INSUFFICIENT_PARAMS, "MASS");
        command_fail(si, fault_needmoreparams, _("Syntax: MASS <#channel> <command> [parameters]"));
        return;
    }

    if (parv[0][0] == '#')
        chan = parv[0], cmd = parv[1];
    else if (parv[1][0] == '#')
        cmd = parv[0], chan = parv[1];
    else {
        command_fail(si, fault_badparams, STR_INVALID_PARAMS, "MASS");
        command_fail(si, fault_badparams, _("Syntax: MASS <#channel> <command> [parameters]"));
        return;
    }

    c = command_find(cs_mass_cmds, cmd);
    if (c == NULL) {
        command_fail(si, fault_badparams, _("Invalid command. Use \2/%s%s help\2 for a command listing."), (ircd->uses_rcommand == false) ? "msg " : "", chansvs.me->disp);
        return;
    }

    parv[1] = chan;
    command_exec(si->service, si, c, parc - 1, parv + 1);
}



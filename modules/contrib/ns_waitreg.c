/*
 * Copyright (c) 2010 William Pitcock <nenolod@atheme.org>
 * Rights to this code are as documented in doc/LICENSE.
 *
 * This file contains code for delaying user registration
 */

#include "atheme-compat.h"
#include "conf.h"
#include <limits.h>

DECLARE_MODULE_V1
(
	"contrib/ns_waitreg", false, _modinit, _moddeinit,
        PACKAGE_STRING,
        "Atheme Development Group <http://www.atheme.org>"
);

unsigned int waitreg_time = 0;

static void waitreg_hook(hook_user_register_check_t *hdata)
{
	return_if_fail(hdata != NULL);
	return_if_fail(hdata->si != NULL);
	return_if_fail(hdata->password != NULL);

	if (hdata->si->su == NULL)
		return;

	if (hdata->si->su->ts >= CURRTIME - waitreg_time)
	{
		command_fail(hdata->si, fault_badparams, _("You can not register your nick so soon after connecting. Please wait a while and try again."));
		hdata->approved++;
	}
}

static void info_hook(sourceinfo_t *si)
{
	return_if_fail(si != NULL);

	command_success_nodata(si, "Time (in seconds) before users may register an account: %u", waitreg_time);
}

void
_modinit(module_t *m)
{

	hook_add_event("user_can_register");
	hook_add_user_can_register(waitreg_hook);

	hook_add_event("operserv_info");
	hook_add_operserv_info(info_hook);

	add_uint_conf_item("WAITREG_TIME", &nicksvs.me->conf_table, 0, &waitreg_time, 0, INT_MAX, 0);
}

void
_moddeinit(module_unload_intent_t intent)
{
	hook_del_user_can_register(waitreg_hook);
	hook_del_operserv_info(info_hook);

	del_conf_item("WAITREG_TIME", &nicksvs.me->conf_table);
}

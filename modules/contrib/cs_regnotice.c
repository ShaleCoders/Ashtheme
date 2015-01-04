/*
 * Copyright (c) 2010 William Pitcock <nenolod@atheme.org>
 * Rights to this code are as documented in doc/LICENSE.
 *
 * Sends a customized welcome message on channel registration.
 */

#include "atheme-compat.h"
#include "conf.h"

DECLARE_MODULE_V1
(
	"contrib/cs_regnotice", false, _modinit, _moddeinit,
        PACKAGE_STRING,
        "Atheme Development Group <http://www.atheme.org>"
);

static mowgli_list_t regnotices = { NULL, NULL, 0 };

static void regnotice_hook(hook_channel_req_t *hdata)
{
	mowgli_node_t *n;
	sourceinfo_t *si = hdata->si;
	mychan_t *mc = hdata->mc;

	if (si == NULL || mc == NULL)
		return;

	MOWGLI_ITER_FOREACH(n, regnotices.head)
	{
		char *line = n->data;

		command_success_nodata(si, "%s", line);
	}
}

static int regnotice_config_handler(mowgli_config_file_entry_t *ce)
{
	mowgli_config_file_entry_t *cce;

	MOWGLI_ITER_FOREACH(cce, ce->entries)
	{
		char *line = sstrdup(cce->varname);
		mowgli_node_add(line, mowgli_node_create(), &regnotices);
	}

	return 0;
}

static void regnotice_config_purge(void *unused)
{
	mowgli_node_t *n, *tn;

	MOWGLI_ITER_FOREACH_SAFE(n, tn, regnotices.head)
	{
		char *line = n->data;

		free(line);
		mowgli_node_delete(n, &regnotices);
		mowgli_node_free(n);
	}
}

void
_modinit(module_t *m)
{
	hook_add_event("config_purge");
	hook_add_config_purge(regnotice_config_purge);

	hook_add_event("channel_register");
	hook_add_channel_register(regnotice_hook);

	add_conf_item("REGNOTICE", &chansvs.me->conf_table, regnotice_config_handler);
}

void
_moddeinit(module_unload_intent_t intent)
{
	hook_del_channel_register(regnotice_hook);
	hook_del_config_purge(regnotice_config_purge);

	del_conf_item("REGNOTICE", &chansvs.me->conf_table);
}

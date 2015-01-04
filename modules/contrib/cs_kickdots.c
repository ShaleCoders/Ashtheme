/*
 * Copyright (c) 2006 William Pitcock
 * Rights to this code are as documented in doc/LICENSE.
 *
 * Kicks people saying "..." on channels with "kickdots" metadata set.
 *
 */

#include "atheme-compat.h"

DECLARE_MODULE_V1
(
	"contrib/cs_kickdots", false, _modinit, _moddeinit,
	PACKAGE_STRING,
	"William Pitcock <nenolod -at- nenolod.net>"
);

static void
on_channel_message(hook_cmessage_data_t *data)
{
	if (data != NULL && data->msg != NULL && !strncmp(data->msg, "...", 3))
	{
		mychan_t *mc = MYCHAN_FROM(data->c);

		if (mc == NULL)
			return;

		if (metadata_find(mc, "kickdots"))
		{
			kick(chansvs.me->me, data->c, data->u, data->msg);
		}
	}
}

void _modinit(module_t *m)
{
	hook_add_event("channel_message");
	hook_add_channel_message(on_channel_message);
}

void _moddeinit(module_unload_intent_t intent)
{
	hook_del_channel_message(on_channel_message);
}

/* vim:cinoptions=>s,e0,n0,f0,{0,}0,^0,=s,ps,t0,c3,+s,(2s,us,)20,*30,gs,hs
 * vim:ts=8
 * vim:sw=8
 * vim:noexpandtab
 */

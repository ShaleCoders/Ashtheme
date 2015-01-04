/*
 * Copyright (c) 2006 Atheme Development Group
 * Rights to this code are as documented in doc/LICENSE.
 *
 * PLAIN mechanism provider
 *
 */

#include "atheme.h"

DECLARE_MODULE_V1
(
	"saslserv/plain", MODULE_UNLOAD_CAPABILITY_NEVER, _modinit, _moddeinit,
	PACKAGE_STRING,
	"Atheme Development Group <http://www.atheme.org>"
);

mowgli_list_t *mechanisms;
mowgli_node_t *mnode;
static int mech_start(sasl_session_t *p, char **out, int *out_len);
static int mech_step(sasl_session_t *p, char *message, int len, char **out, int *out_len);
static void mech_finish(sasl_session_t *p);
sasl_mechanism_t mech = {"PLAIN", &mech_start, &mech_step, &mech_finish};

void _modinit(module_t *m)
{
	MODULE_TRY_REQUEST_SYMBOL(m, mechanisms, "saslserv/main", "sasl_mechanisms");
	mnode = mowgli_node_create();
	mowgli_node_add(&mech, mnode, mechanisms);
}

void _moddeinit(module_unload_intent_t intent)
{
	mowgli_node_delete(mnode, mechanisms);
}

static int mech_start(sasl_session_t *p, char **out, int *out_len)
{
	return ASASL_MORE;
}

static int mech_step(sasl_session_t *p, char *message, int len, char **out, int *out_len)
{
	char auth[256];
	char pass[256];
	myuser_t *mu;
	char *end;

	/* Skip the authzid entirely */
	end = memchr(message, '\0', len);
	if (end == NULL)
		return ASASL_FAIL;
	len -= end - message + 1;
	if (len <= 0)
		return ASASL_FAIL;
	message = end + 1;

	/* Copy the authcid */
	end = memchr(message, '\0', len);
	if (end == NULL)
		return ASASL_FAIL;
	if (end - message > 255)
		return ASASL_FAIL;
	len -= end - message + 1;
	if (len <= 0)
		return ASASL_FAIL;
	memcpy(auth, message, end - message + 1);
	message = end + 1;

	/* Copy the password */
	end = memchr(message, '\0', len);
	if (end == NULL)
		end = message + len;
	if (end - message > 255)
		return ASASL_FAIL;
	memcpy(pass, message, end - message);
	pass[end - message] = '\0';

	/* Done dissecting, now check. */
	if(!(mu = myuser_find_by_nick(auth)))
		return ASASL_FAIL;

	p->username = strdup(auth);
	return verify_password(mu, pass) ? ASASL_DONE : ASASL_FAIL;
}

static void mech_finish(sasl_session_t *p)
{
}

/* vim:cinoptions=>s,e0,n0,f0,{0,}0,^0,=s,ps,t0,c3,+s,(2s,us,)20,*30,gs,hs
 * vim:ts=8
 * vim:sw=8
 * vim:noexpandtab
 */

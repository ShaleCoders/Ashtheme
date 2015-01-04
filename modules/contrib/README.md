### Community-supported Atheme Modules

This directory contains modules that are not included in the main modules
folders for one reason or another. Either their code is a bit ugly, their
functionality is frowned upon, they only work with a limited number of IRCd's
or similar cases. 

### Building other modules not included in this distribution

Just drop the file in here, and it will be built/installed.

Alternatively just to build a single module, use the `$SRCS`
make variable to build and install modules.

```
$ make SRCS=fileyouwanttocompile.c
Successfully compiled fileyouwanttocompile.c as fileyouwanttocompile.so.
$ make SRCS=fileyouwanttocompile.c install
Successfully installed fileyouwanttocompile.so.
```

### Adding additional modules here

Any modules you want to add can be considered for inclusion here by sending us
a pull request on GitHub.

### Incomplete list of modules

#### cs_babbler.c

Repeats what others users in a channel say back to a specific
user. Useful for users that claim they have entire channels on
ignore.

#### cs_badwords.c

Takes actions against users (KICK, BAN, KICKBAN or QUIET) for
using badwords in channel, specified on a per-channel basis
with the BADWORDS command. Be aware it will check every message
sent to channels that BLOCKBADWORDS is set on so it can be a bit
CPU-heavy.

#### cs_kickdots.c

Kicks users from a channel when kickdots metadata is set on
that channel and users send a line containing only "...".
Deprecated by cs_badwords (/cs badwords #channel add ... kick).

#### cs_ping.c

Responds to users that ping ChanServ with "Pong!".

#### cs_regmode.c

Sets the stupid, pointless DALNet-style +/-r mode when a channel
is registered or dropped. NOT RECOMMENDED TO USE.

#### cs_regnotice.c

Sends a user a notice with some information specified in a
regnotice {} block inside the chanserv {} block of your
atheme.conf when the user registers a channel.

#### cs_updown.c

Either gives or removes all your channel status modes at once.

#### cs_userinfo.c

Display a message when a user joins a channel. You must be able
to edit the channel access list to add or remove a userinfo entry.

#### gen_echoserver.c

A small sample echoserver using the connection_t framework (deprecated).
NOT RECOMMENDED TO USE.

#### gen_httpd.c

A small sample httpd for serving files. It is highly recommended to use
misc/httpd.c instead.

#### gen_listenerdemo.c

Demonstrates how to use listeners using the connection_t framework (deprecated).
NOT RECOMMENDED TO USE.

#### gen_vhostonreg.c

Assigns a $account.hidehostsuffix vhost to all users upon
account registration. $account will be replaced by the users'
accountname and hidehostsuffix is that config option from the
serverinfo {} block of your atheme.conf.

#### graphtastical.c

Graphs user->channel relationships. Not recommended to use if
there are privacy concerns.

#### gs_roulette.c

A nice GameServ game of Russian Roulette.

#### ircd_catserv.c

Little module showing a CatServ Services client, pretty much all modular
services since forever implement this as an example, so we do too.

#### ircd_announceserv.c

A services bot which allows users to request network
announcements that will then (when approved by a soper)
be sent to all users on the network. This is seperate
from InfoServ so that users can easily ignore users'
announcements but won't miss any important announcements
from network staff.

#### ircd_loveserv.c

A services bot for sending love-related items to other users.
NOT COMPILED BY DEFAULT.

#### ircd_crypto_trans.c

A encryption module for IRCServices weird password encryption scheme, useful
for transitioning to crypto/posix. 

#### mlocktweaker.c

Sets the mlock to all new channels to something specified in
the source code of the module. See line 16 of the module's
code for what to edit.

#### ns_ajoin.c

Allows users to set a AJOIN/autojoin list of channels that Atheme
will automatically join them to upon identify. Only works on
ShadowIRCd, InspIRCd and UnrealIRCd.

#### ns_cleannick.c

Detects and cleans 'lame' nicknames using case normalization.

#### ns_fenforce.c

Allows opers to force the ENFORCE flag on/off on other users' accounts.

#### ns_forbid.c

Allows opers to forbid the registration and use of a nickname.

#### ns_fregister.c

Allows opers to register an account on behalf of another user.
An oper must have the user:fregister priv to use this command.

#### ns_generatehash.c

Generates a password hash from the password given as part
of the command. Extremely useful if your passwords are
encrypted and you want to set SOPER passwords.

#### ns_generatepass.c

Generates a random password.

#### ns_guestnoreg.c

Disallows the registration of nicks beginning with a string
specified in the guestnicks {} block inside the nickserv {}
block of your atheme.conf.

#### ns_listlogins.c

Allows users to list the other clients currently logged in 
to the same account as them.

#### ns_mxcheck.c

Checks if a email address provided by a user upon registration
is valid and fails registration if it is not.

#### ns_mxcheck_async.c

Same as ns_mxcheck.c, but asynchronous.

#### ns_regnotice.c

Sends a user a notice with some information specified in a
regnotice {} block inside the nickserv {} block of your
atheme.conf when the user registers an account.

#### ns_waitreg.c

Requires a user to have been connected for waitreg_time (in
the nickserv {} block of your atheme.conf) seconds before
they are allowed to register their nick.

#### on_db_save.c

Allows you to specify a command that is run every time the Atheme
database is saved.

#### os_akillnicklist.c

AKILLs users matched in a nicklist specified in your
atheme.conf. See the comment at the top of the module's
source code for details.

#### os_defcon.c

Allows you to use DEFCON-based security on your network.  This may be
useful to people migrating from Anope.

#### os_helpme.c

Sets usermode +h on all users listed with the general:helper
soper priv upon recieving soper status. Requires an IRCd that has
+h (helper) usermode support.

#### os_joinmon.c

Allows adding nick patterns to a joinmon list and when a user
matching one of the patterns joins a channel, a message will
be sent to the logchan (with the info loglevel).

#### os_kill.c

Allows opers to KILL users via services.

#### os_klinechan.c

KLINEs all users who join a KLINECHAN.

#### os_pingspam.c

Spam a user with pings and various messages either on-demand or
spams all users a bit upon connect.  Basically, the same functionality as
NeoStats' SecureServ.

#### os_procwatch.c

Watch a specified process and log a message when it finishes
running. Requires kqueue (FreeBSD).

#### os_savechanmodes.c

Allows you to dump and restore channelmodes of all channels
on the network, including unregistered ones.  Useful for ircd transitions.

#### os_tabletest.c

Tests the dynamic table generation APIs for command replies.
NOT RECOMMENDED TO USE.

#### os_testcmd.c

Run a test command.

#### os_testproc.c

Runs a test of child processes.

#### os_trace.c

Looks up users by certain criteria and allows you to perform
various actions on them.

#### wumpus.c

Allows users to play a game of Hunt the Wumpus!

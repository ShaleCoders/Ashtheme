# atheme-services -- a set of services for IRC networks

This program is free but copyrighted software; see the COPYING file for
details.

Information about atheme-services may be found at http://www.atheme.net/.

## Credits

atheme-services contains code from Shrike, Sentinel and ircd-ratbox. 
Some of the initial design was influenced by Shrike too.

Information about Shrike can be found at http://www.malkier.net/projects.php?p=shrike.

Information about Sentinel can be found at http://ircd.botbay.net/sentinel/.

Information about ircd-ratbox can be found at http://www.ircd-ratbox.org/.

For further information about our relationship with those projects, see 
the Atheme FAQ: http://atheme.net/faq.html

## Presentation (also, what atheme is not)

atheme-services is a set of Services for IRC networks that allows users to
manage their channels in a secure and efficient way and allows operators to
manage various things about their networks. Unlike it's predecessor, Shrike,
services has a completely reworked form of channel management that feels 
somewhat like eggdrop and is somewhat more useful.

Services currently works with many irc daemons. More details are 
available in the config file.

Internally, atheme-services shares more similarities with ircd than it 
does with IRCServices. Anope/Epona, Cygnus, OperStats, Hybserv, Theia, etc
are all based on IRCServices and as such have very old legacy code that 
none of the authors, except Church truly understand. Atheme was written 
completely from scratch with the more complex concepts taken from 
various modern ircd packages, including ircu, ircd-ratbox, hybrid and 
bahamut.

atheme-services is not a drop-in replacement for Anope or Andy Church's IRC 
Services. It is designed with an entirely different set of goals and as 
such should not be migrated to with the expectation that it will behave 
exactly like what was previously implemented. Atheme is designed to act 
as a directory server, with alternative ways of getting to the data 
implemented as well as the IRC presence.

## Installation

See the INSTALL file.

## Command line options

Normally, services can be run simply by invoking the "atheme-services" 
executable.  Services will then use the defaults specified in the 
configuraiton file and connect to the specified uplink server. 
Alternatively, any of the following command-line options can be 
specified to change the default behavior:

```
-c </path/to/file> - specify the configuration file
-d                 - start in debugging mode
-h                 - print the help message and exit
-r                 - start atheme in read-only mode
-l </path/to/file> - specify the main log file
-n                 - do not fork into the background
-p </path/to/file> - specify the PID file
-v                 - print the version information and exit
```

Services also handles the following signals:

* HUP  - force a REHASH
* INT  - force a RESTART
* TERM - force a SHUTDOWN

Upon starting, atheme-services will parse its command-line arguments, 
open its log file, parse its configuration file, load its database, 
connect to the uplink, and (assuming -n is not specified) detach into 
the background.  If services encounters an error while parsing the 
configuration or database files it will terminate immediately. 
Otherwise, it will run until killed or otherwise stopped.

## Getting Support

If you are stuck, or services are doing something really weird, or you have
some sort of brilliant idea, we have a channel on IRC! (Surprising, no?)
To access this channel, connect to irc.atheme.org, and join #atheme.

It is important to note that operating Atheme in obviously insane
configurations automatically loses your support privileges.

## Reporting Bugs

If you find a bug in services, you must report it via the bugtracker; 
our developers have a tendency to forget things. Your bug is not 
actually a bug until it's reported.

Report bugs at <http://github.com/atheme/atheme/issues/new>.

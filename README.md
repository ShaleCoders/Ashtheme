## Ashtheme
[![Build Status](https://travis-ci.org/ShaleCoders/Ashtheme.svg?branch=master)](https://travis-ci.org/ShaleCoders/Ashtheme)

Ashtheme is a set of services for IRC networks designed for large IRC networks with high
scalability requirements.  It is relatively mature software, with some code and design
derived from another package called Shrike, and is a fork of a dying services package named Atheme.

Ashtheme's behavior is tunable using modules and a highly detailed configuration file.
Almost all behavior can be changed at deployment time just by editing the configuration.

## basic build instructions for the impatient

Whatever you do, make sure you do *not* install Ashtheme into the same location as the source.
Ashtheme will default to installing in `$HOME/ashtheme`, so make sure you plan accordingly for this.

    $ ./configure
    $ make
    $ make install

If you're still lost, read [INSTALL](INSTALL) for hints.

## links / contact

 * [GitHub](http://www.github.com/ShaleCoders/Ashtheme)
 * [Website](http://www.chatfreedom.us)
 * [IRC](irc://irc.chatfreedom.us/#Ashtheme)


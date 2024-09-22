# stable branch

As of Summer 2024 This branch is no longer maintained. 

The active branch, master, is the primary development and release branch.   

switch to [master](https://github.com/aurarad/Auroracoin/tree/master).

Background: 
This was previously "stable branch", representing development branch for integrating new features and bug fixes before merging into master for a major release. 

However, the master and stable branch have diverged and we decided to deprecate the stable branch. 

Currently master branch is the branch for development pull-requests and build ready. 

( We will probably create "development" or similar branch (from master) for new features and bug fixes. ) 

# Auroracoin AUR

http://en.auroracoin.is

Follow [@OfficialAUR](https://twitter.com/OfficialAUR)

Copyright (c) 2014-2022 Auroracoin Developers


## What is Auroracoin?

Auroracoin is a cryptocurrency for Iceland started on 24th January 2014. 

It was originally based on Litecoin and later in 2016 incorporated the multi-algorithm PoW approach of DigiByte.

There was a 50% premine for distribution to Icelandic residents in 2014-2015 using national identification.

Roughly half of the airdrop coins were claimed with the other half verifiably destroyed. 


## Community

Irc: #aur on freenode

Forums: http://discord.gg/Fhm4758

Reddit: http://www.reddit.com/r/auroracoin

Community: http://www.auroracoin101.is

Market: http://coinpaprika.com/coin/aur-auroracoin/

Explorer: http://chainz.cryptoid.info/aur

Announcement: https://bitcointalk.org/index.php?topic=1044432.0

## License

Auroracoin is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

## Development Process

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/aurarad/auroracoin/tags) are created
regularly to indicate new official, stable release versions of Auroracoin.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md)
and useful hints for developers can be found in [doc/developer-notes.md](doc/developer-notes.md).

## Testing

### Automated Testing

Developers are strongly encouraged to write [unit tests](src/test/README.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`. Further details on running
and extending unit tests can be found in [/src/test/README.md](/src/test/README.md).

There are also [regression and integration tests](/test), written in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/test) are installed) with: `test/functional/test_runner.py`

The Travis CI system makes sure that every pull request is built for Windows, Linux, and macOS, and that unit/sanity tests are run automatically.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.


## Developers

Developers are encouraged to create tools for Auroracoin to support the adoption of Auroracoin. 

Such software, e.g. for payments, will help Icelanders start using the currency in their daily lives.

Interested in helping out? Please email auroracoin@auroracoin.is, and let us know how you can help.

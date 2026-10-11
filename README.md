# MetroHash - MetroHash non-cryptographic hash functions C++ library

This is a `build2` package repository for
[`MetroHash`](https://github.com/jandrewrogers/MetroHash),
a set of hash functions for non-cryptographic use cases.

This file contains setup instructions and other details that are more
appropriate for development rather than consumption. If you want to use
`libmetrohash` in your `build2`-based project, then instead see the accompanying
[`PACKAGE-README.md`](libmetrohash/PACKAGE-README.md) file.

The development setup for `MetroHash` uses the standard `bdep`-based workflow.
For example:

```
git clone .../MetroHash.git
cd MetroHash

bdep init -C @gcc cc config.cxx=g++
bdep update
bdep test
```

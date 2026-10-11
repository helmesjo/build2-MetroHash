# libmetrohash - MetroHash non-cryptographic hash functions C++ library

This is a `build2` package for the
[`MetroHash`](https://github.com/jandrewrogers/MetroHash) C++ library. It
provides a set of hash functions for non-cryptographic use cases that are
notable for being algorithmically generated. The 64-bit, 128-bit, and 128-bit
CRC variants are available, with the 64-bit and 128-bit variants also
implemented as classes that support incremental hashing.


## Usage

To start using `libmetrohash` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libmetrohash ^1.1.3
```

Then import the library in your `buildfile`:

```
import libs = libmetrohash%lib{metrohash}
```


## Importable targets

This package provides the following importable targets:

```
lib{metrohash}
```

The MetroHash library. Its headers are included with the `metrohash/`
prefix (the same as in Debian), for example:

```
#include <metrohash/metrohash.h>
```

The CRC variants (`metrohash128crc_1()` and `metrohash128crc_2()`) use the
SSE4.2 CRC32 instruction and are only built for x86_64, where they require
a CPU with SSE4.2 support at runtime. On other targets they are declared in
`metrohash128crc.h` (which `metrohash.h` includes) but not defined.

When linking the DLL built with MSVC or Clang on Windows, the test vector
data members of the `MetroHash64` and `MetroHash128` classes cannot be used,
since only functions are imported automatically. Use their
`ImplementationVerified()` functions instead.


## Configuration variables

This package provides no configuration variables.

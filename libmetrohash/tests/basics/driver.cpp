#include <cstdio>
#include <cstring>
#include <string>

#include <metrohash/metrohash.h>

#undef NDEBUG
#include <cassert>

// Return the hash bytes as an upper-case hex string, in memory order (the
// same representation as used by upstream's test vectors).
//
static std::string
hex (const uint8_t* h, std::size_t n)
{
  std::string r;
  for (std::size_t i (0); i != n; ++i)
  {
    char b[3];
    std::snprintf (b, sizeof (b), "%02X", h[i]);
    r += b;
  }
  return r;
}

int main ()
{
  using namespace std;

  // Test key that exercises every internal branch of the hash functions.
  //
  const char* s (
    "012345678901234567890123456789012345678901234567890123456789012");
  const uint8_t* k (reinterpret_cast<const uint8_t*> (s));
  const uint64_t n (strlen (s));

  // Built-in test vectors.
  //
  assert (MetroHash64::ImplementationVerified ());
  assert (MetroHash128::ImplementationVerified ());

  // Incremental vs stateless hashing.
  //
  {
    uint8_t h1[8], h2[8];

    MetroHash64 m (1);
    m.Update (k, 10);
    m.Update (k + 10, n - 10);
    m.Finalize (h1);

    MetroHash64::Hash (k, n, h2, 1);

    assert (hex (h1, 8) == hex (h2, 8));
  }

  {
    uint8_t h1[16], h2[16];

    MetroHash128 m (1);
    m.Update (k, 40);
    m.Update (k + 40, n - 40);
    m.Finalize (h1);

    MetroHash128::Hash (k, n, h2, 1);

    assert (hex (h1, 16) == hex (h2, 16));
  }

  // Original functions.
  //
  {
    uint8_t h[16];

    metrohash64_1 (k, n, 0, h);
    assert (hex (h, 8) == "658F044F5C730E40");

    metrohash64_2 (k, n, 1, h);
    assert (hex (h, 8) == "CF518E9CF58402C0");

    metrohash128_1 (k, n, 0, h);
    assert (hex (h, 16) == "ED9997ED9D0A8B0FF3F266399477788F");

    metrohash128_2 (k, n, 1, h);
    assert (hex (h, 16) == "2DA6AF149A5CDBC12B09DB0846D69EF0");
  }

  // CRC variants (only available on x86_64).
  //
#if defined(__x86_64__) || defined(_M_X64)
  {
    uint8_t h[16];

    metrohash128crc_1 (k, n, 0, h);
    assert (hex (h, 16) == "B329ED67831604D3DFAC4E4876D8262F");

    metrohash128crc_2 (k, n, 1, h);
    assert (hex (h, 16) == "2D54F87181A0CF64B02C50D95692BC19");
  }
#endif
}

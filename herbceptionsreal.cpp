#include <cmath>
#include <span>
#include <herbceptions/error>

static void doSqrt(std::span<double> values) throws __attribute__((noinline));
static void doSqrt(std::span<double> values) throws {
   for (auto& v : values) {
      if (v < 0) throw throws ::std::errc::argument_out_of_domain;
      v = sqrt(v);
   }
}

unsigned herbceptionsRealSqrt(std::span<double> values, unsigned repeat) noexcept {
   unsigned failures = 0;
   for (unsigned index = 0; index != repeat; ++index)
   try
   {
      doSqrt(values);
   }
   catch throws(::std::error)
   {
      ++failures;
   }
   return failures;
}

static unsigned doFib(unsigned n, unsigned maxDepth) throws __attribute((noinline, optimize("no-optimize-sibling-calls")));
static unsigned doFib(unsigned n, unsigned maxDepth) throws {
   if (!maxDepth) throw throws ::std::errc::argument_out_of_domain;
   if (n <= 2) return 1;
   return doFib(n - 2, maxDepth - 1) + doFib(n - 1, maxDepth - 1);
}

unsigned herbceptionsRealFib(unsigned n, unsigned maxDepth) noexcept
try
{
   return doFib(n, maxDepth);
}
catch throws(::std::error e)
{
   return 0;
}

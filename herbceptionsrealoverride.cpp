#include <cmath>
#include <span>
#include <herbceptions/error>

static inline constexpr ::std::error_domain_singleton domainsingle{};

enum class test_out_of_domain{val=5};

namespace std
{
template<>
class error_domain<test_out_of_domain>
{
public:
	using errc_type = test_out_of_domain;
	static inline constexpr ::std::error_domain_singleton const* domain() noexcept
	{
		return &domainsingle;
	}
	static inline constexpr ::std::size_t code(test_out_of_domain d) noexcept
	{
		return static_cast<::std::size_t>(d);
	}
};
}

static void doSqrt(std::span<double> values) throws __attribute__((noinline));
static void doSqrt(std::span<double> values) throws {
   for (auto& v : values) {
      if (v < 0)
         throw throws test_out_of_domain::val;
      v = sqrt(v);
   }
}

unsigned herbceptionsRealOverrideSqrt(std::span<double> values, unsigned repeat) noexcept {
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
   if (!maxDepth)
      throw throws test_out_of_domain::val;
   if (n <= 2) return 1;
   return doFib(n - 2, maxDepth - 1) + doFib(n - 1, maxDepth - 1);
}

unsigned herbceptionsRealOverrideFib(unsigned n, unsigned maxDepth) noexcept
try
{
   return doFib(n, maxDepth);
}
catch throws(::std::error e)
{
   return 0;
}

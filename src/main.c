#include <stdio.h>
#include <float.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <locale.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

#define C_RED     "\x1b[31m"
#define C_GREEN   "\x1b[32m"
#define C_RESET   "\x1b[0m"

#define	CONVERSIONS	"dDibBoOuUxXeEfFgGcCsSpPt%"
#define	FLAGS		"#0-+ "
#define	CAST		"hljzL"
const char			g_spaces[256] = { [0 ... 255] = ' ' };
#define SPACES		((char *)g_spaces)
#define LINE_WIDTH	80

int		ret_orig;
int		ret_mine;
char	buf_orig[16384];
char	buf_mine[16384];
int		margin;
int		show;
int		binterr;
int		namelen;

#define PRINT_TITLE(fmtl, fmtr, name, reslen) {\
	namelen = ft_strlen(fmtl) + ft_strlen(fmtr) + ft_strlen(name) + reslen;\
	if (namelen - 4 > LINE_WIDTH)\
		margin = ft_printf("%s%.*s...%s", fmtl, namelen - ft_strlen(fmtl)\
			- ft_strlen(fmtr) - reslen - 7, name, fmtr);\
	else\
		margin = ft_printf("%s%s%s", fmtl, name, fmtr);\
	ft_printf("%.*s", LINE_WIDTH - reslen - margin, SPACES);\
}

#define	PRINTF_TEST(format, ...) {\
	ret_orig = sprintf(buf_orig, format, __VA_ARGS__);\
	ret_mine = ft_sprintf(buf_mine, format, __VA_ARGS__);\
	PRINT_TITLE("TEST:  [", "]", #format, 2);\
	if (ret_orig == ret_mine\
			&& (ret_orig == -1 || !strncmp(buf_orig, buf_mine, ret_orig)))\
	{\
		ft_printf(C_GREEN"OK\n"C_RESET);\
		if (show && ret_orig != -1)\
			ft_printf("%.*s\n", ret_orig, buf_orig);\
		else if (show)\
			ft_printf("ERROR\n");\
	}\
	else\
	{\
		ft_printf(C_RED "KO\n" C_RESET);\
		ft_printf("ret_orig = %d\n", ret_orig);\
		ft_printf("ret_mine = %d\n", ret_mine);\
		ft_printf("ORIG>\t");\
		if (ret_orig != -1)\
		{\
			ft_printf("%.*s", ret_orig, buf_orig);\
			ft_printf("\n");\
		}\
		else\
			ft_printf("ERROR\n");\
		ft_printf("MINE>\t");\
		if (ret_mine != -1)\
		{\
			ft_printf("%.*s", ret_mine, buf_mine);\
			ft_printf("\n");\
		}\
		else\
			ft_printf("ERROR\n");\
	}\
}

#define	FT_PRINTF_TEST(format, ...) {\
	ret_mine = ft_sprintf(buf_mine, format, __VA_ARGS__);\
	PRINT_TITLE("TEST:  [", "]", #format, 2);\
	if (ret_mine != -1)\
	{\
		ft_printf(C_GREEN"OK\n"C_RESET);\
		if (show)\
			ft_printf("%.*s\n", ret_mine, buf_mine);\
	}\
	else\
	{\
		ft_printf(C_RED "KO\n" C_RESET);\
		ft_printf("ret_mine = %d\n", ret_mine);\
	}\
}

#define BINT_TEST(title, functions, ops) {\
	if (show)\
	{\
		ft_printf("\n//////// BEFORE /////////\n");\
		bint_print(a, 1, 16);\
		bint_print(b, 1, 16);\
		bint_print(c, 1, 16);\
		bint_print(d, 1, 16);\
	}\
	binterr = 0;\
	ops;\
	if (show || binterr)\
	{\
		ft_printf("\n//////// AFTER /////////\n");\
		bint_print(a, 1, 16);\
		bint_print(b, 1, 16);\
		bint_print(c, 1, 16);\
		bint_print(d, 1, 16);\
	}\
	PRINT_TITLE("TEST:  ", "", title, 2);\
	if (show)\
		ft_printf("functions: %s\n", functions);\
	if (!binterr)\
		ft_printf(C_GREEN"OK\n"C_RESET);\
	else\
		ft_printf(C_RED "KO\n" C_RESET);\
}

#define BINT_ASSERT(name, test, ops) {\
	if (!binterr)\
	{\
		ops;\
		binterr = !(test);\
		if (show || binterr)\
		{\
			PRINT_TITLE("ASSERT:  ", "", name, 7);\
			if (!binterr)\
				ft_printf(C_GREEN"SUCCESS\n"C_RESET);\
			else\
				ft_printf(C_RED "FAILURE\n" C_RESET);\
		}\
	}\
}

int		bint_print(const t_bint n, uint32_t info, uint32_t base)
{
	if (base != 2 && base != 10 && base != 16)
		return (BINT_FAILURE);
	if (base == 10 && (dragon42(NULL, 1, n) == -1 || !ft_printf("\n")))
		return (BINT_FAILURE);
	ft_printf(base == 2 ? "0b " : base == 16 ? "0x " : "");
	for (int i = BINT_LEN(n); base != 10 && i >= 0; --i)
	{
		if (!i)
			ft_printf("%s", BINT_LEN(n) ? "" : "0\n");
		else if (base == 16)
			ft_printf("%08x%c", n[i], i > 1 ? ' ' : '\n');
		else if (base == 2)
			ft_printf("%032b%c", n[i], i > 1 ? ' ' : '\n');
	}
	if (info)
		ft_printf("info block: size = %u | sign = %u | len = %u\n",
			BINT_SIZE(n), BINT_SIGN(n), BINT_LEN(n));
	return (BINT_SUCCESS);
}

void	test_mandatory(int ac, char **av)
{
	ft_printf("implemented in original funcion:\n");
	PRINTF_TEST("%f", 42.00);
	PRINTF_TEST("{%f}", 1.42);
	PRINTF_TEST("%f", FLT_MIN);
	PRINTF_TEST("%f", FLT_MAX);
	PRINTF_TEST("%f", DBL_MIN);
	PRINTF_TEST("%f", DBL_MAX);
	PRINTF_TEST("%Lf", LDBL_MIN);
	PRINTF_TEST("%e", 1.000);
	PRINTF_TEST("%f", 1000.00);
	PRINTF_TEST("%g", 1000.00);
	PRINTF_TEST("%e", 4242.42424242);
	PRINTF_TEST("%e", 0.0004242);
	PRINTF_TEST("%.3e", 0.0004242);
	PRINTF_TEST("%10.2e", 0.0004242);
	PRINTF_TEST("%#5.12e", 0.0004242);
	PRINTF_TEST("%#5.12e", 0.0004242);
	PRINTF_TEST("%e", FLT_MIN);
	PRINTF_TEST("%e", FLT_MAX);
	PRINTF_TEST("%e", DBL_MIN);
	PRINTF_TEST("%e", DBL_MAX);
	PRINTF_TEST("%Le", LDBL_MIN);
	PRINTF_TEST("%Le", LDBL_MAX);
	PRINTF_TEST("%g", 42.000);
	PRINTF_TEST("%g", 42.420);
	PRINTF_TEST("%g", FLT_MIN);
	PRINTF_TEST("%g", FLT_MAX);
	PRINTF_TEST("%g", DBL_MIN);
	PRINTF_TEST("%g", DBL_MAX);
	PRINTF_TEST("%Lg", LDBL_MIN);
	PRINTF_TEST("%Lg", LDBL_MAX);

	ft_printf("\n\nnot implemented in original function:\n");
	ft_printf("\nt conversion:\n");

	FT_PRINTF_TEST("%#*t\t\t%s\n", ac, av);

	unsigned int		int_tab[10] = {
		0, 1, UINT_MAX, UINT_MAX, INT_MIN, INT_MIN, 6, 654676, 42, 9
	};
	FT_PRINTF_TEST("%#10.2t\t\tfirst field: %08x\tsecond field: %u\n", int_tab);

	ft_printf("\nb conversion:\n");
	FT_PRINTF_TEST("dec: %#3t%-32u \n", int_tab + 5);
	FT_PRINTF_TEST("bin: %#3t%.32b \n", int_tab + 5);

	ft_printf("\nBINT tests:\n");

	int			ret;
	uint32_t	a[BINT_SIZE_DEF];
	uint32_t	b[BINT_SIZE_DEF];
	uint32_t	c[BINT_SIZE_DEF];
	uint32_t	d[BINT_SIZE_DEF];

	bintinit(a, 0);
	bintinit(b, 0);
	bintinit(c, 0);
	bintinit(d, 0);

	BINT_TEST(
		"pow mult test setup",
		"bintset_u64",
		{
			BINT_ASSERT("set b to 1", ret == BINT_SUCCESS,
				ret = bintset_u64(b, 1));
			BINT_ASSERT("set d to 1", ret == BINT_SUCCESS,
				ret = bintset_u64(d, 1));
		}
	);

	char	assert_name[256];
	char	test_name[256];
	int		step = 16;
	for (uint32_t i = 16; i <= 128; i += step)
	{
		ft_sprintf(test_name, "set vs smult (pow = %u)", i);
		BINT_TEST(
			test_name,
			"bintset_pow2, bintset_pow10, bint_smult2, bint_smult10",
			{
				ft_sprintf(assert_name, "set a to 2^%u", i);
				BINT_ASSERT(assert_name, ret == BINT_SUCCESS,
					ret = bintset_pow2(a, i));

				ft_sprintf(assert_name, "mult b by 2 (%d times)", step);
				BINT_ASSERT(
					assert_name,
					ret == BINT_SUCCESS,
					{
						for (int j = 0; j < step && ret == BINT_SUCCESS; ++j)
							ret = bint_smult2(b);
					}
				);

				ft_sprintf(assert_name, "set c to 10^%u", i);
				BINT_ASSERT(assert_name, ret == BINT_SUCCESS,
					ret = bintset_pow10(c, i));

				ft_sprintf(assert_name, "mult d by 10 (%d times)", step);
				BINT_ASSERT(
					assert_name,
					ret == BINT_SUCCESS,
					{
						for (int j = 0; j < step && ret == BINT_SUCCESS; ++j)
							ret = bint_smult10(d);
					}
				);

				BINT_ASSERT("a == b", !ret, ret = bintcmp(a, b));
				BINT_ASSERT("c == d", !ret, ret = bintcmp(c, d));
				BINT_ASSERT("a != d", !!ret, ret = bintcmp(a, d));
				BINT_ASSERT("b != c", !!ret, ret = bintcmp(b, c));
			}
		);
	}

	if (bintcpy(a, c) == BINT_FAILURE || bintcpy(b, c) == BINT_FAILURE
		|| bintcmp(a, c) || bintcmp(b, c) || bintcmp(d, c))
		ft_printf("FAILURE: COULD NOT COPY c to a and to b\n");
	else
	{
		ft_printf("\nTEST: bint_sub, bint_mult_u32\n");
		ft_printf("TEST: a = b = c = d = 10^128\n");
		ft_printf("\n/////////////////////// BEFORE /////////////////////////\n");
		bint_print(a, 1, 16);
		bint_print(b, 1, 16);
		bint_print(c, 1, 16);
		bint_print(d, 1, 16);
		/* set a to: a * 10 */
		ret = bint_smult10(a);
		ft_printf("\n%s: a = a * 10\n", ret == BINT_FAILURE ? "ERROR" : "SUCCESS");
		/* set b to: c * 9 */
		ret = bint_mult_u32(b, c, 9);
		ft_printf("%s: b = c * 9\n", ret == BINT_FAILURE ? "ERROR" : "SUCCESS");
		/* set c to 0 */
		bintclr(c);
		/* set c to: a - b */
		ret = bint_sub(c, a, b);
		ft_printf("%s: c = a - b\n", ret == BINT_FAILURE ? "ERROR" : "SUCCESS");
		/* check that c == d */
		ret = bintcmp(c, d);
		ft_printf("\n%s: c %s d (ret = %d)\n", !ret ? "SUCCESS" : "ERROR",
			!ret ? "=" : "!=", ret);
		ft_printf("\n/////////////////////// AFTER /////////////////////////\n");
		bint_print(a, 1, 16);
		bint_print(b, 1, 16);
		bint_print(c, 1, 16);
		bint_print(d, 1, 16);
	}
	if (bintcpy(a, c) == BINT_FAILURE || bintcpy(b, c) == BINT_FAILURE
		|| bintcmp(a, c) || bintcmp(b, c) || bintcmp(d, c))
		ft_printf("FAILURE: COULD NOT COPY c to a and to b\n");
	else
	{
		ft_printf("\nTEST: bint_sub, bint_add_abs, BINT_SET_SIGN\n");
		ft_printf("TEST: a = b = c = d = 10^128\n");
		ft_printf("\n/////////////////////// BEFORE /////////////////////////\n");
		bint_print(a, 1, 16);
		bint_print(b, 1, 16);
		bint_print(c, 1, 16);
		bint_print(d, 1, 16);
		/* set a to: -a */
		SET_BINT_SIGN(a, 1);
		ft_printf("\n%s: a = -a\n", bintcmp_abs(a, b) || !BINT_SIGN(a) ?
			"ERROR" : "SUCCESS");
		/* set c to: a - b */
		ret = bint_sub(c, a, b);
		ft_printf("%s: c = a - b\n", ret == BINT_FAILURE ? "ERROR" : "SUCCESS");
		/* check that c < 0 && c == -(2 * d) */
		bint_smult2(d);
		ret = bintcmp_abs(c, d);
		ft_printf("\n%s: c %s -(2 * d) (ret = %d)\n", !ret && BINT_SIGN(c) ?
			"SUCCESS" : "ERROR", !ret && BINT_SIGN(c) ? "=" : "!=", ret);
		ft_printf("\n/////////////////////// AFTER /////////////////////////\n");
		bint_print(a, 1, 16);
		bint_print(b, 1, 16);
		bint_print(c, 1, 16);
		bint_print(d, 1, 16);
	}
	{
		ft_printf("\nTEST: bint_sub, bint_sub_abs\n");
		ft_printf("TEST: c = b - d (where d = 2*b) \n");
		/* set c to: b - d */
		ret = bint_sub(c, b, d);
		ft_printf("%s: c = b - d\n", ret == BINT_FAILURE ? "ERROR" : "SUCCESS");
		/* check that c == -b */
		ret = bintcmp_abs(c, b);
		ft_printf("\n%s: c %s -b (ret = %d)\n", !ret && BINT_SIGN(c) ?
			"SUCCESS" : "ERROR", !ret && BINT_SIGN(c) ? "=" : "!=", ret);
		ft_printf("\n/////////////////////// AFTER /////////////////////////\n");
		bint_print(a, 1, 16);
		bint_print(b, 1, 16);
		bint_print(c, 1, 16);
		bint_print(d, 1, 16);
	}
	bintset_u64(a, UINT64_MAX);
	bintset_u64(b, UINT64_MAX);
	bintset_u64(c, UINT64_MAX);
	bintclr(d);
	{
		ft_printf("\nTEST: bint_add, bint_sub\n");
		ft_printf("TEST: a = b = c = UINT64_MAX && d = 0\n");
		ft_printf("\n/////////////////////// BEFORE /////////////////////////\n");
		bint_print(a, 1, 16);
		bint_print(b, 1, 16);
		bint_print(c, 1, 16);
		bint_print(d, 1, 16);
		/* set d to: a + b */
		bint_add(d, a, b);
		bint_smult2(a);
		ft_printf("\n%s: d = a + b = 2 * a\n", bintcmp(a, d) ? "ERROR" : "SUCCESS");
		ft_printf("\n/////////////////////// AFTER /////////////////////////\n");
		bint_print(a, 1, 16);
		bint_print(b, 1, 16);
		bint_print(c, 1, 16);
		bint_print(d, 1, 16);
	}
	bintset_u64(a, UINT64_MAX);
	bintset_u64(b, UINT64_MAX);
	bintset_u64(c, UINT64_MAX);
	bintclr(d);
	{
		ft_printf("\nTEST: bint_sub\n");
		ft_printf("TEST: a = b = c = UINT64_MAX && d = 0\n");
		ft_printf("\n/////////////////////// BEFORE /////////////////////////\n");
		bint_print(a, 1, 16);
		bint_print(b, 1, 16);
		bint_print(c, 1, 16);
		bint_print(d, 1, 16);
		/* set d to: a - b */
		bint_sub(d, a, b);
		bintclr(a);
		ft_printf("\n%s: d = a - b = 0\n", bintcmp(a, d) ? "ERROR" : "SUCCESS");
		ft_printf("\n/////////////////////// AFTER /////////////////////////\n");
		bint_print(a, 1, 16);
		bint_print(b, 1, 16);
		bint_print(c, 1, 16);
		bint_print(d, 1, 16);
	}
	bintset_u64(a, UINT64_MAX);
	bintset_u64(b, UINT64_MAX - 1);
	bintset_u64(c, 1);
	bintclr(d);
	{
		ft_printf("\nTEST: bint_sub\n");
		ft_printf("TEST: a = UINT64_MAX && b = UINT64_MAX-1 && c = 1 && d = 0\n");
		ft_printf("\n/////////////////////// BEFORE /////////////////////////\n");
		bint_print(a, 1, 16);
		bint_print(b, 1, 16);
		bint_print(c, 1, 16);
		bint_print(d, 1, 16);
		/* set d to: a - b */
		bint_sub(d, a, b);
		ft_printf("\n%s: d = a - b = 1\n", bintcmp(c, d) ? "ERROR" : "SUCCESS");
		ft_printf("\n/////////////////////// AFTER /////////////////////////\n");
		bint_print(a, 1, 16);
		bint_print(b, 1, 16);
		bint_print(c, 1, 16);
		bint_print(d, 1, 16);
	}
	bintset_u64(a, UINT64_MAX);
	bintset_u64(b, UINT64_MAX - 1);
	bintset_u64(c, 1);
	SET_BINT_SIGN(c, 1);
	bintclr(d);
	{
		ft_printf("\nTEST: bint_sub\n");
		ft_printf("TEST: a = UINT64_MAX && b = UINT64_MAX-1 && c = -1 && d = 0\n");
		ft_printf("\n/////////////////////// BEFORE /////////////////////////\n");
		bint_print(a, 1, 16);
		bint_print(b, 1, 16);
		bint_print(c, 1, 16);
		bint_print(d, 1, 16);
		/* set d to: b - a */
		bint_sub(d, b, a);
		ft_printf("\n%s: d = b - a = -1\n", bintcmp(c, d) ? "ERROR" : "SUCCESS");
		ft_printf("\n/////////////////////// AFTER /////////////////////////\n");
		bint_print(a, 1, 16);
		bint_print(b, 1, 16);
		bint_print(c, 1, 16);
		bint_print(d, 1, 16);
	}
	bintset_u64(a, UINT64_MAX);
	bint_smult2(a);
	bintset_u64(b, UINT64_MAX);
	bintset_u64(c, UINT64_MAX);
	bintclr(d);
	{
		ft_printf("\nTEST: bint_sub\n");
		ft_printf("TEST: b = c = UINT64_MAXb && a = 2*UINT64_MAX && d = 0\n");
		ft_printf("\n/////////////////////// BEFORE /////////////////////////\n");
		bint_print(a, 1, 16);
		bint_print(b, 1, 16);
		bint_print(c, 1, 16);
		bint_print(d, 1, 16);
		/* set d to: a - b */
		bint_sub(d, a, b);
		ft_printf("\n%s: d = a - b = c\n", bintcmp(c, d) ? "ERROR" : "SUCCESS");
		ft_printf("\n/////////////////////// AFTER /////////////////////////\n");
		bint_print(a, 1, 16);
		bint_print(b, 1, 16);
		bint_print(c, 1, 16);
		bint_print(d, 1, 16);
	}
}

#define BINTF_MAX_ARGS 3

/*
** FIRST: return (V for void, I for int)
** SECOND AND AFTER: parameters
** B for t_bint
** U32 for uint32_t
** U64 for uint64_t
** I64 for int64_t
**
** NONE is just for the null element
*/
enum				e_ftype {
	V_B_U32,
	V_B,
	I_B_B,
	I_B_U64,
	I_B_I64,
	I_B_U32,
	I_B_B_B,
	I_B_B_U32,
	I_B,
	I_B_U32_U32,
	V,
	NONE
};

/*
** NOPE: nothing (end of arguments)
** VR: void return
** IR: int return
** BA: t_bint argument
** U32A: uint32_t argument
** U64A: uint64_t argument
** I64A: int64_t argument
*/
enum				e_argtype { NOPE, VR, IR, BA, U32A, U64A, I64A };

const int			g_ftypes_protos[][BINTF_MAX_ARGS + 2] = {
	{VR,	BA,		U32A,	NOPE,	NOPE},
	{VR,	BA,		NOPE,	NOPE,	NOPE},
	{IR,	BA,		BA,		NOPE,	NOPE},
	{IR,	BA,		U64A,	NOPE,	NOPE},
	{IR,	BA,		I64A,	NOPE,	NOPE},
	{IR,	BA,		U32A,	NOPE,	NOPE},
	{IR,	BA,		BA,		BA,		NOPE},
	{IR,	BA,		BA,		U32A,	NOPE},
	{IR,	BA,		NOPE,	NOPE,	NOPE},
	{IR,	BA,		U32A,	U32A,	NOPE},
	{VR,	NOPE,	NOPE,	NOPE,	NOPE},
	{NOPE,	NOPE,	NOPE,	NOPE,	NOPE},
};

typedef struct		s_bintcmd
{
	const char		*name;
	int				name_len;
	enum e_ftype	ftype;
	void			*f;
}					t_bintcmd;

static void	bc_help(void);
static void	bc_env(void);

#define DEFINE_BINTCMD(name, ftype, f) { name, (sizeof(name) - 1), ftype, f}
const t_bintcmd		g_bint_commands[] = {
	DEFINE_BINTCMD( "init",			V_B_U32,		bintinit			),
	DEFINE_BINTCMD( "clr",			V_B,			bintclr				),
	DEFINE_BINTCMD( "cpy",			I_B_B,			bintcpy				),
	DEFINE_BINTCMD( "set_u64",		I_B_U64,		bintset_u64			),
	DEFINE_BINTCMD( "set_i64",		I_B_I64,		bintset_i64			),
	DEFINE_BINTCMD( "set_pow2",		I_B_U32,		bintset_pow2		),
	DEFINE_BINTCMD( "set_pow10",	I_B_U32,		bintset_pow10		),
	DEFINE_BINTCMD( "cmp",			I_B_B,			bintcmp				),
	DEFINE_BINTCMD( "cmp_abs",		I_B_B,			bintcmp_abs			),
	DEFINE_BINTCMD( "add",			I_B_B_B,		bint_add			),
	DEFINE_BINTCMD( "add_abs",		I_B_B_B,		bint_add_abs		),
	DEFINE_BINTCMD( "sadd_u32_abs",	I_B_U32,		bint_sadd_u32_abs	),
	DEFINE_BINTCMD( "sub",			I_B_B_B,		bint_sub			),
	DEFINE_BINTCMD( "sub_abs",		I_B_B_B,		bint_sub_abs		),
	DEFINE_BINTCMD( "ssub_u32_abs",	I_B_U32,		bint_ssub_u32_abs	),
	DEFINE_BINTCMD( "mult",			I_B_B_B,		bint_mult			),
	DEFINE_BINTCMD( "mult_u32",		I_B_B_U32,		bint_mult_u32		),
	DEFINE_BINTCMD( "mult2",		I_B_B,			bint_mult2			),
	DEFINE_BINTCMD( "multpow10",	I_B_B_U32,		bint_multpow10		),
	DEFINE_BINTCMD( "smult2",		I_B,			bint_smult2			),
	DEFINE_BINTCMD( "smult10",		I_B,			bint_smult10		),
	DEFINE_BINTCMD( "shiftleft",	I_B_U32,		bint_shiftleft		),
	DEFINE_BINTCMD( "print",		I_B_U32_U32,	bint_print			),
	DEFINE_BINTCMD( "help",			V,				bc_help				),
	DEFINE_BINTCMD( "env",			V,				bc_env				),
	DEFINE_BINTCMD( NULL,			NONE,			NULL				),
};

static void	bc_help(void)
{
	int			ftype;
	const char	*argtypes[4] = { "t_bint", "uint32_t", "uint64_t", "int64_t" };

	for (int i = 0; g_bint_commands[i].name; ++i)
	{
		ftype = g_bint_commands[i].ftype;
		ft_printf("%1$-16s --  %2$s %1$s(", g_bint_commands[i].name,
			g_ftypes_protos[ftype][0] == VR ? "void" : "int" );
		for (int j = 1; g_ftypes_protos[ftype][j] != NOPE; ++j)
			ft_printf("%s%s", j > 1 ? ", " : "",
				argtypes[g_ftypes_protos[ftype][j] - 3]);
		ft_printf(")\n");
	}
}

static int	get_var_bint(t_bint *res, const char *str, int init);

static void	bc_env(void)
{
	t_bint	var;
	int		first;
	char	name[2] = { 0 };

	first = 1;
	var = NULL;
	for (int c = 'a'; c <= 'z'; ++c)
	{
		name[0] = c;
		get_var_bint(&var, name, 0);
		if (var && *var)
		{
			ft_printf("%c%c:\n", first ? '\0' : '\n', c - 32);
			bint_print(var, 1, 16);
			first = 0;
		}
	}
}

int	v_b_u32(int cmdi, t_bint args[BINTF_MAX_ARGS],
	uint32_t u32args[BINTF_MAX_ARGS],
	uint64_t u64args[BINTF_MAX_ARGS],
	int64_t i64args[BINTF_MAX_ARGS])
{
	void	(*f)(t_bint, uint32_t) = g_bint_commands[cmdi].f;

	(void)u32args;
	(void)u64args;
	(void)i64args;
	f(args[0], u32args[1]);
	return (BINT_SUCCESS);
}

int	v_b(int cmdi, t_bint args[BINTF_MAX_ARGS],
	uint32_t u32args[BINTF_MAX_ARGS],
	uint64_t u64args[BINTF_MAX_ARGS],
	int64_t i64args[BINTF_MAX_ARGS])
{
	void	(*f)(t_bint) = g_bint_commands[cmdi].f;

	(void)u32args;
	(void)u64args;
	(void)i64args;
	f(args[0]);
	return (BINT_SUCCESS);
}

int	i_b_b(int cmdi, t_bint args[BINTF_MAX_ARGS],
	uint32_t u32args[BINTF_MAX_ARGS],
	uint64_t u64args[BINTF_MAX_ARGS],
	int64_t i64args[BINTF_MAX_ARGS])
{
	int		ret;
	int		(*f)(t_bint, t_bint) = g_bint_commands[cmdi].f;

	(void)u32args;
	(void)u64args;
	(void)i64args;
	if (f == bintcmp || f == bintcmp_abs)
	{
		ret = f(args[0], args[1]);
		ft_printf("cmp: %d\n", ret);	
		return (BINT_SUCCESS);
	}
	return (f(args[0], args[1]));
}

int	i_b_u64(int cmdi, t_bint args[BINTF_MAX_ARGS],
	uint32_t u32args[BINTF_MAX_ARGS],
	uint64_t u64args[BINTF_MAX_ARGS],
	int64_t i64args[BINTF_MAX_ARGS])
{
	int		(*f)(t_bint, uint64_t) = g_bint_commands[cmdi].f;

	(void)u32args;
	(void)u64args;
	(void)i64args;
	return (f(args[0], u64args[1]));
}

int	i_b_i64(int cmdi, t_bint args[BINTF_MAX_ARGS],
	uint32_t u32args[BINTF_MAX_ARGS],
	uint64_t u64args[BINTF_MAX_ARGS],
	int64_t i64args[BINTF_MAX_ARGS])
{
	int		(*f)(t_bint, int64_t) = g_bint_commands[cmdi].f;

	(void)u32args;
	(void)u64args;
	(void)i64args;
	return (f(args[0], i64args[1]));
}

int	i_b_u32(int cmdi, t_bint args[BINTF_MAX_ARGS],
	uint32_t u32args[BINTF_MAX_ARGS],
	uint64_t u64args[BINTF_MAX_ARGS],
	int64_t i64args[BINTF_MAX_ARGS])
{
	int		(*f)(t_bint, uint32_t) = g_bint_commands[cmdi].f;

	(void)u32args;
	(void)u64args;
	(void)i64args;
	return (f(args[0], u32args[1]));
}

int	i_b_b_b(int cmdi, t_bint args[BINTF_MAX_ARGS],
	uint32_t u32args[BINTF_MAX_ARGS],
	uint64_t u64args[BINTF_MAX_ARGS],
	int64_t i64args[BINTF_MAX_ARGS])
{
	int		(*f)(t_bint, t_bint, t_bint) = g_bint_commands[cmdi].f;

	(void)u32args;
	(void)u64args;
	(void)i64args;
	return (f(args[0], args[1], args[2]));
}

int	i_b_b_u32(int cmdi, t_bint args[BINTF_MAX_ARGS],
	uint32_t u32args[BINTF_MAX_ARGS],
	uint64_t u64args[BINTF_MAX_ARGS],
	int64_t i64args[BINTF_MAX_ARGS])
{
	int		(*f)(t_bint, t_bint, uint32_t) = g_bint_commands[cmdi].f;

	(void)u32args;
	(void)u64args;
	(void)i64args;
	return (f(args[0], args[1], u32args[2]));
}

int	i_b(int cmdi, t_bint args[BINTF_MAX_ARGS],
	uint32_t u32args[BINTF_MAX_ARGS],
	uint64_t u64args[BINTF_MAX_ARGS],
	int64_t i64args[BINTF_MAX_ARGS])
{
	int		(*f)(t_bint) = g_bint_commands[cmdi].f;

	(void)u32args;
	(void)u64args;
	(void)i64args;
	return (f(args[0]));
}

int	i_b_u32_u32(int cmdi, t_bint args[BINTF_MAX_ARGS],
	uint32_t u32args[BINTF_MAX_ARGS],
	uint64_t u64args[BINTF_MAX_ARGS],
	int64_t i64args[BINTF_MAX_ARGS])
{
	int		(*f)(t_bint, uint32_t, uint32_t) = g_bint_commands[cmdi].f;

	(void)u32args;
	(void)u64args;
	(void)i64args;
	return (f(args[0], u32args[1], u32args[2]));
}

int	v(int cmdi, t_bint args[BINTF_MAX_ARGS],
	uint32_t u32args[BINTF_MAX_ARGS],
	uint64_t u64args[BINTF_MAX_ARGS],
	int64_t i64args[BINTF_MAX_ARGS])
{
	void	(*f)(void) = g_bint_commands[cmdi].f;

	(void)args;
	(void)u32args;
	(void)u64args;
	(void)i64args;
	f();
	return (BINT_SUCCESS);
}

static int	bint_to_u32(uint32_t *res, t_bint n)
{
	if (BINT_SIGN(n) || BINT_LEN(n) > 1)
		return (BINT_FAILURE);
	*res = BINT_LEN(n) ? n[1] : 0;
	return (BINT_SUCCESS);
}

static int	bint_to_u64(uint64_t *res, t_bint n)
{
	if (BINT_SIGN(n) || BINT_LEN(n) > 2)
		return (BINT_FAILURE);
	*res = BINT_LEN(n) ? (uint64_t)n[1] : 0;
	if (BINT_LEN(n) == 2)
		*res = *res + ((uint64_t)n[2] << 32);
	return (BINT_SUCCESS);
}

static int	bint_to_i64(int64_t *res, t_bint n)
{
	uint64_t	abs;

	if (BINT_LEN(n) > 2)
		return (BINT_FAILURE);
	abs = BINT_LEN(n) ? (uint64_t)n[1] : 0;
	if (BINT_LEN(n) == 2)
		abs += (uint64_t)n[2] << 32;

	if (!BINT_SIGN(n) && abs > (uint64_t)INT64_MAX)
		return (BINT_FAILURE);
	else if (BINT_SIGN(n) && abs > (((uint64_t)INT64_MAX) + 1))
		return (BINT_FAILURE);
	*res = abs;
	if (BINT_SIGN(n))
		*res *= -1;
	return (BINT_SUCCESS);
}

static int	exec_cmd(t_bint args[BINTF_MAX_ARGS], int cmdi)
{
	uint32_t	u32args[BINTF_MAX_ARGS];
	uint64_t	u64args[BINTF_MAX_ARGS];
	int64_t		i64args[BINTF_MAX_ARGS];
	int			ftype;
	int			ret;

	ret = BINT_SUCCESS;
	ftype = g_bint_commands[cmdi].ftype;
	for (int i = 1; i < BINTF_MAX_ARGS + 2; ++i)
	{
		switch (g_ftypes_protos[ftype][i])
		{
			case U32A: ret = bint_to_u32(u32args + i - 1, args[i-1]);
				break;
			case U64A: ret = bint_to_u64(u64args + i - 1, args[i-1]);
				break;
			case I64A: ret = bint_to_i64(i64args + i - 1, args[i-1]);
				break;
			default:
				break;
		}
	}
	switch (ftype)
	{
		case V_B_U32: ret = v_b_u32(cmdi, args, u32args, u64args, i64args);
			break;
		case V_B: ret = v_b(cmdi, args, u32args, u64args, i64args);
			break;
		case I_B_B: ret = i_b_b(cmdi, args, u32args, u64args, i64args);
			break;
		case I_B_U64: ret = i_b_u64(cmdi, args, u32args, u64args, i64args);
			break;
		case I_B_I64: ret = i_b_i64(cmdi, args, u32args, u64args, i64args);
			break;
		case I_B_U32: ret = i_b_u32(cmdi, args, u32args, u64args, i64args);
			break;
		case I_B_B_B: ret = i_b_b_b(cmdi, args, u32args, u64args, i64args);
			break;
		case I_B_B_U32: ret = i_b_b_u32(cmdi, args, u32args, u64args, i64args);
			break;
		case I_B: ret = i_b(cmdi, args, u32args, u64args, i64args);
			break;
		case I_B_U32_U32: ret = i_b_u32_u32(cmdi, args, u32args, u64args, i64args);
			break;
		case V: ret = v(cmdi, args, u32args, u64args, i64args);
			break;
		default: ret = BINT_FAILURE;
			break;
	}
	return (ret);
}

static int	skip_whites(char **line)
{
	char	*l;
	int		skipped;

	l = *line;
	while (*l && ft_isspace(*l))
		++l;
	skipped = l - *line;
	*line = l;
	return (skipped);
}

static int		read_command_name(char **line)
{
	int	len;
	int	cmdi;

	if (!ft_strncmp(*line, "bint", 4))
	{
		*line += 4;
		*line = **line == '_' ? *line + 1 : *line;
	}
	for (cmdi = 0; g_bint_commands[cmdi].name; ++cmdi)
	{
		len = g_bint_commands[cmdi].name_len;
		if (!ft_strncmp(*line, g_bint_commands[cmdi].name, len)
			&& ((*line)[len] == '(' || !(*line)[len]
			|| ft_isspace((*line)[len])))
		{
			*line += len;
			skip_whites(line);
			break ;
		}
	}
	return (cmdi);
}

int				decimal_to_bint(t_bint res, const char *str)
{
	uint32_t	n;
	const char	*p;
	int			sign;

	if ((sign = *str == '-'))
		++str;
	for (p = str; *p && ft_isdigit(*p); ++p);
	if (*p || p == str)
		return (BINT_FAILURE);
	bintclr(res);
	for (p = str; *p && bint_smult10(res) == BINT_SUCCESS; ++p)
	{
		n = (uint32_t)(*p - '0');
		if (bint_sadd_u32_abs(res, n) == BINT_FAILURE)
			return (BINT_FAILURE);
	}
	SET_BINT_SIGN(res, sign);
	return (*p ? BINT_FAILURE : BINT_SUCCESS);
}

#define HEXL 8 //max length in hexadecimal of an unsigned int of 32bits

static int		hextouint32(t_bint res, char hex[HEXL], int i)
{
	uint32_t	n;
	char		*d;
	const char	digits[] = "0123456789abcdef";

	for (int j = 0; j < HEXL; ++j)
		hex[j] = ft_tolower(hex[j]);
	n = 0;
	for (int k = 0; k < HEXL; ++k)
	{
		n <<= 4;
		if (!(d = ft_strchr(digits, hex[k])))
			return (BINT_FAILURE);	
		n |= (uint32_t)(d - digits);
	}
	res[i] = n;
	if (!n && (uint32_t)i == BINT_LEN(res))
		SET_BINT_LEN(res, (uint32_t)i - 1);
	if (!BINT_LEN(res))
		SET_BINT_SIGN(res, 0);
	return (BINT_SUCCESS);
}

int				hex_to_bint(t_bint res, const char *str)
{
	const char	*p;
	uint32_t	len;
	uint32_t	blen;
	char		hex[HEXL];

	bintclr(res);
	SET_BINT_SIGN(res, *str == '-');
	str = *str == '-' ? str + 1 : str;
	if (str[0] != '0' || !(str[1] == 'x' || str[1] == 'X'))
		return (BINT_FAILURE);
	str += 2;
	for (p = str; *p && (ft_isdigit(*p) || ft_strchr("abcdefABCDEF", *p)); ++p);
	if (*p || p == str)
		return (BINT_FAILURE);
	len = ft_strlen(str);
	if ((blen = len / HEXL + !!(len % HEXL)) >= BINT_SIZE(res))
		return (BINT_FAILURE);
	SET_BINT_LEN(res, blen);
	len = len % HEXL ? len % HEXL : HEXL;
	ft_memset((void *)hex, '0', HEXL - len);
	ft_strncpy(hex + HEXL - len, str, len);
	for (str += len; hextouint32(res, hex, blen--) == BINT_SUCCESS && blen > 0;
		str += HEXL)
		ft_strncpy(hex, str, HEXL);
	return (BINT_SUCCESS);
}

/*
** The exponent is limited to a size 2 because the maximum size of bint is
** (2^15)-1 = 32767, which means the absolute value can at most 1048544 bits
** long, so the exponent can't be superior to 1048543. A single uint32_t
** number is more than enough to hold this value hence the size of exp.
*/
int				pow2_to_bint(t_bint res, const char *str)
{
	int			ret;
	int			sign;
	uint32_t	exp[2];

	sign = *str == '-';
	str = *str == '-' ? str + 1 : str;
	if (ft_strncmp(str, "2^", 2) || !str[2])
		return (BINT_FAILURE);
	str += 2;
	bintinit(exp, 2);
	if (decimal_to_bint(exp, str) == BINT_FAILURE || BINT_SIGN(exp))
		return (BINT_FAILURE);
	if ((ret = bintset_pow2(res, exp[1])) == BINT_SUCCESS)
		SET_BINT_SIGN(res, sign);
	return (ret);
}

/*
** The same holds for the exponent of the pow10, since the resulting value
** would be even bigger than with a power of 2 for the same exponent.
*/
int				pow10_to_bint(t_bint res, const char *str)
{
	int			ret;
	int			sign;
	uint32_t	exp[2];

	sign = *str == '-';
	str = *str == '-' ? str + 1 : str;
	if (ft_strncmp(str, "10^", 3) || !str[3])
		return (BINT_FAILURE);
	str += 3;
	bintinit(exp, 2);
	if (decimal_to_bint(exp, str) == BINT_FAILURE || BINT_SIGN(exp))
		return (BINT_FAILURE);
	if ((ret = bintset_pow10(res, exp[1])) == BINT_SUCCESS)
		SET_BINT_SIGN(res, sign);
	return (ret);
}

#define BINT_VARS_LEN	26

/*
** Right now variable names are only one letter (so 26 variables)
*/
static int		get_var_bint(t_bint *res, const char *str, int init)
{
	int				c;
	static uint32_t	vars[BINT_SIZE_DEF * BINT_VARS_LEN] = { 0 };

	if (ft_strlen(str) > 1 || !ft_isalpha(*str))
		return (BINT_FAILURE);
	c = ft_tolower(*str) - 'a';
	*res = vars + (BINT_SIZE_DEF * c);
	if (init && !**res)
		bintinit(*res, 0);
	return (BINT_SUCCESS);
}

static char		*get_arg(char **line, int expect_com)
{
	char	*p;
	char	*arg;

	p = *line;
	arg = NULL;
	while (*p && !ft_isspace(*p) && !(expect_com && *p == ',')
		&& !(expect_com && *p == ')'))
		++p;
	if (p > *line)
		arg = ft_strndup(*line, (size_t)(p - (*line)));
	*line = p;
	return (arg);
}

static int		read_args(t_bint *args, char **line, int expect_com)
{
	int		ret;
	char	*arg;

	for (int i = 0; i < BINTF_MAX_ARGS && **line && **line != ')'; ++i)
	{
		if (i > 0 && expect_com && **line != ',')
			return (-1);
		else if (i > 0 && expect_com)
		{
			*line = *line + 1;
			skip_whites(line);
		}
		if (!(arg = get_arg(line, expect_com)))
			return (-1);
		ret = decimal_to_bint(args[i], arg) == BINT_FAILURE 
			&& hex_to_bint(args[i], arg) == BINT_FAILURE
			&& pow2_to_bint(args[i], arg) == BINT_FAILURE
			&& pow10_to_bint(args[i], arg) == BINT_FAILURE
			&& get_var_bint(args + i, arg, 1) == BINT_FAILURE;
		ft_memdel((void **)&arg);
		if (ret)
			return (-1);
		skip_whites(line);
	}
	return (0);
}

static int		parse_input(t_bint *args, char *line)
{
	int	cmdi;
	int	expect_par;

	skip_whites(&line);
	cmdi = read_command_name(&line);
	if (!g_bint_commands[cmdi].name)
		return (cmdi);
	if ((expect_par = *line == '('))
		++line;
	skip_whites(&line);
	if (read_args(args, &line, expect_par) || (expect_par && *line != ')')
		|| (!expect_par && *line == ')'))
		return (-1);
	else if (expect_par)
		++line;
	skip_whites(&line);
	return (*line ? -1 : cmdi);
}

static int		read_input(t_bint *args)
{
	int		ret;
	char	*line;

	line = NULL;
	if ((ret = get_next_line(0, &line)) < 0)
		ft_exit("read_input: get_next_line error\n", EXIT_FAILURE);
	else if (!ret)
		ft_exit(NULL, EXIT_SUCCESS);
	ret = parse_input(args, line);
	ft_memdel((void **)&line);
	return (ret);
}

static void	bintbc(const char *exec)
{
	int			ret;
	int			cmdi;
	t_bint		args[BINTF_MAX_ARGS];
	uint32_t	static_args[BINTF_MAX_ARGS][BINT_SIZE_DEF];

	ret = -1;
	for (int i = 0; i < BINTF_MAX_ARGS; ++i)
		bintinit(static_args[i], 0);
	while (1)
	{
		for (int i = 0; i < BINTF_MAX_ARGS; ++i)
		{
			args[i] = (t_bint)&static_args[i];
			bintclr(args[i]);
		}
		ft_printf("[%c]%s> ", ret == -1 ? '\0'
			: ret == BINT_SUCCESS ? 'S' : 'F', exec);
		cmdi = read_input(args);
		if (cmdi < 0)
			ft_dprintf(2, "%s: invalid command\n", exec);
		else if (g_bint_commands[cmdi].name == NULL)
			ft_dprintf(2, "%s: unknown command\n", exec);
		else
			ret = exec_cmd(args, cmdi);
	}
}

int		main(int argc, char **argv)
{
	show = argc > 1;
	setlocale(LC_ALL, "C");
	if (show && !ft_strcmp(argv[1], "bc"))
		bintbc(argv[0]);
	else
		test_mandatory(argc, argv);
	return (0);
}

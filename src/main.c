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
#include "bint.h"

#define C_RED     "\x1b[31m"
#define C_GREEN   "\x1b[32m"
#define C_RESET   "\x1b[0m"

#define	CONVERSIONS	"dDibBoOuUxXeEfFgGcCsSpPt%"
#define	FLAGS		"#0-+ "
#define	CAST		"hljzL"
#define	SPACES		"                                                         "

int		ret_orig;
int		ret_mine;
char	buf_orig[16384];
char	buf_mine[16384];
int		margin;
int		show;

#define	PRINTF_TEST(format, arg) {\
	ret_orig = sprintf(buf_orig, format, arg);\
	ret_mine = ft_sprintf(buf_mine, format, arg);\
	margin = ft_printf("TEST:\t[%s]", format);\
	ft_printf("%.*s", 50 - margin, SPACES);\
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
		ft_printf(C_RED "FAILED\n" C_RESET);\
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

int		bint_print(t_bint n, int info, int base)
{
	uint32_t	bint_size;
	uint32_t	bint_sign;
	uint32_t	bint_len;

	if (base != 2 && base != 16)
		return (-1);
	bint_size = BINT_SIZE(n);
	bint_sign = BINT_SIGN(n);
	bint_len = BINT_LEN(n);
	ft_printf(base == 2 ? "0b " : base == 16 ? "0x " : "");
	if (!bint_len)
		ft_printf("0\n");
	for (int i = bint_len; i > 0; --i)
	{
		if (base == 16)
			ft_printf("%08x%c", n[i], i > 1 ? ' ' : '\n');
		else if (base == 2)
			ft_printf("%032b%c", n[i], i > 1 ? ' ' : '\n');
		//TODO: add the base 10 mode later (harder to do)
	}
	if (info)
		ft_printf("info block: size = %u | sign = %u | len = %u\n",
			bint_size, bint_sign, bint_len);
	return (0);
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
	ft_printf("\targv:\n");
	ft_printf("%#*t\t\t%s\n", ac, av);

	unsigned int		int_tab[10] = {
		0, 1, UINT_MAX, UINT_MAX, INT_MIN, INT_MIN, 6, 654676, 42, 9
	};
	ft_printf("\n\tunsigned int array (with 2 fields):\n");
	ft_printf("%#10.2t\t\tfirst field: %08x\tsecond field: %u\n", int_tab);

	ft_printf("b conversion:\n");
	ft_printf("\t\tunsigned int array:\n");
	ft_printf("\t\tdec: %#3t%-32u \n", int_tab + 5);
	ft_printf("\t\tbin: %#3t%.32b \n", int_tab + 5);

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

	ft_printf("TEST: bintset_pow2, bintset_pow10, bint_smult2, bint_smult10\n");
	ft_printf("TEST: a = b = c = d = 0\n");

	ret = bintset_u64(b, 1);
	ft_printf("\nset b to 1: ret = %s\n", ret == BINT_SUCCESS ?
		"BINT_SUCCESS" : "BINT_FAILURE");
	bint_print(b, 1, 16);

	ret = bintset_u64(d, 1);
	ft_printf("\nset d to 1: ret = %s\n", ret == BINT_SUCCESS ?
		"BINT_SUCCESS" : "BINT_FAILURE");
	bint_print(d, 1, 16);

	int step = 16;
	for (uint32_t i = 16; i <= 128; i += step)
	{
		ret = bintset_pow2(a, i);
		ft_printf("\nset a to 2^%u: ret = %s\n", i, ret == BINT_SUCCESS ?
			"BINT_SUCCESS" : "BINT_FAILURE");
		bint_print(a, 1, 2);

		ret = BINT_SUCCESS;
		for (int j = 0; j < step && ret == BINT_SUCCESS; ++j)
			ret = bint_smult2(b);
		ft_printf("\nmult b by 2 (%d times): ret = %s\n", step,
			ret == BINT_SUCCESS ? "BINT_SUCCESS" : "BINT_FAILURE");
		bint_print(b, 1, 2);

		ret = bintset_pow10(c, i);
		ft_printf("\nset c to 10^%u: ret = %s\n", i, ret == BINT_SUCCESS ?
			"BINT_SUCCESS" : "BINT_FAILURE");
		bint_print(c, 1, 16);

		ret = BINT_SUCCESS;
		for (int j = 0; j < step && ret == BINT_SUCCESS; ++j)
			ret = bint_smult10(d);
		ft_printf("\nmult d by 10 (%d times): ret = %s\n", step,
			ret == BINT_SUCCESS ? "BINT_SUCCESS" : "BINT_FAILURE");
		bint_print(d, 1, 16);

		ret = bintcmp(a, b);
		ft_printf("\n%s: a %s b (ret = %d)\n", !ret ? "SUCCESS" : "ERROR",
			!ret ? "=" : "!=", ret);

		ret = bintcmp(c, d);
		ft_printf("\n%s: c %s d (ret = %d)\n", !ret ? "SUCCESS" : "ERROR",
			!ret ? "=" : "!=", ret);

		ret = bintcmp(a, d);
		ft_printf("\n%s: a %s d (ret = %d)\n", ret ? "SUCCESS" : "ERROR",
			ret ? "!=" : "=", ret);

		ret = bintcmp(b, c);
		ft_printf("\n%s: b %s c (ret = %d)\n", ret ? "SUCCESS" : "ERROR",
			ret ? "!=" : "=", ret);
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
	NONE
};

#define BINTF_MAX_ARGS 3

typedef struct		s_bintcmd
{
	const char		*name;
	int				name_len;
	enum e_ftype	ftype;
	void			*f;
}					t_bintcmd;

#define DEFINE_BINTCMD(name, ftype, f) { name, (sizeof(name) - 1), ftype, f}
const t_bintcmd		g_bint_commands[] = {
	DEFINE_BINTCMD( "init",			V_B_U32,	bintinit			),
	DEFINE_BINTCMD( "clr",			V_B,		bintclr				),
	DEFINE_BINTCMD( "cpy",			I_B_B,		bintcpy				),
	DEFINE_BINTCMD( "set_u64",		I_B_U64,	bintset_u64			),
	DEFINE_BINTCMD( "set_i64",		I_B_I64,	bintset_i64			),
	DEFINE_BINTCMD( "set_pow2",		I_B_U32,	bintset_pow2		),
	DEFINE_BINTCMD( "set_pow10",	I_B_U32,	bintset_pow10		),
	DEFINE_BINTCMD( "cmp",			I_B_B,		bintcmp				),
	DEFINE_BINTCMD( "cmp_abs",		I_B_B,		bintcmp_abs			),
	DEFINE_BINTCMD( "add",			I_B_B_B,	bint_add			),
	DEFINE_BINTCMD( "add_abs",		I_B_B_B,	bint_add_abs		),
	DEFINE_BINTCMD( "sadd_u32_abs",	I_B_U32,	bint_sadd_u32_abs	),
	DEFINE_BINTCMD( "sub",			I_B_B_B,	bint_sub			),
	DEFINE_BINTCMD( "sub_abs",		I_B_B_B,	bint_sub_abs		),
	DEFINE_BINTCMD( "ssub_u32_abs",	I_B_U32,	bint_ssub_u32_abs	),
	DEFINE_BINTCMD( "mult",			I_B_B_B,	bint_mult			),
	DEFINE_BINTCMD( "mult_u32",		I_B_B_U32,	bint_mult_u32		),
	DEFINE_BINTCMD( "mult2",		I_B_B,		bint_mult2			),
	DEFINE_BINTCMD( "multpow10",	I_B_B_U32,	bint_multpow10		),
	DEFINE_BINTCMD( "smult2",		I_B,		bint_smult2			),
	DEFINE_BINTCMD( "smult10",		I_B,		bint_smult10		),
	DEFINE_BINTCMD( "shiftleft",	I_B_U32,	bint_shiftleft		),
	DEFINE_BINTCMD( NULL,			NONE,		NULL				),
};

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

	skip_whites(line);
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
			*line += len + ((*line)[len] == '(');
			break ;
		}
	}
	return (cmdi);
}

/*
** TODO:
** - actually do the parsing
** - create a t_bint variables array (like a, b, c, d, etc...) to be able
**	to assign t_bint variables
*/

static int		parse_input(t_bint *args, char *line)
{
	int	cmdi;

	(void)args; //TEMP
	(void)line; //TEMP
	cmdi = read_command_name(&line);
	if (!g_bint_commands[cmdi].name)
		return (cmdi);
	//read the BINTF_MAX_ARGS first arguments (err if more than that)
	//	try to parse as decimal
	//	try to parse as hex
	//	try to parse as a power of 2
	//	try to parse as a power of 10
	//	try to parse as a variable
	//	else --> err
	return (cmdi);
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
	int			cmdi; //command id (index in the g_bint_commands array)
	uint32_t	static_args[BINTF_MAX_ARGS][BINT_SIZE_DEF]; //t_bint array
	t_bint		args[BINTF_MAX_ARGS]; //store args pointers

	for (int i = 0; i < BINTF_MAX_ARGS; ++i)
		bintinit(static_args[i], 0);
	while (1)
	{
		for (int i = 0; i < BINTF_MAX_ARGS; ++i)
		{
			args[i] = (t_bint)&static_args[i];
			bintclr(args[i]);
		}
		ft_printf("%s> ", exec);
		cmdi = read_input(args);
		if (cmdi < 0)
			ft_dprintf(2, "%s: invalid command\n", exec);
		else if (g_bint_commands[cmdi].name == NULL)
			ft_dprintf(2, "%s: unknown command\n", exec);
		else
			ft_printf("Valid Command\n"); //TEMP (obviously)
		//exec_cmd(cmdi ); //TODO
	}
}

int		main(int argc, char **argv)
{
	show = argc > 1;
	setlocale(LC_ALL, "");
	if (show && !ft_strcmp(argv[1], "bc"))
		bintbc(argv[0]);
	else
		test_mandatory(argc, argv);
	return (0);
}

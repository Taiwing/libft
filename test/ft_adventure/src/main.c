#include "libft.h"

int	main(void)
{
	int		count = 0;
	t_ip	ip = { 0 };

	while (1)
	{
		if (ft_adventure(&ip, NULL) < 0)
			ft_exit(EXIT_FAILURE, "ft_adventure: %s", ft_strerror(ft_errno));
		++count;
		ft_printf("IP (%d): %s", count, ft_ip_str(&ip));
	}
	return (EXIT_SUCCESS);
}

#include "unity.h"

void	test_escalonat(void);
void	test_lore_ipsum(void);
void	setUp(void)
{
	return ;
}

void	tearDown(void)
{
	return ;
}

int	main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_escalonat);
	RUN_TEST(test_lore_ipsum);
	return (UNITY_END());
}

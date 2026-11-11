#include "unity.h"

void	test_escalonat(void);
void	test_lore_ipsum(void);
void	test_empty(void);
void	test_perms(void);
void	test_bonus(void);

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
	RUN_TEST(test_empty);
	RUN_TEST(test_perms);
#ifdef TEST_BONUS
	RUN_TEST(test_bonus);
#endif
	return (UNITY_END());
}

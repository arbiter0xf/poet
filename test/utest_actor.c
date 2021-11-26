#include <criterion/criterion.h>

#if 0
void setup(void) {
	    puts("Runs before the test");
}

void teardown(void) {
	    puts("Runs after the test");
}
#endif

Test(first, test)
{
	cr_expect(0 == 0);
}

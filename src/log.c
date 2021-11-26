#include "log.h"

FILE* g_log_handle = 0;
char g_log_buffer[LOG_STR_SIZE] = {0};

void initialize_logging(void)
{
	// First, truncate previous log if there is such.
	g_log_handle = fopen(LOG_FILE_NAME, "w");
	fclose(g_log_handle);

	g_log_handle = fopen(LOG_FILE_NAME, "w+");
}

void teardown_logging(void)
{
	fclose(g_log_handle);
	g_log_handle = 0;
}

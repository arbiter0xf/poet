#ifndef LOG_H_DEFINED
#define LOG_H_DEFINED

#include <assert.h>
#include <stdio.h>

#define LOG_FILE_NAME "game_log.txt"
#define LOG_STR_SIZE 256

#define LOG_INFO(new_log, ...) LOG_COMMON("[INFO] " , new_log, __VA_ARGS__)
#define LOG_DEBUG(new_log, ...) LOG_COMMON("[DBUG] " , new_log, __VA_ARGS__)
#define LOG_WARNING(new_log, ...) LOG_COMMON("[WARN] " , new_log, __VA_ARGS__)
#define LOG_ERROR(new_log, ...) LOG_COMMON("[ERR ] " , new_log, __VA_ARGS__)

#if LOGGING_DISABLED
#define LOG_COMMON(priority, new_log, ...)
#else
#define LOG_COMMON(priority, new_log, ...)			\
	bzero(g_log_buffer, LOG_STR_SIZE);			\
	strcat(g_log_buffer, priority);				\
	strcat(g_log_buffer, new_log);				\
	g_log_buffer[LOG_STR_SIZE - 1] = '\0';			\
	assert(g_log_handle);					\
	fprintf(g_log_handle, g_log_buffer, __VA_ARGS__);	\
	fflush(g_log_handle);
#endif

extern FILE* g_log_handle;
extern char g_log_buffer[LOG_STR_SIZE];

void initialize_logging(void);
void teardown_logging(void);

#endif

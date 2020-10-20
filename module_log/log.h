#ifndef log_h
#define log_h
#ifdef __cplusplus
extern "C" {
#endif
/**
 * printf now time
 */
void LOG_TIME();

/**
 * log i
 */
void LOG_I(const char *formatStr, ...);

/**
 * log e
 */
void LOG_E(const char *formatStr, ...);

#ifdef __cplusplus
}
#endif

#endif /* log_h */
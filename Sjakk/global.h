#ifndef GLOBAL_H
#define GLOBAL_H

#ifdef LOGGING_ENABLED
#define LOG(x) log_message(x)
#else
#define LOG(x)
#endif

#endif // GLOBAL_H

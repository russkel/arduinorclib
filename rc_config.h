#ifndef INC_RC_CONFIG_H
#define INC_RC_CONFIG_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** rc_config.h
** Configuration for compilation and debugging levels
** Changes in this file will cause a rebuild of the entire lib
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

// This is the global debug level
// If you just want to change the debug level of the library, modify rc_debug_lib.h!
#define RC_GLOBAL_LEVEL 5

// 0 = OFF - asserts disabled
// 1 = ERROR - Asserts enabled
// 2 = WARN  - Warnings enabled
// 3 = INFO  - Informational messages enabled
// 4 = DEBUG - Debugging messages enabled
// 5 = TRACE - Trace messages enabled

// By default we set the debug level to the global level.
// You can change this on a per file basis by setting RC_DEBUG_LEVEL before including rc_debug.h
#ifndef RC_DEBUG_LEVEL
#define RC_DEBUG_LEVEL RC_GLOBAL_LEVEL
#endif

#endif // INC_RC_CONFIG_H

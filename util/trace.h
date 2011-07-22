/******************************************************************************
 * trace.h
 * Copyright 2010 Iain Peet
 *
 * Provides faculties for simple control of trace message logging and 
 * filtering.
 ******************************************************************************
 * This program is distributed under the of the GNU Lesser Public License. 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *****************************************************************************/

#ifndef TRACE_H_
#define TRACE_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/** This is the control structure tracing a particular logical section
 *  of code.  It contains essential information:  the current trace level,
 *  the name of the section, and a method for writing its output */
typedef struct trc_ctrl_s {
    // The current trace level (messages with levels <= this print):
    int print_level;
    // The name to tag prints with (may be 0):
    const char* name;
    // Function which writes trace data to its destination:
    void (* write_fn)(const char*);
} trc_ctl_t;

/** Define common interpretations for trace levels: */
#define TRC_ERR          1
#define TRC_WARN         2
#define TRC_STAT         3
#define TRC_INFO         4
#define TRC_DTL          5
// Specifying this trace level should disable all tracing
#define TRC_NONE         0
// A nice default level for programs to use
#define TRC_DFL_LVL  TRC_WARN

/** Define some standard output functions */
// Print to stdout:
inline void trc_stdprint(const char* msg) {
    printf("%s",msg);   
    fflush(stdout);
}
#define TRC_STDOUT      trc_stdprint

// Print to stderr:
inline void trc_errprint(const char* msg) {
    fprintf(stderr,"%s",msg);
    fflush(stderr);
}
#define TRC_STDERR       trc_errprint

// Write to the file TRC_DFL_FILENAME in CWD:
void trc_def_fprint(const char* msg);
#define TRC_DFL_FILE     trc_def_fprint
#define TRC_DFL_FILENAME "trace.txt"

// The default output function:
#define TRC_DFL_PRINT TRC_STDOUT

/** A default control structure for those quick-and-dirty situations 
 *  ( uses default definitions above ) */
extern trc_ctl_t       trc_default;

/** Print a formatted message according to the configuration structure
 *  @param ctl           The trace control structure to use.
 *                       If 0, trc_defaults will be used.
 *  @param level         The trace level for the message.  Message will
 *                       only be printed if level <= ctl->print_level
 *  @param do_tag        Whether to prepend the name/date.
 *  @param fmt           The message format.  Uses standard printf format.
 *  @param ...           Arguments to printf message format
 *  (It is suggested that you use a macro to simplify this appropriately) */
void trc_printf
    (trc_ctl_t* ctl, int level, int do_tag, const char * fmt, ...);
 
/** Ways in which the trace can be configured at runtime */
enum trc_global_type {
    // Trace level is controlled by the passed trc_ctl_t:
    TRC_NORMAL,
    // Messages with levels higher than a global level will not be printed,
    // even if the trc_ctl_t is sufficiently high for them to be printed
    // normally:
    TRC_LIMIT_LEVEL,
    // A global print_level completely overrides the trc_ctl_t print_level:
    TRC_OVERRIDE_LEVEL,
    // End of list, not actual type:
    TRC_NUM_TYPES
};

/** Allows trace behaviour to be modified at runtime.
 *  @param type          The type of global level to set (see above)
 *  @param level         The global level to set, effect varies according
 *                       to type */
void trc_global_set(enum trc_global_type type, int level);
    
#ifdef __cplusplus
};  // extern "C"
#endif

#endif // TRACE_H_

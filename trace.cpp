/******************************************************************************
* trace.cpp
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

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "trace.h"
#include "unit.h"

/** For tracing trace ;) */
#define TRACE(args...)   printf(args)
//#define TRACE(msg,args...)

//! Size of buffer used in trace_printf
#define TRC_PRBUF_SIZE   256

//! Default trace control block
trc_ctl_t trc_default = {
    TRC_DFL_LVL,
    0,
    TRC_DFL_PRINT
};

//! Runtime configurable trace level
static enum trc_global_type _trc_type = TRC_NORMAL;
static int _trc_global_level =          TRC_DFL_LVL;

//! Prints to the file 'trace'
void trc_def_fprint(const char* msg) {
    // Null check:
    if(!msg) {
        TRACE("Warning: null message provided to trc_def_fprint\n");
        return;
    }
    
    /* Open the output file if we haven't already */
    static FILE* out_file = 0;
    if(!out_file) {
        TRACE("Opening " TRC_DFL_FILENAME "\n");
        out_file = fopen(TRC_DFL_FILENAME,"a");
        if(!out_file) return;
    }
    if(ferror(out_file)) {
        TRACE("Error writing " TRC_DFL_FILENAME "\n");
        return;
    }
    
    // Write:
    fprintf(out_file,"%s",msg);
    fflush(out_file);
}

//! Prints a trace message
void trc_printf
(trc_ctl_t *ctl, int level, int do_tag, const char *fmt, ...) {
    // Used for constructing mesages:
    char prbuf [TRC_PRBUF_SIZE]; 
    /* Handle null args, as appropriate */
    if(!fmt) {
        TRACE("Warning: null message provided to trc_printf");
        return;
    }
    if(!ctl) ctl = &trc_default;
    if(!ctl->write_fn) {
        TRACE("Error: trace control has null write pointer.");
        return;
    }
    // Variable length args:
    va_list args;
    va_start(args,fmt);
    
    /* Check level */
    switch(_trc_type) {
        case TRC_NORMAL:
            if( level > ctl->print_level ) return;
            break;
        case TRC_LIMIT_LEVEL:
            if( level > ctl->print_level ) return;
            // fall through is intentional
        case TRC_OVERRIDE_LEVEL:
            if( level > _trc_global_level ) return;
            break;
        default:
            TRACE("Error: invalid _trc_type\n");
            break;
    }
    
    /* Print the tag, if desired */
    if(do_tag) {
        time_t timer = time(0);
        struct tm * cur_time = localtime(&timer);
        strftime(prbuf,TRC_PRBUF_SIZE,"[%b%d-%H:%M:%S]",cur_time);
        prbuf[TRC_PRBUF_SIZE-1]='\0';
        (ctl->write_fn)(prbuf);
        if(ctl->name) {
            snprintf(prbuf,TRC_PRBUF_SIZE,"[%s]",ctl->name);
            prbuf[TRC_PRBUF_SIZE-1]='\0';
            (ctl->write_fn)(prbuf);
        }
    }
    
    /* Print the message */
    vsnprintf(prbuf,TRC_PRBUF_SIZE,fmt,args);
    prbuf[TRC_PRBUF_SIZE-1]='\0';
    (ctl->write_fn)(prbuf);
}

//! Set global trace behaviour
void trc_global_set(enum trc_global_type type, int level) {
    if( type>=TRC_NUM_TYPES ) {
        TRACE("Warning: attempted to set invalid trace type.\n");
        return;
    }
    _trc_type = type;
    _trc_global_level = level;
}

/*****************************************************************************
 * Unit tests
 * Note that these tests are mostly intended to catch crashes, since it isn't 
 * really practical to try to make sure output actually got output (that's up
 * to a human being to check) */

START_TEST_FN(check_stdprint,"Check Trace to stdout")
    trc_stdprint("Test trace message on stdout.\n");
    TEST_CONDITION(1,"Printed without crashing\n");
END_TEST_FN

START_TEST_FN(check_errprint,"Check Trace to stderr")
    trc_errprint("Test trace message on stderr.\n");
    TEST_CONDITION(1,"Printed without crashing\n");
END_TEST_FN

START_TEST_FN(check_def_fprint,"Check Trace to default file")
    trc_def_fprint("Test race message to default file.\n");
    trc_def_fprint("Another message in default file.\n");
    TEST_CONDITION(1,"Printed without crashing\n");
END_TEST_FN

START_TEST_FN(check_trc_print,"Check Trace function")
    // Check using default control block
    trc_printf(&trc_default,1,0,"Printed with default handler\n");
    trc_printf(0,1,0,"Printed with (implicit) default handler\n");
    trc_printf(0,1,1,"Printed with tag\n");
    trc_printf(0,TRC_DFL_LVL+1,0,"This should NOT print\n");
    // Check using a special control block
    trc_ctl_t ctl = {
        TRC_STAT,
        "TRC",
        TRC_STDERR
    };
    trc_printf(&ctl,1,0,"Printed with control block\n");
    trc_printf(&ctl,1,1,"Printed with tag\n");
    trc_printf(&ctl,TRC_INFO,1,"This should NOT print\n");
    trc_printf(&ctl,1,1,"Args: %s %d %f\n","foo",42,3.14159);
    ctl.write_fn = TRC_DFL_FILE;
    trc_printf(&ctl,1,1,"trc_printf to file (0x%06x)\n",0xfeed);
    
    TEST_CONDITION(1,"Printed without crashing\n");
END_TEST_FN

START_TEST_FN(check_trc_set,"Check Trace Runtime Configuration\n")
    trc_printf(0,2,0,"Normal print.\n");
    trc_printf(0,TRC_DFL_LVL+1,0,"This should NOT print\n");
    trc_global_set(TRC_LIMIT_LEVEL,1);
    trc_printf(0,1,0,"Limited level.\n");
    trc_printf(0,2,0,"This should NOT print.\n");
    trc_global_set(TRC_OVERRIDE_LEVEL,5);
    trc_printf(0,1,0,"Overrode level.\n");
    trc_printf(0,5,0,"This should print.\n");
    
    TEST_CONDITION(1,"Tested without crashing\n");
END_TEST_FN

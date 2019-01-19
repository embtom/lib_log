/*
 * This file is part of the EMBTOM project
 * Copyright (c) 2018-2019 Thomas Willetal 
 * (https://github.com/tom3333)
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/* *******************************************************************
 * includes
 * ******************************************************************/

/* c-runtime */
#include <stdlib.h>

#ifdef NO_TTY_PORTMUX
#include <stdio.h>
#elif TRACE
#include <lib_ttyportmux.h>
#else
#error "No output is defined"
#endif

#include <stdarg.h>


/* own libs */

/* project */
#include "lib_log.h"

/* *******************************************************************
 * defines
 * ******************************************************************/

#ifdef NO_TTY_PORTMUX
#define M_WRITE_FORMATED_OUTPUT(_level, _format, ...) 		do { fprintf(stdout, _format, __VA_ARGS__); } while (0)
#define M_WRITE_FORMATED_OUTPUT_VA(_level, _format, _vargs) do { vfprintf(stdout, _format, _vargs); } while (0)
#define M_PRINT_FORMATED_OUTPUT_END(_level)					do { fflush(stdout); } while (0)

#else
#define M_WRITE_FORMATED_OUTPUT(_level, _format, ...) 	    do { lib_ttyportmux__print(lib_log__translate_log_level(_level), _format, __VA_ARGS__); } while (0)
#define M_WRITE_FORMATED_OUTPUT_VA(_level, _format, _vargs) do { lib_ttyportmux__vprint(lib_log__translate_log_level(_level), _format, _vargs); } while (0)
#define M_PRINT_FORMATED_OUTPUT_END(_level)					do { lib_ttyportmux__print(lib_log__translate_log_level(_level), "\n"); } while (0)

#endif


/* *******************************************************************
 * (static) variables declarations
  ******************************************************************/
static enum log_level s_log_level = LOG_LEVEL_warning;

/* *******************************************************************
 * static function declarations
 * ******************************************************************/
static char* lib_log__str_log_level(enum log_level _level);
enum ttyStreamType lib_log__translate_log_level(enum log_level _level);

/* *******************************************************************
 * \brief	Set active logging level
 * ---------
 * \remark
 * ---------
 *
 * \param	_level		: Set of logging level
 *
 * ---------
 * \return	void
 * ******************************************************************/
void lib_log__set_level(enum log_level _level)
{
	s_log_level = _level;
}

/* *******************************************************************
 * \brief	Get active logging level
 * ---------
 * \remark
 * ---------
 *
 * \param	void
 *
 * ---------
 * \return	reqest of active logging level
 * ******************************************************************/
enum log_level lib_log__get_level(void)
{
	return s_log_level;
}

/* *******************************************************************
 * \brief	Print of logging messages
 * ---------
 * \remark
 * ---------
 *
 * \param	_level				: 	Logging message level
 * 			_module_name [in]	:	Module name
 * 			_format [in]		:	Formatted output to print
 *
 * ---------
 * \return	void
 * ******************************************************************/
void lib_log__msg(enum log_level _level, const char *_module_name, const char *_format, ...)
{
	va_list args;
	//char *str1, *str2;


	if (_level < s_log_level)
	    return;

	/* prefix */
	if (_module_name == NULL)
	{

		M_WRITE_FORMATED_OUTPUT(_level, "[%s] ",lib_log__str_log_level(_level));
		//fprintf(stdout,"[%s] ",lib_log__str_log_level(_level));
	}
	else
	{
		M_WRITE_FORMATED_OUTPUT(_level, "[%s] - %s ",lib_log__str_log_level(_level),_module_name);
	//	fprintf(stdout,"[%s] - %s ",lib_log__str_log_level(_level),_module_name);
	}

	va_start(args, _format);
	M_WRITE_FORMATED_OUTPUT_VA(_level, _format, args);
	//vfprintf(stdout, _format, args);
	va_end(args);

	M_PRINT_FORMATED_OUTPUT_END(_level);
}



static char* lib_log__str_log_level(enum log_level _level)
{
	switch (_level)
	{

		case LOG_LEVEL_critical			: return "CRIT";
		case LOG_LEVEL_error			: return "ERR";
		case LOG_LEVEL_warning			: return "WRN";
		case LOG_LEVEL_info				: return "INFO";
		case LOG_LEVEL_debug 			: return "DBG_PRIO2";
		case LOG_LEVEL_stream_control	: return "DBG_PRIO1";
		default							: return "INV";
	}
}

enum ttyStreamType lib_log__translate_log_level(enum log_level _level)
{
	switch (_level)
	{
		case LOG_LEVEL_critical			: return TTYSTREAM_critical;
		case LOG_LEVEL_error			: return TTYSTREAM_error;
		case LOG_LEVEL_warning			: return TTYSTREAM_warning;
		case LOG_LEVEL_info				: return TTYSTREAM_info;
		case LOG_LEVEL_debug 			: return TTYSTREAM_debug;
		case LOG_LEVEL_stream_control	: return TTYSTREAM_control;
		default							: return TTYSTREAM_control;
	}
}


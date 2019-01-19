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


#ifndef SRC_LIB_LOG_H_
#define SRC_LIB_LOG_H_


/* *******************************************************************
 * custom data types (e.g. enumerations, structures, unions)
 * ******************************************************************/
enum log_level
{
	LOG_LEVEL_stream_control,
	LOG_LEVEL_debug,
	LOG_LEVEL_info,
	LOG_LEVEL_warning,
	LOG_LEVEL_error,
	LOG_LEVEL_critical
};


/* *******************************************************************
 * defines
 * ******************************************************************/
#ifdef TRACE
	#define msg(_level, _moduel_name, ...) do { \
			lib_log__msg(_level, _moduel_name, __VA_ARGS__);  \
	} while (0)
#else
	#define msg
#endif


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
void lib_log__set_level(enum log_level _level);

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
enum log_level lib_log__get_level(void);

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
void lib_log__msg(enum log_level _level, const char *_module_name, const char *_format, ...);



#endif /* SRC_LIB_LOG_H_ */

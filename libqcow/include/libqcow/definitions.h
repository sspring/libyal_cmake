/*
 * Definitions for libqcow
 *
 * Copyright (C) 2010-2017, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBQCOW_DEFINITIONS_H )
#define _LIBQCOW_DEFINITIONS_H

#include <libqcow/types.h>

#define LIBQCOW_VERSION				20170222

/* The version string
 */
#define LIBQCOW_VERSION_STRING			"20170222"

/* The access flags definitions
 * bit 1        set to 1 for read access
 * bit 2        set to 1 for write access
 * bit 3-8      not used
 */
enum LIBQCOW_ACCESS_FLAGS
{
	LIBQCOW_ACCESS_FLAG_READ		= 0x01,
/* Reserved: not supported yet */
	LIBQCOW_ACCESS_FLAG_WRITE		= 0x02
};

/* The file access macros
 */
#define LIBQCOW_OPEN_READ			( LIBQCOW_ACCESS_FLAG_READ )
/* Reserved: not supported yet */
#define LIBQCOW_OPEN_WRITE			( LIBQCOW_ACCESS_FLAG_WRITE )
/* Reserved: not supported yet */
#define LIBQCOW_OPEN_READ_WRITE			( LIBQCOW_ACCESS_FLAG_READ | LIBQCOW_ACCESS_FLAG_WRITE )

/* The encryption method definitions
 */
enum LIBQCOW_ENCRYPTION_METHODS
{
	LIBQCOW_ENCRYPTION_METHOD_NONE		= 0,
	LIBQCOW_ENCRYPTION_METHOD_AES_128_CBC	= 1
};

#endif /* !defined( _LIBQCOW_DEFINITIONS_H ) */


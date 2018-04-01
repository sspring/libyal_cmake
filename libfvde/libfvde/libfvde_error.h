/*
 * Error functions
 *
 * Copyright (C) 2011-2018, Omar Choudary <choudary.omar@gmail.com>,
 *                          Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBFVDE_INTERNAL_ERROR_H )
#define _LIBFVDE_INTERNAL_ERROR_H

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if !defined( HAVE_LOCAL_LIBFVDE )
#include <libfvde/error.h>
#endif

#include "libfvde_extern.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_LOCAL_LIBFVDE )

LIBFVDE_EXTERN \
void libfvde_error_free(
      libfvde_error_t **error );

LIBFVDE_EXTERN \
int libfvde_error_fprint(
     libfvde_error_t *error,
     FILE *stream );

LIBFVDE_EXTERN \
int libfvde_error_sprint(
     libfvde_error_t *error,
     char *string,
     size_t size );

LIBFVDE_EXTERN \
int libfvde_error_backtrace_fprint(
     libfvde_error_t *error,
     FILE *stream );

LIBFVDE_EXTERN \
int libfvde_error_backtrace_sprint(
     libfvde_error_t *error,
     char *string,
     size_t size );

#endif /* !defined( HAVE_LOCAL_LIBFVDE ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFVDE_INTERNAL_ERROR_H ) */


/*
 * Data area descriptor functions
 *
 * Copyright (C) 2011-2018, Omar Choudary <choudary.omar@gmail.com>
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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libfvde_data_area_descriptor.h"
#include "libfvde_libcerror.h"

/* Creates data area descriptor
 * Make sure the value data_area_descriptor is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfvde_data_area_descriptor_initialize(
     libfvde_data_area_descriptor_t **data_area_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libfvde_data_area_descriptor_initialize";

	if( data_area_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data area descriptor.",
		 function );

		return( -1 );
	}
	if( *data_area_descriptor != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid data area descriptor value already set.",
		 function );

		return( -1 );
	}
	*data_area_descriptor = memory_allocate_structure(
	                         libfvde_data_area_descriptor_t );

	if( *data_area_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to data area descriptor.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *data_area_descriptor,
	     0,
	     sizeof( libfvde_data_area_descriptor_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear data area descriptor.",
		 function );

		memory_free(
		 *data_area_descriptor );

		*data_area_descriptor = NULL;

		return( -1 );
	}
	return( 1 );

on_error:
	if( *data_area_descriptor != NULL )
	{
		memory_free(
		 *data_area_descriptor );

		*data_area_descriptor = NULL;
	}
	return( -1 );
}

/* Frees data area descriptor
 * Returns 1 if successful or -1 on error
 */
int libfvde_data_area_descriptor_free(
     libfvde_data_area_descriptor_t **data_area_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libfvde_data_area_descriptor_free";

	if( data_area_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data area descriptor.",
		 function );

		return( -1 );
	}
	if( *data_area_descriptor != NULL )
	{
		memory_free(
		 *data_area_descriptor );

		*data_area_descriptor = NULL;
	}
	return( 1 );
}


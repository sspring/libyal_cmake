/*
 * Library segment_descriptor type test program
 *
 * Copyright (C) 2011-2018, Joachim Metz <joachim.metz@gmail.com>
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
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fvde_test_libcerror.h"
#include "fvde_test_libfvde.h"
#include "fvde_test_macros.h"
#include "fvde_test_memory.h"
#include "fvde_test_unused.h"

#include "../libfvde/libfvde_segment_descriptor.h"

#if defined( __GNUC__ ) && !defined( LIBFVDE_DLL_IMPORT )

/* Tests the libfvde_segment_descriptor_initialize function
 * Returns 1 if successful or 0 if not
 */
int fvde_test_segment_descriptor_initialize(
     void )
{
	libcerror_error_t *error                         = NULL;
	libfvde_segment_descriptor_t *segment_descriptor = NULL;
	int result                                       = 0;

#if defined( HAVE_FVDE_TEST_MEMORY )
	int number_of_malloc_fail_tests                  = 1;
	int number_of_memset_fail_tests                  = 1;
	int test_number                                  = 0;
#endif

	/* Test regular cases
	 */
	result = libfvde_segment_descriptor_initialize(
	          &segment_descriptor,
	          &error );

	FVDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FVDE_TEST_ASSERT_IS_NOT_NULL(
	 "segment_descriptor",
	 segment_descriptor );

	FVDE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfvde_segment_descriptor_free(
	          &segment_descriptor,
	          &error );

	FVDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FVDE_TEST_ASSERT_IS_NULL(
	 "segment_descriptor",
	 segment_descriptor );

	FVDE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfvde_segment_descriptor_initialize(
	          NULL,
	          &error );

	FVDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FVDE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	segment_descriptor = (libfvde_segment_descriptor_t *) 0x12345678UL;

	result = libfvde_segment_descriptor_initialize(
	          &segment_descriptor,
	          &error );

	FVDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FVDE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	segment_descriptor = NULL;

#if defined( HAVE_FVDE_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfvde_segment_descriptor_initialize with malloc failing
		 */
		fvde_test_malloc_attempts_before_fail = test_number;

		result = libfvde_segment_descriptor_initialize(
		          &segment_descriptor,
		          &error );

		if( fvde_test_malloc_attempts_before_fail != -1 )
		{
			fvde_test_malloc_attempts_before_fail = -1;

			if( segment_descriptor != NULL )
			{
				libfvde_segment_descriptor_free(
				 &segment_descriptor,
				 NULL );
			}
		}
		else
		{
			FVDE_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			FVDE_TEST_ASSERT_IS_NULL(
			 "segment_descriptor",
			 segment_descriptor );

			FVDE_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libfvde_segment_descriptor_initialize with memset failing
		 */
		fvde_test_memset_attempts_before_fail = test_number;

		result = libfvde_segment_descriptor_initialize(
		          &segment_descriptor,
		          &error );

		if( fvde_test_memset_attempts_before_fail != -1 )
		{
			fvde_test_memset_attempts_before_fail = -1;

			if( segment_descriptor != NULL )
			{
				libfvde_segment_descriptor_free(
				 &segment_descriptor,
				 NULL );
			}
		}
		else
		{
			FVDE_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			FVDE_TEST_ASSERT_IS_NULL(
			 "segment_descriptor",
			 segment_descriptor );

			FVDE_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_FVDE_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( segment_descriptor != NULL )
	{
		libfvde_segment_descriptor_free(
		 &segment_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfvde_segment_descriptor_free function
 * Returns 1 if successful or 0 if not
 */
int fvde_test_segment_descriptor_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfvde_segment_descriptor_free(
	          NULL,
	          &error );

	FVDE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FVDE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBFVDE_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc FVDE_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] FVDE_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc FVDE_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] FVDE_TEST_ATTRIBUTE_UNUSED )
#endif
{
	FVDE_TEST_UNREFERENCED_PARAMETER( argc )
	FVDE_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( HAVE_DEBUG_OUTPUT ) && defined( FVDE_TEST_SEGMENT_DESCRIPTOR_VERBOSE )
	libfvde_notify_set_verbose(
	 1 );
	libfvde_notify_set_stream(
	 stderr,
	 NULL );
#endif

#if defined( __GNUC__ ) && !defined( LIBFVDE_DLL_IMPORT )

	FVDE_TEST_RUN(
	 "libfvde_segment_descriptor_initialize",
	 fvde_test_segment_descriptor_initialize );

	FVDE_TEST_RUN(
	 "libfvde_segment_descriptor_free",
	 fvde_test_segment_descriptor_free );

#endif /* defined( __GNUC__ ) && !defined( LIBFVDE_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}


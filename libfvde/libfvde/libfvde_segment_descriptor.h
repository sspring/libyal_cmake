/*
 * Segment descriptor functions
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

#if !defined( _LIBFVDE_SEGMENT_DESCRIPTOR_H )
#define _LIBFVDE_SEGMENT_DESCRIPTOR_H

#include <common.h>
#include <types.h>

#include "libfvde_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfvde_segment_descriptor libfvde_segment_descriptor_t;

struct libfvde_segment_descriptor
{
	/* The logical block number
	 */
	uint64_t logical_block_number;

	/* The number of blocks
	 */
	uint64_t number_of_blocks;

	/* The physical block number
	 */
	uint64_t physical_block_number;
};

int libfvde_segment_descriptor_initialize(
     libfvde_segment_descriptor_t **segment_descriptor,
     libcerror_error_t **error );

int libfvde_segment_descriptor_free(
     libfvde_segment_descriptor_t **segment_descriptor,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFVDE_SEGMENT_DESCRIPTOR_H ) */

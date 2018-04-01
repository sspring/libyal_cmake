/*
 * Encryption functions
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

#if !defined( _LIBFVDE_ENCRYPTION_H )
#define _LIBFVDE_ENCRYPTION_H

#include <common.h>
#include <types.h>

#include "libfvde_libcaes.h"
#include "libfvde_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

int libfvde_encryption_aes_key_unwrap(
     const uint8_t *key,
     size_t key_size_bits,
     const uint8_t *wrapped_data,
     size_t wrapped_data_size,
     uint8_t *unwrapped_data,
     size_t unwrapped_data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFVDE_ENCRYPTION_H ) */


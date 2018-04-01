/*
 * Python object definition of the libfvde volume
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

#if !defined( _PYFVDE_VOLUME_H )
#define _PYFVDE_VOLUME_H

#include <common.h>
#include <types.h>

#include "pyfvde_libfvde.h"
#include "pyfvde_libbfio.h"
#include "pyfvde_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyfvde_volume pyfvde_volume_t;

struct pyfvde_volume
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libfvde volume
	 */
	libfvde_volume_t *volume;

	/* The libbfio file IO handle
	 */
	libbfio_handle_t *file_io_handle;
};

extern PyMethodDef pyfvde_volume_object_methods[];
extern PyTypeObject pyfvde_volume_type_object;

PyObject *pyfvde_volume_new(
           void );

PyObject *pyfvde_volume_new_open(
           PyObject *self,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfvde_volume_new_open_file_object(
           PyObject *self,
           PyObject *arguments,
           PyObject *keywords );

int pyfvde_volume_init(
     pyfvde_volume_t *pyfvde_volume );

void pyfvde_volume_free(
      pyfvde_volume_t *pyfvde_volume );

PyObject *pyfvde_volume_signal_abort(
           pyfvde_volume_t *pyfvde_volume,
           PyObject *arguments );

PyObject *pyfvde_volume_open(
           pyfvde_volume_t *pyfvde_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfvde_volume_open_file_object(
           pyfvde_volume_t *pyfvde_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfvde_volume_close(
           pyfvde_volume_t *pyfvde_volume,
           PyObject *arguments );

PyObject *pyfvde_volume_is_locked(
           pyfvde_volume_t *pyfvde_volume,
           PyObject *arguments );

PyObject *pyfvde_volume_read_buffer(
           pyfvde_volume_t *pyfvde_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfvde_volume_read_buffer_at_offset(
           pyfvde_volume_t *pyfvde_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfvde_volume_seek_offset(
           pyfvde_volume_t *pyfvde_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfvde_volume_get_offset(
           pyfvde_volume_t *pyfvde_volume,
           PyObject *arguments );

PyObject *pyfvde_volume_get_size(
           pyfvde_volume_t *pyfvde_volume,
           PyObject *arguments );

PyObject *pyfvde_volume_set_keys(
           pyfvde_volume_t *pyfvde_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfvde_volume_set_password(
           pyfvde_volume_t *pyfvde_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfvde_volume_set_recovery_password(
           pyfvde_volume_t *pyfvde_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfvde_volume_read_encrypted_root_plist(
           pyfvde_volume_t *pyfvde_volume,
           PyObject *arguments,
           PyObject *keywords );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYFVDE_VOLUME_H ) */


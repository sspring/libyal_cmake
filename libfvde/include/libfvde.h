/*
 * Library to access the FileVault Drive Encryption (FVDE) format
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

#if !defined( _LIBFVDE_H )
#define _LIBFVDE_H

#include <libfvde/codepage.h>
#include <libfvde/definitions.h>
#include <libfvde/error.h>
#include <libfvde/extern.h>
#include <libfvde/features.h>
#include <libfvde/types.h>

#include <stdio.h>

#if defined( LIBFVDE_HAVE_BFIO )
#include <libbfio.h>
#endif

#if defined( __cplusplus )
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Support functions
 * ------------------------------------------------------------------------- */

/* Returns the library version
 */
LIBFVDE_EXTERN \
const char *libfvde_get_version(
             void );

/* Returns the access flags for reading
 */
LIBFVDE_EXTERN \
int libfvde_get_access_flags_read(
     void );

/* Retrieves the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_get_codepage(
     int *codepage,
     libfvde_error_t **error );

/* Sets the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_set_codepage(
     int codepage,
     libfvde_error_t **error );

/* Determines if a file contains a FVDE volume signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_check_volume_signature(
     const char *filename,
     libfvde_error_t **error );

#if defined( LIBFVDE_HAVE_WIDE_CHARACTER_TYPE )

/* Determines if a file contains a FVDE volume signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_check_volume_signature_wide(
     const wchar_t *filename,
     libfvde_error_t **error );

#endif /* defined( LIBFVDE_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBFVDE_HAVE_BFIO )

/* Determines if a file contains a FVDE volume signature using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_check_volume_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libfvde_error_t **error );

#endif /* defined( LIBFVDE_HAVE_BFIO ) */

/* -------------------------------------------------------------------------
 * Notify functions
 * ------------------------------------------------------------------------- */

/* Sets the verbose notification
 */
LIBFVDE_EXTERN \
void libfvde_notify_set_verbose(
      int verbose );

/* Sets the notification stream
 * Returns 1 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_notify_set_stream(
     FILE *stream,
     libfvde_error_t **error );

/* Opens the notification stream using a filename
 * The stream is opened in append mode
 * Returns 1 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_notify_stream_open(
     const char *filename,
     libfvde_error_t **error );

/* Closes the notification stream if opened using a filename
 * Returns 0 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_notify_stream_close(
     libfvde_error_t **error );

/* -------------------------------------------------------------------------
 * Error functions
 * ------------------------------------------------------------------------- */

/* Frees an error
 */
LIBFVDE_EXTERN \
void libfvde_error_free(
      libfvde_error_t **error );

/* Prints a descriptive string of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_error_fprint(
     libfvde_error_t *error,
     FILE *stream );

/* Prints a descriptive string of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_error_sprint(
     libfvde_error_t *error,
     char *string,
     size_t size );

/* Prints a backtrace of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_error_backtrace_fprint(
     libfvde_error_t *error,
     FILE *stream );

/* Prints a backtrace of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_error_backtrace_sprint(
     libfvde_error_t *error,
     char *string,
     size_t size );

/* -------------------------------------------------------------------------
 * Volume functions
 * ------------------------------------------------------------------------- */

/* Creates a volume
 * Make sure the value volume is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_volume_initialize(
     libfvde_volume_t **volume,
     libfvde_error_t **error );

/* Frees a volume
 * Returns 1 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_volume_free(
     libfvde_volume_t **volume,
     libfvde_error_t **error );

/* Signals the volume to abort its current activity
 * Returns 1 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_volume_signal_abort(
     libfvde_volume_t *volume,
     libfvde_error_t **error );

/* Opens a volume
 * Returns 1 if successful, 0 if the keys could not be read or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_volume_open(
     libfvde_volume_t *volume,
     const char *filename,
     int access_flags,
     libfvde_error_t **error );

#if defined( LIBFVDE_HAVE_WIDE_CHARACTER_TYPE )

/* Opens a volume
 * Returns 1 if successful, 0 if the keys could not be read or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_volume_open_wide(
     libfvde_volume_t *volume,
     const wchar_t *filename,
     int access_flags,
     libfvde_error_t **error );

#endif /* defined( LIBFVDE_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBFVDE_HAVE_BFIO )

/* Opens a volume using a Basic File IO (bfio) handle
 * Returns 1 if successful, 0 if the keys could not be read or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_volume_open_file_io_handle(
     libfvde_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libfvde_error_t **error );

#endif /* defined( LIBFVDE_HAVE_BFIO ) */

/* Closes a volume
 * Returns 0 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_volume_close(
     libfvde_volume_t *volume,
     libfvde_error_t **error );

/* Determines if the volume is locked
 * Returns 1 if locked, 0 if not or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_volume_is_locked(
     libfvde_volume_t *volume,
     libfvde_error_t **error );

/* Reads data at the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
LIBFVDE_EXTERN \
ssize_t libfvde_volume_read_buffer(
         libfvde_volume_t *volume,
         void *buffer,
         size_t buffer_size,
         libfvde_error_t **error );

/* Reads (media) data at a specific offset
 * Returns the number of bytes read or -1 on error
 */
LIBFVDE_EXTERN \
ssize_t libfvde_volume_read_buffer_at_offset(
         libfvde_volume_t *volume,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libfvde_error_t **error );

#ifdef TODO_WRITE_SUPPORT

/* Writes (media) data at the current offset
 * Returns the number of input bytes written, 0 when no longer bytes can be written or -1 on error
 */
LIBFVDE_EXTERN \
ssize_t libfvde_volume_write_buffer(
         libfvde_volume_t *volume,
         void *buffer,
         size_t buffer_size,
         libfvde_error_t **error );

/* Writes (media) data at a specific offset,
 * Returns the number of input bytes written, 0 when no longer bytes can be written or -1 on error
 */
LIBFVDE_EXTERN \
ssize_t libfvde_volume_write_buffer_at_offset(
         libfvde_volume_t *volume,
         const void *buffer,
         size_t buffer_size,
         off64_t offset,
         libfvde_error_t **error );

#endif /* TODO_WRITE_SUPPORT */

/* Seeks a certain offset of the data
 * Returns the offset if seek is successful or -1 on error
 */
LIBFVDE_EXTERN \
off64_t libfvde_volume_seek_offset(
         libfvde_volume_t *volume,
         off64_t offset,
         int whence,
         libfvde_error_t **error );

/* Retrieves the the current offset of the (volume) data
 * Returns 1 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_volume_get_offset(
     libfvde_volume_t *volume,
     off64_t *offset,
     libfvde_error_t **error );

/* Retrieves the logical volume size
 * Returns 1 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_volume_get_logical_volume_size(
     libfvde_volume_t *volume,
     size64_t *size,
     libfvde_error_t **error );

/* Retrieves the encryption method of the logical volume
 * Returns 1 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_volume_get_logical_volume_encryption_method(
     libfvde_volume_t *volume,
     uint32_t *encryption_method,
     libfvde_error_t **error );

/* Retrieves the physical volume size
 * Returns 1 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_volume_get_physical_volume_size(
     libfvde_volume_t *volume,
     size64_t *size,
     libfvde_error_t **error );

/* Retrieves the encryption method of the physical volume
 * Returns 1 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_volume_get_physical_volume_encryption_method(
     libfvde_volume_t *volume,
     uint32_t *encryption_method,
     libfvde_error_t **error );

/* Sets the keys
 * This function needs to be used before one of the open functions
 * Returns 1 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_volume_set_keys(
     libfvde_volume_t *volume,
     const uint8_t *volume_master_key,
     size_t volume_master_key_size,
     libfvde_error_t **error );

/* Sets an UTF-8 formatted password
 * This function needs to be used before one of the open functions
 * Returns 1 if successful, 0 if password is invalid or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_volume_set_utf8_password(
     libfvde_volume_t *volume,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfvde_error_t **error );

/* Sets an UTF-16 formatted password
 * This function needs to be used before one of the open functions
 * Returns 1 if successful, 0 if password is invalid or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_volume_set_utf16_password(
     libfvde_volume_t *volume,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libfvde_error_t **error );

/* Sets an UTF-8 formatted recovery password
 * This function needs to be used before one of the open functions
 * Returns 1 if successful, 0 if recovery password is invalid or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_volume_set_utf8_recovery_password(
     libfvde_volume_t *volume,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfvde_error_t **error );

/* Sets an UTF-16 formatted recovery password
 * This function needs to be used before one of the open functions
 * Returns 1 if successful, 0 if recovery password is invalid or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_volume_set_utf16_recovery_password(
     libfvde_volume_t *volume,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libfvde_error_t **error );

/* Reads the EncryptedRoot.plist file
 * This function needs to be used before one of the open functions
 * Returns 1 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_volume_read_encrypted_root_plist(
     libfvde_volume_t *volume,
     const char *filename,
     libfvde_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Reads the EncryptedRoot.plist file
 * This function needs to be used before one of the open functions
 * Returns 1 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_volume_read_encrypted_root_plist_wide(
     libfvde_volume_t *volume,
     const wchar_t *filename,
     libfvde_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBFVDE_HAVE_BFIO )

/* Reads the EncryptedRoot.plist file using a Basic File IO (bfio) handle
 * This function needs to be used before one of the open functions
 * Returns 1 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_volume_read_encrypted_root_plist_file_io_handle(
     libfvde_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     libfvde_error_t **error );

#endif /* defined( LIBFVDE_HAVE_BFIO ) */

/* -------------------------------------------------------------------------
 * Volume functions - deprecated
 * ------------------------------------------------------------------------- */

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 *
 * This function deprecated use libfvde_volume_get_logical_volume_size instead
 */
LIBFVDE_DEPRECATED \
LIBFVDE_EXTERN \
int libfvde_volume_get_size(
     libfvde_volume_t *volume,
     size64_t *size,
     libfvde_error_t **error );

/* Retrieves the encryption method
 * Returns 1 if successful or -1 on error
 *
 * This function deprecated use libfvde_volume_get_physical_volume_encryption_method instead
 */
LIBFVDE_DEPRECATED \
LIBFVDE_EXTERN \
int libfvde_volume_get_encryption_method(
     libfvde_volume_t *volume,
     uint32_t *encryption_method,
     libfvde_error_t **error );

/* -------------------------------------------------------------------------
 * Volume group functions
 * ------------------------------------------------------------------------- */

/* Frees a volume group
 * Returns 1 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_volume_group_free(
     libfvde_volume_group_t **volume_group,
     libfvde_error_t **error );

/* -------------------------------------------------------------------------
 * LVF encryption context and EncryptedRoot.plist file functions
 * ------------------------------------------------------------------------- */

/* Creates an encryption context plist
 * Make sure the value plist is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_encryption_context_plist_initialize(
     libfvde_encryption_context_plist_t **plist,
     libfvde_error_t **error );

/* Frees an encryption context plist
 * Returns 1 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_encryption_context_plist_free(
     libfvde_encryption_context_plist_t **plist,
     libfvde_error_t **error );

/* Retrieves the (un)encrypted data size of an encryption context plist
 * Returns 1 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_encryption_context_plist_get_data_size(
     libfvde_encryption_context_plist_t *plist,
     size64_t *data_size,
     libfvde_error_t **error );

/* Copies the unencrypted data of an encryption context plist
 * Returns 1 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_encryption_context_plist_copy_data(
     libfvde_encryption_context_plist_t *plist,
     uint8_t *data,
     size_t data_size,
     libfvde_error_t **error );

#if defined( LIBFVDE_HAVE_BFIO )

/* Reads an encryption context plist file (EncryptedRoot.plist) using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_encryption_context_plist_read_file_io_handle(
     libfvde_encryption_context_plist_t *plist,
     libbfio_handle_t *file_io_handle,
     libfvde_error_t **error );

#endif /* defined( LIBFVDE_HAVE_BFIO ) */

/* Decrypts the previously read encryption context plist file (EncryptedRoot.plist) with the given key.
 * Returns 1 if successful, 0 if not or -1 on error
 */
LIBFVDE_EXTERN \
int libfvde_encryption_context_plist_decrypt(
     libfvde_encryption_context_plist_t *plist,
     const uint8_t *key,
     size_t key_bit_size,
     libfvde_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFVDE_H ) */


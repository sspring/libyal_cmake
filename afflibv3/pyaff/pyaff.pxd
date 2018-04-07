cimport afflib
from libc.stdint cimport int64_t

cdef class affile:
    cdef afflib.AFFILE *af
    cdef int64_t size

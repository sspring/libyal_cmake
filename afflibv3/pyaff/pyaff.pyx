import sys
from cpython.version cimport PY_MAJOR_VERSION
cimport afflib

"""Open afflib file (or set of files)"""
def open(filename):
    return affile(filename)

"""afflib File Object"""
cdef class affile(object):
    def __cinit__(self, basestring filename):
        self.af = afflib.af_open(filename.encode(sys.getfilesystemencoding()), afflib.O_RDONLY, 0)
        if self.af == NULL:
            raise IOError("Failed to initialise afflib")

        self.size = afflib.af_get_imagesize(self.af)

    """Read data from file"""
    def read(self, int size=-1):
        readlen = size if 0 <= size <= self.size else self.size

        retdata = bytearray(readlen)
        written = afflib.af_read(self.af, retdata, size)
        if written != readlen:
            raise IOError("Failed to read all data: wanted {}, got {}".format(readlen, written))

        return bytes(retdata)

    """Seek within a file"""
    def seek(self, int offset, int whence=0):
        if afflib.af_seek(self.af, offset, whence) < 0:
            raise IOError("libaff_seek_offset failed")

    """Retrieve an aff segment by name"""
    def get_seg(self, basestring segname):
        cdef size_t buflen = 0
        cdef _segname = segname.encode('ascii')

        if afflib.af_get_seg(self.af, _segname, NULL, NULL, &buflen) != 0:
            raise IOError("error reading libaff segment")
        print(buflen)

        retdata = bytearray(buflen)

        if afflib.af_get_seg(self.af, _segname, NULL, retdata, &buflen) != 0:
            raise IOError("error reading libaff segment")

        return bytes(retdata)

    """Retrieve a list of segments present"""
    def get_seg_names(self):
        headers = []
        segname = bytearray(afflib.AF_MAX_NAME_LEN)

        afflib.af_rewind_seg(self.af)
        while afflib.af_get_next_seg(self.af, segname, len(segname), NULL, NULL, NULL) == 0:
            if PY_MAJOR_VERSION < 3:
                headers.append(<char*> segname)
            else:
                headers.append((<char*> segname).decode('ascii'))

        return headers

    """Return possition within file"""
    def tell(self):
        return afflib.af_tell(self.af)

    """Close the file"""
    def close(self):
        afflib.af_close(self.af)


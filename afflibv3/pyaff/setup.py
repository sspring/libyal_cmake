try:
    from setuptools import setup, Extension, command
except ImportError:
    from distutils.core import setup, Extension

try:
    from Cython.Build import cythonize
    USE_CYTHON = True
except ImportError:
    USE_CYTHON = False

pyaff = [Extension('pyaff', ['pyaff.pyx'], libraries = ['afflib'])]

if USE_CYTHON:
    pyaff = cythonize(pyaff)

setup (name = 'PyAFF',
       version = '0.1',
       description = 'Python wrapper for AFFLIB',
       author = 'David Collett',
       author_email = 'david.collett@gmail.com',
       url = 'www.pyflag.net',
       license = "GPL",
       ext_modules = pyaff)

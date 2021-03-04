import ctypes

class ValueType(ctypes.Structure):
    _fields_ = [
        ('is_int', ctypes.c_bool),
        ('is_float', ctypes.c_bool),
        ('is_bool', ctypes.c_bool),
        ('is_char', ctypes.c_bool),
        ('int_value', ctypes.c_int),
        ('float_value', ctypes.c_float),
        ('bool_value', ctypes.c_bool),
        ('char_value', ctypes.c_char*8)
    ]

class MapValue(ctypes.Structure):
    _fields_ = [
        ('key', ctypes.c_char*16),
        ('is_valid', ctypes.c_bool),
        ('is_deleted', ctypes.c_bool),
        ('value', ValueType)
    ]

def _wrap_function(lib, fname, restype, argtypes):
    fn = lib.__getattr__(fname)
    fn.restype = restype
    fn.argtypes = argtypes
    return fn


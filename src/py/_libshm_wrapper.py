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

ctypes.CDLL('librt.so', mode=ctypes.RTLD_GLOBAL)
_libshm = ctypes.CDLL('libshm.so')

get_map_value = _wrap_function(_libshm, 'get_map_value', ctypes.POINTER(MapValue), [ctypes.c_char_p])
set_int_value = _wrap_function(_libshm, 'set_int_value', ctypes.c_bool, [ctypes.c_char_p, ctypes.c_int])
set_float_value = _wrap_function(_libshm, 'set_float_value', ctypes.c_bool, [ctypes.c_char_p, ctypes.c_float])
set_bool_value = _wrap_function(_libshm, 'set_bool_value', ctypes.c_bool, [ctypes.c_char_p, ctypes.c_bool])
set_char_value = _wrap_function(_libshm, 'set_char_value', ctypes.c_bool, [ctypes.c_char_p, ctypes.c_char_p])
contains_key = _wrap_function(_libshm, 'contains_key', ctypes.c_bool, [ctypes.c_char_p])
delete_key = _wrap_function(_libshm, 'delete_key', ctypes.c_bool, [ctypes.c_char_p])

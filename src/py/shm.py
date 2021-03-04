import ctypes 

from c_wrappers import ValueType, MapValue, _wrap_function

class SharedMemoryHandle():
    _libshm = None
    
    def __init__(self):
        if SharedMemoryHandle._libshm: 
            return

        ctypes.CDLL('librt.so', mode=ctypes.RTLD_GLOBAL)
        SharedMemoryHandle._libshm = ctypes.CDLL('libshm.so')

        self.get_map_value = _wrap_function(SharedMemoryHandle._libshm, 'get_map_value', ctypes.POINTER(MapValue), [ctypes.c_char_p])
        self.set_int_value = _wrap_function(SharedMemoryHandle._libshm, 'set_int_value', ctypes.c_bool, [ctypes.c_char_p, ctypes.c_int])
        self.set_float_value = _wrap_function(SharedMemoryHandle._libshm, 'set_float_value', ctypes.c_bool, [ctypes.c_char_p, ctypes.c_float])
        self.set_bool_value = _wrap_function(SharedMemoryHandle._libshm, 'set_bool_value', ctypes.c_bool, [ctypes.c_char_p, ctypes.c_bool])
        self.set_char_value = _wrap_function(SharedMemoryHandle._libshm, 'set_char_value', ctypes.c_bool, [ctypes.c_char_p, ctypes.c_char_p])

    def __getitem__(self, key):
        c_key = ctypes.c_char_p(str.encode(key))
        map_value_p = self.get_map_value(c_key)

        if not map_value_p:
            return None

        map_value = map_value_p.contents.value

        if (map_value.is_int):
            return map_value.int_value
        if (map_value.is_float):
            return map_value.float_value
        if (map_value.is_bool):
            return map_value.bool_value
        if (map_value.is_char):
            return map_value.char_value
        
    def __setitem__(self, key, value):
        c_key = ctypes.c_char_p()
        c_key.value = str.encode(key)

        if type(value) == int:
            c_value = ctypes.c_int(value)
            c_return = self.set_int_value(c_key, c_value)
        if type(value) == float:
            c_value = ctypes.c_float(value)
            c_return = self.set_float_value(c_key, c_value)
        if type(value) == bool:
            c_value = ctypes.c_bool(value)
            c_return = self.set_bool_value(c_key, c_value)
        if type(value) == str:
            c_value = ctypes.c_char_p(str.encode(value))
            c_return = self.set_char_value(c_key, c_value)

        if not c_return:
            map_value_p = self.get_map_value(c_key)

            if not map_value_p:
                return None

            map_value = map_value_p.contents.value

            if (map_value.is_int):
                c_value = ctypes.c_int(int(value))
                c_return = self.set_int_value(c_key, c_value)
            if (map_value.is_float):
                c_value = ctypes.c_float(float(value))
                c_return = self.set_float_value(c_key, c_value)
            if (map_value.is_bool):
                c_value = ctypes.c_bool(bool(value))
                c_return = self.set_bool_value(c_key, c_value)
            if (map_value.is_char):
                c_value = ctypes.c_char_p(str.encode(str(value)))
                c_return = self.set_char_value(c_key, c_value)


shm = SharedMemoryHandle()

import ctypes
import _libshm_wrapper as libshm

class SharedMemoryHandle():

    def __init__(self):
        pass

    def __getitem__(self, key):
        c_key = ctypes.c_char_p(str.encode(key))
        map_value_p = libshm.get_map_value(c_key)

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
        c_key = ctypes.c_char_p(str.encode(key))

        if type(value) == int:
            c_value = ctypes.c_int(value)
            c_return = libshm.set_int_value(c_key, c_value)
        if type(value) == float:
            c_value = ctypes.c_float(value)
            c_return = libshm.set_float_value(c_key, c_value)
        if type(value) == bool:
            c_value = ctypes.c_bool(value)
            c_return = libshm.set_bool_value(c_key, c_value)
        if type(value) == str:
            c_value = ctypes.c_char_p(str.encode(value))
            c_return = libshm.set_char_value(c_key, c_value)

        if not c_return:
            map_value_p = libshm.get_map_value(c_key)

            if not map_value_p:
                return None

            map_value = map_value_p.contents.value

            if (map_value.is_int):
                c_value = ctypes.c_int(int(value))
                c_return = libshm.set_int_value(c_key, c_value)
            if (map_value.is_float):
                c_value = ctypes.c_float(float(value))
                c_return = libshm.set_float_value(c_key, c_value)
            if (map_value.is_bool):
                c_value = ctypes.c_bool(bool(value))
                c_return = libshm.set_bool_value(c_key, c_value)
            if (map_value.is_char):
                c_value = ctypes.c_char_p(str.encode(str(value)))
                c_return = libshm.set_char_value(c_key, c_value)

            # TODO What if c_return is false?

    def __delitem__(self, key):
        c_key = ctypes.c_char_p(str.encode(key))
        libshm.delete_key(c_key)

    def __contains__(self, key):
        c_key = ctypes.c_char_p(str.encode(key))

        return libshm.contains_key(c_key)

shm = SharedMemoryHandle()

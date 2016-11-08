# This file was automatically generated by SWIG (http://www.swig.org).
# Version 3.0.8
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.





from sys import version_info
if version_info >= (2, 6, 0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_libpinyin', [dirname(__file__)])
        except ImportError:
            import _libpinyin
            return _libpinyin
        if fp is not None:
            try:
                _mod = imp.load_module('_libpinyin', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _libpinyin = swig_import_helper()
    del swig_import_helper
else:
    import _libpinyin
del version_info
try:
    _swig_property = property
except NameError:
    pass  # Python < 2.2 doesn't have 'property'.


def _swig_setattr_nondynamic(self, class_type, name, value, static=1):
    if (name == "thisown"):
        return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name, None)
    if method:
        return method(self, value)
    if (not static):
        if _newclass:
            object.__setattr__(self, name, value)
        else:
            self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)


def _swig_setattr(self, class_type, name, value):
    return _swig_setattr_nondynamic(self, class_type, name, value, 0)


def _swig_getattr_nondynamic(self, class_type, name, static=1):
    if (name == "thisown"):
        return self.this.own()
    method = class_type.__swig_getmethods__.get(name, None)
    if method:
        return method(self)
    if (not static):
        return object.__getattr__(self, name)
    else:
        raise AttributeError(name)

def _swig_getattr(self, class_type, name):
    return _swig_getattr_nondynamic(self, class_type, name, 0)


def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except Exception:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object:
        pass
    _newclass = 0


class SwigPyIterator(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, SwigPyIterator, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, SwigPyIterator, name)

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _libpinyin.delete_SwigPyIterator
    __del__ = lambda self: None

    def value(self):
        return _libpinyin.SwigPyIterator_value(self)

    def incr(self, n=1):
        return _libpinyin.SwigPyIterator_incr(self, n)

    def decr(self, n=1):
        return _libpinyin.SwigPyIterator_decr(self, n)

    def distance(self, x):
        return _libpinyin.SwigPyIterator_distance(self, x)

    def equal(self, x):
        return _libpinyin.SwigPyIterator_equal(self, x)

    def copy(self):
        return _libpinyin.SwigPyIterator_copy(self)

    def next(self):
        return _libpinyin.SwigPyIterator_next(self)

    def __next__(self):
        return _libpinyin.SwigPyIterator___next__(self)

    def previous(self):
        return _libpinyin.SwigPyIterator_previous(self)

    def advance(self, n):
        return _libpinyin.SwigPyIterator_advance(self, n)

    def __eq__(self, x):
        return _libpinyin.SwigPyIterator___eq__(self, x)

    def __ne__(self, x):
        return _libpinyin.SwigPyIterator___ne__(self, x)

    def __iadd__(self, n):
        return _libpinyin.SwigPyIterator___iadd__(self, n)

    def __isub__(self, n):
        return _libpinyin.SwigPyIterator___isub__(self, n)

    def __add__(self, n):
        return _libpinyin.SwigPyIterator___add__(self, n)

    def __sub__(self, *args):
        return _libpinyin.SwigPyIterator___sub__(self, *args)
    def __iter__(self):
        return self
SwigPyIterator_swigregister = _libpinyin.SwigPyIterator_swigregister
SwigPyIterator_swigregister(SwigPyIterator)

class ivec(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, ivec, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, ivec, name)
    __repr__ = _swig_repr

    def iterator(self):
        return _libpinyin.ivec_iterator(self)
    def __iter__(self):
        return self.iterator()

    def __nonzero__(self):
        return _libpinyin.ivec___nonzero__(self)

    def __bool__(self):
        return _libpinyin.ivec___bool__(self)

    def __len__(self):
        return _libpinyin.ivec___len__(self)

    def __getslice__(self, i, j):
        return _libpinyin.ivec___getslice__(self, i, j)

    def __setslice__(self, *args):
        return _libpinyin.ivec___setslice__(self, *args)

    def __delslice__(self, i, j):
        return _libpinyin.ivec___delslice__(self, i, j)

    def __delitem__(self, *args):
        return _libpinyin.ivec___delitem__(self, *args)

    def __getitem__(self, *args):
        return _libpinyin.ivec___getitem__(self, *args)

    def __setitem__(self, *args):
        return _libpinyin.ivec___setitem__(self, *args)

    def pop(self):
        return _libpinyin.ivec_pop(self)

    def append(self, x):
        return _libpinyin.ivec_append(self, x)

    def empty(self):
        return _libpinyin.ivec_empty(self)

    def size(self):
        return _libpinyin.ivec_size(self)

    def swap(self, v):
        return _libpinyin.ivec_swap(self, v)

    def begin(self):
        return _libpinyin.ivec_begin(self)

    def end(self):
        return _libpinyin.ivec_end(self)

    def rbegin(self):
        return _libpinyin.ivec_rbegin(self)

    def rend(self):
        return _libpinyin.ivec_rend(self)

    def clear(self):
        return _libpinyin.ivec_clear(self)

    def get_allocator(self):
        return _libpinyin.ivec_get_allocator(self)

    def pop_back(self):
        return _libpinyin.ivec_pop_back(self)

    def erase(self, *args):
        return _libpinyin.ivec_erase(self, *args)

    def __init__(self, *args):
        this = _libpinyin.new_ivec(*args)
        try:
            self.this.append(this)
        except Exception:
            self.this = this

    def push_back(self, x):
        return _libpinyin.ivec_push_back(self, x)

    def front(self):
        return _libpinyin.ivec_front(self)

    def back(self):
        return _libpinyin.ivec_back(self)

    def assign(self, n, x):
        return _libpinyin.ivec_assign(self, n, x)

    def resize(self, *args):
        return _libpinyin.ivec_resize(self, *args)

    def insert(self, *args):
        return _libpinyin.ivec_insert(self, *args)

    def reserve(self, n):
        return _libpinyin.ivec_reserve(self, n)

    def capacity(self):
        return _libpinyin.ivec_capacity(self)
    __swig_destroy__ = _libpinyin.delete_ivec
    __del__ = lambda self: None
ivec_swigregister = _libpinyin.ivec_swigregister
ivec_swigregister(ivec)

class dvec(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, dvec, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, dvec, name)
    __repr__ = _swig_repr

    def iterator(self):
        return _libpinyin.dvec_iterator(self)
    def __iter__(self):
        return self.iterator()

    def __nonzero__(self):
        return _libpinyin.dvec___nonzero__(self)

    def __bool__(self):
        return _libpinyin.dvec___bool__(self)

    def __len__(self):
        return _libpinyin.dvec___len__(self)

    def __getslice__(self, i, j):
        return _libpinyin.dvec___getslice__(self, i, j)

    def __setslice__(self, *args):
        return _libpinyin.dvec___setslice__(self, *args)

    def __delslice__(self, i, j):
        return _libpinyin.dvec___delslice__(self, i, j)

    def __delitem__(self, *args):
        return _libpinyin.dvec___delitem__(self, *args)

    def __getitem__(self, *args):
        return _libpinyin.dvec___getitem__(self, *args)

    def __setitem__(self, *args):
        return _libpinyin.dvec___setitem__(self, *args)

    def pop(self):
        return _libpinyin.dvec_pop(self)

    def append(self, x):
        return _libpinyin.dvec_append(self, x)

    def empty(self):
        return _libpinyin.dvec_empty(self)

    def size(self):
        return _libpinyin.dvec_size(self)

    def swap(self, v):
        return _libpinyin.dvec_swap(self, v)

    def begin(self):
        return _libpinyin.dvec_begin(self)

    def end(self):
        return _libpinyin.dvec_end(self)

    def rbegin(self):
        return _libpinyin.dvec_rbegin(self)

    def rend(self):
        return _libpinyin.dvec_rend(self)

    def clear(self):
        return _libpinyin.dvec_clear(self)

    def get_allocator(self):
        return _libpinyin.dvec_get_allocator(self)

    def pop_back(self):
        return _libpinyin.dvec_pop_back(self)

    def erase(self, *args):
        return _libpinyin.dvec_erase(self, *args)

    def __init__(self, *args):
        this = _libpinyin.new_dvec(*args)
        try:
            self.this.append(this)
        except Exception:
            self.this = this

    def push_back(self, x):
        return _libpinyin.dvec_push_back(self, x)

    def front(self):
        return _libpinyin.dvec_front(self)

    def back(self):
        return _libpinyin.dvec_back(self)

    def assign(self, n, x):
        return _libpinyin.dvec_assign(self, n, x)

    def resize(self, *args):
        return _libpinyin.dvec_resize(self, *args)

    def insert(self, *args):
        return _libpinyin.dvec_insert(self, *args)

    def reserve(self, n):
        return _libpinyin.dvec_reserve(self, n)

    def capacity(self):
        return _libpinyin.dvec_capacity(self)
    __swig_destroy__ = _libpinyin.delete_dvec
    __del__ = lambda self: None
dvec_swigregister = _libpinyin.dvec_swigregister
dvec_swigregister(dvec)

class svec(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, svec, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, svec, name)
    __repr__ = _swig_repr

    def iterator(self):
        return _libpinyin.svec_iterator(self)
    def __iter__(self):
        return self.iterator()

    def __nonzero__(self):
        return _libpinyin.svec___nonzero__(self)

    def __bool__(self):
        return _libpinyin.svec___bool__(self)

    def __len__(self):
        return _libpinyin.svec___len__(self)

    def __getslice__(self, i, j):
        return _libpinyin.svec___getslice__(self, i, j)

    def __setslice__(self, *args):
        return _libpinyin.svec___setslice__(self, *args)

    def __delslice__(self, i, j):
        return _libpinyin.svec___delslice__(self, i, j)

    def __delitem__(self, *args):
        return _libpinyin.svec___delitem__(self, *args)

    def __getitem__(self, *args):
        return _libpinyin.svec___getitem__(self, *args)

    def __setitem__(self, *args):
        return _libpinyin.svec___setitem__(self, *args)

    def pop(self):
        return _libpinyin.svec_pop(self)

    def append(self, x):
        return _libpinyin.svec_append(self, x)

    def empty(self):
        return _libpinyin.svec_empty(self)

    def size(self):
        return _libpinyin.svec_size(self)

    def swap(self, v):
        return _libpinyin.svec_swap(self, v)

    def begin(self):
        return _libpinyin.svec_begin(self)

    def end(self):
        return _libpinyin.svec_end(self)

    def rbegin(self):
        return _libpinyin.svec_rbegin(self)

    def rend(self):
        return _libpinyin.svec_rend(self)

    def clear(self):
        return _libpinyin.svec_clear(self)

    def get_allocator(self):
        return _libpinyin.svec_get_allocator(self)

    def pop_back(self):
        return _libpinyin.svec_pop_back(self)

    def erase(self, *args):
        return _libpinyin.svec_erase(self, *args)

    def __init__(self, *args):
        this = _libpinyin.new_svec(*args)
        try:
            self.this.append(this)
        except Exception:
            self.this = this

    def push_back(self, x):
        return _libpinyin.svec_push_back(self, x)

    def front(self):
        return _libpinyin.svec_front(self)

    def back(self):
        return _libpinyin.svec_back(self)

    def assign(self, n, x):
        return _libpinyin.svec_assign(self, n, x)

    def resize(self, *args):
        return _libpinyin.svec_resize(self, *args)

    def insert(self, *args):
        return _libpinyin.svec_insert(self, *args)

    def reserve(self, n):
        return _libpinyin.svec_reserve(self, n)

    def capacity(self):
        return _libpinyin.svec_capacity(self)
    __swig_destroy__ = _libpinyin.delete_svec
    __del__ = lambda self: None
svec_swigregister = _libpinyin.svec_swigregister
svec_swigregister(svec)

class Pinyin(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Pinyin, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Pinyin, name)
    __repr__ = _swig_repr
    __swig_destroy__ = _libpinyin.delete_Pinyin
    __del__ = lambda self: None
    __swig_getmethods__["Load"] = lambda x: _libpinyin.Pinyin_Load
    if _newclass:
        Load = staticmethod(_libpinyin.Pinyin_Load)
    __swig_getmethods__["Convert"] = lambda x: _libpinyin.Pinyin_Convert
    if _newclass:
        Convert = staticmethod(_libpinyin.Pinyin_Convert)

    def __init__(self):
        this = _libpinyin.new_Pinyin()
        try:
            self.this.append(this)
        except Exception:
            self.this = this
Pinyin_swigregister = _libpinyin.Pinyin_swigregister
Pinyin_swigregister(Pinyin)

def Pinyin_Load(dictPath):
    return _libpinyin.Pinyin_Load(dictPath)
Pinyin_Load = _libpinyin.Pinyin_Load

def Pinyin_Convert(input):
    return _libpinyin.Pinyin_Convert(input)
Pinyin_Convert = _libpinyin.Pinyin_Convert

# This file is compatible with both classic and new-style classes.


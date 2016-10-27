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
            fp, pathname, description = imp.find_module('_libstringutil', [dirname(__file__)])
        except ImportError:
            import _libstringutil
            return _libstringutil
        if fp is not None:
            try:
                _mod = imp.load_module('_libstringutil', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _libstringutil = swig_import_helper()
    del swig_import_helper
else:
    import _libstringutil
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
    __swig_destroy__ = _libstringutil.delete_SwigPyIterator
    __del__ = lambda self: None

    def value(self):
        return _libstringutil.SwigPyIterator_value(self)

    def incr(self, n=1):
        return _libstringutil.SwigPyIterator_incr(self, n)

    def decr(self, n=1):
        return _libstringutil.SwigPyIterator_decr(self, n)

    def distance(self, x):
        return _libstringutil.SwigPyIterator_distance(self, x)

    def equal(self, x):
        return _libstringutil.SwigPyIterator_equal(self, x)

    def copy(self):
        return _libstringutil.SwigPyIterator_copy(self)

    def next(self):
        return _libstringutil.SwigPyIterator_next(self)

    def __next__(self):
        return _libstringutil.SwigPyIterator___next__(self)

    def previous(self):
        return _libstringutil.SwigPyIterator_previous(self)

    def advance(self, n):
        return _libstringutil.SwigPyIterator_advance(self, n)

    def __eq__(self, x):
        return _libstringutil.SwigPyIterator___eq__(self, x)

    def __ne__(self, x):
        return _libstringutil.SwigPyIterator___ne__(self, x)

    def __iadd__(self, n):
        return _libstringutil.SwigPyIterator___iadd__(self, n)

    def __isub__(self, n):
        return _libstringutil.SwigPyIterator___isub__(self, n)

    def __add__(self, n):
        return _libstringutil.SwigPyIterator___add__(self, n)

    def __sub__(self, *args):
        return _libstringutil.SwigPyIterator___sub__(self, *args)
    def __iter__(self):
        return self
SwigPyIterator_swigregister = _libstringutil.SwigPyIterator_swigregister
SwigPyIterator_swigregister(SwigPyIterator)

class ivec(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, ivec, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, ivec, name)
    __repr__ = _swig_repr

    def iterator(self):
        return _libstringutil.ivec_iterator(self)
    def __iter__(self):
        return self.iterator()

    def __nonzero__(self):
        return _libstringutil.ivec___nonzero__(self)

    def __bool__(self):
        return _libstringutil.ivec___bool__(self)

    def __len__(self):
        return _libstringutil.ivec___len__(self)

    def __getslice__(self, i, j):
        return _libstringutil.ivec___getslice__(self, i, j)

    def __setslice__(self, *args):
        return _libstringutil.ivec___setslice__(self, *args)

    def __delslice__(self, i, j):
        return _libstringutil.ivec___delslice__(self, i, j)

    def __delitem__(self, *args):
        return _libstringutil.ivec___delitem__(self, *args)

    def __getitem__(self, *args):
        return _libstringutil.ivec___getitem__(self, *args)

    def __setitem__(self, *args):
        return _libstringutil.ivec___setitem__(self, *args)

    def pop(self):
        return _libstringutil.ivec_pop(self)

    def append(self, x):
        return _libstringutil.ivec_append(self, x)

    def empty(self):
        return _libstringutil.ivec_empty(self)

    def size(self):
        return _libstringutil.ivec_size(self)

    def swap(self, v):
        return _libstringutil.ivec_swap(self, v)

    def begin(self):
        return _libstringutil.ivec_begin(self)

    def end(self):
        return _libstringutil.ivec_end(self)

    def rbegin(self):
        return _libstringutil.ivec_rbegin(self)

    def rend(self):
        return _libstringutil.ivec_rend(self)

    def clear(self):
        return _libstringutil.ivec_clear(self)

    def get_allocator(self):
        return _libstringutil.ivec_get_allocator(self)

    def pop_back(self):
        return _libstringutil.ivec_pop_back(self)

    def erase(self, *args):
        return _libstringutil.ivec_erase(self, *args)

    def __init__(self, *args):
        this = _libstringutil.new_ivec(*args)
        try:
            self.this.append(this)
        except Exception:
            self.this = this

    def push_back(self, x):
        return _libstringutil.ivec_push_back(self, x)

    def front(self):
        return _libstringutil.ivec_front(self)

    def back(self):
        return _libstringutil.ivec_back(self)

    def assign(self, n, x):
        return _libstringutil.ivec_assign(self, n, x)

    def resize(self, *args):
        return _libstringutil.ivec_resize(self, *args)

    def insert(self, *args):
        return _libstringutil.ivec_insert(self, *args)

    def reserve(self, n):
        return _libstringutil.ivec_reserve(self, n)

    def capacity(self):
        return _libstringutil.ivec_capacity(self)
    __swig_destroy__ = _libstringutil.delete_ivec
    __del__ = lambda self: None
ivec_swigregister = _libstringutil.ivec_swigregister
ivec_swigregister(ivec)

class dvec(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, dvec, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, dvec, name)
    __repr__ = _swig_repr

    def iterator(self):
        return _libstringutil.dvec_iterator(self)
    def __iter__(self):
        return self.iterator()

    def __nonzero__(self):
        return _libstringutil.dvec___nonzero__(self)

    def __bool__(self):
        return _libstringutil.dvec___bool__(self)

    def __len__(self):
        return _libstringutil.dvec___len__(self)

    def __getslice__(self, i, j):
        return _libstringutil.dvec___getslice__(self, i, j)

    def __setslice__(self, *args):
        return _libstringutil.dvec___setslice__(self, *args)

    def __delslice__(self, i, j):
        return _libstringutil.dvec___delslice__(self, i, j)

    def __delitem__(self, *args):
        return _libstringutil.dvec___delitem__(self, *args)

    def __getitem__(self, *args):
        return _libstringutil.dvec___getitem__(self, *args)

    def __setitem__(self, *args):
        return _libstringutil.dvec___setitem__(self, *args)

    def pop(self):
        return _libstringutil.dvec_pop(self)

    def append(self, x):
        return _libstringutil.dvec_append(self, x)

    def empty(self):
        return _libstringutil.dvec_empty(self)

    def size(self):
        return _libstringutil.dvec_size(self)

    def swap(self, v):
        return _libstringutil.dvec_swap(self, v)

    def begin(self):
        return _libstringutil.dvec_begin(self)

    def end(self):
        return _libstringutil.dvec_end(self)

    def rbegin(self):
        return _libstringutil.dvec_rbegin(self)

    def rend(self):
        return _libstringutil.dvec_rend(self)

    def clear(self):
        return _libstringutil.dvec_clear(self)

    def get_allocator(self):
        return _libstringutil.dvec_get_allocator(self)

    def pop_back(self):
        return _libstringutil.dvec_pop_back(self)

    def erase(self, *args):
        return _libstringutil.dvec_erase(self, *args)

    def __init__(self, *args):
        this = _libstringutil.new_dvec(*args)
        try:
            self.this.append(this)
        except Exception:
            self.this = this

    def push_back(self, x):
        return _libstringutil.dvec_push_back(self, x)

    def front(self):
        return _libstringutil.dvec_front(self)

    def back(self):
        return _libstringutil.dvec_back(self)

    def assign(self, n, x):
        return _libstringutil.dvec_assign(self, n, x)

    def resize(self, *args):
        return _libstringutil.dvec_resize(self, *args)

    def insert(self, *args):
        return _libstringutil.dvec_insert(self, *args)

    def reserve(self, n):
        return _libstringutil.dvec_reserve(self, n)

    def capacity(self):
        return _libstringutil.dvec_capacity(self)
    __swig_destroy__ = _libstringutil.delete_dvec
    __del__ = lambda self: None
dvec_swigregister = _libstringutil.dvec_swigregister
dvec_swigregister(dvec)

class svec(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, svec, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, svec, name)
    __repr__ = _swig_repr

    def iterator(self):
        return _libstringutil.svec_iterator(self)
    def __iter__(self):
        return self.iterator()

    def __nonzero__(self):
        return _libstringutil.svec___nonzero__(self)

    def __bool__(self):
        return _libstringutil.svec___bool__(self)

    def __len__(self):
        return _libstringutil.svec___len__(self)

    def __getslice__(self, i, j):
        return _libstringutil.svec___getslice__(self, i, j)

    def __setslice__(self, *args):
        return _libstringutil.svec___setslice__(self, *args)

    def __delslice__(self, i, j):
        return _libstringutil.svec___delslice__(self, i, j)

    def __delitem__(self, *args):
        return _libstringutil.svec___delitem__(self, *args)

    def __getitem__(self, *args):
        return _libstringutil.svec___getitem__(self, *args)

    def __setitem__(self, *args):
        return _libstringutil.svec___setitem__(self, *args)

    def pop(self):
        return _libstringutil.svec_pop(self)

    def append(self, x):
        return _libstringutil.svec_append(self, x)

    def empty(self):
        return _libstringutil.svec_empty(self)

    def size(self):
        return _libstringutil.svec_size(self)

    def swap(self, v):
        return _libstringutil.svec_swap(self, v)

    def begin(self):
        return _libstringutil.svec_begin(self)

    def end(self):
        return _libstringutil.svec_end(self)

    def rbegin(self):
        return _libstringutil.svec_rbegin(self)

    def rend(self):
        return _libstringutil.svec_rend(self)

    def clear(self):
        return _libstringutil.svec_clear(self)

    def get_allocator(self):
        return _libstringutil.svec_get_allocator(self)

    def pop_back(self):
        return _libstringutil.svec_pop_back(self)

    def erase(self, *args):
        return _libstringutil.svec_erase(self, *args)

    def __init__(self, *args):
        this = _libstringutil.new_svec(*args)
        try:
            self.this.append(this)
        except Exception:
            self.this = this

    def push_back(self, x):
        return _libstringutil.svec_push_back(self, x)

    def front(self):
        return _libstringutil.svec_front(self)

    def back(self):
        return _libstringutil.svec_back(self)

    def assign(self, n, x):
        return _libstringutil.svec_assign(self, n, x)

    def resize(self, *args):
        return _libstringutil.svec_resize(self, *args)

    def insert(self, *args):
        return _libstringutil.svec_insert(self, *args)

    def reserve(self, n):
        return _libstringutil.svec_reserve(self, n)

    def capacity(self):
        return _libstringutil.svec_capacity(self)
    __swig_destroy__ = _libstringutil.delete_svec
    __del__ = lambda self: None
svec_swigregister = _libstringutil.svec_swigregister
svec_swigregister(svec)


def is_gb2312(ch1, ch2):
    return _libstringutil.is_gb2312(ch1, ch2)
is_gb2312 = _libstringutil.is_gb2312

def is_gbk_ch(*args):
    return _libstringutil.is_gbk_ch(*args)
is_gbk_ch = _libstringutil.is_gbk_ch

def all_en(phrase):
    return _libstringutil.all_en(phrase)
all_en = _libstringutil.all_en

def is_en_dominate(phrase, var=3):
    return _libstringutil.is_en_dominate(phrase, var)
is_en_dominate = _libstringutil.is_en_dominate

def extract_gbk_dual(temp):
    return _libstringutil.extract_gbk_dual(temp)
extract_gbk_dual = _libstringutil.extract_gbk_dual

def extract_suspect_symb(temp):
    return _libstringutil.extract_suspect_symb(temp)
extract_suspect_symb = _libstringutil.extract_suspect_symb

def filter_str(temp, withSpace=False):
    return _libstringutil.filter_str(temp, withSpace)
filter_str = _libstringutil.filter_str

def normalize_str(input, withSpace=False):
    return _libstringutil.normalize_str(input, withSpace)
normalize_str = _libstringutil.normalize_str

def extract_chinese(temp):
    return _libstringutil.extract_chinese(temp)
extract_chinese = _libstringutil.extract_chinese

def remove_space_cn(phrase):
    return _libstringutil.remove_space_cn(phrase)
remove_space_cn = _libstringutil.remove_space_cn

def remove_space_cnonly(phrase):
    return _libstringutil.remove_space_cnonly(phrase)
remove_space_cnonly = _libstringutil.remove_space_cnonly

def wchar_count(buf, len):
    return _libstringutil.wchar_count(buf, len)
wchar_count = _libstringutil.wchar_count

def word_count(phrase):
    return _libstringutil.word_count(phrase)
word_count = _libstringutil.word_count

def unicode_index(input):
    return _libstringutil.unicode_index(input)
unicode_index = _libstringutil.unicode_index

def remove_dupspace(input):
    return _libstringutil.remove_dupspace(input)
remove_dupspace = _libstringutil.remove_dupspace

def replace_special_whitespace(*args):
    return _libstringutil.replace_special_whitespace(*args)
replace_special_whitespace = _libstringutil.replace_special_whitespace

def str_replace_all(tstr, old_value, new_value):
    return _libstringutil.str_replace_all(tstr, old_value, new_value)
str_replace_all = _libstringutil.str_replace_all

def replace(input, a, b):
    return _libstringutil.replace(input, a, b)
replace = _libstringutil.replace

def is_alpha_only(input):
    return _libstringutil.is_alpha_only(input)
is_alpha_only = _libstringutil.is_alpha_only

def gbk_substr(*args):
    return _libstringutil.gbk_substr(*args)
gbk_substr = _libstringutil.gbk_substr

def startswith(*args):
    return _libstringutil.startswith(*args)
startswith = _libstringutil.startswith

def endswith(input, part):
    return _libstringutil.endswith(input, part)
endswith = _libstringutil.endswith

def contains(*args):
    return _libstringutil.contains(*args)
contains = _libstringutil.contains

def max(input, length):
    return _libstringutil.max(input, length)
max = _libstringutil.max

def first(input, length):
    return _libstringutil.first(input, length)
first = _libstringutil.first

def last(input, length):
    return _libstringutil.last(input, length)
last = _libstringutil.last

def erase(content, chars):
    return _libstringutil.erase(content, chars)
erase = _libstringutil.erase

def erase_chars(content, chars):
    return _libstringutil.erase_chars(content, chars)
erase_chars = _libstringutil.erase_chars

def replace_chars(content, chars, dest):
    return _libstringutil.replace_chars(content, chars, dest)
replace_chars = _libstringutil.replace_chars

def erase_from(content, part):
    return _libstringutil.erase_from(content, part)
erase_from = _libstringutil.erase_from

def to_cnvec(line):
    return _libstringutil.to_cnvec(line)
to_cnvec = _libstringutil.to_cnvec

def conf_trim(input):
    return _libstringutil.conf_trim(input)
conf_trim = _libstringutil.conf_trim

def normalize_feature_str(feature_str):
    return _libstringutil.normalize_feature_str(feature_str)
normalize_feature_str = _libstringutil.normalize_feature_str

def get_words(*args):
    return _libstringutil.get_words(*args)
get_words = _libstringutil.get_words

def get_skipn_bigram(*args):
    return _libstringutil.get_skipn_bigram(*args)
get_skipn_bigram = _libstringutil.get_skipn_bigram

def get_skip_bigram(*args):
    return _libstringutil.get_skip_bigram(*args)
get_skip_bigram = _libstringutil.get_skip_bigram

def json_empty(value):
    return _libstringutil.json_empty(value)
json_empty = _libstringutil.json_empty

def GetOutputFileNameWithSuffix(infile, suffix, removeTxt=False):
    return _libstringutil.GetOutputFileNameWithSuffix(infile, suffix, removeTxt)
GetOutputFileNameWithSuffix = _libstringutil.GetOutputFileNameWithSuffix

def pad_right(input, count):
    return _libstringutil.pad_right(input, count)
pad_right = _libstringutil.pad_right

def arg(input):
    return _libstringutil.arg(input)
arg = _libstringutil.arg
# This file is compatible with both classic and new-style classes.

cvar = _libstringutil.cvar
kSmallStringLength = cvar.kSmallStringLength


#ifndef __DEFINES_H__
#define __DEFINES_H__

#define D_NOINIT_PROPERTY(_type, _name) \
    private: \
        _type _##_name; \
    public: \
        const _type & _name () const { return _##_name; }; \
        void set##_name (const _type & value) { _##_name = value; };

#define D_PROPERTY(_type, _name, _default) \
    D_NOINIT_PROPERTY(_type, _name) \
    private: \
        void init##_name () { _##_name = _default; } \

#define D_POINTER_PROPERTY(_type, _name) \
    private: \
        _type * _##_name; \
        void init##_name () { _##_name = new _type(); } \
        void destroy##_name () { delete _##_name; } \
    public: \
        const _type * _name () const { return _##_name; };

#endif // __DEFINES_H__

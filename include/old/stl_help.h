/** 
 *  ==============================================================================
 * 
 *          \file   stl_help.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-05-20 19:32:04.650872
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef STL_HELP_H_
#define STL_HELP_H_
#include <iterator>
#include <algorithm>
#include <functional>
namespace std2 {

template<typename _Container>
class back_insert_iterator
: public std::iterator<output_iterator_tag, void, void, void, void>
{
protected:
    _Container* container;

public:
    /// A nested typedef for the type of whatever container you used.
    typedef _Container container_type;
    typedef typename _Container::value_type value_type; //????value_type?

    /// The only way to create this %iterator is with a container.
    explicit
    back_insert_iterator(_Container& __x) : container(&__x)
    {
    }
    /**
     *  @param  value  An instance of whatever type
     *                 container_type::const_reference is; presumably a
     *                 reference-to-const T for container<T>.
     *  @return  This %iterator, for chained operations.
     *
     *  This kind of %iterator doesn't really have a "position" in the
     *  container (you can think of the position as being permanently at
     *  the end, if you like).  Assigning a value to the %iterator will
     *  always append the value to the end of the container.
     */
    back_insert_iterator &
            operator=(typename _Container::const_reference __value)
    {
        container->push_back(__value);
        return *this;
    }

#ifdef __GXX_EXPERIMENTAL_CXX0X__
    back_insert_iterator &
            operator=(typename _Container::value_type && __value)
    {
        container->push_back(std::move(__value));
        return *this;
    }
#endif

    /// Simply returns *this.
    back_insert_iterator &
    operator*()
    {
        return *this;
    }

    /// Simply returns *this.  (This %iterator does not "move".)
    back_insert_iterator &
    operator++()
    {
        return *this;
    }

    /// Simply returns *this.  (This %iterator does not "move".)
    back_insert_iterator
    operator++(int)
    {
        return *this;
    }
};
template<typename _Container>
inline back_insert_iterator<_Container>
back_inserter(_Container& __x)
{
    return back_insert_iterator<_Container > (__x);
}


}  //----end of namespace std2

#endif  //----end of STL_HELP_H_

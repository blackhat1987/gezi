/**
 *  ==============================================================================
 *
 *          \file   exception.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-02-17 15:06:41.283000
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_
#include <glog/logging.h>
#include <exception>

namespace gezi
{
	class Exception : public std::exception
	{
	private:
		string _msg;
	public:
		//without it gcc 3 will complain for no throw() which is in base
		virtual ~Exception() throw(); 
		Exception(const string& msg = "")
			:_msg(msg)
		{

		}
		virtual const char *what() const throw()
		{
			return _msg.c_str();
		}
	};
}

#define  THROW(msg)\
	LOG(WARNING) << msg;\
	throw gezi::Exception(msg)

#endif  //----end of EXCEPTION_H_

/**
 *  ==============================================================================
 *
 *          \file   LoadSave.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-04-13 08:41:46.900935
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef LOAD_SAVE_H_
#define LOAD_SAVE_H_
#include <string>
#include <glog/logging.h>
namespace gezi {

	class LoadSave
	{
	public:
		virtual void Save(std::string path)
		{
			VLOG(0) << Name() << " try save to " << path;
		}

		virtual bool Load(std::string path)
		{
			VLOG(0) << Name() << " try load from " << path;
			return true;
		}

		virtual void CustomSave(std::string path)
		{
			VLOG(0) << Name() << " try custom save to " << path;
		}

		virtual bool CustomLoad(std::string path)
		{
			VLOG(0) << Name() << " try custom load from " << path;
			return true;
		}

		//另外兼容之前 小写开头的load save看做类似 LoadText, SaveText
		virtual void SaveText(std::string file)
		{
			VLOG(0) << Name() << " try save as text to " << file;
		}

		virtual bool LoadText(std::string file)
		{
			VLOG(0) << Name() << " try load as text from " << file;
			return true;
		}

		virtual void SaveXml(std::string file)
		{
			VLOG(0) << Name() << " try save as xml to " << file;
		}

		virtual bool LoadXml(std::string file)
		{
			VLOG(0) << Name() << " try load as xml from " << file;
			return true;
		}

		virtual void SaveJson(std::string file)
		{
			VLOG(0) << Name() << " try save as json to " << file;
		}

		virtual bool LoadJson(std::string file)
		{
			VLOG(0) << Name() << " load as json from " << file;
			return true;
		}

		virtual std::string Name()
		{
			return "";
		}

	};

}  //----end of namespace gezi

#endif  //----end of LOAD_SAVE_H_

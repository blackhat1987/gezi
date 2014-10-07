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

namespace gezi {

	class LoadSave
	{
	public:
		virtual void Save(string path)
		{
			VLOG(0) << Name() << " try save to " << path;
		}

		virtual void Load(string path)
		{
			VLOG(0) << Name() << " try load from " << path;
		}

		//另外兼容之前 小写开头的load save看做类似 LoadText, SaveText
		virtual void SaveText(string file)
		{
			VLOG(0) << Name() << " try save as text to " << file;
		}

		virtual void LoadText(string file)
		{
			VLOG(0) << Name() << " try load as text from " << file;
		}

		virtual void SaveXml(string file)
		{
			VLOG(0) << Name() << " try save as xml to " << file;
		}

		virtual void LoadXml(string file)
		{
			VLOG(0) << Name() << " try load as xml from " << file;
		}

		virtual void SaveJson(string file)
		{
			VLOG(0) << Name() << " try save as json to " << file;
		}

		virtual void LoadJson(string file)
		{
			VLOG(0) << Name() << " load as json from " << file;
		}

		virtual string Name()
		{
			return "";
		}

	};

}  //----end of namespace gezi

#endif  //----end of LOAD_SAVE_H_

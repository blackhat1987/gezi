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
			VLOG(0) << Name() << " sav to " << path;
		}

		virtual void Load(string path)
		{
			VLOG(0) << Name() << " load from " << path;
		}

		virtual void SaveText(string file)
		{
			VLOG(0) << Name() << " save as text to " << file;
		}

		virtual void LoadText(string file)
		{
			VLOG(0) << Name() << " load as text from " << file;
		}

		virtual string Name()
		{
			return "";
		}

	};

}  //----end of namespace gezi

#endif  //----end of LOAD_SAVE_H_

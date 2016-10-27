#ifndef LOAD_SAVE_H_
#define LOAD_SAVE_H_
namespace gezi {
class LoadSave
{
public:
virtual void Save(string path);
virtual bool Load(string path);
virtual void CustomSave(string path);
virtual bool CustomLoad(string path);
virtual void SaveText(string file);
virtual bool LoadText(string file);
virtual void SaveXml(string file);
virtual bool LoadXml(string file);
virtual void SaveJson(string file);
virtual bool LoadJson(string file);
virtual string Name();
};
}
#endif

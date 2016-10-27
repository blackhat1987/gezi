#ifndef GEZI_NLP__VOCABULARY_H_
#define GEZI_NLP__VOCABULARY_H_
#include "Identifer.h"
namespace gezi {
class Vocabulary : public ValueIdentifer<int64>
{
public:
int64 freq(int index) const;
int64 freq(string key) const;
protected:
private:
};
}
#endif

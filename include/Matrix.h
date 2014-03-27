/**
 *  ==============================================================================
 *
 *          \file   Matrix.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-01-19 08:00:46.364395
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef MATRIX_H_
#define MATRIX_H_
#include <vector>
namespace gezi
{
namespace ufo
{

template<typename T>
class Matrix
{
public:

  Matrix()
  {

  }

  Matrix(int rows, int cols)
		:_nrow(rows), _ncol(cols)
  {
    resize(rows, cols);
  }

  Matrix(int rows, int cols, T defaultValue)
		:_nrow(rows), _ncol(cols)
	{
    resize(rows, cols, defaultValue);
  }

  inline void resize(int rows, int cols)
  {
		_nrow = rows;
		_ncol = cols;
    _mat.resize(rows);
    for (int i = 0; i < rows; i++)
    {
      _mat[i].resize(cols);
    }
  }

  inline void resize(int rows, int cols, T defaultValue)
  {
		_nrow = rows;
		_ncol = cols;
    _mat.resize(rows);
    for (int i = 0; i < rows; i++)
    {
      _mat[i].resize(cols, defaultValue);
    }
  }

  inline T operator()(int rowIdx, int colIdx)
  {
    return _mat[rowIdx][colIdx];
  }

  std::vector<std::vector<T> >& mat()
  {
    return _mat;
  }

	inline int rows()
	{
		return _nrow;
	}

	inline int cols()
	{
		return _ncol;
	}
private:
  std::vector<std::vector<T> > _mat;
	int _nrow = 0;
	int _ncol = 0;
};

}

template<typename T>
inline void init(std::vector<std::vector<T> >& mat, int rows, int cols, T value)
{
  mat.resize(rows);
  for (int i = 0; i < rows; i++)
  {
    mat[i].resize(cols, value);
  }
}

template<typename T>
inline void init(std::vector<std::vector<T> >& mat, int rows, int cols)
{
  mat.resize(rows);
  for (int i = 0; i < rows; i++)
  {
    mat[i].resize(cols);
  }
}

typedef std::vector<std::vector<int> > IMat;
typedef std::vector<std::vector<float> > FMat;
typedef std::vector<std::vector<double> > DMat;
} //----end of namespace gezi

#endif  //----end of MATRIX_H_

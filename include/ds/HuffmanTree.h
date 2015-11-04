/**
 *  ==============================================================================
 *
 *          \file   ds/HuffmanTree.h
 *
 *        \author   chenghuige
 *
 *          \date   2015-10-30 16:44:52.307013
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef GEZI_DS__HUFFMAN_TREE_H_
#define GEZI_DS__HUFFMAN_TREE_H_

#include "common_util.h"

namespace gezi {

	//主要输出接口是根据wordId来定位 路径上面的node和branch
	class HuffmanTree
	{
	public:
		//默认假定输入的freqs是从大到小排好序的 needSort = false
		//@TODO 对应 NumBranch不是2 比如3叉huffman 要检查叶子数目是否ok
		HuffmanTree(const vector<int64>& freqs, const int numBranchces = 2)
			:_numBranches(numBranchces),
			_numLeaves(freqs.size()),
			_numInterNodes(freqs.size() - 1),
			_numNodes(_numLeaves + _numInterNodes),
			_childs(_numBranches, _numInterNodes),
			_root(_numNodes - 1),
			_weight(freqs.begin(), freqs.end()),
			_nodePaths(_numLeaves),
			_branchPaths(_numLeaves)
		{
			Init();
			Build();
		}

		int NumBranches() const
		{
			return _numBranches;
		}

		bool IsLeaf(int node) const
		{
			return node < _numLeaves;
		}

		int Root() const
		{
			return _root;
		}

		int NumLeaves() const
		{
			return _numLeaves;
		}

		size_t size() const
		{
			return _numLeaves;
		}

		const vector<int>& NodePaths(int node) const
		{
			return _nodePaths[node];
		}

		const vector<int>& BranchPaths(int node) const
		{
			return _branchPaths[node];
		}

	protected:
	private:
		void Init()
		{
			_weight.resize(_numNodes, std::numeric_limits<int64>::max());
		}

		int InterNodeIndex(int index) const
		{
			return _numLeaves + index;
		}

		void Build()
		{
			int minLeafIndex = _numLeaves - 1;
			int minInterIndex = _numLeaves;

			vector<int>  parents(_numNodes);
			vector<int> branches(_numNodes);
			//每次选取_numBranches个最小的节点，并将它们的和按照顺序
			for (int interIndex = 0; interIndex < _numInterNodes; interIndex++)
			{
				int64 weight = 0;
				int index = InterNodeIndex(interIndex);
				for (int branch = 0; branch < _numBranches; branch++)
				{
					if (minLeafIndex >= 0 && _weight[minLeafIndex] <= _weight[minInterIndex])
					{
						weight += _weight[minLeafIndex];
						_childs[branch][interIndex] = minLeafIndex;
						parents[minLeafIndex] = index;
						branches[minLeafIndex] = branch;
						minLeafIndex--;
					}
					else
					{
						weight += _weight[minInterIndex];
						_childs[branch][interIndex] = minInterIndex;
						parents[minInterIndex] = index;
						branches[minInterIndex] = branch;
						minInterIndex++;
					}
				}
				_weight[index] = weight;
			}

			for (int leafNode = 0; leafNode < _numLeaves; leafNode++)
			{
				for (int node = leafNode; node != _root; node = parents[node])
				{
					_nodePaths[leafNode].push_back(parents[node]);
					_branchPaths[leafNode].push_back(branches[node]);
				} 
				std::reverse(_nodePaths[leafNode].begin(), _nodePaths[leafNode].end());
				std::reverse(_branchPaths[leafNode].begin(), _branchPaths[leafNode].end());
			}
		}

	private:
		int _numBranches = 2;

		//@TODO 目前都是只考虑int 后面考虑改为 WordIndex ? unsigned
		int _numLeaves;
		int _numInterNodes;
		int _numNodes;
		int _root;

		//存储所有node的weight最开始存储所有叶子节点从大到小排列，然后存储内部节点从小到大排列，root节点就是最后一个节点
		//保持和faster-rnnlm中策略一致
		vector<int64> _weight;
		ufo::Matrix<int> _childs;

		//记录每一个叶子节点对应从root到它自身路径的所有节点，不包括它自己
		vector<vector<int> > _nodePaths;
		//记录每一个叶子节点对应从root到它自身的所有路径的branch标记 比如 010100
		vector<vector<int> > _branchPaths;
	};

}  //----end of namespace gezi

#endif  //----end of GEZI_DS__HUFFMAN_TREE_H_

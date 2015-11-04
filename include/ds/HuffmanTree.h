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

	//��Ҫ����ӿ��Ǹ���wordId����λ ·�������node��branch
	class HuffmanTree
	{
	public:
		//Ĭ�ϼٶ������freqs�ǴӴ�С�ź���� needSort = false
		//@TODO ��Ӧ NumBranch����2 ����3��huffman Ҫ���Ҷ����Ŀ�Ƿ�ok
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
			//ÿ��ѡȡ_numBranches����С�Ľڵ㣬�������ǵĺͰ���˳��
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

		//@TODO Ŀǰ����ֻ����int ���濼�Ǹ�Ϊ WordIndex ? unsigned
		int _numLeaves;
		int _numInterNodes;
		int _numNodes;
		int _root;

		//�洢����node��weight�ʼ�洢����Ҷ�ӽڵ�Ӵ�С���У�Ȼ��洢�ڲ��ڵ��С�������У�root�ڵ�������һ���ڵ�
		//���ֺ�faster-rnnlm�в���һ��
		vector<int64> _weight;
		ufo::Matrix<int> _childs;

		//��¼ÿһ��Ҷ�ӽڵ��Ӧ��root��������·�������нڵ㣬���������Լ�
		vector<vector<int> > _nodePaths;
		//��¼ÿһ��Ҷ�ӽڵ��Ӧ��root�������������·����branch��� ���� 010100
		vector<vector<int> > _branchPaths;
	};

}  //----end of namespace gezi

#endif  //----end of GEZI_DS__HUFFMAN_TREE_H_

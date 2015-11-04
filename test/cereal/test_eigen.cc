/** 
 *  ==============================================================================
 * 
 *          \file   test_eigen.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-11-04 19:06:40.539541
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#include <fstream>
#include "serialize_util.h"
#include "debug_util.h"

int main() {
	Eigen::MatrixXd test = Eigen::MatrixXd::Random(10, 3);
	std::ofstream out("eigen.cereal", std::ios::binary);
	cereal::BinaryOutputArchive archive_o(out);
	archive_o(test);

	std::cout << "test:" << std::endl << test << std::endl;

	out.close();

	Eigen::MatrixXd test_loaded;
	std::ifstream in("eigen.cereal", std::ios::binary);
	cereal::BinaryInputArchive archive_i(in);
	archive_i(test_loaded);

	std::cout << "test loaded:" << std::endl << test_loaded << std::endl;

	{
		serialize_util::save(test, "eigen.matrix");
	}
	{
		serialize_util::load(test_loaded, "eigen.matrix");
		Pval(test_loaded);
	}
}
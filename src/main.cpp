#include <string>
#include <vector>
#include <fstream>

#include <Eigen/Core>

#include "Clusterer.h"

void serializeMatrixXfAscii(const Eigen::MatrixXf& data, const std::string& fileName) {
  int rows(static_cast<int>(data.rows()));
  int cols(static_cast<int>(data.cols()));
  // open the file for writing
  std::ofstream opFile;
  opFile.open(fileName, std::ios::out);
  float temp;
	for (int rIt = 0; rIt < rows; rIt ++) {
		for (int cIt = 0; cIt < cols; cIt ++) {
      temp = data(rIt, cIt);
      opFile << temp;
      if (cIt < cols-1) opFile << ",";
		}
    opFile << "\n";
	}
	opFile.close();
}

Eigen::MatrixXf deserializeMatrixXfAscii(const std::string& file_name) {
  std::vector<std::vector<float> > floats;
  std::ifstream  data(file_name);
  std::string line;
  int rows(0);
  int cols(0);
  while(std::getline(data,line)) {
    floats.push_back(std::vector<float>());
    std::stringstream lineStream(line);
    std::string cell;
    while(std::getline(lineStream,cell,',')) {
      floats[rows].push_back(atof(cell.c_str()));
    }
    ++rows;
  }
  cols = floats[0].size();
  Eigen::MatrixXf mat(rows, cols);
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      mat(r, c) = floats[r][c];
    }
  }
  return mat;
};

void main(int argc, char* argv[]) {
  Clusterer clustr(20);
  Eigen::MatrixXf dummy = deserializeMatrixXfAscii("..\\..\\data.csv");
  clustr.AddPoints(dummy);
  Eigen::MatrixXf means = clustr.means();
  serializeMatrixXfAscii(means, "..\\..\\means.csv");
}
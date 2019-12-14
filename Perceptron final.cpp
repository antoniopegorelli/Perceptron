#include <iostream>
#include <memory>
#include <math.h>
#include <ctime>
#include <time.h> 
#include <sstream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

// Random integer generator
int randomIntCalc(int init, int max)
{
	return init + static_cast<int>(rand()) / (static_cast<int>(RAND_MAX / (max - init)));
}

// Random double generator
double randomDoubleCalc(double init, double max)
{
	return init + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (max - init)));
}


//------------------------------------------------- Matrix Class -----------------------------------------------------------

// Matrix class declaration
class matrix
{
private:
	int matrixRows;
	int matrixCols;
	vector<vector<double>> matrixData;
public:
	matrix(int, int);
	~matrix();
	void addData(double, int, int);
	void sumData(double, int, int);
	void fillZeros(void);
	void fillConst(double);
	void fillRand(double, double);
	double getData(int, int);
	int getRows(void);
	int getCols(void);
	double getMaxInCol(int col);
	int getMaxInRow(int row);
	int getMinInCol(int col);
	int getMinInRow(int row);
	int countClass(int col, int classVal);
	std::shared_ptr<matrix> exportRow(int row);
	std::shared_ptr<matrix> exportCol(int col);
	void scalarSum(std::shared_ptr<matrix> mat);
	void scalarSub(std::shared_ptr<matrix> mat);
	void scalarMult(std::shared_ptr<matrix> mat);
	void print(string name);
	void printToFile(string name);
	void appendToFile(string name, string var);
};

// Matrix class contructor
matrix::matrix(int rows, int cols)
{
	matrixRows = rows;
	matrixCols = cols;
	matrixData.resize(matrixRows, vector<double>(matrixCols, 0));
	for (int i = 0; i < matrixRows; i++)
	{
		for (int j = 0; j < matrixCols; j++)
		{
			matrixData[i][j] = 0;
		}
	}
}

// Matrix class destructor
matrix::~matrix()
{

}

// Matrix class to add data
void matrix::addData(double data, int row, int col)
{
	matrixData[row][col] = data;
}

// Matrix class to sum data
void matrix::sumData(double data, int row, int col)
{
	matrixData[row][col] += data;
}

// Matrix class to fill with zeros
void matrix::fillZeros(void)
{
	for (int i = 0; i < matrixRows; i++)
	{
		for (int j = 0; j < matrixCols; j++)
		{
			matrixData[i][j] = 0;
		}
	}
}

// Matrix class to fill with constant
void matrix::fillConst(double value)
{
	for (int i = 0; i < matrixRows; i++)
	{
		for (int j = 0; j < matrixCols; j++)
		{
			matrixData[i][j] = value;
		}
	}
}

// Matrix class to fill with random number
void matrix::fillRand(double min, double max)
{
	for (int i = 0; i < matrixRows; i++)
	{
		for (int j = 0; j < matrixCols; j++)
		{
			matrixData[i][j] = randomDoubleCalc(min, max);
		}
	}
}

// Matrix class to get data
double matrix::getData(int row, int col)
{
	return matrixData[row][col];
}

// Matrix class to get row size
int matrix::getRows(void)
{
	return matrixRows;
}

// Matrix class to get column size
int matrix::getCols(void)
{
	return matrixCols;
}

// Matrix class to get maximum value
double matrix::getMaxInCol(int col)
{
	double max = numeric_limits<int>::min();

	for (int i = 0; i < matrixRows; i++)
	{
		if (matrixData[i][col] > max) { max = matrixData[i][col]; }
	}

	return max;
}

// Matrix class to get maximum value
int matrix::getMaxInRow(int row)
{
	int max = numeric_limits<int>::min();

	for (int i = 0; i < matrixCols; i++)
	{
		if (matrixData[row][i] > max) { max = matrixData[row][i]; }
	}

	return max;
}

// Matrix class to get minimum value
int matrix::getMinInCol(int col)
{
	int min = numeric_limits<int>::max();

	for (int i = 0; i < matrixRows; i++)
	{
		if (matrixData[i][col] < min) { min = matrixData[i][col]; }
	}

	return min;
}

// Matrix class to get minimum value
int matrix::getMinInRow(int row)
{
	int min = numeric_limits<int>::max();

	for (int i = 0; i < matrixCols; i++)
	{
		if (matrixData[row][i] < min) { min = matrixData[row][i]; }
	}

	return min;
}

// Matrix class to count class quantity
int matrix::countClass(int col, int classVal)
{
	int count = 0;

	for (int i = 0; i < matrixRows; i++)
	{
		if (matrixData[i][col] == classVal) { count++; }
	}

	return count;
}

// Export one row of data to a new matrix
std::shared_ptr<matrix> matrix::exportRow(int row)
{
	std::shared_ptr<matrix> result = std::make_shared<matrix>(1, this->getCols());

	for (int j = 0; j < this->getCols(); j++)
	{
		result->addData(matrixData[row][j], 0, j);
	}
	return result;
}

// Export one column of data to a new matrix
std::shared_ptr<matrix> matrix::exportCol(int col)
{
	std::shared_ptr<matrix> result = std::make_shared<matrix>(this->getRows(), 1);

	for (int i = 0; i < this->getRows(); i++)
	{
		result->addData(matrixData[i][col], i, 0);
	}
	return result;
}

// Sum matrix to current
void matrix::scalarSum(std::shared_ptr<matrix> mat)
{
	if (matrixRows != mat->getRows() || matrixCols != mat->getCols())
	{
		cout << "matSum with different size matrices" << endl << endl;
	}

	for (int i = 0; i < matrixRows; i++)
	{
		for (int j = 0; j < matrixCols; j++)
		{
			matrixData[i][j] += mat->getData(i, j);
		}
	}
}

// Subtract matrix to current
void matrix::scalarSub(std::shared_ptr<matrix> mat)
{
	if (matrixRows != mat->getRows() || matrixCols != mat->getCols())
	{
		cout << "matSum with different size matrices" << endl << endl;
	}

	for (int i = 0; i < matrixRows; i++)
	{
		for (int j = 0; j < matrixCols; j++)
		{
			matrixData[i][j] -= mat->getData(i, j);
		}
	}

}

// Multiply matrix with constant
void matrix::scalarMult(std::shared_ptr<matrix> mat)
{
	for (int i = 0; i < matrixRows; i++)
	{
		for (int j = 0; j < matrixCols; j++)
		{
			matrixData[i][j] *= mat->getData(i, j);
		}
	}
}

// Matrix class to print it on screen
void matrix::print(string name)
{
	cout << name << ": " << endl << matrixRows << " x " << matrixCols << " matrix" << endl << endl;

	for (int i = 0; i < this->getRows(); i++)
	{
		for (int j = 0; j < this->getCols(); j++)
		{
			cout << this->getData(i, j) << "    ";
		}
		cout << endl << endl;
	}
	cout << endl;
}

// Matrix class to print it on file
void matrix::printToFile(string name)
{
	name += ".csv";

	ofstream outputFile;
	outputFile.open(name);

	//outputFile << name << ": " << matrixRows << " x " << matrixCols << " matrix\n";

	for (int i = 0; i < this->getCols(); i++)
	{
		outputFile << name << " " << i << ";";
	}
	outputFile << "\n";

	for (int i = 0; i < this->getRows(); i++)
	{
		for (int j = 0; j < this->getCols(); j++)
		{
			outputFile << this->getData(i, j) << ";";
		}
		outputFile << "\n";
	}
	outputFile << "\n";

	outputFile.close();

	cout << "Successfully written to file: " << name << endl << endl;
}

// Matrix class to print it on file
void matrix::appendToFile(string name, string var = "")
{
	name += ".csv";

	ofstream outputFile;
	outputFile.open(name, fstream::app);

	for (int i = 0; i < this->getCols(); i++)
	{
		outputFile << name << " " << i << " " << var << ";";
	}
	outputFile << "\n";

	for (int i = 0; i < this->getRows(); i++)
	{
		for (int j = 0; j < this->getCols(); j++)
		{
			outputFile << this->getData(i, j) << ";";
		}
		outputFile << "\n";
	}
	outputFile << "\n";

	outputFile.close();

	//cout << "Successfully appended to file: " << name << endl << endl;
}


//----------------------------------------------------- Global Variables ---------------------------------------------------------------

std::shared_ptr<matrix> W;
double bias;


//----------------------------------------------------- Datasets ---------------------------------------------------------------

// Import CSV file to matrix
std::shared_ptr<matrix> dataImportCSV(string filename, char delimiter)
{
	filename += ".csv";
	ifstream inputFile(filename);
	string line;

	int i = 0;
	int j = 0;
	bool firstLine = true;

	if (inputFile.good())
		cout << filename << " opened successfully!" << endl;

	while (getline(inputFile, line))
	{
		if (line.find(delimiter) == string::npos)
			break;

		istringstream lineString(line);
		string singleData;

		bool stringErr = false;

		while (getline(lineString, singleData, delimiter))
		{
			if (firstLine) j++;

			singleData.erase(remove_if(singleData.begin(), singleData.end(), [](char c) { return !(c >= 32 && c < 167); }), singleData.end());

			try
			{
				stod(singleData);
			}
			catch (exception & e)
			{
				stringErr = true;
			}
		}

		if (stringErr)
		{
			i--;
		}

		firstLine = false;
		i++;
	}

	cout << "i = " << i << endl << "j = " << j << endl;

	std::shared_ptr<matrix> result = std::make_shared<matrix>(i, j);

	inputFile.clear();
	inputFile.seekg(0, ios::beg);

	i = 0;
	j = 0;

	while (getline(inputFile, line))
	{
		if (line.find(delimiter) == string::npos)
			break;

		istringstream lineString(line);
		string singleData;

		//cout << endl << line << endl;

		bool stringErr = false;

		while (getline(lineString, singleData, delimiter))
		{

			//cout << "|" << singleData << "|";
			singleData.erase(remove_if(singleData.begin(), singleData.end(), [](char c) { return !(c >= 32 && c < 167); }), singleData.end());
			//cout << "|" << singleData << "|" << endl;

			try
			{
				result->addData(stod(singleData), i, j);
			}
			catch (exception & e)
			{
				//cout << "Could not convert string to double" << endl;
				stringErr = true;
			}
			j++;
		}
		if (!stringErr)
		{
			i++;
		}
		j = 0;
	}

	if (inputFile.bad())
		cout << "error while reading file" << endl;

	inputFile.close();

	return result;
}

// Data from class presentation
double aula[17][2] = {
	{ 1.9, 7.3 },
	{ 3.4, 7.5 },
	{ 2.5, 6.8 },
	{ 1.5, 6.5 },
	{ 3.5, 6.4 },
	{ 2.2, 5.8 },
	{ 3.4, 5.2 },
	{ 3.6, 4 },
	{ 5, 3.2 },
	{ 4.5, 2.4 },
	{ 6, 2.6 },
	{ 1.9, 3 },
	{ 1, 2.7 },
	{ 1.9,2.4 },
	{ 0.8,2 },
	{ 1.6,1.8 },
	{1, 1 }
};

// Prepare class presentation database on matrix class
std::shared_ptr<matrix> classPresentationData(void)
{
	std::shared_ptr<matrix> result = std::make_shared<matrix>(17, 2);

	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			result->addData(aula[i][j], i, j);
		}
	}

	return result;
}

// Iris flower database
double iris[100][5] = { {5.1, 3.5, 1.4, 0.2, 1},
{4.9,3.0,1.4,0.2,1},
{4.7,3.2,1.3,0.2,1},
{4.6,3.1,1.5,0.2,1},
{5.0,3.6,1.4,0.3,1},
{5.4,3.9,1.7,0.4,1},
{4.6,3.4,1.4,0.3,1},
{5.0,3.4,1.5,0.2,1},
{4.4,2.9,1.4,0.2,1},
{4.9,3.1,1.5,0.1,1},
{5.4,3.7,1.5,0.2,1},
{4.8,3.4,1.6,0.2,1},
{4.8,3.0,1.4,0.1,1},
{4.3,3.0,1.1,0.1,1},
{5.8,4.0,1.2,0.2,1},
{5.7,4.4,1.5,0.4,1},
{5.4,3.9,1.3,0.4,1},
{5.1,3.5,1.4,0.3,1},
{5.7,3.8,1.7,0.3,1},
{5.1,3.8,1.5,0.3,1},
{5.4,3.4,1.7,0.2,1},
{5.1,3.7,1.5,0.4,1},
{4.6,3.6,1.0,0.2,1},
{5.1,3.3,1.7,0.5,1},
{4.8,3.4,1.9,0.2,1},
{5.0,3.0,1.6,0.2,1},
{5.0,3.4,1.6,0.4,1},
{5.2,3.5,1.5,0.2,1},
{5.2,3.4,1.4,0.2,1},
{4.7,3.2,1.6,0.2,1},
{4.8,3.1,1.6,0.2,1},
{5.4,3.4,1.5,0.4,1},
{5.2,4.1,1.5,0.1,1},
{5.5,4.2,1.4,0.2,1},
{4.9,3.1,1.5,0.2,1},
{5.0,3.2,1.2,0.2,1},
{5.5,3.5,1.3,0.2,1},
{4.9,3.6,1.4,0.1,1},
{4.4,3.0,1.3,0.2,1},
{5.1,3.4,1.5,0.2,1},
{5.0,3.5,1.3,0.3,1},
{4.5,2.3,1.3,0.3,1},
{4.4,3.2,1.3,0.2,1},
{5.0,3.5,1.6,0.6,1},
{5.1,3.8,1.9,0.4,1},
{4.8,3.0,1.4,0.3,1},
{5.1,3.8,1.6,0.2,1},
{4.6,3.2,1.4,0.2,1},
{5.3,3.7,1.5,0.2,1},
{5.0,3.3,1.4,0.2,1},
{7.0,3.2,4.7,1.4,-1},
{6.4,3.2,4.5,1.5,-1},
{6.9,3.1,4.9,1.5,-1},
{5.5,2.3,4.0,1.3,-1},
{6.5,2.8,4.6,1.5,-1},
{5.7,2.8,4.5,1.3,-1},
{6.3,3.3,4.7,1.6,-1},
{4.9,2.4,3.3,1.0,-1},
{6.6,2.9,4.6,1.3,-1},
{5.2,2.7,3.9,1.4,-1},
{5.0,2.0,3.5,1.0,-1},
{5.9,3.0,4.2,1.5,-1},
{6.0,2.2,4.0,1.0,-1},
{6.1,2.9,4.7,1.4,-1},
{5.6,2.9,3.6,1.3,-1},
{6.7,3.1,4.4,1.4,-1},
{5.6,3.0,4.5,1.5,-1},
{5.8,2.7,4.1,1.0,-1},
{6.2,2.2,4.5,1.5,-1},
{5.6,2.5,3.9,1.1,-1},
{5.9,3.2,4.8,1.8,-1},
{6.1,2.8,4.0,1.3,-1},
{6.3,2.5,4.9,1.5,-1},
{6.1,2.8,4.7,1.2,-1},
{6.4,2.9,4.3,1.3,-1},
{6.6,3.0,4.4,1.4,-1},
{6.8,2.8,4.8,1.4,-1},
{6.7,3.0,5.0,1.7,-1},
{6.0,2.9,4.5,1.5,-1},
{5.7,2.6,3.5,1.0,-1},
{5.5,2.4,3.8,1.1,-1},
{5.5,2.4,3.7,1.0,-1},
{5.8,2.7,3.9,1.2,-1},
{6.0,2.7,5.1,1.6,-1},
{5.4,3.0,4.5,1.5,-1},
{6.0,3.4,4.5,1.6,-1},
{6.7,3.1,4.7,1.5,-1},
{6.3,2.3,4.4,1.3,-1},
{5.6,3.0,4.1,1.3,-1},
{5.5,2.5,4.0,1.3,-1},
{5.5,2.6,4.4,1.2,-1},
{6.1,3.0,4.6,1.4,-1},
{5.8,2.6,4.0,1.2,-1},
{5.0,2.3,3.3,1.0,-1},
{5.6,2.7,4.2,1.3,-1},
{5.7,3.0,4.2,1.2,-1},
{5.7,2.9,4.2,1.3,-1},
{6.2,2.9,4.3,1.3,-1},
{5.1,2.5,3.0,1.1,-1},
{5.7,2.8,4.1,1.3,-1} };

// Prepare iris flower database on matrix class
std::shared_ptr<matrix> irisData(void)
{
	std::shared_ptr<matrix> result = std::make_shared<matrix>(150, 4);
	for (int i = 0; i < 150; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result->addData(iris[i][j], i, j);
		}
	}

	return result;
}

// Prepare iris flower database on matrix class
std::shared_ptr<matrix> irisInData(void)
{
	std::shared_ptr<matrix> result = std::make_shared<matrix>(100, 4);
	for (int i = 0; i < 100; i++)
	{

		result->addData(iris[i][0], i, 0);
		result->addData(iris[i][1], i, 1);
		result->addData(iris[i][2], i, 2);
		result->addData(iris[i][3], i, 3);

	}

	return result;
}

// Prepare iris flower database on matrix class
std::shared_ptr<matrix> irisOutData(void)
{


	std::shared_ptr<matrix> result = std::make_shared<matrix>(100, 1);
	for (int i = 0; i < 100; i++)
	{
		result->addData(iris[i][4], i, 0);
	}

	return result;
}

// Prepare survey data on matrix class
std::shared_ptr<matrix> happinessSurveyData(void)
{
	std::shared_ptr<matrix> data = dataImportCSV("SomervilleHappinessSurvey2015", ';');
	std::shared_ptr<matrix> result = std::make_shared<matrix>(data->getRows(), 2);

	for (int i = 0; i < data->getRows(); i++)
	{
		result->addData(data->getData(i, 2), i, 0);
		result->addData(data->getData(i, 5), i, 1);
	}
	return result;
}

// Prepare car data on matrix class
std::shared_ptr<matrix> carData(void)
{
	std::shared_ptr<matrix> data = dataImportCSV("car", ';');
	std::shared_ptr<matrix> result = std::make_shared<matrix>(data->getRows(), 2);

	for (int i = 0; i < data->getRows(); i++)
	{
		result->addData(data->getData(i, 1), i, 0);
		result->addData(data->getData(i, 5), i, 1);
	}
	return result;
}

// Prepare auto-mpg data on matrix class
std::shared_ptr<matrix> autoMPGData(void)
{
	std::shared_ptr<matrix> data = dataImportCSV("auto-mpg", ';');
	std::shared_ptr<matrix> result = std::make_shared<matrix>(data->getRows(), 3);

	for (int i = 0; i < data->getRows(); i++)
	{
		result->addData(data->getData(i, 0), i, 0);
		result->addData(data->getData(i, 2), i, 1);
		result->addData(data->getData(i, 4), i, 2);
	}
	return result;
}

// Data for xOR
double xorDatabase[4][3] = {
	{ 0, 0, -1},
	{ 0, 1, 1},
	{ 1, 0, 1},
	{ 1, 1, -1},
};

// Prepare xOR data
std::shared_ptr<matrix> xorData(void)
{
	std::shared_ptr<matrix> result = std::make_shared<matrix>(4, 3);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			result->addData(xorDatabase[i][j], i, j);
		}
	}

	return result;
}

// Prepare xOR inputs
std::shared_ptr<matrix> xorInData(void)
{
	std::shared_ptr<matrix> result = std::make_shared<matrix>(4, 2);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			result->addData(xorDatabase[i][j], i, j);
		}
	}

	return result;
}

// Prepare xOR Outputs
std::shared_ptr<matrix> xorOutData(void)
{
	std::shared_ptr<matrix> result = std::make_shared<matrix>(4, 1);

	for (int i = 0; i < 4; i++)
	{
		result->addData(xorDatabase[i][2], i, 0);
	}

	return result;
}

// Data for OR
double orDatabase[4][3] = {
	{ 0, 0, -1},
	{ 0, 1, 1},
	{ 1, 0, 1},
	{ 1, 1, 1},
};

// Prepare OR data
std::shared_ptr<matrix> orData(void)
{
	std::shared_ptr<matrix> result = std::make_shared<matrix>(4, 3);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			result->addData(orDatabase[i][j], i, j);
		}
	}

	return result;
}

// Prepare OR inputs
std::shared_ptr<matrix> orInData(void)
{
	std::shared_ptr<matrix> result = std::make_shared<matrix>(4, 2);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			result->addData(orDatabase[i][j], i, j);
		}
	}

	return result;
}

// Prepare OR Outputs
std::shared_ptr<matrix> orOutData(void)
{
	std::shared_ptr<matrix> result = std::make_shared<matrix>(4, 1);

	for (int i = 0; i < 4; i++)
	{
		result->addData(orDatabase[i][2], i, 0);
	}

	return result;
}

// Data for AND
double andDatabase[4][3] = {
	{ 0, 0, -1},
	{ 0, 1, -1},
	{ 1, 0, -1},
	{ 1, 1, 1},
};

// Prepare AND data
std::shared_ptr<matrix> andData(void)
{
	std::shared_ptr<matrix> result = std::make_shared<matrix>(4, 3);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			result->addData(andDatabase[i][j], i, j);
		}
	}

	return result;
}

// Prepare AND inputs
std::shared_ptr<matrix> andInData(void)
{
	std::shared_ptr<matrix> result = std::make_shared<matrix>(4, 2);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			result->addData(andDatabase[i][j], i, j);
		}
	}

	return result;
}

// Prepare AND Outputs
std::shared_ptr<matrix> andOutData(void)
{
	std::shared_ptr<matrix> result = std::make_shared<matrix>(4, 1);

	for (int i = 0; i < 4; i++)
	{
		result->addData(andDatabase[i][2], i, 0);
	}

	return result;
}


//------------------------------------------------- Support Functions -----------------------------------------------------------

// Sigmoid function
double sigmoid(double input)
{
	return 1 / (1 + exp(-input));
}


//------------------------------------------------- Matrix Functions -----------------------------------------------------------

// Matrix sum
std::shared_ptr<matrix> matSum(std::shared_ptr<matrix> matA, std::shared_ptr<matrix> matB)
{
	std::shared_ptr<matrix> result = std::make_shared<matrix>(matA->getRows(), matA->getCols());

	if (matA->getRows() != matB->getRows() || matA->getCols() != matB->getCols())
	{
		cout << "matSum with different size matrices" << endl << endl;
	}

	for (int i = 0; i < matA->getRows(); i++)
	{
		for (int j = 0; j < matA->getCols(); j++)
		{
			result->addData(matA->getData(i, j) + matB->getData(i, j), i, j);
		}
	}

	return result;
}

// Matrix subtraction
std::shared_ptr<matrix> matSub(std::shared_ptr<matrix> matA, std::shared_ptr<matrix> matB)
{
	if (matA->getRows() != matB->getRows() || matA->getCols() != matB->getCols())
	{
		cout << "matSub with different size matrices" << endl << endl;
	}

	std::shared_ptr<matrix> result = std::make_shared<matrix>(matA->getRows(), matA->getCols());

	for (int i = 0; i < matA->getRows(); i++)
	{
		for (int j = 0; j < matA->getCols(); j++)
		{
			result->addData(matA->getData(i, j) - matB->getData(i, j), i, j);
		}
	}

	return result;
}

// Matrix transposer
std::shared_ptr<matrix> matTrans(std::shared_ptr<matrix> mat)
{
	std::shared_ptr<matrix> result = std::make_shared<matrix>(mat->getCols(), mat->getRows());

	for (int i = 0; i < mat->getRows(); i++)
	{
		for (int j = 0; j < mat->getCols(); j++)
		{
			result->addData(mat->getData(i, j), j, i);
		}
	}

	return result;
}

// Matrix multiplier
std::shared_ptr<matrix> matMult(std::shared_ptr<matrix> matA, std::shared_ptr<matrix> matB)
{

	if (matA->getCols() != matB->getRows())
	{
		cout << "Matrix multiplication incompatibility" << endl;
	}

	std::shared_ptr<matrix> result = std::make_shared<matrix>(matA->getRows(), matB->getCols());
	double total;

	for (int i = 0; i < matA->getRows(); i++)
	{
		for (int j = 0; j < matB->getCols(); j++)
		{
			total = 0;
			for (int a = 0; a < matA->getCols(); a++)
			{
				total += matA->getData(i, a) * matB->getData(a, j);
			}
			result->addData(total, i, j);
		}
	}

	return result;
}

// Matrix scalar multiplier
std::shared_ptr<matrix> matScalarMult(std::shared_ptr<matrix> matA, std::shared_ptr<matrix> matB)
{

	if (matA->getRows() != matB->getRows() || matA->getCols() != matB->getCols())
	{
		cout << "Matrix scalar multiplication incompatibility" << endl;
	}

	std::shared_ptr<matrix> result = std::make_shared<matrix>(matA->getRows(), matB->getCols());

	for (int i = 0; i < matA->getRows(); i++)
	{
		for (int j = 0; j < matA->getCols(); j++)
		{
			result->addData(matA->getData(i, j) * matB->getData(i, j), i, j);
		}
	}

	return result;
}

// Matrix scalar divider
std::shared_ptr<matrix> matScalarDiv(std::shared_ptr<matrix> matA, std::shared_ptr<matrix> matB)
{

	if (matA->getRows() != matB->getRows() || matA->getCols() != matB->getCols())
	{
		cout << "Matrix scalar division incompatibility" << endl;
	}

	std::shared_ptr<matrix> result = std::make_shared<matrix>(matA->getRows(), matB->getCols());

	for (int i = 0; i < matA->getRows(); i++)
	{
		for (int j = 0; j < matA->getCols(); j++)
		{
			result->addData(matA->getData(i, j) / matB->getData(i, j), i, j);
		}
	}

	return result;
}

// Matrix constant multiplier
std::shared_ptr<matrix> matConstMult(double mult, std::shared_ptr<matrix> mat)
{
	std::shared_ptr<matrix> result = std::make_shared<matrix>(mat->getRows(), mat->getCols());

	for (int i = 0; i < mat->getRows(); i++)
	{
		for (int j = 0; j < mat->getCols(); j++)
		{
			result->addData(mat->getData(i, j) * mult, i, j);
		}
	}

	return result;
}

// Matrix constant divider
std::shared_ptr<matrix> matConstDiv(double div, std::shared_ptr<matrix> mat)
{
	std::shared_ptr<matrix> result = std::make_shared<matrix>(mat->getRows(), mat->getCols());

	for (int i = 0; i < mat->getRows(); i++)
	{
		for (int j = 0; j < mat->getCols(); j++)
		{
			result->addData(mat->getData(i, j) / div, i, j);
		}
	}

	return result;
}

// Matrix constant sum
std::shared_ptr<matrix> matConstSum(double sum, std::shared_ptr<matrix> mat)
{
	std::shared_ptr<matrix> result = std::make_shared<matrix>(mat->getRows(), mat->getCols());

	for (int i = 0; i < mat->getRows(); i++)
	{
		for (int j = 0; j < mat->getCols(); j++)
		{
			result->addData(mat->getData(i, j) + sum, i, j);
		}
	}

	return result;
}

// Matrix constant subtractor
std::shared_ptr<matrix> matConstSub(double sub, std::shared_ptr<matrix> mat)
{
	std::shared_ptr<matrix> result = std::make_shared<matrix>(mat->getRows(), mat->getCols());

	for (int i = 0; i < mat->getRows(); i++)
	{
		for (int j = 0; j < mat->getCols(); j++)
		{
			result->addData(mat->getData(i, j) - sub, i, j);
		}
	}

	return result;
}

// Matrix minor build
std::shared_ptr<matrix> matMinor(std::shared_ptr<matrix> mat, int row, int col)
{
	std::shared_ptr<matrix> calc = std::make_shared<matrix>(mat->getRows() - 1, mat->getCols() - 1);

	for (int i = 0; i < mat->getRows(); i++)
	{
		for (int j = 0; j < mat->getCols(); j++)
		{
			if (i != row && j != col)
			{
				int a = i;
				int b = j;
				if (i > row)
				{
					a--;
				}
				if (j > col)
				{
					b--;
				}
				calc->addData(mat->getData(i, j), a, b);
			}
		}
	}

	return calc;
}

// Matrix determinant calculator
double matDet(std::shared_ptr<matrix> mat)
{
	double det = 0;

	if (mat->getRows() == 2)
	{
		det = (mat->getData(0, 0) * mat->getData(1, 1)) - (mat->getData(0, 1) * mat->getData(1, 0));
	}
	else
	{
		for (int a = 0; a < mat->getCols(); a++)
		{
			std::shared_ptr<matrix> calc = matMinor(mat, 0, a);

			if (a % 2 == 0)
			{
				det += mat->getData(0, a) * (matDet(calc));
			}
			else
			{
				det -= mat->getData(0, a) * (matDet(calc));
			}
		}
	}

	return det;
}

// Matrix inverter
std::shared_ptr<matrix> matInv(std::shared_ptr<matrix> mat)
{
	double det = matDet(mat);
	std::shared_ptr<matrix> calc = std::make_shared<matrix>(mat->getRows(), mat->getCols());

	if (mat->getRows() == 1)
	{
		calc->addData(1 / mat->getData(0, 0), 0, 0);
	}
	else if (mat->getRows() == 2)
	{
		calc->addData(mat->getData(1, 1) / det, 0, 0);
		calc->addData(-mat->getData(0, 1) / det, 0, 1);
		calc->addData(-mat->getData(1, 0) / det, 1, 0);
		calc->addData(mat->getData(0, 0) / det, 1, 1);
	}
	else
	{
		std::shared_ptr<matrix> cofactors = std::make_shared<matrix>(mat->getRows(), mat->getCols());
		std::shared_ptr<matrix> adjugate = std::make_shared<matrix>(mat->getRows(), mat->getCols());

		for (int i = 0; i < mat->getRows(); i++)
		{
			for (int j = 0; j < mat->getCols(); j++)
			{
				if (((i % 2 == 0) && (j % 2 == 0)) || ((i % 2 != 0) && (j % 2 != 0)))
				{
					cofactors->addData(matDet(matMinor(mat, i, j)), i, j);
				}
				else
				{
					cofactors->addData(-matDet(matMinor(mat, i, j)), i, j);
				}
			}
		}

		for (int i = 0; i < cofactors->getRows(); i++)
		{
			for (int j = i; j < cofactors->getCols(); j++)
			{
				if (i == j)
				{
					adjugate->addData(cofactors->getData(i, j), i, j);
				}
				else
				{
					adjugate->addData(cofactors->getData(i, j), j, i);
					adjugate->addData(cofactors->getData(j, i), i, j);
				}
			}
		}

		for (int i = 0; i < adjugate->getRows(); i++)
		{
			for (int j = 0; j < adjugate->getCols(); j++)
			{
				calc->addData(adjugate->getData(i, j) / det, i, j);
			}
		}
	}

	return calc;
}

// Matrix sigmoid calculation (fnet)
std::shared_ptr<matrix> matSig(std::shared_ptr<matrix> mat)
{
	std::shared_ptr<matrix> result = std::make_shared<matrix>(mat->getRows(), mat->getCols());

	for (int i = 0; i < mat->getRows(); i++)
	{
		for (int j = 0; j < mat->getCols(); j++)
		{
			result->addData(sigmoid(mat->getData(i, j)), i, j);
		}
	}

	return result;
}

// Matrix derivative calculation
std::shared_ptr<matrix> matDeriv(std::shared_ptr<matrix> mat)
{
	return matScalarMult(mat, matConstSub(1, mat));
}


//------------------------------------------------- Perceptron Functions -----------------------------------------------------------

// Perceptron activation function
int actFunc(std::shared_ptr<matrix> dataX, int i)
{
	double result = 0;

	for (int j = 0; j < dataX->getCols(); j++)
	{
		result += W->getData(0, j) * dataX->getData(i, j);
	}

	result += bias;

	return result > 0 ? 1 : -1;
}

// Perceptron wieghts update
void train(std::shared_ptr<matrix> dataX, double Y, int i, int fnet, double learnRate)
{
	for (int j = 0; j < dataX->getCols(); j++)
	{
		W->sumData((learnRate * (Y - fnet) * dataX->getData(i, j)), 0, j);
	}
	bias += learnRate * (Y - fnet);
}

// Perceptron training
void perceptronTrain(std::shared_ptr<matrix> dataX, std::shared_ptr<matrix> dataY, double learnRate, int iterations)
{
	W = std::make_shared<matrix>(1, dataX->getCols());

	for (int j = 0; j < dataX->getCols(); j++)
	{
		W->fillRand(0, 1);
	}
	
	bias = 1;

	cout << "                                        Training progress:" << endl;
	cout << "0%----------------------------------------------50%---------------------------------------------100%" << endl;


	for (int t = 0; t < iterations; t++)
	{
		if (t % (iterations / 100) == 0) { cout << "#"; }

		for (int i = 0; i < dataX->getRows(); i++)
		{
			int fnet = actFunc(dataX, i);

			train(dataX, dataY->getData(i, 0), i, fnet, learnRate);
		}
	}

	cout << endl << endl;
}

// Perceptron test
void perceptronTest(std::shared_ptr<matrix> dataX, std::shared_ptr<matrix> dataY)
{
	W->print("W");

	cout << "Bias = " << bias << endl << endl;

	for (int i = 0; i < dataX->getRows(); i++)
	{
		cout << "Data: ";
		for (int j = 0; j < dataX->getCols(); j++)
		{
			cout << dataX->getData(i, j);

			if (j < dataX->getCols() - 1)
			{
				cout << ", ";
			}
		}
		cout << "      \tResult: " << actFunc(dataX, i) << "\tExpected: " << dataY->getData(i, 0) << endl;
	}
}

int main()
{
	srand(time(NULL));

	// AND testing
	cout << "AND training:" << endl << endl;
	perceptronTrain(andInData(), andOutData(), 0.1, 10000000);
	perceptronTest(andInData(), andOutData());

	// OR testing
	cout << endl << endl << "OR training:" << endl << endl;
	perceptronTrain(orInData(), orOutData(), 0.1, 10000000);
	perceptronTest(orInData(), orOutData());

	// XOR testing
	cout << endl << endl << "XOR training:" << endl << endl;
	perceptronTrain(xorInData(), xorOutData(), 0.1, 10000000);
	perceptronTest(xorInData(), xorOutData());

	// Iris Flower testing
	cout << endl << endl << "Iris Flower training:" << endl << endl;
	perceptronTrain(irisInData(), irisOutData(), 0.1, 1000000);
	perceptronTest(irisInData(), irisOutData());


	cin.get();
}
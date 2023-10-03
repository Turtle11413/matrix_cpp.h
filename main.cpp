#include <iostream>

class Matrix {
	private:
		int rows_, cols_;
		double** matrix_;
		void allocate_matrix(int rows, int cols);
	
	public:
		Matrix();
		Matrix(int rows, int cols);
		~Matrix();

		void fillMatrix();
		void printMatrix();
};

Matrix::Matrix() {
	rows_ = 1;
	cols_ = 1;
	allocate_matrix(rows_, cols_);
}

Matrix::Matrix(int rows, int cols) {
	if (rows_ < 1 || cols_ < 1)
		throw std::logic_error("Rows and columns cannot be < 1");
	rows_ = rows;
	cols_ = cols;
	allocate_matrix(rows, cols);
}

Matrix::~Matrix() {
	for (int i = 0; i < rows_; ++i)
		delete matrix_[i];
	delete matrix_;
}

void Matrix::allocate_matrix(int rows, int cols) {
	matrix_ = new double*[rows_];
	for (int i = 0; i < rows_; ++i) {
		matrix_[i] = new double[cols_];
	}
}

void Matrix::fillMatrix() {
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j)
			this->matrix_[i][j] = rows_ * i + j + 1;
	}
}

void Matrix::printMatrix() {
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j)
			std::cout << matrix_[i][j] << " ";
		std::cout << "\n";
	}
}

int main() {
	Matrix m1;
	m1.fillMatrix();
	m1.printMatrix();
}


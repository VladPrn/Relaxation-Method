//Класс, решающий систему уравнений по методу релаксации
class Task {
private:
	int n;
	double** matrix;
	double* b;
	double e;

public:
	Task(int n);
	~Task();
	//Установить значение ячейки матрицы
	void setCell(int i, int j, double value);
	//Установить значение свободного члена
	void setB(int i, double value);
	//Установить допустимое значение погрешности
	void setE(double e);
	//Получить решение задачи
	double* solve();
private:
	//Привести матрицу и свободные члены к требуемуму виду
	void format(double** nmatrix, double* nb);
	//Получить значения невязок
	void getR(double** nmatrix, double* nb, double* r, double* x);
	//Получить максимальную невязку
	double getMaxR(double* r, int& index);
	//Релаксировать вектор x
	void realX(double* x, double rMax, int index);
	//Релаксировать вектор невязок
	void realR(double** nmatrix, double* r, double rMax, int index);
	//Проверить допустимо ли решение
	bool check(double* r);
};

Task::Task(int n) {
	this->n = n;
	this->matrix = new double*[n];
	this->b = new double[n];
	for (int i = 0; i < n; i++) {
		this->matrix[i] = new double[n];
	}
}

Task::~Task() {
	for (int i = 0; i < n; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
	delete[] b;
}

void Task::setCell(int i, int j, double value) {
	matrix[i][j] = value;
}

void Task::setB(int i, double value) {
	b[i] = value;
}

void Task::setE(double e) {
	this->e = e;
}

double* Task::solve() {
	double** nmatrix = new double*[n];
	double* nb = new double[n];
	double* r = new double[n];
	double* x = new double[n];
	for (int i = 0; i < n; i++) {
		nmatrix[i] = new double[n];
		x[i] = 0;
	}

	format(nmatrix, nb);
	getR(nmatrix, nb, r, x);
	while (!check(r)) {
		int index;
		double maxR = getMaxR(r, index);
		realX(x, maxR, index);
		realR(nmatrix, r, maxR, index);
	}


	for (int i = 0; i < n; i++) {
		delete[] nmatrix[i];
	}
	delete[] nmatrix;
	delete[] nb;
	delete[] r;

	return x;
}

void Task::format(double** nmatrix, double* nb) {
	for (int i = 0; i < n; i++) {
		nb[i] = b[i] / matrix[i][i];
		for (int j = 0; j < n; j++) {
			nmatrix[i][j] = matrix[i][j] / matrix[i][i];
		}
	}
}

void Task::getR(double** nmatrix, double* nb, double* r, double* x) {
	for (int i = 0; i < n; i++) {
		r[i] = nb[i];
		for (int j = 0; j < n; j++) {
			if (i != j) {
				r[i] += nmatrix[i][j] * x[j];
			}
			else {
				r[i] -= x[j];
			}
		}
	}
}

double Task::getMaxR(double* r, int& index) {
	double res = 0;
	for (int i = 0; i < n; i++) {
		if (abs(res) < abs(r[i])) {
			res = r[i];
			index = i;
		}
	}
	return res;
}

void Task::realX(double* x, double rMax, int index) {
	x[index] += rMax;
}

void Task::realR(double** nmatrix, double* r, double rMax, int index) {
	for (int i = 0; i < n; i++) {
		if (i != index) {
			r[i] -= nmatrix[i][index] * rMax;
		}
		else {
			r[i] = 0;
		}
	}
}

bool Task::check(double* r) {
	for (int i = 0; i < n; i++) {
		if (abs(r[i]) > e) {
			return false;
		}
	}
	return true;
}
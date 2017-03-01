#include <iostream>
#include <conio.h>
#include "task.h"

using namespace std;

void main() {
	int n;
	double e, tmp;
	cin >> n >> e;
	Task t = Task(n);
	t.setE(e);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> tmp;
			t.setCell(i, j, tmp);
		}
		cin >> tmp;
		t.setB(i, tmp);
	}
	
	double* x = t.solve();
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << x[i] << " ";
	}

	_getch();
}
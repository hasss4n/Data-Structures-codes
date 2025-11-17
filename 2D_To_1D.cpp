// Hassan Saeed
// BSAI-F24/A
// 241384

#include <iostream>
using namespace std;

int main() {
	const int n = 4;

	//simple 2D array
	int counter = 1;
	int arr[n][n]; 
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arr[i][j] = counter++;

		}
	}
	cout << "The matrix is: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

	// row wise 1D mapping of the 2d array Along with its reverse mapping

	int row[n * n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int index = i * n + j;
			row[index] = arr[i][j];
		}
	}
	cout << endl<< "Row wise mapping:"<< endl;
	for (int k = 0; k < n * n; k++) {
		cout << row[k] << " ";
	}
	cout << endl << endl << "Reverse row mapping: " << endl;
	for (int k = 0; k < n*n; k++) {
		int i = k / n;
		int j = k % n;
		cout << "index " << k << " -> ( " << i << "," << j << " ) = " << row[k] << endl;
	}

	// column wise mapping of the 2D array and its reverse mapping

	int column[n * n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int index = j * n + i;
			column[index] = arr[i][j];
		}
	}
	cout << endl << "Column wise mapping:" << endl;
	for (int k = 0; k < n * n; k++) {
		cout << column[k] << " ";
	}
	cout << endl<< endl<< "Reverse comlumn mapping: " << endl;
	for (int k = 0; k < n * n; k++) {
		int i = k / n;
		int j = k % n;
		cout << "index " << k << " -> ( " << i << "," << j << " ) = " << column[k] << endl;
	}

	// special matrix(Diagonal mapping)

	int diagnol[n];
	for (int i = 0; i < n; i++) {
		diagnol[i] = arr[i][i];
	}
	cout << "\nDiagonal mapping:\n";
	for (int i = 0; i < n; i++) {
		cout << diagnol[i] << " ";
	}
	cout << "\n\nReverse diagonal mapping:\n";
	for (int k = 0; k < n; k++) {
		cout << "index " << k << " -> (" << k << "," << k << ") = " << diagnol[k] << "\n";
	}
	
	// Special Matrice(Upper triangular mapping)

	int uppertriangle[n * (n + 1) / 2];
	int ind=0;
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			uppertriangle[ind++] = arr[i][j];
		}
	}
	cout << "\nUpper Triangle Mapping: \n";
	for (int i = 0; i < n *(n+1)/2 ; i++) {
		cout << uppertriangle[i] << " ";
	}
	cout << "\n\nReverse uppertraingular mapping:\n";
	ind = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			cout << "index "<< ind << " -> (" << i << "," << j << ") = " << uppertriangle[ind] << "\n";
			ind++;
		}
	}

	// Special Matrice(Summetric matrix)

	int symmetric[n * (n + 1) / 2];
	ind = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			symmetric[ind++] = arr[i][j];
		}
	}
	cout << "\nSymmetric storage (upper half):\n";
	for (int i = 0; i < n*(n+1)/2; i++) cout << symmetric[i] << " ";
	cout << "\n\nReconstructed symmetric matrix:\n";
	ind = 0;
	int s[n][n] = { 0 };
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			s[i][j] = symmetric[ind];
			s[j][i] = symmetric[ind];
			ind++;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << s[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}


bool is_inside(double v1x, double v1y,
	double v2x, double v2y,
	double v3x, double v3y,
	double px, double py)
{
	//S - the area of the original triangle.
	//S1,S2,S3 - the areas of three triangles (which can be equal to zero if there is some sort of
	//figure's degeneracy into lines or points). These triangles are the result of connecting 
	//the original point with the vertices.
	double S, S1, S2, S3;
	//The formula of the triangle's area (depended from its coordinates) is rather easy to obtain by compounding all of the
	//vertices with one of the coordinate axes (in addition, it's possible to do by moving the figure to the first quarter).
	//After these simple transformations you'll have three trapezes. If you deduct the area of the third trapeze
	//from the sum of the first trapeze and the second one, you'll get the following resulting formula.
	S = ((v1x - v3x) * (v2y - v3y) - (v2x - v3x) * (v1y - v3y)) / 2.0; if (S < 0) S = -S;
	S1 = ((px - v3x) * (v2y - v3y) - (v2x - v3x) * (py - v3y)) / 2.0; if (S1 < 0) S1 = -S1;
	S2 = ((v1x - v3x) * (py - v3y) - (px - v3x) * (v1y - v3y)) / 2.0; if (S2 < 0) S2 = -S2;
	S3 = ((v1x - px) * (v2y - py) - (v2x - px) * (v1y - py)) / 2.0; if (S3 < 0) S3 = -S3;
	//If the point is outside of the triangle then S>S1+S2+S3; otherwise the point can be situated on the border of the figure.
	//In this case one of the areas equals zero if we've got on the edge, two areas are equal to zero if we've got on
	//some vertices, and all of the areas can equal to zero if our triangle is a point.
	return ((S == S1 + S2 + S3) && (S1 != 0) && (S2 != 0) && (S3 != 0));
}


unsigned char median(const unsigned char arr[], int N)
{	
	//In this task we deal with the array of symbols. We must compare their codes (from 0 to 255)
	//and find a symbol which is the median among other symbols from the point of view of their codes.
	//To reach the goals we have to build an array of frequences (like in the probability theory and statistics).
	//It will be a histogram: the X-axis will range from 0 to 255 (it will be the index of the array)
	//and the Y-axis will represent the frequences of these indexes.
	int histogram[256] = { 0, 0 };
	for (int i = 0; i < N; ++i) ++histogram[(int)(arr[i])];
	int N1 = N;
	int conditional_N = N / 2;
	for (int i = 0; i < 256; ++i) {
		N1 -= histogram[i];
		if (N1 <= conditional_N) return (unsigned char)(i);
	}
	return 0;
}


double determinant(const double mat[], int M)
{
	//Here we're making a copy of the original array in order to change it.
	double** matrix = new double* [M];
	for (int i = 0; i < M; ++i) {
		matrix[i] = new double[M];
		for (int j = 0; j < M; ++j) {
			matrix[i][j] = mat[i * M + j];
		}
	}
	//Forming a triangular matrix
	double lambda; //lambda - is a coefficient needed to form a triangular matrix
	double* tmp; //tmp - is a temporary cell
	double determ = 1; //By this variable we'll create a "cumulative" determinant
	for (int i = 0; i < M; ++i) { //We're following the elements of the main diagonal and...
		if (matrix[i][i] == 0) { //...if the element of the main diagonal is equal to zero, we must change rows' places
			for (int k = i + 1; k < M; ++k) //We're running down within the column, verifing if there is some row with a non-zero element
				if (matrix[k][i] != 0) { // If we've found such a row...					
					tmp = matrix[i]; //...we must change the pointers to these rows using the rule of "three glasses"
					matrix[i] = matrix[k];
					matrix[k] = tmp;
					determ *= (-1); //As a result, the sign of the determinant will be reversed
					break;//Here we should escape from the cycle
				}
		}
		if (matrix[i][i] != 0) {//It's quite possible that we've failed to get some row with a non-zero element. But if we've done it...
			for (int ii = i + 1; ii < M; ++ii) {//...we must consider all the "sub"-rows, which are below the current one
				lambda = -matrix[ii][i] / matrix[i][i]; //First of all, we must calculate lambda, which is used to form a triangular matrix
				if (lambda != 0) { //If lambda is equal to zero there is no point in further calculations. Âut if it's no so...
					for (int j = 0; j < M; ++j) {//...we must summarize the "sub"-row and the original one multiplied by lambda
						matrix[ii][j] += lambda * matrix[i][j];
					}
				}
			}
		}
		determ *= matrix[i][i]; // Multiplying of the elements of the main diagonal in the triangular matrix
		if (determ == 0) return 0; //If the "cumulative" determinant is equal to zero, there is no point in further calculations.
	}
	//In conclusion we end the work with dynamic memory.
	for (int i = 0; i < M; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
	return determ;
}
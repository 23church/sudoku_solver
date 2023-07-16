#include "stdafx.h"
/* Sudoku solving program
Arrays contain X,Y pairs for the location of each number in successive boxes. General array setup:
[x0][y0][x1][y1][x2][y2][x3][y3][x4][y4][x5][y5][x6][y6][x7][y7][x8][y8]
x4, y4: the X and Y position of the number in box 4.
Boxes are numbered 0 to 8. How boxes are numbered relative to a normal sudoku:
 0  1  2  <-- box columns == box%3
[0][1][2] 0 :
[3][4][5] 1 : box rows == box/3
[6][7][8] 2 :
X/Y values can have values from 2 to 10, starting at 2 from the left/top, and ending at 10 at the right/bottom.
They go from 2-10 (instead of 1-9 or 0-8) so that a unique position can be determined for the first box row/column.*/
int one[18]={0}, two[18]={0}, thr[18]={0}, fou[18]={0}, fiv[18]={0}, six[18]={0}, sev[18]={0}, eig[18]={0}, nin[18]={0};
int xCheck(int num[18], int box){ //finds an X position
	int boxCol=box%3, colSum=9*boxCol+9, xPos=num[2*boxCol]+num[2*boxCol+6]+num[2*boxCol+12];
	if(colSum-xPos < (3*boxCol)+5){return colSum-xPos;} //if less than 2 in the box column, X cannot be easily found
	else{return 0;}}
int yCheck(int num[18], int box){ //finds a Y position
	int boxRow=box/3, rowSum=9*boxRow+9, yPos=num[6*boxRow+1]+num[6*boxRow+3]+num[6*boxRow+5];
	if(rowSum-yPos < 3*boxRow+5){return rowSum-yPos;} //if less than 2 in the box row, Y cannot be easily found
	else{return 0;}}
int xCheckIndirect(int num[18], int row, int box){ //If Y position is known, but X position is not.
	int boxCol=box%3, xPos=num[2*boxCol]+num[2*boxCol+6]+num[2*boxCol+12], xTot=0;
	if(one[2*box+1] == row){xTot+=one[2*box];} //check box for numbers at known Y position
	if(two[2*box+1] == row){xTot+=two[2*box];}
	if(thr[2*box+1] == row){xTot+=thr[2*box];}
	if(fou[2*box+1] == row){xTot+=fou[2*box];}
	if(fiv[2*box+1] == row){xTot+=fiv[2*box];}
	if(six[2*box+1] == row){xTot+=six[2*box];}
	if(sev[2*box+1] == row){xTot+=sev[2*box];}
	if(eig[2*box+1] == row){xTot+=eig[2*box];}
	if(nin[2*box+1] == row){xTot+=nin[2*box];}
	if(9*boxCol+9-xTot < 3*boxCol+5){return 9*boxCol+9-xTot;} //two numbers at same Y 
	else if((xTot != xPos) && xTot && xPos){return 9*boxCol+9-(xTot+xPos);} //one number at same Y, one number in same box column but different X
	else{return 0;}}
int yCheckIndirect(int num[18], int col, int box){ //If X position is known, but Y position is not.
	int boxRow=box/3, yPos=num[6*boxRow+1]+num[6*boxRow+3]+num[6*boxRow+5], yTot=0;
	if(one[2*box] == col){yTot+=one[2*box+1];} //check box for numbers at known X position
	if(two[2*box] == col){yTot+=two[2*box+1];}
	if(thr[2*box] == col){yTot+=thr[2*box+1];}
	if(fou[2*box] == col){yTot+=fou[2*box+1];}
	if(fiv[2*box] == col){yTot+=fiv[2*box+1];}
	if(six[2*box] == col){yTot+=six[2*box+1];}
	if(sev[2*box] == col){yTot+=sev[2*box+1];}
	if(eig[2*box] == col){yTot+=eig[2*box+1];}
	if(nin[2*box] == col){yTot+=nin[2*box+1];}
	if(9*boxRow+9-yTot < 3*boxRow+5){return 9*boxRow+9-yTot;} //two numbers at same X
	else if((yTot != yPos) && yTot && yPos){return 9*boxRow+9-(yTot+yPos);} //one number at same X, one number in same box row but different Y
	else{return 0;}}
int xCheckObscure(int num[18], int box){
	int boxCol=box%3, boxRow=box/3, j=3*boxCol+2, k=3*boxCol+5, m=0, xLoc[3]={0},
		xVal=num[2*boxCol]+num[2*boxCol+6]+num[2*boxCol+12], xPos=(9*boxCol+9)-xVal,
		yVal=num[6*boxRow+1]+num[6*boxRow+3]+num[6*boxRow+5];
	if(yVal < (3*boxRow+5)){
		while(j < k){
			if(j != xVal){
				if((one[2*box] == j) && (one[2*box+1] != yVal) && one[2*box+1]){xLoc[m]++;}
				if((two[2*box] == j) && (two[2*box+1] != yVal) && two[2*box+1]){xLoc[m]++;}
				if((thr[2*box] == j) && (thr[2*box+1] != yVal) && thr[2*box+1]){xLoc[m]++;}
				if((fou[2*box] == j) && (fou[2*box+1] != yVal) && fou[2*box+1]){xLoc[m]++;}
				if((fiv[2*box] == j) && (fiv[2*box+1] != yVal) && fiv[2*box+1]){xLoc[m]++;}
				if((six[2*box] == j) && (six[2*box+1] != yVal) && six[2*box+1]){xLoc[m]++;}
				if((sev[2*box] == j) && (sev[2*box+1] != yVal) && sev[2*box+1]){xLoc[m]++;}
				if((eig[2*box] == j) && (eig[2*box+1] != yVal) && eig[2*box+1]){xLoc[m]++;}
				if((nin[2*box] == j) && (nin[2*box+1] != yVal) && nin[2*box+1]){xLoc[m]++;}}
			if(((xLoc[m] == 2) && yVal) || (xLoc[m] == 3)){xPos-=j;} m++; j++;}}
	if(xPos < k){return xPos;}
	else{return 0;}}
int yCheckObscure(int num[18], int box){
	int boxCol=box%3, boxRow=box/3, j=3*boxRow+2, k=3*boxRow+5, m=0, yLoc[3]={0},
		xVal=num[2*boxCol]+num[2*boxCol+6]+num[2*boxCol+12],
		yVal=num[6*boxRow+1]+num[6*boxRow+3]+num[6*boxRow+5], yPos=(9*boxRow+9)-yVal;
	if(xVal < (3*boxCol+5)){
		while(j < k){
			if(j != yVal){
				if((one[2*box+1] == j) && (one[2*box] != xVal) && one[2*box]){yLoc[m]++;}
				if((two[2*box+1] == j) && (two[2*box] != xVal) && two[2*box]){yLoc[m]++;}
				if((thr[2*box+1] == j) && (thr[2*box] != xVal) && thr[2*box]){yLoc[m]++;}
				if((fou[2*box+1] == j) && (fou[2*box] != xVal) && fou[2*box]){yLoc[m]++;}
				if((fiv[2*box+1] == j) && (fiv[2*box] != xVal) && fiv[2*box]){yLoc[m]++;}
				if((six[2*box+1] == j) && (six[2*box] != xVal) && six[2*box]){yLoc[m]++;}
				if((sev[2*box+1] == j) && (sev[2*box] != xVal) && sev[2*box]){yLoc[m]++;}
				if((eig[2*box+1] == j) && (eig[2*box] != xVal) && eig[2*box]){yLoc[m]++;}
				if((nin[2*box+1] == j) && (nin[2*box] != xVal) && nin[2*box]){yLoc[m]++;}}
			if(((yLoc[m] == 2) && xVal) || (yLoc[m] == 3)){yPos-=j;} m++; j++;}}
	if(yPos < k){return yPos;}
	else{return 0;}}
int rowCheck(int num[18], int box){
	int boxRow=box/3, j=3*boxRow, k=3*boxRow+3, n=3*boxRow+5, r=0, y=3*boxRow+2, row[30]={0};
	while(y < n){
		if((y != num[6*boxRow+1]) && (y != num[6*boxRow+3]) && (y != num[6*boxRow+5])){
			while(j < k){
				if(one[2*j+1] == y){row[10*r]++; row[10*r+1] = one[2*j];}
				if(two[2*j+1] == y){row[10*r]++; row[10*r+2] = two[2*j];}
				if(thr[2*j+1] == y){row[10*r]++; row[10*r+3] = thr[2*j];}
				if(fou[2*j+1] == y){row[10*r]++; row[10*r+4] = fou[2*j];}
				if(fiv[2*j+1] == y){row[10*r]++; row[10*r+5] = fiv[2*j];}
				if(six[2*j+1] == y){row[10*r]++; row[10*r+6] = six[2*j];}
				if(sev[2*j+1] == y){row[10*r]++; row[10*r+7] = sev[2*j];}
				if(eig[2*j+1] == y){row[10*r]++; row[10*r+8] = eig[2*j];}
				if(nin[2*j+1] == y){row[10*r]++; row[10*r+9] = nin[2*j];} j++;} j = 3*boxRow;
			if(row[10*r] == 8){return y;}} y++; r++;}
	return 0;}
int colCheck(int num[18], int box){
	int boxCol=box%3, j=boxCol, k=boxCol+7, n=3*boxCol+5, r=0, x=3*boxCol+2, col[30]={0};
	while(x < n){
		if((x != num[2*boxCol]) && (x != num[2*boxCol+6]) && (x != num[2*boxCol+12])){
			while(j < k){
				if(one[2*j] == x){col[10*r]++; col[10*r+1] = one[2*j+1];}
				if(two[2*j] == x){col[10*r]++; col[10*r+2] = two[2*j+1];}
				if(thr[2*j] == x){col[10*r]++; col[10*r+3] = thr[2*j+1];}
				if(fou[2*j] == x){col[10*r]++; col[10*r+4] = fou[2*j+1];}
				if(fiv[2*j] == x){col[10*r]++; col[10*r+5] = fiv[2*j+1];}
				if(six[2*j] == x){col[10*r]++; col[10*r+6] = six[2*j+1];}
				if(sev[2*j] == x){col[10*r]++; col[10*r+7] = sev[2*j+1];}
				if(eig[2*j] == x){col[10*r]++; col[10*r+8] = eig[2*j+1];}
				if(nin[2*j] == x){col[10*r]++; col[10*r+9] = nin[2*j+1];} j+=3;} j = boxCol;
			if(col[10*r] == 8){return x;}} x++; r++;}
	return 0;}
void colCheckIndirect(int num[18], int box){
	int boxCol=box%3, b=boxCol, i=0, xVals[3]={0}, yVals[3]={num[2*boxCol+1], num[2*boxCol+7], num[2*boxCol+13]};
	if(num[2*boxCol] || num[2*boxCol+6] || num[2*boxCol+12]){return;}
	if(yVals[0] == 0){
		if(yVals[1] == 0){return;}
		else if(yVals[2] == 0){return;}}
	else if(yVals[1] == 0){
		if(yVals[2] == 0){return;}}
	while(b < boxCol+7){
		if(one[2*b+1] == yVals[i] && one[2*b]){xVals[i] = one[2*b];} //for a number that has Y values determined in 2 boxes in the same
		if(two[2*b+1] == yVals[i] && two[2*b]){xVals[i] = two[2*b];} //box column, but no X or Y in the third box in that same box column.
		if(thr[2*b+1] == yVals[i] && thr[2*b]){xVals[i] = thr[2*b];} //checks for a taken square in each of the same rows of the boxes
		if(fou[2*b+1] == yVals[i] && fou[2*b]){xVals[i] = fou[2*b];} //with determined Y values. if there are 2 taken squares, and they
		if(fiv[2*b+1] == yVals[i] && fiv[2*b]){xVals[i] = fiv[2*b];} //have the same X value, then the number must have that X value in
		if(six[2*b+1] == yVals[i] && six[2*b]){xVals[i] = six[2*b];} //the third box, as neither of the numbers in the other 2 boxes can
		if(sev[2*b+1] == yVals[i] && sev[2*b]){xVals[i] = sev[2*b];} //have that X value.
		if(eig[2*b+1] == yVals[i] && eig[2*b]){xVals[i] = eig[2*b];}
		if(nin[2*b+1] == yVals[i] && nin[2*b]){xVals[i] = nin[2*b];} b+=3; i++;}
	if(xVals[1] == xVals[2] && xVals[2]){num[2*boxCol] = xVals[1]; return;}
	else if(xVals[0] == xVals[2] && xVals[0]){num[2*boxCol+6] = xVals[2]; return;}
	else if(xVals[0] == xVals[1] && xVals[1]){num[2*boxCol+12] = xVals[0]; return;}}
int posCheck(int xVal, int yVal, int box){ //to ensure that a location is not already taken
	if((one[2*box] == xVal) && (one[2*box+1] == yVal)){return 0;}
	else if((two[2*box] == xVal) && (two[2*box+1] == yVal)){return 0;}
	else if((thr[2*box] == xVal) && (thr[2*box+1] == yVal)){return 0;}
	else if((fou[2*box] == xVal) && (fou[2*box+1] == yVal)){return 0;}
	else if((fiv[2*box] == xVal) && (fiv[2*box+1] == yVal)){return 0;}
	else if((six[2*box] == xVal) && (six[2*box+1] == yVal)){return 0;}
	else if((sev[2*box] == xVal) && (sev[2*box+1] == yVal)){return 0;}
	else if((eig[2*box] == xVal) && (eig[2*box+1] == yVal)){return 0;}
	else if((nin[2*box] == xVal) && (nin[2*box+1] == yVal)){return 0;}
	else{return 1;}}
void numPlace(int num[18]){int i=0, xVal, yVal;
	while(i < 17){
		if(!(num[i] || num[i+1])){ //if X and Y are not known
			xVal = xCheck(num, (i/2)); yVal = yCheck(num, (i/2)); //check if X and Y position are easily determined
			if(xVal && yVal){
				num[i] = xVal; num[i+1] = yVal;}
			else if(yVal){num[i+1] = yVal; //if Y is known
				xVal = xCheckIndirect(num, yVal, (i/2));
				if(xVal){num[i] = xVal;}
				else{colCheckIndirect(num, (i/2));}}
			else if(xVal){num[i] = xVal; //if X is known
				yVal = yCheckIndirect(num, xVal, (i/2));
				if(yVal && posCheck(xVal, yVal, (i/2))){num[i+1] = yVal;}}
			else{xVal = xCheckObscure(num, (i/2)); //if neither X nor Y is known
				yVal = yCheckObscure(num, (i/2));
				if(xVal && yVal){num[i] = xVal; num[i+1] = yVal;} //if X and Y were determined obscurely
				else if(xVal){num[i] = xVal; //if X was found
					yVal = yCheckIndirect(num, xVal, (i/2));
					if(yVal){num[i+1] = yVal;}}
				else if(yVal){num[i+1] = yVal; //if Y was found
					xVal = xCheckIndirect(num, yVal, (i/2));
					if(xVal){num[i] = xVal;}
					else{colCheckIndirect(num, (i/2));}}
				else{yVal = rowCheck(num, (i/2)); //if neither were found, check to see if it's the only missing value from a column/row
					xVal = colCheck(num, (i/2));
					if(xVal && yVal && posCheck(xVal, yVal, (i/2))){num[i] = xVal; num[i+1] = yVal;}
					else if(xVal && posCheck(xVal, yVal, (i/2))){num[i] = xVal;}
					else if(yVal && posCheck(xVal, yVal, (i/2))){num[i+1] = yVal; colCheckIndirect(num, (i/2));}}}}
		else if(num[i] && (num[i+1] == 0)){yVal = yCheck(num, (i/2)); xVal = num[i]; //if X was already known
			if(yVal){num[i+1] = yVal;}
			else{yVal = yCheckIndirect(num, xVal, (i/2));
				if(yVal){num[i+1] = yVal;}
				else{yVal = yCheckObscure(num, (i/2));
					if(yVal){num[i+1] = yVal;}}}}
		else if(num[i+1] && (num[i] == 0)){xVal = xCheck(num, (i/2)); yVal = num[i+1]; //if Y was already known
			if(xVal){num[i] = xVal;}
			else{xVal = xCheckIndirect(num, yVal, (i/2));
				if(xVal){num[i] = xVal;}
				else{xVal = xCheckObscure(num, (i/2));
					if(xVal){num[i] = xVal;}
					else{colCheckIndirect(num, (i/2));}}}}
		i+=2;}} //if X and Y cannot be determined indirectly (or are already known), move on to next box
int newTot(){int j=0, k=0; //calculates the total amount of numbers placed
	while(j < 17){
		if(one[j] && one[j+1]){k++;} //if both an X and Y value exist
		if(two[j] && two[j+1]){k++;}
		if(thr[j] && thr[j+1]){k++;}
		if(fou[j] && fou[j+1]){k++;}
		if(fiv[j] && fiv[j+1]){k++;}
		if(six[j] && six[j+1]){k++;}
		if(sev[j] && sev[j+1]){k++;}
		if(eig[j] && eig[j+1]){k++;}
		if(nin[j] && nin[j+1]){k++;} j+=2;}
	return k;}
int main(){int Sudoku[9][9] = {0}, j=0, tot=0;
	one[2] = 7; one[3] = 2; one[8] = 6; one[9] = 7;
	two[12] = 2; two[13] = 8;
	thr[0] = 2; thr[1] = 3; thr[2] = 6; thr[3] = 4; thr[4] = 8; thr[5] = 2; thr[16] = 10; thr[17] = 8;
	fou[4] = 10; fou[5] = 4; fou[6] = 4; fou[7] = 7; fou[16] = 8; fou[17] = 8;
	fiv[0] = 2; fiv[1] = 4; fiv[2] = 6; fiv[3] = 3; fiv[12] = 4; fiv[13] = 10;
	six[4] = 8; six[5] = 3; six[8] = 6; six[9] = 5; six[10] = 10; six[11] = 6; six[12] = 4; six[13] = 9;
	sev[0] = 4; sev[1] = 2; sev[6] = 2; sev[7] = 6; sev[10] = 9; sev[11] = 7; sev[14] = 6; sev[15] = 9; sev[16] = 8; sev[17] = 10;
	eig[0] = 4; eig[1] = 4; eig[6] = 3; eig[7] = 5; eig[14] = 6; eig[15] = 8; eig[16] = 10; eig[17] = 9;
	nin[10] = 8; nin[11] = 5; nin[14] = 5; nin[15] = 10;
	while(tot < 81){numPlace(one);
		numPlace(two); numPlace(thr);
		numPlace(fou); numPlace(fiv);
		numPlace(six); numPlace(sev);
		numPlace(eig); numPlace(nin);
		tot = newTot();}
	while(j < 17){
		Sudoku[one[j+1]-2][one[j]-2] = 1;
		Sudoku[two[j+1]-2][two[j]-2] = 2;
		Sudoku[thr[j+1]-2][thr[j]-2] = 3;
		Sudoku[fou[j+1]-2][fou[j]-2] = 4;
		Sudoku[fiv[j+1]-2][fiv[j]-2] = 5;
		Sudoku[six[j+1]-2][six[j]-2] = 6;
		Sudoku[sev[j+1]-2][sev[j]-2] = 7;
		Sudoku[eig[j+1]-2][eig[j]-2] = 8;
		Sudoku[nin[j+1]-2][nin[j]-2] = 9; j+=2;}
	for(int k=0; k < 9; k++){
		for(int l=0; l < 9; l++){
			printf("%d ", Sudoku[k][l]);}
		printf("\n");}
	system("pause");
	return 0;}
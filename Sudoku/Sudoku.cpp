#include "stdafx.h"
/* Sudoku solving program
Arrays contain X,Y pairs for the location of each number in successive boxes. General array setup:
[x0][y0][x1][y1][x2][y2][x3][y3][x4][y4][x5][y5][x6][y6][x7][y7][x8][y8]
x4,y4: the X and Y position of the number in box 4.
Boxes are numbered 0 to 8. How boxes are numbered relative to a normal sudoku:
 0  1  2  <-- box columns == box%3
[0][1][2] 0 :
[3][4][5] 1 : box rows == box/3
[6][7][8] 2 :
X/Y values can have values from 2 to 10, starting at 2 from the left/top, and ending at 10 at the right/bottom.
They go from 2-10 (instead of 1-9 or 0-8) so that a unique position can be determined for the first box row/column.*/
	boost::array<int, 18> one = {0}; boost::array<int, 18> two = {0};
	boost::array<int, 18> thr = {0}; boost::array<int, 18> fou = {0};
	boost::array<int, 18> fiv = {0}; boost::array<int, 18> six = {0};
	boost::array<int, 18> sev = {0}; boost::array<int, 18> eig = {0};
	boost::array<int, 18> nin = {0};
int xCheck(boost::array<int, 18> num, int box){ //finds an X position
	if(box%3 == 0){
		if(9-num[0]-num[6]-num[12] > 4){return 0;} //if less than 2 in the box column, X cannot be easily found
		else{return 9-(num[0]+num[6]+num[12]);}}
	else if(box%3 == 1){
		if(18-num[2]-num[8]-num[14] > 7){return 0;}
		else{return 18-(num[2]+num[8]+num[14]);}}
	else if(box%3 == 2){
		if(27-num[4]-num[10]-num[16] > 10){return 0;}
		else{return 27-(num[4]+num[10]+num[16]);}}
	else{return 0;}}
int yCheck(boost::array<int, 18> num, int box){ //finds a Y position
	if(box/3 == 0){
		if(9-(num[1]+num[3]+num[5]) > 4){return 0;} //if less than 2 in the box row, Y cannot be easily found
		else{return 9-(num[1]+num[3]+num[5]);}}
	else if(box/3 == 1){
		if(18-(num[7]+num[9]+num[11]) > 7){return 0;}
		else{return 18-(num[7]+num[9]+num[11]);}}
	else if(box/3 == 2){
		if(27-(num[13]+num[15]+num[17]) > 10){return 0;}
		else{return 27-(num[13]+num[15]+num[17]);}}
	else{return 0;}}
int xCheckIndirect(boost::array<int, 18> num, int row, int box){ //If Y position is known, but X position is not.
	int BoxCol=box%3, xTot=0, xVal=num[2*BoxCol]+num[2*BoxCol+6]+num[2*BoxCol+12];
	if(one[2*box+1] == row){xTot+=one[2*box];} //check box for numbers at known Y position
	if(two[2*box+1] == row){xTot+=two[2*box];}
	if(thr[2*box+1] == row){xTot+=thr[2*box];}
	if(fou[2*box+1] == row){xTot+=fou[2*box];}
	if(fiv[2*box+1] == row){xTot+=fiv[2*box];}
	if(six[2*box+1] == row){xTot+=six[2*box];}
	if(sev[2*box+1] == row){xTot+=sev[2*box];}
	if(eig[2*box+1] == row){xTot+=eig[2*box];}
	if(nin[2*box+1] == row){xTot+=nin[2*box];}
	if(9*BoxCol+9-xTot < 3*BoxCol+5){return 9*BoxCol+9-xTot;} //two numbers at same Y 
	else if(xTot != xVal){return 9*BoxCol+9-xTot-xVal;} //one number at same Y, one number in same box column, when: same Y != same box column
	else{return 0;}}
int yCheckIndirect(boost::array<int, 18> num, int col, int box){ //If X position is known, but Y position is not.
	int BoxRow=box/3, yTot=0, yVal=num[6*BoxRow+1]+num[6*BoxRow+3]+num[6*BoxRow+5];
	if(one[2*box] == col){yTot+=one[2*box+1];} //check box for numbers at known X position
	if(two[2*box] == col){yTot+=two[2*box+1];}
	if(thr[2*box] == col){yTot+=thr[2*box+1];}
	if(fou[2*box] == col){yTot+=fou[2*box+1];}
	if(fiv[2*box] == col){yTot+=fiv[2*box+1];}
	if(six[2*box] == col){yTot+=six[2*box+1];}
	if(sev[2*box] == col){yTot+=sev[2*box+1];}
	if(eig[2*box] == col){yTot+=eig[2*box+1];}
	if(nin[2*box] == col){yTot+=nin[2*box+1];}
	if(9*BoxRow+9-yTot < 3*BoxRow+5){return 9*BoxRow+9-yTot;} //two numbers at same X
	else if(yTot != yVal){return 9*BoxRow+9-yTot-yVal;} //one number at same X, one number in same box row, when: same X != same box row
	else{return 0;}}
int numCheckObscure(boost::array<int, 18> num, int box, int tot){ //if X and Y cannot be determined indirectly
/*The numLoc array is for checking occupied locations within a box to hopefully find an X or Y position with only one of either of them to go on. 
numLoc[0], numLoc[3], and numLoc[6] store the number of taken spaces in the first, second and third columns of the box respectively.
The 2 spaces following each are for the Y values of the first 2 numbers encountered in the column.*/
	int BoxRow=box/3, BoxCol=box%3, j=3*BoxCol+2, k=3*BoxCol+5, m=0, numLoc[9]={0},
	xPos=0, xVal=num[2*BoxCol]+num[2*BoxCol+6]+num[2*BoxCol+12],
	yPos=0, yVal=num[6*BoxRow+1]+num[6*BoxRow+3]+num[6*BoxRow+5], xValDiff, yValDiff;
	if(xVal || yVal){ //checks that there is one value in either the box row and box column
		xValDiff = 9*BoxCol+9-xVal, yValDiff = 9*BoxRow+9-yVal;
		while(j < k){
			if(j != xVal){ //skips the column already taken by the number in the box column, if there is one
				if(one[2*box+1] && (one[2*box+1] != yVal) && (one[2*box] == j)){numLoc[m]++; numLoc[m+1] = one[2*box+1];}
				if(two[2*box+1] && (two[2*box+1] != yVal) && (two[2*box] == j)){numLoc[m]++; //checks that a number /is not/ in the (potentially) occupied row and /is/ in the 
					if(numLoc[m+1]){numLoc[m+2] = two[2*box+1];}							 //(potentailly) unoccupied column. if so, saves the Y position of said number to
					else{numLoc[m+1] = two[2*box+1];}}										 //possibly determine the Y position of num
				if(thr[2*box+1] && (thr[2*box+1] != yVal) && (thr[2*box] == j)){numLoc[m]++;
					if(numLoc[m+1]){numLoc[m+2] = thr[2*box+1];}
					else{numLoc[m+1] = thr[2*box+1];}}
				if(fou[2*box+1] && (fou[2*box+1] != yVal) && (fou[2*box] == j)){numLoc[m]++;
					if(numLoc[m+1]){numLoc[m+2] = fou[2*box+1];}
					else{numLoc[m+1] = fou[2*box+1];}}
				if(fiv[2*box+1] && (fiv[2*box+1] != yVal) && (fiv[2*box] == j)){numLoc[m]++;
					if(numLoc[m+1]){numLoc[m+2] = fiv[2*box+1];}
					else{numLoc[m+1] = fiv[2*box+1];}}
				if(six[2*box+1] && (six[2*box+1] != yVal) && (six[2*box] == j)){numLoc[m]++;
					if(numLoc[m+1]){numLoc[m+2] = six[2*box+1];}
					else{numLoc[m+1] = six[2*box+1];}}
				if(sev[2*box+1] && (sev[2*box+1] != yVal) && (sev[2*box] == j)){numLoc[m]++;
					if(numLoc[m+1]){numLoc[m+2] = sev[2*box+1];}
					else{numLoc[m+1] = sev[2*box+1];}}
				if(eig[2*box+1] && (eig[2*box+1] != yVal) && (eig[2*box] == j)){numLoc[m]++;
					if(numLoc[m+1]){numLoc[m+2] = eig[2*box+1];}
					else{numLoc[m+1] = eig[2*box+1];}}
				if(nin[2*box+1] && (nin[2*box+1] != yVal) && (nin[2*box] == j)){numLoc[m]++;
					if(numLoc[m+1]){numLoc[m+2] = nin[2*box+1];}
					else{numLoc[m+1] = nin[2*box+1];}}
				if((numLoc[m] == 2 && yVal) || (numLoc[m] == 3)){xPos = xValDiff-j;} m+=3; j++;}} //if the column is full, num cannot have that X position
		if(yVal && xVal){
			if(numLoc[0]%2 && numLoc[3]%2){
				if(numLoc[1] == numLoc[4]){yPos = yValDiff-numLoc[1];}} //if both numbers are in the same row, num cannot have that Y position
			else if(numLoc[0] == 2 == numLoc[3]){yPos = yValDiff-numLoc[4];} //2 numbers in the first column, 1 in the second, the Y position is the empty space in the second column
			else if(numLoc[3] == 2 == numLoc[0]){yPos = yValDiff-numLoc[1];}} //1 number in the first column, 2 in the second, the Y position is the empty space in the first column
		else if(yVal){
			if(numLoc[0]+numLoc[3]+numLoc[6] == 5){ //5 = number of occupied locations, 1 column guaranteed to have one number
				if(numLoc[0] == 1){yPos = yValDiff-numLoc[1];}
				else if(numLoc[3] == 1){yPos = yValDiff-numLoc[4];}
				else{yPos = yValDiff-numLoc[7];}}
			else if(numLoc[0]+numLoc[3]+numLoc[6] == 4){ //4 = number of occupied locations, 1 column guaranteed to have two numbers
				if((numLoc[0] == 2) && (numLoc[4] == numLoc[7])){yPos = yValDiff-numLoc[4];}
				else if((numLoc[3] == 2) && (numLoc[1] == numLoc[7])){yPos = yValDiff-numLoc[1];}
				else if(numLoc[1] == numLoc[4]){yPos = yValDiff-numLoc[1];}}
			else if(numLoc[0]+numLoc[3]+numLoc[6] == 3){ //3 = number of occupied locations
				if((numLoc[1] == numLoc[4]) && (numLoc[4] == numLoc[7])){yPos = yValDiff-numLoc[1];}}}
		else if(xVal && (1 < numLoc[0] < numLoc[3])){ //Y position cannot be determined if there is only one number in a column
			if(numLoc[3] < numLoc[0]){yPos = yValDiff-numLoc[4]-numLoc[5];}
			else if(numLoc[0] < numLoc[3]){yPos = yValDiff-numLoc[1]-numLoc[2];}
			else if(numLoc[1]+numLoc[2] == numLoc[4]+numLoc[5]){yPos = yValDiff-numLoc[1]-numLoc[2];}}}
	else{return tot;}
	if(xPos && yPos){num[2*box] = xPos; num[2*box+1] = yPos; return tot++;} //if both X and Y of num have been determined
	else if(xPos){num[2*box] = xPos;} 
	else if(yPos){num[2*box+1] = yPos;}
	return tot;}
int numPlace(boost::array<int, 18> num, int tot){int i=0, xVal, yVal;
	while(i < 17){
		if(!(num[i] || num[i+1])){ //if X and Y are not known
			xVal = xCheck(num, (i/2)), yVal = yCheck(num, (i/2)); //check if X and Y position are easily determined
			if(xVal && yVal){
				num[i] = xVal; num[i+1] = yVal; tot++;}
			else if(yVal != 0){num[i+1] = yVal; //if Y is known
				xVal = xCheckIndirect(num, yVal, (i/2));
				if(xVal != 0){num[i] = xVal; tot++;}}
			else if(xVal != 0){num[i] = xVal; //if X is known
				yVal = yCheckIndirect(num, xVal, (i/2));
				if(yVal != 0){num[i+1] = yVal; tot++;}}
			else{tot = numCheckObscure(num, (i/2), tot);}} //if neither X nor Y is known
		else if(num[i+1] != 0){ //if Y is known
			xVal = xCheckIndirect(num, num[i+1], (i/2));
			if(xVal != 0){num[i] = xVal; tot++;}}
		i+=2;} //if X and Y cannot be determined indirectly, move on to next box
	return tot;}
int main(){int Sudoku[9][9] = {0}, j=0, tot=0;
	one[2] = 7; one[3] = 2; one[8] = 6; one[9] = 7; tot+=2;
	two[12] = 2; two[13] = 8; tot++;
	thr[0] = 2; thr[1] = 3; thr[2] = 6; thr[3] = 4; thr[4] = 8; thr[5] = 2; thr[16] = 10; thr[17] = 8; tot+=4;
	fou[4] = 10; fou[5] = 4; fou[6] = 4; fou[7] = 7; fou[16] = 8; fou[17] = 8; tot+=3;
	fiv[0] = 2; fiv[1] = 4; fiv[2] = 6; fiv[3] = 3; fiv[12] = 4; fiv[13] = 10; tot+=3;
	six[4] = 8; six[5] = 3; six[8] = 6; six[9] = 5; six[10] = 10; six[11] = 6; six[12] = 4; six[13] = 9; tot+=4;
	sev[0] = 4; sev[1] = 2; sev[6] = 2; sev[7] = 6; sev[10] = 9; sev[11] = 7; sev[14] = 6; sev[15] = 9; sev[16] = 8; sev[17] = 10; tot+=5;
	eig[0] = 4; eig[1] = 4; eig[6] = 3; eig[7] = 5; eig[14] = 6; eig[15] = 8; eig[16] = 10; eig[17] = 9; tot+=4;
	nin[10] = 8; nin[11] = 5; nin[14] = 5; nin[15] = 10; tot+=2;
	while(tot < 81){
		tot = numPlace(one, tot);
		tot = numPlace(two, tot);
		tot = numPlace(thr, tot);
		tot = numPlace(fou, tot);
		tot = numPlace(fiv, tot);
		tot = numPlace(six, tot);
		tot = numPlace(sev, tot);
		tot = numPlace(eig, tot);
		tot = numPlace(nin, tot);}
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
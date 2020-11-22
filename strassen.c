#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>


int** initializeMatrix(int n)
{

	int** Mat;
	Mat=(int**)calloc(n,sizeof(int*));

	for(int i=0;i<n;i++){
            *(Mat+i)=(int*)calloc(n,sizeof(int));
            for(int j=0;j<n;j++){
            			Mat[i][j]=rand() % 10;
            }
    }
    return  Mat;
}


int ** ajouter (int ** M1, int ** M2, int n) { 
    int ** temp = initializeMatrix (n); 
    for (int i = 0; i <n; i ++) 
        for (int j = 0; j <n; j ++) 
            temp [i] [j] = M1 [i] [j] + M2 [i] [j]; 
    return temp;
}


int ** soustraire (int ** M1, int ** M2, int n) { 
    int ** temp = initializeMatrix (n); 
    for (int i = 0; i <n; i ++) 
        for (int j = 0; j <n; j ++) 
            temp [i] [j] = M1 [i] [j] - M2 [i] [j]; 
    return temp; 
}



int **strassenMultiply(int **A,int** B,int n){



if (n == 1) { 
    int ** C = initializeMatrix (1); 
    C [0] [0] = A [0] [0] * B [0] [0]; 
    return C; 
}


int ** C = initializeMatrix (n); 
int k = n / 2;


int ** A11 = initializeMatrix (k); 
int ** A12 = initializeMatrix (k); 
int ** A21 = initializeMatrix (k); 
int ** A22 = initializeMatrix (k); 
int ** B11 = initializeMatrix (k); 
int ** B12 = initializeMatrix (k); 
int ** B21 = initializeMatrix (k); 
int ** B22 = initializeMatrix (k);
for (int i = 0; i <k; i ++) 
    for (int j = 0; j <k; j ++) { 
        A11 [i] [j] = A [i] [j]; 
        A12 [i] [j] = A [i] [k + j]; 
        A21 [i] [j] = A [k + i] [j]; 
        A22 [i] [j] = A [k + i] [k + j]; 
        B11 [i] [j] = B [i] [j]; 
        B12 [i] [j] = B [i] [k + j]; 
        B21 [i] [j] = B [k + i] [j]; 
        B22 [i] [j] = B [k + i] [k + j]; 
    }


int ** P1 = strassenMultiply (A11, soustraire (B12, B22, k), k); 
int ** P2 = strassenMultiply (ajouter (A11, A12, k), B22, k); 
int ** P3 = strassenMultiply (ajouter (A21, A22, k), B11, k); 
int ** P4 = strassenMultiply (A22, soustraire (B21, B11, k), k); 
int ** P5 = strassenMultiply (ajouter (A11, A22, k), ajouter (B11, B22, k), k); 
int ** P6 = strassenMultiply (soustraire (A12, A22, k), ajouter (B21, B22, k), k); 
int ** P7 = strassenMultiply (soustraire (A11, A21, k), ajouter (B11, B12, k), k);

int ** C11 = soustraire (ajouter (ajouter (P5, P4, k), P6, k), P2, k); 
int ** C12 = ajouter (P1, P2, k); 
int ** C21 = ajouter (P3, P4, k); 
int ** C22 = soustraire (soustraire (ajouter (P5, P1, k), P3, k), P7, k);


 for(int i = 0; i <k; i ++) 
    for (int j = 0; j <k; j ++) { 
        C [i] [j] = C11 [i] [j]; 
        C [i] [j + k] = C12 [i] [j]; 
        C [k + i] [j] = C21 [i] [j]; 
        C [k + i] [k + j] = C22 [i] [j]; 
    }

  for(int i=0; i<k; i++) {

    free(A11[i]);
    free(A12[i]);
    free(A21[i]);
    free(A22[i]);
   	free(B11[i]);
    free(B12[i]);
    free(B21[i]);
    free(B22[i]);
    free(P1[i]);
    free(P2[i]);
    free(P3[i]);
    free(P4[i]);
    free(P5[i]);
    free(P6[i]);
    free(P7[i]);
    free(C11[i]);
    free(C12[i]);
    free(C21[i]);
    free(C22[i]);
    }
        
    free(A11);
    free(A12);
    free(A21);
    free(A22);
   	free(B11);
    free(B12);
    free(B21);
    free(B22);
    free(P1);
    free(P2);
    free(P3);
    free(P4);
    free(P5);
    free(P6);
    free(P7);
    free(C11);
    free(C12);
    free(C21);
    free(C22);

return C;

}

void afficher(int ** Mat, int n)

{

		for(int i=0;i<n;i++){
        printf("\n");
       		 for(int j=0;j<n;j++)
           		 printf("\t%d",Mat[i][j]);
    	}
    	printf("\n");
}


void Free(int ** Mat)
{

	free(Mat);
}

int main()
{

	int n;
	printf("Entrez la taille des matrices\n");
	scanf("%d",&n);

	int** A = initializeMatrix(n);
    int** B = initializeMatrix(n);

    afficher(A,n);
    afficher(B,n);

   int **C= strassenMultiply(A,B,n);

    afficher(C,n);



}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>

int** initializeMatrix(int n,int x)
{

	int** Mat;
	Mat=(int**)calloc(n,sizeof(int*));

	for(int i=0;i<n;i++){
            *(Mat+i)=(int*)calloc(n,sizeof(int));
            for(int j=0;j<n;j++){
            		if(x==1)
            			Mat[i][j]=rand() % 10;
            		else
            			Mat[i][j]=0; // Pour initialiser la matrice a 0.
            }
    }
    return  Mat;
}


float timedifference_msec(struct timeval t0, struct timeval t1)
{
    return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
}

//*************Fonction d'affichage*********

void afficher(int ** Mat, int n,int m)

{

		for(int i=0;i<n;i++){
        printf("\n");
       		 for(int j=0;j<n;j++)
           		 printf("\t%d",Mat[i][j]);
    	}
    	printf("\n");
}



int ** multiplier (int ** A, int ** B,int n,int m) { 

        int ** C=initializeMatrix(n,0);

        struct timeval t0;
   		struct timeval t1;
   		float elapsed;
       
       gettimeofday(&t0, 0);

        FILE *fp=NULL;
  		fp=fopen("mat.txt","w");
       
        for (int i = 0; i <n; i ++){
        	gettimeofday(&t0, 0);
            for (int j = 0; j <n; j ++) {
                for (int k = 0; k <n; k ++) {
                    C [i] [j] += A [ i] [k] * B [k] [j]; 
                    gettimeofday(&t1, 0);

                    
    				elapsed = timedifference_msec(t0, t1);

                    fprintf(fp,"%d\t%f\n",C [i] [j],elapsed);
                }
            }
        }
        
        for(int i=0;i<n;i++){
		
    	

       

    return C; 
}


void tracer(int** Mat,int n,int m){


	FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
    	fprintf(gnuplotPipe, "plot '-' \n");
        fprintf(gnuplotPipe, "%d\n",Mat[i][j]);
 		}
		}
		fprintf(gnuplotPipe, "e\n");
    	fflush(gnuplotPipe);
   		fclose(gnuplotPipe);
}

int main()
{

	 
	
	int n=8,m=8;
	int** A=initializeMatrix( n,0);
	int** B=initializeMatrix( n,1);
	//gettimeofday(&t0, 0);
	int **C=multiplier(A,B,n,m);
	//gettimeofday(&t1, 0);

   //elapsed = timedifference_msec(t0, t1);
	afficher(A,n,m);
	afficher(B,n,m);
	afficher(C,n,m);
	//tracer(C,n,m);
	//tracer(A,n);
	//tracer(B,n);

	//gettimeofday(&t1, 0);
    //elapsed = timedifference_msec(t0, t1);
	//printf(" %f milliseconds.\n", elapsed);
	printf("%d\n", n); 

	free(C);
}
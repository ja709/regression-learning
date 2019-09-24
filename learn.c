#include<stdio.h>
#include<stdlib.h>

void clear(double **matrix, int r){

	for(int i = 0; i < r; i++)
		free(matrix[i]);
	free(matrix);
	
}

void clearT(double **matrix, int c){

	for(int i = 0; i < c+1; i++)
		free(matrix[i]);
	free(matrix);
	
}

void trans(double **matrix, double **matrix2, int r, int c){

  for(int i = 0; i < r; i++){
    for(int j = 0; j< c +1; j++){
      matrix[j][i] = matrix2[i][j];
    }
  }

}


int main (int argc, char **argv){
  FILE *fp = NULL;
  char *filename = NULL;
  int row, row1, col;
  double **m1, **mt, **mi, **multi, **result, **m2;
  double *y, *price, *final;
  double sum, ratio,factor;
  int i,j,k;
  
  if(argc <3){
    printf("\n");
    return 0;
  }
  
  filename = argv[1];
  fp = fopen(filename, "r");
  
  if(fp == NULL){
    printf("error\n");
    exit(0);
  }
  
  fscanf(fp,"%d\n", &col);
  fscanf(fp,"%d\n", &row);
  

  m1 = (double**)malloc(row * sizeof(double*));
  for(i = 0; i < row; i++){
    m1[i]=(double*)malloc((col+1) * sizeof(double));
  }

 
  y = (double*)malloc(row * sizeof(double));
  
  for(i = 0 ; i < row; i ++){
    m1[i][0] = 1.0;
    for(j = 1 ; j < col + 1; j++){	
      
      fscanf(fp, "%lf"",", &m1[i][j]);
      
    }
    fscanf(fp,"%lf", &y[i]);
    fscanf(fp,"\n");
  }

  //transpose of X

  mt = (double**)malloc((col+1) * sizeof(double*));
  
  for(i = 0; i < col+1; i++){
    mt[i]=(double*)malloc(row * sizeof(double));
  }
  
	trans(mt, m1, row, col);


   multi = (double**)malloc((col +1) * sizeof(double*));
   for(i = 0; i < col+1; i++){
    multi[i] = (double*)malloc((col +1) * sizeof(double));
   }
   
   for(i = 0; i < col + 1; i++){
     for(j = 0; j < col +1; j++){
       sum = 0;
       for(k = 0; k < row; k++){
				 sum += mt[i][k] * m1 [k][j];
				 multi[i][j] = sum;
      }
     }
   }
   
   //make another same size Aug matrix 
    
   mi = (double**)malloc(row * sizeof(double*));
   for(i = 0; i < row; i++){
    mi[i] = (double*)malloc(row * sizeof(double));
   }

   for(i = 0 ; i < col + 1 ; i++){
     for(j = 0 ; j < col + 1; j++){
       if (i == j){
				 mi[i][j] = 1.0;
       }else{
				 mi[i][j] = 0.0;
       }	
     }						
   }

   //inverse of multi matrix
   
   for(i = 0 ; i < col + 1 ; i++){
     ratio = multi[i][i];
     for(k = 0; k < col + 1; k++){
       multi[i][k] /= ratio;
       mi[i][k] /= ratio;
     }  
     for(j = i+1; j < col +1; j ++){
       factor = multi[j][i];
       
       for(k = 0; k < col +1; k++){       
	 multi[j][k] -= factor * multi[i][k];
	 mi[j][k] -= factor * mi[i][k];     
	}	
     }
   }

   for(i = col; i > 0; i--){     
     for(j = i-1; j >= 0; j--){
       factor = multi[j][i];
       for(k = col; k >= 0; k--){	 
	 multi[j][k] -= factor * multi[i][k];
	 mi[j][k] -= factor * mi[i][k]; 
       }
     }
   }
   

   //multiply mi and mt
   
   result = (double**)malloc((col +1) * sizeof(double*));
   for(i = 0; i < col+1; i++){
     result[i] = (double*)malloc(row * sizeof(double));
   }
   
   for(i = 0; i < col+1; i++){
     for(j = 0; j < row; j++){
       sum = 0;
       for(k = 0; k < col+1; k++){
	 sum += mi[i][k] * mt[k][j];
	 result[i][j] = sum;
       }
     }
  }

   //multiply the result by y
   
   final = (double*)malloc((col +1) * sizeof(double));
   
   for(i = 0 ; i < col +1; i++){
     sum = 0;
     for(j= 0; j < row; j ++){
       sum += result[i][j] * y[j];
       final[i] = sum;
     } 
   }

//=======================test data==============================   
  filename = argv[2];
  fp = fopen(filename, "r");
  
  if(fp == NULL){
    printf("error\n");
    exit(0);
  }

  fscanf(fp,"%d\n", &row1);

  m2 = (double**)malloc(row1 * sizeof(double*));

  for(i = 0; i < row1; i++){
    m2[i]=(double*)malloc((col+1) * sizeof(double));
  }

  price = (double*)malloc(row1 * sizeof(double));
 
  for(i = 0 ; i < row1; i ++){
    m2[i][0] = 1.0;
    for(j = 1 ; j < col+1; j++){	
      fscanf(fp, "%lf"",", &m2[i][j]);
    }
    fscanf(fp,"\n");
  }

   for(i = 0 ; i < row1 ; i++){
     sum = 0;
     for(j= 0; j < col+1 ; j ++){
       sum += m2[i][j] * final[j];
       price[i] = sum;
     } 
   }

   for(i = 0; i < row1;i ++){
     printf("%0.0lf\n", price[i]);
   }

// ============free memory==============      


	 clear(m1, row);
	 clear(m2, row1);
	 clear(mi, row);
	
   clearT(mt, col);
   clearT(multi, col);
	 clearT(result, col);
  
   free(final);
   free(price);
   free(y);
   
   return 0;
}

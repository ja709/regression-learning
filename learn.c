#include<stdio.h>
#include<stdlib.h>

void transpose(){
  //transpose of X

  mt = (double**)malloc((col+1) * sizeof(double*));
  
  for(i = 0; i < col+1; i++){
    mt[i]=(double*)malloc(row * sizeof(double));
  }
  
  for(i = 0; i < row; i++){
    for(j = 0; j< col +1; j++){
      mt[j][i] = m1[i][j];
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

  /*=============print===================
  for(i = 0; i < row ;i ++){
    for(j = 0; j < col + 1; j++){
      printf("%lf"", ", m1[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  printf("\n");
  for(i = 0; i < row; i++){
    printf("%lf\n", y[i]);
  }
  printf("\n");
  
  */
  //transpose of X

  mt = (double**)malloc((col+1) * sizeof(double*));
  
  for(i = 0; i < col+1; i++){
    mt[i]=(double*)malloc(row * sizeof(double));
  }
  
  for(i = 0; i < row; i++){
    for(j = 0; j< col +1; j++){
      mt[j][i] = m1[i][j];
    }
  }
  /*=============print===================
  for(i = 0; i < row ;i ++){
    for(j = 0; j < col+1; j++){
      printf("%lf"",", m1[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  printf("transpose");
  printf("\n");
  for(i = 0; i < col + 1 ;i ++){
    for(j = 0; j < row; j++){
      printf("%lf"", ", mt[i][j]);
    }
    printf("\n");
  }
   printf("\n");
   printf("\n");
   printf("\n");
   */
   //multiplication of XT and X
   //printf("Xtranspose.X is\n");
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
   
   /*=============print===================
   for(i = 0; i < col + 1 ;i ++){
     for(j = 0; j < col + 1; j++){
      printf("%lf"",", multi[i][j]);
     }
     printf("\n");
   }
   printf("\n");
   printf("\n");
   printf("\n");
   */
   
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
   /*=============print===================
  printf("Aug is\n\n");
   for(i = 0; i < col + 1;i ++){
     for(j = 0; j < col + 1; j++){
       printf("%lf"",", mi[i][j]);
     }
     printf("\n");
   }
   
   printf("\n");
   printf("\n"); 
   printf("\n");
   printf("\n"); 
   printf("\n"); 
   printf("\n");
   */
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
   
   /*
   printf("inverse is\n\n");
   for(i = 0; i < col + 1;i ++){
     for(j = 0; j < col + 1; j++){
       printf("%lf"",", mi[i][j]);
     }
     printf("\n");
   }  
   
   
   
   printf("\n");
   printf("\n"); 
   printf("\n");
   printf("\n"); 
   printf("\n"); 
   printf("\n");
   */
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
/*
  printf("result is\n\n");
   for(i = 0; i < col +1 ;i ++){
     for(j = 0; j < row; j++){
       printf("%lf"",", result[i][j]);
     }
     printf("\n");
   }
   printf("\n");
   printf("\n"); 
   printf("\n");
   printf("\n"); 
   printf("\n"); 
   printf("\n");
   */
   //multiply the result by y
   
   final = (double*)malloc((col +1) * sizeof(double));
   
   for(i = 0 ; i < col +1; i++){
     sum = 0;
     for(j= 0; j < row; j ++){
       sum += result[i][j] * y[j];
       final[i] = sum;
     } 
   }
/*
   printf("final is\n\n");
   for(i = 0; i < col +1 ;i ++){
     printf("%lf\n", final[i]);
   }

   printf("\n\n");
*/
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

// ============free==============      
   for(i = 0; i < row; i ++)
     free(m1[i]);
   free(m1);


   for(i = 0; i < row1; i ++)
     free(m2[i]);
   free(m2);
     

   for(i = 0; i < col+1; i ++)
     free(mt[i]);
   free(mt);

   for(i = 0; i < col+1; i ++)
     free(multi[i]);
   free(multi);

         
   for(i = 0; i < row; i ++)
     free(mi[i]);
   free(mi);

   for(i = 0; i < col+1; i ++)
     free(result[i]);
   free(result);

      
   free(final);
   free(price);
   free(y);
   
   return 0;
}

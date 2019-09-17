# regression-learning

This is a C program that implements simple “one-shot” machine learning algorithm for predicting house prices.
The price of the house (y) can depend on certain attributes of the house:  number ofbedrooms (x1), total size of the house (x2), number of baths (x3), and the year the house was built (x4).Then, the price of the house can be computed by the following equation:
\[y=w0+w1.x1+w2.x2+w3.x3+w4.x4\]


## Getting Started

The goal of our machine learning algorithm is to learn this matrix from the training data. Now in the matrix notation, entire learning process can be represented by the following equation,where X,Y, and W are matrices as described above $.X.W=Y$ Using the training data, we can learn the weights using the below equation:
\[W= (X^T.X)^−1.X^T.Y\]
where \(X^T\) is the transpose of the matrixX, \((XT.X)^−1\) is the inverse of the matrix \(X^T.X\).

### Gauss-Jordan Elimination

Computing the Inverse using Gauss-Jordan Elimination To compute the weights above, your program has to compute the inverse of matrix.  There are numerous methods  to  compute  the  inverse  of  a  matrix.   We  want  you  to  implement  aspecific  method  for computing  the  inverse  of  a  matrix  known  as  Guass-Jordan  elimination,  which  is  described below.  If you compute inverse using any other method, you will risk losing all points for this part. An inverse of a square matrixAis another square matrixB, such thatA.B=B.A=I, whereIisthe identity matrix.


## Running the tests

where<train-data-file-name>is the name of the training data file with attributes and price ofthe  house.   You  can  assume  that  the  training  data  file  will  exist  and  that  it  is  well  structured.   The<test-data-file-name>is  the  name  of  the  test  data  file  with  attributes  of  the  house.   You  have  topredict the price of the house for each entry in the test data file.

```
./learn <train-data-file-name> <test-data-file-name>
```

## Built by

* [Jeeho](linkedin.com/in/jeeho-ahn-a01830181)

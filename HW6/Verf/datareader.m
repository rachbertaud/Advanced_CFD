row = readmatrix("row.dat");
row = row + 1;
col = readmatrix("col.dat");
col = col + 1;
val = readmatrix("val.dat");

A = sparse(row, col, val);

A = A/max(max(A));

scatter(row, col, 15)

figure(2) 
spy(A)
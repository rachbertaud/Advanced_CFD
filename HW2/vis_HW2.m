rows = readmatrix("row.dat");
rows = rows + 1;

col = readmatrix("col.dat");
col = col + 1;

val = ones(length(rows), 1);

A = sparse(rows', col', val', 16, 16);

spy(A)
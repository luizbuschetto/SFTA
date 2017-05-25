clear 
clc

tic
[ xTrain yTrain ] = extractfeatures( 'sets/set3' );
cd('results/10');
save('data_set3');
writearchive('set3', xTrain, yTrain);
cd('../..');
toc
function [ xTrain yTrain ] = extractfeatures( path )

cd (path);
cd('B');
files = dir('*jpg');

contTrain = 0;

for id = 1:(length(files)/2)
    contTrain = contTrain + 1;
    [~, name] = fileparts(files(id).name);
    s = strcat(name, '.jpg')
    I = imread(s);
    xTrain(contTrain, :) = sfta(I, 8);
    yTrain(contTrain, 1) = 1;
end

% contTest = 0;
% 
% for id = ((length(files)/2)+1):length(files)
%     contTest = contTest + 1;
%     [~, name] = fileparts(files(id).name);
%     s = strcat(name, '.jpg')
%     I = imread(s);
%     xTest(contTest, :) = sfta(I, 8);
%     yTest(contTest, 1) = 1;
% end

cd('../R');
files = dir('*jpg');

for id = 1:(length(files)/2)
    contTrain = contTrain + 1;
    [~, name] = fileparts(files(id).name);
    s = strcat(name, '.jpg')
    I = imread(s);
    xTrain(contTrain, :) = sfta(I, 8);
    yTrain(contTrain, 1) = -1;
end

% for id = ((length(files)/2)+1):length(files)
%     contTest = contTest + 1;
%     [~, name] = fileparts(files(id).name);
%     s = strcat(name, '.jpg')
%     I = imread(s);
%     xTest(contTest, :) = sfta(I, 8);
%     yTest(contTest, 1) = -1;
% end

cd('../../..');

end


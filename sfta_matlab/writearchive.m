function [] = writearchive(name, xTrain, yTrain)
tam = size(xTrain);

fid = fopen(name, 'w');

    for i = 1:tam(1)
        fprintf(fid, '%i ', yTrain(i, 1));
        for j = 1:tam(2)
            fprintf(fid, '%i:%f ', j, xTrain(i,j));
        end
        fprintf(fid, '\n');
    end
fclose(fid);
end


clear
clc


%Definindo Caminho das Imagens
srcFiles = dir('2Test\B\*');
    for i = 1 : length(srcFiles)
        %Checando se o caminho representa um arquivo ou um diretório
        if (~isdir(srcFiles(i).name))
            %Concatenando com  onome da imagem
            filename = strcat('2Test\B\',srcFiles(i).name);
            %Lendo imagem
            I = imread(filename);
            IR = imresize(I,1/5);
            imwrite(IR,strcat('2Test\B\',srcFiles(i).name));
            %IR = imresize(I,1/5);
            %imwrite(IR,strcat('5\',srcFiles(i).name));
            %IR = imresize(I,1/10);
            %imwrite(IR,strcat('10\',srcFiles(i).name));
        end
    end

    %Definindo Caminho das Imagens
srcFiles = dir('2Test\R\*');
    for i = 1 : length(srcFiles)
        %Checando se o caminho representa um arquivo ou um diretório
        if (~isdir(srcFiles(i).name))
            %Concatenando com  onome da imagem
            filename = strcat('2Test\R\',srcFiles(i).name);
            %Lendo imagem
            I = imread(filename);
            IR = imresize(I,1/5);
            imwrite(IR,strcat('2Test\R\',srcFiles(i).name));
            %IR = imresize(I,1/5);
            %imwrite(IR,strcat('5\',srcFiles(i).name));
            %IR = imresize(I,1/10);
            %imwrite(IR,strcat('10\',srcFiles(i).name));
        end
    end

    %Definindo Caminho das Imagens
srcFiles = dir('2Train\B\*');
    for i = 1 : length(srcFiles)
        %Checando se o caminho representa um arquivo ou um diretório
        if (~isdir(srcFiles(i).name))
            %Concatenando com  onome da imagem
            filename = strcat('2Train\B\',srcFiles(i).name);
            %Lendo imagem
            I = imread(filename);
            IR = imresize(I,1/5);
            imwrite(IR,strcat('2Train\B\',srcFiles(i).name));
            %IR = imresize(I,1/5);
            %imwrite(IR,strcat('5\',srcFiles(i).name));
            %IR = imresize(I,1/10);
            %imwrite(IR,strcat('10\',srcFiles(i).name));
        end
    end

    %Definindo Caminho das Imagens
srcFiles = dir('2Train\R\*');
    for i = 1 : length(srcFiles)
        %Checando se o caminho representa um arquivo ou um diretório
        if (~isdir(srcFiles(i).name))
            %Concatenando com  onome da imagem
            filename = strcat('2Train\R\',srcFiles(i).name);
            %Lendo imagem
            I = imread(filename);
            IR = imresize(I,1/5);
            imwrite(IR,strcat('2Train\R\',srcFiles(i).name));
            %IR = imresize(I,1/5);
            %imwrite(IR,strcat('5\',srcFiles(i).name));
            %IR = imresize(I,1/10);
            %imwrite(IR,strcat('10\',srcFiles(i).name));
        end
    end


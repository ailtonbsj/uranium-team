%Dados com bordas brancas
%entrada = [0,39,45,58,71,78,91,98,111,117,130,137,143,150,163,163,163,163,163,163,163,163,170,163,170,163,163,163,170,163,163,163,163,163,170,163,163,163,163,156,150,150,130,124,137,150,156,156,163,156,150,150,163,156,163,163,170,163,176,170,170,170,176,176,176,170,176,163,156,156,156,150,156,150,150,156,150,143,150,143,143,143,137,130,137,130,137,137,137,130,137,137,137,130,137,137,176,228,255,235];
entrada = [0,31,40,49,58,67,71,76,85,93,98,102,102,111,111,111,111,111,111,111,111,116,116,116,116,116,111,116,111,116,111,111,111,116,111,111,111,111,111,102,102,93,85,93,102,111,111,111,107,102,107,111,107,111,111,116,116,120,116,116,116,120,120,125,116,120,111,111,107,111,107,107,107,107,107,102,102,107,102,102,102,98,93,98,107,147,205,250,255,255,255,250,246,241,223,214,196,187,165,134];
%entrada = [0,24,32,40,48,56,60,64,72,76,80,89,89,97,97,101,97,97,97,97,97,101,97,101,101,97,97,101,101,101,97,97,97,101,97,101,97,101,97,89,89,80,72,80,89,97,97,97,93,93,93,101,97,101,97,101,101,105,105,105,105,109,109,113,105,113,105,129,186,246,254,250,254,250,250,250,250,254,250,250,246,242,246,250,246,242,242,234,202,161,121,137,194,214,202,198,182,170,153,137];
%entrada = [0,22,22,29,36,44,51,55,62,66,73,77,81,85,88,88,92,88,92,92,92,92,96,92,96,92,92,92,92,92,92,92,92,92,92,88,92,92,92,88,85,85,77,70,81,88,96,96,103,133,199,247,255,243,255,251,251,251,255,251,255,255,255,251,255,251,255,251,255,251,251,247,247,247,243,229,177,99,73,129,203,232,229,232,236,232,229,229,225,221,221,218,214,210,206,192,188,173,162,147];
%entrada = [0,25,32,40,47,51,54,61,69,72,76,80,83,87,87,91,87,91,91,91,91,94,91,94,94,94,94,94,94,94,94,98,98,134,182,229,236,244,240,233,240,244,247,251,240,247,244,251,247,251,251,255,244,251,247,251,247,251,244,244,236,171,91,58,98,182,229,240,236,240,240,240,240,236,233,233,233,233,229,225,225,222,222,222,218,214,214,214,211,211,207,204,196,193,174,171,153,142,127,116];
%entrada = [0,22,22,30,37,45,52,56,60,67,75,78,82,86,90,93,97,97,123,172,202,225,232,228,232,236,236,232,236,240,243,240,236,243,247,243,251,247,251,243,228,183,105,52,86,161,232,247,251,251,251,251,255,247,251,251,251,247,251,247,251,251,247,247,247,243,247,243,247,243,243,240,240,240,240,240,236,236,240,236,232,232,225,225,225,217,213,213,210,206,202,198,191,187,183,165,157,142,131,116];
%entrada = [0,22,22,29,36,44,51,55,66,92,140,181,206,218,229,229,229,229,232,236,225,232,236,232,232,229,199,129,77,96,170,218,236,243,243,240,247,243,247,243,232,243,247,247,251,243,251,247,251,247,251,251,255,243,251,251,251,247,251,247,251,251,251,247,251,243,251,243,247,243,243,240,240,240,236,236,236,236,232,232,229,229,221,221,225,218,214,210,210,206,203,195,173,140,103,92,129,140,133,118];
    %Centro
%entrada = [0,29,44,81,118,147,162,177,192,203,214,221,225,232,229,214,158,110,129,177,218,236,232,236,236,240,240,240,243,243,243,240,243,243,243,247,247,251,247,236,247,247,247,255,247,255,251,255,255,251,251,255,247,251,247,251,251,255,251,255,255,255,251,255,247,255,247,251,247,247,243,243,243,240,240,236,232,232,229,229,225,221,210,177,121,88,118,173,203,203,199,195,188,181,155,133,88,55,40,36];
%entrada = [0,57,61,57,54,85,123,146,166,181,197,204,212,220,224,224,227,224,227,231,220,224,231,227,227,227,227,227,231,227,235,235,235,239,243,239,247,243,247,243,231,243,243,243,247,239,251,247,255,251,251,251,251,243,247,247,247,243,235,162,73,30,73,162,231,231,239,231,239,239,239,235,231,231,227,227,224,212,173,112,73,61,54,50,54,50,50,46,46,46,46,42,42,38,38,30,27,19,15,7];
%entrada = [0,63,63,83,103,123,143,159,175,191,203,211,219,223,231,231,235,235,235,239,231,235,243,235,239,239,239,239,243,243,247,243,239,247,231,155,83,39,103,183,227,247,247,251,255,247,255,251,255,251,251,251,255,243,247,227,171,103,87,83,83,79,83,79,83,75,79,71,71,63,67,63,63,63,59,59,55,55,55,51,51,51,47,43,43,43,43,39,39,35,39,35,35,31,31,23,19,15,7,0];
%entrada = [0,68,72,89,110,127,148,165,182,195,212,221,233,238,242,238,246,242,242,246,233,208,140,85,119,187,233,242,246,246,250,246,246,250,255,250,255,250,246,191,119,80,63,55,63,72,76,76,76,72,68,68,76,72,76,72,76,76,80,80,80,76,80,80,80,72,76,68,68,63,68,59,63,59,59,59,55,55,55,51,51,46,42,38,42,38,38,38,38,34,34,29,29,25,25,17,17,8,4,0];
%entrada = [0,74,97,115,106,92,125,171,204,227,236,245,250,255,222,166,120,97,92,88,92,92,88,92,88,83,83,88,83,88,83,88,83,88,83,88,83,88,83,74,74,64,55,64,74,78,83,83,78,74,74,83,83,83,83,88,83,92,88,88,88,92,92,92,83,88,78,78,74,74,69,74,69,69,69,64,60,64,60,60,55,51,46,51,46,46,46,46,41,41,37,37,32,32,23,23,13,9,4,0];

%Dados sem bords brancas
%entrada = [0,39,51,68,73,85,90,102,107,119,124,130,136,141,141,147,141,147,147,141,147,153,147,153,147,147,147,153,147,147,147,147,147,147,141,147,141,153,141,136,136,119,113,124,136,141,141,147,141,136,136,147,141,147,147,153,147,158,153,158,153,158,158,164,153,158,147,141,141,147,141,141,141,141,136,136,136,136,136,136,130,124,124,124,124,124,124,124,124,124,124,119,113,124,147,215,255,249,221,204];
%entrada = [0,27,27,31,43,47,55,59,67,71,79,83,87,91,95,95,99,95,95,99,95,99,103,99,99,99,99,95,99,99,99,99,99,95,99,95,99,95,99,95,91,91,79,75,83,91,95,95,95,91,91,91,99,95,99,99,103,103,107,103,103,103,107,107,111,103,107,99,99,95,99,95,95,95,87,67,55,95,179,239,251,251,247,251,255,251,247,247,247,247,243,243,235,227,223,207,203,187,175,159];
%entrada = [0,21,21,28,35,42,49,53,60,63,70,74,77,81,85,85,88,88,88,88,88,88,92,88,92,88,88,88,92,88,88,88,88,88,92,88,92,88,92,88,81,81,74,70,77,85,88,88,81,60,42,56,138,212,244,244,247,247,251,247,251,251,251,251,255,247,255,247,251,247,251,247,247,244,244,240,237,237,237,233,237,237,233,233,233,230,230,230,226,223,223,219,216,208,208,194,191,173,159,141];
%entrada = [0,27,34,40,47,51,54,61,64,71,74,81,81,88,88,88,88,88,88,88,91,95,91,95,91,91,91,88,68,51,57,129,197,231,234,241,238,241,238,231,241,244,244,248,241,248,248,251,251,251,251,255,244,251,248,248,244,248,244,248,248,248,248,248,241,248,241,244,244,244,241,241,241,238,238,234,234,234,231,231,231,227,227,231,227,224,224,217,214,210,207,197,173,136,78,47,51,54,47,44];
    %centro
%entrada = [0,24,31,38,45,52,55,59,62,73,76,80,83,87,90,90,76,59,69,125,181,220,223,227,227,230,230,234,234,241,237,237,241,244,241,248,244,248,244,234,244,244,244,248,244,251,248,255,251,251,248,251,244,251,248,251,251,251,248,251,248,248,248,248,244,248,241,244,241,244,241,241,241,241,237,237,237,237,227,227,223,216,213,185,125,62,45,59,69,76,73,73,69,69,59,59,52,48,41,34];
%entrada = [0,24,24,31,37,41,41,44,89,144,182,199,213,217,223,223,227,227,230,234,223,230,234,230,234,234,234,234,237,237,241,237,237,241,244,244,248,248,248,248,234,244,248,248,251,244,251,251,255,251,251,251,255,248,251,251,255,251,251,244,248,244,241,237,237,230,223,148,68,34,48,65,82,82,79,79,79,75,79,75,75,72,68,65,68,68,68,65,68,65,65,65,65,62,62,55,51,44,41,34];
%entrada = [0,76,102,116,134,153,167,182,193,207,214,222,229,236,233,236,236,236,244,233,240,244,236,240,240,244,240,244,244,247,247,244,251,251,247,255,251,251,247,236,244,244,244,244,236,218,138,65,40,54,76,91,87,91,91,94,91,94,94,94,91,94,94,98,91,94,87,87,83,87,83,83,83,83,80,80,80,80,80,80,76,72,69,72,72,69,72,72,69,72,69,69,69,65,58,58,51,47,36,32];
%entrada = [0,74,97,115,139,162,180,199,213,231,241,250,255,255,204,120,64,60,74,83,83,92,83,88,83,83,83,88,83,83,83,83,83,83,78,83,78,83,78,74,74,60,55,64,69,78,78,78,74,74,74,83,78,83,83,83,83,88,88,88,88,92,88,92,88,88,83,78,74,78,74,78,74,74,74,74,69,74,69,69,64,64,60,60,60,60,60,60,60,60,60,60,55,55,46,41,32,27,18,13];

%branco
%entrada = [0,63,63,87,103,127,143,151,167,175,187,199,207,215,219,215,215,215,215,223,211,219,223,219,223,223,227,227,227,231,231,231,231,239,239,235,243,239,243,239,231,243,243,243,247,243,251,247,251,251,251,251,255,243,251,251,255,251,251,247,255,251,251,251,251,247,251,247,251,251,251,247,247,247,247,247,247,243,247,243,247,247,243,243,247,243,239,239,239,239,239,239,235,231,227,211,203,187,171,151];
%entrada = [0,64,85,105,125,145,157,170,182,194,206,214,218,222,218,218,214,214,214,202,210,214,206,210,210,214,210,214,218,222,218,218,222,222,222,230,226,230,230,218,230,234,234,238,230,238,234,238,238,238,238,242,234,238,238,242,238,246,242,250,246,246,246,250,246,254,246,250,250,250,246,246,246,246,246,242,242,246,242,242,242,242,242,246,246,242,242,242,242,242,242,242,238,234,214,206,190,174,153,141];

%novos dados
%entrada = [23,34,36,34,39,40,40,40,40,41,40,41,41,42,41,42,42,43,42,37,33,47,67,81,83,84,83,84,85,86,85,85,87,87,87,89,88,89,88,85,89,89,90,90,88,90,89,91,90,91,91,91,89,90,90,91,90,91,90,92,91,91,90,92,90,92,90,91,90,91,90,90,90,89,90,90,90,90,89,89,89,87,88,88,84,68,48,36,39,45,45,44,44,45,43,44,42,42,42,42];
%entrada = [22,32,35,32,37,38,38,39,39,40,40,39,36,45,62,77,79,80,82,80,81,82,81,82,82,83,83,83,84,85,84,84,85,86,85,86,85,86,85,82,85,85,86,87,84,86,85,87,86,86,86,87,85,87,86,87,86,87,86,88,88,87,87,89,87,89,88,89,87,88,87,87,83,64,39,31,36,41,43,43,43,42,42,43,43,43,44,44,43,42,41,41,40,41,40,41,41,40,39,39];
%entrada = [23,33,35,34,39,40,40,37,44,61,75,79,80,81,82,83,82,83,84,82,84,85,84,85,85,86,85,86,86,87,87,87,88,89,88,90,90,91,90,88,91,92,92,93,91,93,92,93,93,92,92,93,91,93,93,93,93,93,92,93,93,91,79,53,33,34,40,45,45,46,45,46,45,44,45,46,45,45,44,45,44,44,43,43,43,42,42,43,43,44,43,42,42,42,41,42,40,41,39,37];
%entrada = [24,34,35,33,35,48,64,75,77,78,78,79,79,81,81,82,82,82,83,81,82,84,83,84,85,86,85,86,87,87,87,87,88,89,89,90,89,90,89,86,89,89,89,90,89,91,90,91,90,90,90,90,87,75,46,29,29,37,40,42,43,43,43,45,44,44,44,46,44,44,44,45,45,44,43,44,43,44,44,44,43,43,43,43,43,41,42,42,41,41,41,40,40,40,36,37,38,39,39,39];
%entrada = [30,33,35,36,37,37,38,37,38,39,39,39,40,40,41,40,41,40,41,42,42,42,43,43,43,43,44,42,37,32,45,68,82,85,86,85,87,87,87,87,84,87,88,88,88,86,88,87,89,88,89,89,89,87,89,88,88,88,89,88,89,89,89,88,89,88,89,88,89,88,89,88,88,88,88,88,88,88,89,88,88,88,86,87,87,87,84,87,86,86,85,85,83,78,63,42,37,41,43,42];
%entrada = [31,46,39,36,38,39,40,40,40,40,40,40,40,40,41,40,41,41,42,42,42,42,42,41,43,43,43,42,43,43,44,42,41,42,43,42,43,41,42,42,41,42,42,37,31,30,49,74,85,85,85,86,87,85,87,87,87,87,87,86,87,87,87,86,87,85,87,85,85,84,85,85,84,84,84,84,83,83,84,82,83,83,82,83,83,83,80,83,83,83,83,83,83,83,84,82,83,82,82,82];
%entrada = [34,59,65,69,72,74,75,75,75,75,76,75,75,75,77,77,77,77,78,79,75,62,49,53,70,80,82,82,82,83,84,83,83,84,85,84,85,83,85,84,81,84,84,84,85,83,84,83,84,83,84,83,84,82,84,83,84,83,84,83,85,84,83,82,84,82,84,82,84,83,84,83,83,84,83,83,83,83,83,81,81,82,81,82,83,82,78,75,58,42,42,60,78,81,82,81,82,81,82,81];
%entrada = [31,57,62,57,71,73,73,73,73,73,73,73,73,74,74,74,74,74,74,73,73,75,74,75,75,76,75,76,76,70,49,34,46,67,76,78,77,78,77,74,77,77,77,79,77,79,78,79,78,78,77,78,76,77,77,77,77,77,76,78,77,77,77,78,76,78,76,77,77,78,78,77,77,77,77,77,77,78,77,78,78,78,78,79,79,76,79,79,79,80,79,79,79,81,79,79,70,53,45,59];
%entrada = [29,52,59,65,69,71,72,72,72,71,72,73,73,74,75,74,75,74,75,75,74,74,75,74,75,75,76,75,75,75,75,74,74,75,75,75,76,75,76,74,72,75,75,69,48,30,35,55,73,75,76,76,77,75,77,76,76,76,77,76,77,77,76,76,77,76,78,76,77,76,77,76,76,76,76,77,77,77,77,76,77,77,77,77,78,77,74,77,77,77,78,78,78,78,79,78,79,79,79,78];

%problematica das bordas
%entrada = [18,27,35,27,54,54,54,55,55,55,55,55,54,55,55,55,55,55,55,54,55,56,55,56,57,58,57,58,58,59,59,59,59,59,59,60,59,60,59,58,59,60,60,60,59,60,60,61,60,60,59,56,44,32,22,21,23,27,28,29,28,28,28,29,28,29,28,29,28,29,28,29,29,29,29,28,28,28,27,28,28,28,28,29,29,29,30,31,31,32,31,32,31,31,30,31,30,31,30,31];
entrada = [15,22,24,22,25,27,28,29,29,31,30,30,30,31,30,31,31,32,32,32,31,31,30,32,31,32,31,32,31,32,32,32,32,33,32,33,33,33,33,33,33,33,30,27,24,33,46,60,66,67,67,68,66,67,67,67,67,68,67,68,68,68,68,69,67,69,67,69,68,68,68,68,67,68,67,68,68,68,67,68,68,66,67,68,67,65,67,67,67,67,66,66,66,67,66,67,66,66,67,67];

%redimensiona
vmax = max(entrada);
vmin = min(entrada);
entrada = (255/(vmax-vmin))*(entrada-vmin);

subplot(2,1,1);
plot(entrada,'-r','LineWidth',1.5);
hold on
plot([0,100],[176,176],'-b','LineWidth',1.5);
title('Sinal Original Redimensionado');

%corte por limiar
saida1 = entrada > 176;
subplot(2,1,2);
plot(saida1,'-b','LineWidth',1.5);
hold on

%border 1  holeL 3 holeR 8 hole 0
BORDER = 1;
HOLE_L = 3;
HOLE_R = 8;
HOLE = 0;
typeBorder = BORDER;
riseFallL = -1;
contZeros = 0;
for i=50:-1:2
    if(saida1(i) == 1 && saida1(i-1) == 0)
        if riseFallL == -1
            riseFallL = i;
        end
        contZeros = contZeros + 1;
    else
        if(saida1(i) == 0 && saida1(i-1) == 1)
            if riseFallL == -1
                riseFallL = i;
            end
            if(contZeros < 7 && contZeros ~= 0)
                riseFallL = i+1;
                typeBorder = HOLE_L;
                break;
            else
                contZeros = 0;
            end
        end
    end
    if(saida1(i) == 0 && contZeros > 0)
       contZeros = contZeros + 1; 
    end
end

riseFallR = -1;
contZeros = 0;
for i=51:99
    if(saida1(i) == 1 && saida1(i+1) == 0)
        if riseFallR == -1
            riseFallR = i;
        end
        contZeros = contZeros + 1;
    else
        if(saida1(i) == 0 && saida1(i+1) == 1)
            if riseFallR == -1
                riseFallR = i;
            end
            if(contZeros < 7 && contZeros ~= 0)
                riseFallR = i-1;
                if typeBorder == HOLE_L
                    typeBorder = HOLE;
                else
                    typeBorder = HOLE_R;
                end
                break;
            else
                contZeros = 0;
            end
        end
    end
    if(saida1(i) == 0 && contZeros > 0)
       contZeros = contZeros + 1; 
    end
end

width = riseFallR-riseFallL;
width = width >= 60 && width <= 70;

if(typeBorder == HOLE_L)
    riseFallR = riseFallL+63;
elseif(typeBorder == HOLE_R)
    riseFallL = riseFallR-63;
elseif((riseFallR ~= -1) && (riseFallL ~= -1))
    if width ~= 1
        if(riseFallR < riseFallL)
        riseFallL = riseFallR+63;
        else
            riseFallR = riseFallL-63;
        end
    end
elseif(riseFallL ~= -1)
    riseFallR = riseFallL+63;
elseif(riseFallR ~= -1)
    riseFallL = riseFallR-63;
end
    
myinput = ((riseFallL + riseFallR)/2);
plot(riseFallR,0.5,'-r*');
plot(riseFallL,0.5,'-r*');
plot(myinput,0.5,'-b*');

axis([0 100 0 1.5])
title('Sinal com Thresholding');
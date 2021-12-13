%Filtro Gaussiano
teta = 1;
core = zeros(3,1)
for x=-1:1
    core(x+2) = (1/(sqrt(2*pi)*teta))*(exp(-(x^2)/(2*(teta^2))));
end
%core = int8(core)
% MATLAB CODE THAT READS A .mat FILE AND TURNS IT INTO A CSV

while(1)
    try
    load("/home/jay/Downloads/a.mat") %load the .mat file
    p=[x,y];
    writematrix(p,"/home/jay/C_testing/Optimization Algorithms/data/ps_read.csv")
    disp("matrix written")
    pause(10)
    catch
        % print error and time of error
        warning('Error using load on ____'  + string(datetime('now')))
        pause(0.5)
    end
end


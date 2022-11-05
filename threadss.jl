
using Plots
#using Threads

iter=1000
N=100

pos=zeros(iter)
posfinal=zeros(N)

@time begin

Threads.@threads for k in 1:N

    for i in 2:iter
        # random number either 1 or -1
        x = rand([-1,1])
        pos[i] = pos[i-1] + x
    end
    posfinal[k]=pos[iter]

end


end

# plot posfinal
#histogram(posfinal, bins=100, normed=true, label="")





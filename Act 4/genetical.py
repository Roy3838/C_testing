import random

# Fitness function
def fitness(x):
    # Calculate the value of the function f(x, y)
    total = 0
    for i in range(len(x)-1):
        total += 100 * (x[i+1] - x[i]**2)**2 + (1 - x[i])**2
    return total

# Genetic algorithm
def genetic_algorithm():
    # Generate a random initial population
    population = [[random.uniform(-10, 10) for _ in range(7)] for _ in range(2000)]

    # Iterate through the generations
    for _ in range(100):
        # Evaluate the fitness of each individual
        fitnesses = [fitness(x) for x in population]

        # Select the best individuals
        population = [x for _, x in sorted(zip(fitnesses, population))][:1000]

        # Generate new individuals through crossover and mutation
        new_population = []
        for i in range(1000):
            # Crossover
            parent1 = population[random.randint(0, len(population)-1)]
            parent2 = population[random.randint(0, len(population)-1)]
            child = [p1 if random.random() < 0.5 else p2 for p1, p2 in zip(parent1, parent2)]
            # Mutation
            child = [x + random.gauss(0, 0.1) for x in child]
            new_population.append(child)

        # Replace the old population with the new one
        population = new_population

    # Return the best solution found
    return min(population, key=fitness)

# Minimize the function f(x, y)
result = genetic_algorithm()
print(result)
# run the previous code 7 times and get the averege of the results








import random

def func(x,y):
    j0=1
    return j0(x**2 + y**2) + 0.1 * abs(1 - x) + 0.1 * abs(1 - y)

num_generations = 100
pop_size = 100
population = [[random.uniform(-10, 10) for _ in range(7)] for _ in range(2000)]
mut_prob = 0.1


def genetic_algorithm(pop_size, mut_prob, num_generations):
# Initialize the population with random solutions
    population = [random.random() for _ in range(pop_size)]

    # Iterate through the number of generations
    for generation in range(num_generations):
        # Calculate the fitness of each member of the population
        fitness = [func(member) for member in population]

        # Select the fittest members of the population for breeding
        breeding_pool = [population[i] for i in range(pop_size) if fitness[i] < min(fitness)]

        # Breed the selected members to create the next generation
        next_generation = []
        for i in range(0, pop_size, 2):
            parent1, parent2 = random.choice(breeding_pool), random.choice(breeding_pool)
            next_generation.append(parent1 + (parent2 - parent1) * random.random())
            next_generation.append(parent2 + (parent1 - parent2) * random.random())

        # Mutate the next generation with a given probability
        for i in range(pop_size):
            if random.random() < mut_prob:
                next_generation[i] += random.uniform(-1, 1)

        # Replace the current population with the next generation
        population = next_generation

# Return the fittest member of the final population
    return min([func(member) for member in population])

a = genetic_algorithm(pop_size, mut_prob, num_generations)
print(a)
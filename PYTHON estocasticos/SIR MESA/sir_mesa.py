import time
import numpy as np
import pandas as pd
import pylab as plt

from mesa import Agent, Model
from mesa.time import RandomActivation
from mesa.space import MultiGrid
from mesa.datacollection import DataCollector
import enum
import matplotlib.pyplot as plt


class InfectionModel(Model):
    """A model for infection spread."""

    def __init__(self, N=10, width=10, height=10, ptrans=0.5,
                 death_rate=0.00, recovery_days=21,
                 recovery_sd=7):

        self.num_agents = N
        self.recovery_days = recovery_days
        self.recovery_sd = recovery_sd
        self.ptrans = ptrans
        self.death_rate = death_rate
        self.grid = MultiGrid(width, height, True)
        self.schedule = RandomActivation(self)
        self.running = True
        self.dead_agents = []
        # Create agents
        for i in range(self.num_agents):
            a = MyAgent(i, self)
            self.schedule.add(a)
            # Add the agent to a random grid cell
            x = self.random.randrange(self.grid.width)
            y = self.random.randrange(self.grid.height)
            self.grid.place_agent(a, (x, y))
            #make some agents infected at start
            infected = np.random.choice([0,1], p=[0.98,0.02])
            if infected == 1:
                a.state = State.INFECTED
                a.recovery_time = self.get_recovery_time()

        self.datacollector = DataCollector(          
            agent_reporters={"State": "state"})

    def get_recovery_time(self):
        return int(self.random.normalvariate(self.recovery_days,self.recovery_sd))

    def step(self):
        self.datacollector.collect(self)
        self.schedule.step()

class State(enum.IntEnum):
    SUSCEPTIBLE = 0
    INFECTED = 1
    REMOVED = 2

class MyAgent(Agent):
    """ An agent in an epidemic model."""
    def __init__(self, unique_id, model):
        super().__init__(unique_id, model)
        self.age = self.random.normalvariate(20,40)        
        self.state = State.SUSCEPTIBLE  
        self.infection_time = 1

    def move(self):
        """Move the agent"""

        possible_steps = self.model.grid.get_neighborhood(
            self.pos,
            moore=True,
            include_center=False)
        new_position = self.random.choice(possible_steps)
        self.model.grid.move_agent(self, new_position)

    def status(self):
        """Check infection status"""

        if self.state == State.INFECTED:     
            drate = self.model.death_rate
            alive = np.random.choice([0,1], p=[drate,1-drate])
            if alive == 0:
                self.model.schedule.remove(self)            
            t = self.model.schedule.time-self.infection_time
            if t >= self.recovery_time:          
                self.state = State.REMOVED

    def contact(self):
        """Find close contacts and infect"""

        cellmates = self.model.grid.get_cell_list_contents([self.pos])       
        if len(cellmates) > 1:
            for other in cellmates:
                if self.random.random() > model.ptrans:
                    continue
                if self.state is State.INFECTED and other.state is State.SUSCEPTIBLE:                    
                    other.state = State.INFECTED
                    other.infection_time = self.model.schedule.time
                    other.recovery_time = model.get_recovery_time()

    def step(self):
        self.status()
        self.move()
        self.contact()


def get_column_data(model):
    """pivot the model dataframe to get states count at each step"""
    agent_state = model.datacollector.get_agent_vars_dataframe()
    X = pd.pivot_table(agent_state.reset_index(),index='Step',columns='State',aggfunc=np.size,fill_value=0)    
    labels = ['Susceptible','Infected','Removed']
    X.columns = labels[:len(X.columns)]
    return X




def get_agent_locations():
    agent_counts = np.zeros((model.grid.width, model.grid.height))

    infectados = np.zeros((model.grid.width, model.grid.height))
    removidos = np.zeros((model.grid.width, model.grid.height))
    susceptibles = np.zeros((model.grid.width, model.grid.height))
    for cell in model.grid.coord_iter():
        cell_content, x, y = cell
        agent_count = len(cell_content)
        agent_counts[x][y] = agent_count
        infectados[x][y] = len([a for a in cell_content if a.state == State.INFECTED])
        removidos[x][y] = len([a for a in cell_content if a.state == State.REMOVED])
        susceptibles[x][y] = len([a for a in cell_content if a.state == State.SUSCEPTIBLE])
    return infectados, susceptibles, removidos
    #print(x,y)


matrix = np.zeros([10, 300])


for l in range(10):
    pop = 500

    model = InfectionModel(pop, 20, 20, ptrans=0.5)
    data = [get_column_data(model) for i in range(100)]

    r0_sum = 0

    steps = 100
    for i in range(steps):
        model.step()
        # calculate r0
        data[i]=get_column_data(model)
        # if i%10 == 0 or i == 0:
            #calculate r0
            # [infectados, susceptibles, removidos] = get_agent_locations()


            # plt.subplot( 1, 3, 1 )
            # plt.imshow(infectados, cmap='Reds')
            # plt.subplot( 1, 3, 2 )
            # plt.imshow(susceptibles, cmap='Greens')
            # plt.subplot( 1, 3, 3 )
            # plt.imshow(removidos, cmap='Blues')
            # plt.show()
        
    agent_state = model.datacollector.get_agent_vars_dataframe()

    import numpy as np

    #print(data[59])

    #concatenate [1 to 2 column of data[59]]
    SIR = data[steps-1].values
    plt.plot(SIR)
    plt.show()
    col1 = SIR[:,0]
    col2 = SIR[:,1]
    col3 = SIR[:,2]
    SIR = np.concatenate((col1,col2,col3),axis=0)
    # plot SIR

    # flip SIR
    SIR = np.flip(SIR)
    matrix[l] = SIR
# save matrix to csv
pd.DataFrame(matrix).to_csv('SIR.csv', index=False, header=False)
    
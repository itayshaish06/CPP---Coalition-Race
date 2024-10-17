# Coalition Race Simulator

This project is a C++ simulation of a political coalition formation process, created for the **Systems Programming** course (Fall 2023). The simulator is based on a graph where nodes represent political parties, and edges represent potential collaborations between them. Each party has agents that attempt to form a coalition of 61 mandates or more, using different selection and join policies.

## Project Overview

In SPLand, after five failed elections, political agents are tasked with forming a coalition through strategic negotiations between parties. The goal of this simulation is to help these agents form the first coalition with at least 61 mandates, or report a failure if no coalition can be formed.

The program operates on a graph structure, where:

- **Parties** are represented as vertices.
- **Collaborations** between parties are edges with associated weights indicating the likelihood of cooperation.
- Each **Agent** selects neighboring parties based on different strategies (Selection Policies) and makes offers for them to join a coalition.

## Project Classes
- **Simulation** - This class is responsible for managing the simulation resources and making simulation steps.
- Graph** - This class is represented by an adjacency matrix (edges) and parties vector (vertices).
- **Party** - A vertex in the graph. Each party has an id, name, number of mandates, join policy and party state (Waiting, CollectingOffers or Joined).
- **JoinPolicy** - class used only by Parties. This is an abstract class that represents a strategy algorithm for choosing which offer to accept and which coalition to join.
    - MandatesJoinPolicy - Selects the coalition with the largest number of mandates.
    - LastOfferJoinPolicy - Selects the coalition that made the last offer.
- **Agent** - This class has agentId, partyId (each agent associated with a single party), and selection policy.
- **SelectionPolicy** - class used only by Agents. This is an abstract class that represents a strategy algorithm for selecting the next party to offer.
    - MandatesSelectionPolicy - Selects the neighboring party with the most mandates.
    - EdgeWeightSelectionPolicy - Selects the neighboring party with the highest edge weight.
- **Coalition** - This class has idCoalition, numOfMandats and a vector of parties.

## Project Flow
1. The program recieves JSON config file, parses it into the objects and builds the Simulation Object.
2. Main function(runs in iterations):
    - Checks if the termination conditions are satisfied.
    - Runs Simulation::step.
    - Saves the state of the simulation as JSON.
3. Simulation::step
    - Runs over the vector of paries and runs Party::step for each party.
        -  Party::step :
            -  checks state of the party.
            -  if state is CollectingOffers and timer is 3 than join a coalition according to the party's JoinPolicy.
    - Runs over the vector of agents and runs Agent::step for each party.
        -  Agent::step :
            -  checks is the agent can suggest to its neighboring parties.
            -  Sends suggestion to a neighboring party according to the agent's SelectionPolicy.

## Installation & Usage

### 0. The makefile was written and tested on linux ubuntu.

### 1. Clone the Repository
   ```bash
   git clone https://github.com/itayshaish06/CPP-Coalition-Race.git
   ```

### 2. Compile the Project
From the folder you cloned the project to, open the terminal and:
   ```bash
   make
   ```

### 3. Run the Program
The simulator takes a JSON configuration file as input, which defines the parties, agents, and initial graph structure.
   ```bash
   bin/cRace path_to_config.json
   ```
for example:
   ```bash
   bin/cRace customTests/MandatesSelectionPolicy1.json
   ```
or use the script that runs 9 tests and compare them to solution out files:
   ```bash
   bash script.sh
   ```
### 4. Visualize the Results (Optional)
Use the provided Python script to visualize the coalition formation process:
install packeges:
   ```bash
   sudo apt-get install libtiff5-dev libjpeg8-dev libopenjp2-7-dev zlib1g-dev \libfreetype6-dev liblcms2-dev libwebp-dev tcl8.6-dev tk8.6-dev python3-tk \libharfbuzz-dev libfribidi-dev libxcb1-dev
   sudo apt-get install python3-pip
   pip3 install networkx
   pip3 install matplotlib
   ```
Run:
   ```bash
   python3 visualization.py path_to_output_file.json
   ```
for example:
   ```bash
   python3 visualization.py customTests/MandatesSelectionPolicy1.out
   ```


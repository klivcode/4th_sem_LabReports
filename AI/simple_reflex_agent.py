'''
Lab 1 (Python): Reflex-based Intelligent Agent
Objective:
To design and implement reflex-based intelligent agents that make real-time decisions based on percepts from dynamic environments, such as traffic flow and presence detection.
To simulate environment-agent interaction using Python, demonstrating how agents can control systems like traffic signals and smart home lighting based on simple condition action rules.

'''

import random
import time
#case 1
# Traffic Light Control Agent
class TrafficEnvironment:
    # constructor to initialize the traffic light state
    def __init__(self):
        self.traffic_density="low"
        self.timer=0
        self.light="Red"
    
    def get_percept(self):
        return self.traffic_density,self.timer,self.light
    
    def update_Environment(self):
        self.traffic_density=random.choice(["low", "high"])
        self.timer+=1

    def execute_action(self, action):
        if action == "SwitchToGreen":
            self.light="Green"
            self.timer=0
            print("Action Light switched to Green")
        elif action=="SwitchToRed":
            self.light="Red"
            self.timer=10000
            print("Action Light switched to Red")
        else:
            self.light="Yellow"
            self.timer=100
            print("Action Light Switched to Yellow")

class TrafficLightAgent:
    def decide(self,traffic_density,timer,current_light):
        if current_light=="Red" and traffic_density=="High":
            return "SwitchToGreen"
        elif current_light=="Green" and traffic_density=="low":
            return "SwitchToRed"
        else:
            return "Yellow Light Get Ready"



#case 2 : Smart Light Authorization

class RoomEnvironment:
    def __init__(self):
        self.presence=False
        self.time="Day"
        self.light="OFF"
    
    def get_percept(self):
        return self.presence, self.time, self.light
    
    def update_environment(self):
        self.presence=random.choice(["True", "False"])
        self.time=random.choice(["Day","Night"])

    def execute_action(self,action):
        if action=="TurnOn":
            self.light="ON"
            print("Action: Light is turned ON")
        elif action=="TurnOFF":
            self.light="OFF"
            print("Action: Light is turned OFF")
        else:
            print("Action: No changes")

class SmartLightAgent:
    def decide(self,presence,time_of_day,current_light):
        if presence=="True" and time_of_day=="Night":
            return "TurnOn"
        elif presence=="False" and time_of_day=="Day":
            return "TurnOff"
        else:
            return "No changes"





#simulation 

def simulate_traffic_light_agent(step=5):
    print("\n----- Traffic Light Agent Simulation -----")
    env= TrafficEnvironment()
    agent=TrafficLightAgent()
   

    for step in range(step):
      print(f"\n [Step: {step+1}]")
      env.update_Environment()
      percepts=env.get_percept()
      print(f"Percept: Traffic Density {percepts[0]}, Timer {percepts[1]}, Light {percepts[2]}")
      action=agent.decide(*percepts)
      env.execute_action(action)
      time.sleep(1)
    print("\n----- Traffic Light Agent Simulation Ended -----")


def simulate_smart_light_agent(step=5):
    print("\n----- Smart Light Agent Simulation -----")
    env=RoomEnvironment()
    agent=SmartLightAgent()

    for step in range(step):
        print(f"\n [Step: {step+1}]")
        env.update_environment()
        percepts=env.get_percept()
        print(f"Percept: Presence {percepts[0]}, Time of Day {percepts[1]}, Light {percepts[2]}")
        action=agent.decide(*percepts)
        env.execute_action(action)
        time.sleep(1)

    
# run both simulations

if __name__=="__main__":
    simulate_smart_light_agent(step=5)
    simulate_traffic_light_agent(step=5)
   




# MicroChallenge-2-Energy-Bot
Welcome to the second microchallenge taken place during our Masters in Design for Emergent Futures at IAAC and ELISAVA in Barcelona. This challenge is a continuation of Oliver and my thesis project fociussing on energy usage and finding ways to decrease our consumption not only in homes but also in other systems. We worked on part of this project in our first micro challenge which can be found here (https://github.com/Oliver-Lloyd-MDEF/MDEF-Microchallenge-1-Energy-Monitors) 

# The Goal of this Challenge

After the first micro challenge we got talking about what ways we could push this opensource device further and how the chatbot aspect would work. As the idea of this challenge was to use a form of intelligence to create a physical output we had the first part figure out but the second part was a bit of a question for us. We brainstormed a bit and had various ideas what physical output could entail for our project. We thought about potentially create a daily report about ones use, or printing list of tips but in the end we thought about how we could raise awareness for the project and issues we are working on. 

The defined intelligence is: **An energy consumption chatbot powered by chatgpt to allow users to have a conversation about their energy usage**

The defined artifact is: **A low-tech energy monitor in combination with a AI generated sticker**

# The Process

https://github.com/ChylkemaMDEF/MicroChallenge-2-Energy-Bot/assets/147051108/a3cf86ed-9f80-4254-b6f6-062837d0c48b

### Creating the chatbot in NodeRed

Before this week we had talked quite a bit about the idea of our chatbot and which different inputs and outputs it would require. Next to this there were also a lot of different components that we needed to decide would be done algorithmicly and which would require some form of AI. To help us get a better understanding of which flows existed in our desired system we created the following flowchart.
![Energy Relationships - Frame 4](https://github.com/ChylkemaMDEF/MicroChallenge-2-Energy-Bot/assets/147051108/6891d68a-fe35-4787-ba5f-962272d0618c)

To then transform the idea in our head to an actual working system we took some time to understand what each component might entail and next to this also go back and forth using chatgpt about what potential functions could be used using NodeRed and also through looking at the NodeRed flows we were able to better understand what already exists. Things like using a form of AI like Chatgpt to process information and send data back to storing our data in GoogleSheets were already nodes that existed and could work to make our jobs slightly easier in the end. 
![Energy Relationships - Node-Red Flow Build](https://github.com/ChylkemaMDEF/MicroChallenge-2-Energy-Bot/assets/147051108/4eadfb89-f101-46ba-8cb9-60296ec0b6a4)

_The Bill of Material Energy Bot_
* NodeRed
* Google Sheets + Sheets API
* Google Cloud Project
* Telegram
* Open AI API Key -> For conversations and image generation
* Energy monitor below or TAPO Plug

_The process we went through to create Dan_

The process that we went through during the first microchallenge opened our eyes to the possibilities of NodeRed but also taught us a lot. For that reason we started this project slightly different. Instead of starting and trying to connect all nodes at once, we focussed on going through step by step through each input and output we wanted and working to create that functioning flow. We did this in tandem and worked together to go through every part of the flow chart mentioned above. In the end once every part was working by itself we started connecting them together. The flow itself for nodered ahs been added in the files, however there are still some limitations in the way that the telegram messages need to be set to your own chat_id and they are currently all linked to one bot instead of everyone having their own. While everyone can talk to dan it would essentially mean we would need the infrastructure to grow with each additional user, as it would require a new flow for new users as they need their own unique flow. As of now we do not have the storage capacity needed to run this at the moment. Next to this the messages still flow in such a way that it works on key words which means there are still a few limitations in what Dan can understand and respond to.  

### Building the Physical Device
![1](https://github.com/ChylkemaMDEF/MicroChallenge-2-Energy-Bot/assets/147051108/e078db04-d3c4-4c41-aa4d-105ae6893b0a)
The energy monitor system itself is based on the work and designs from the [Open Energy Monitor initiative](https://docs.openenergymonitor.org/index.html), the [OkDo Energy Monitor](https://www.okdo.com/project/smart-energy-meter-with-arduino-nano-every/)and the [Luzmon Energy Monitor by Adrien Laveuz](https://miro.com/app/board/uXjVN0VbEd4=/?moveToWidget=3458764580339700228&cot=14). 

It's made up of a simple circuit paired with an Arduino microcontroller. 

_How does it work?_
THe circuit uses a non invasive current transformer (CT) which are a special type of transformer in which the primary coil is the mains power cable in your building wiring, and the secondary coil is connected in series with a low-value resistor called a Burden resistor. The small current flowing in the burden resistor generates a voltage across it which can be measured and used to calculate the current flowing in the primary circuit. 

The CT we are using is rated at 100A, so it’s suitable for measuring the total power in a domestic home. It has 2000 turns : 1, so at its maximum primary current rating of 100A, it induces a 50mA secondary current:
100A / 2000 = 50mA

*The original cirucit we based ours on used an arduino Nano Every, but seeing as ours broke we switched to an arduino UNO*

To adapt the circuit for the Arduino UNO instead of the Arduino Nano Every, we needed to account for the fact that both boards use a 10-bit ADC, but they are based on different microcontrollers. The Arduino UNO is based on the ATmega328P microcontroller, not the ATMega4809. However, the ADC resolution calculation remains the same because both use a 10-bit ADC.

Here's the revised text:

The Arduino UNO is based on the ATmega328P microcontroller, which also has a 10-bit (0 – 1023) Analogue to Digital Converter (ADC) for measuring voltages between 0V and 5V. This gives a resolution of 4.9mV per division, which is quite sensitive:

5000mV / 1024 ≈ 4.88mV

Like with the Nano Every, the ADC of the Arduino UNO can only measure voltages between 0V and 5V (it can be damaged if you exceed these limits), but the mains AC current alternates above and below zero, so the current in the burden resistor will do so in proportion.

If the signal is offset by a DC voltage at 2.5V (called DC biasing) the burden resistor can be sized such that the peak to peak (P2P) voltage is just below 5V, to get the highest resolution and stay within the ADC tolerances.

Now, let's calculate the burden resistor for a 100A @ 50mA CT for the Arduino UNO:

Primary P2P current = 100A rms x √2 = 100 x 1.414 ≈ 141.4A

Secondary P2P current = Primary P2P current / Turns = 141.4A / 2000 ≈ 70.7mA

Burden resistance = 2.5V / Secondary P2P current = 2.5V / 70.7mA = 35.4Ω

33Ω is the closest standard resistor size below 35.4Ω, providing a margin of safety for the ADC and is sufficiently low to prevent the CT from saturating.

# The Outcomes
### Dan Working and Generating Images

_Outputted Stickers_

### The Current state of Energy Measurer

# Reflecting and Moving Forward

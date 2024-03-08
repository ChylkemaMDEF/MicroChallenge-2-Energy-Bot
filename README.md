# MicroChallenge-2-Energy-Bot
Welcome to the second microchallenge taken place during our Masters in Design for Emergent Futures at IAAC and ELISAVA in Barcelona. This challenge is a continuation of Oliver and my thesis project fociussing on energy usage and finding ways to decrease our consumption not only in homes but also in other systems. We worked on part of this project in our first micro challenge which can be found here (https://github.com/Oliver-Lloyd-MDEF/MDEF-Microchallenge-1-Energy-Monitors) 

# The Goal of this Challenge

After the first micro challenge we got talking about what ways we could push this opensource device further and how the chatbot aspect would work. As the idea of this challenge was to use a form of intelligence to create a physical output we had the first part figure out but the second part was a bit of a question for us. We brainstormed a bit and had various ideas what physical output could entail for our project. We thought about potentially create a daily report about ones use, or printing list of tips but in the end we thought about how we could raise awareness for the project and issues we are working on. 

The defined intelligence is: **An energy consumption chatbot powered by chatgpt to allow users to have a conversation about their energy usage**

The defined artifact is: **A low-tech energy monitor in combination with a AI generated sticker**

# The Process

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


# The Outcomes
### Dan Working and Generating Images

_Outputted Stickers_

### The Current state of Energy Measurer

# Reflecting and Moving Forward

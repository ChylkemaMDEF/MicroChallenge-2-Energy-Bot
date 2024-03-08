# MicroChallenge-2-Energy-Bot
Welcome to the second microchallenge taken place during our Masters in Design for Emergent Futures at IAAC and ELISAVA in Barcelona. This challenge is a continuation of Oliver and my thesis project fociussing on energy usage and finding ways to decrease our consumption not only in homes but also in other systems. We worked on part of this project in our first micro challenge which can be found here (https://github.com/Oliver-Lloyd-MDEF/MDEF-Microchallenge-1-Energy-Monitors) 

# The Goal of this Challenge

After the first micro challenge we got talking about what ways we could push this opensource device further and how the chatbot aspect would work. As the idea of this challenge was to use a form of intelligence to create a physical output we had the first part figure out but the second part was a bit of a question for us. We brainstormed a bit and had various ideas what physical output could entail for our project. We thought about potentially create a daily report about ones use, or printing list of tips but in the end we thought about how we could raise awareness for the project and issues we are working on. 

The defined intelligence is: **An energy consumption chatbot powered by chatgpt to allow users to have a conversation about their energy usage**

The defined artifact is: **A low-tech energy monitor in combination with a AI generated sticker**

# The Process

https://github.com/ChylkemaMDEF/MicroChallenge-2-Energy-Bot/assets/147051108/a3cf86ed-9f80-4254-b6f6-062837d0c48b

## Creating the chatbot in NodeRed

Before this week we had talked quite a bit about the idea of our chatbot and which different inputs and outputs it would require. Next to this there were also a lot of different components that we needed to decide would be done algorithmicly and which would require some form of AI. To help us get a better understanding of which flows existed in our desired system we created the following flowchart.
![Energy Relationships - Frame 4](https://github.com/ChylkemaMDEF/MicroChallenge-2-Energy-Bot/assets/147051108/6891d68a-fe35-4787-ba5f-962272d0618c)

To then transform the idea in our head to an actual working system we took some time to understand what each component might entail and next to this also go back and forth using chatgpt about what potential functions could be used using NodeRed and also through looking at the NodeRed flows we were able to better understand what already exists. Things like using a form of AI like Chatgpt to process information and send data back to storing our data in GoogleSheets were already nodes that existed and could work to make our jobs slightly easier in the end. 
![Energy Relationships - Node-Red Flow Build](https://github.com/ChylkemaMDEF/MicroChallenge-2-Energy-Bot/assets/147051108/4eadfb89-f101-46ba-8cb9-60296ec0b6a4)

### The Bill of Material Energy Bot
* NodeRed
* Google Sheets + Sheets API
* Google Cloud Project
* Telegram
* Open AI API Key -> For conversations and image generation
* Energy monitor below or TAPO Plug

_The process we went through to create Dan_

The process that we went through during the first microchallenge opened our eyes to the possibilities of NodeRed but also taught us a lot. For that reason we started this project slightly different. Instead of starting and trying to connect all nodes at once, we focussed on going through step by step through each input and output we wanted and working to create that functioning flow. We did this in tandem and worked together to go through every part of the flow chart mentioned above. In the end once every part was working by itself we started connecting them together. The flow itself for nodered ahs been added in the files, however there are still some limitations in the way that the telegram messages need to be set to your own chat_id and they are currently all linked to one bot instead of everyone having their own. While everyone can talk to dan it would essentially mean we would need the infrastructure to grow with each additional user, as it would require a new flow for new users as they need their own unique flow. As of now we do not have the storage capacity needed to run this at the moment. Next to this the messages still flow in such a way that it works on key words which means there are still a few limitations in what Dan can understand and respond to.  

https://github.com/ChylkemaMDEF/MicroChallenge-2-Energy-Bot/assets/147051108/8ffb0e59-4fab-4c03-a1a0-11ed83f2c7f5

## Building the Physical Device

![1](https://github.com/ChylkemaMDEF/MicroChallenge-2-Energy-Bot/assets/147051108/e078db04-d3c4-4c41-aa4d-105ae6893b0a)
The energy monitor system itself is based on the work and designs from the [Open Energy Monitor initiative](https://docs.openenergymonitor.org/index.html), the [OkDo Energy Monitor](https://www.okdo.com/project/smart-energy-meter-with-arduino-nano-every/)and the [Luzmon Energy Monitor by Adrien Laveuz](https://miro.com/app/board/uXjVN0VbEd4=/?moveToWidget=3458764580339700228&cot=14). 

It's made up of a simple circuit paired with an Arduino microcontroller. 

### How does it work?

THe circuit uses a non invasive current transformer (CT) which are a special type of transformer in which the primary coil is the mains power cable in your building wiring, and the secondary coil is connected in series with a low-value resistor called a Burden resistor. The small current flowing in the burden resistor generates a voltage across it which can be measured and used to calculate the current flowing in the primary circuit. 

The CT we are using is rated at 100A, so it’s suitable for measuring the total power in a domestic home. It has 2000 turns : 1, so at its maximum primary current rating of 100A, it induces a 50mA secondary current:
100A / 2000 = 50mA

*The original circuit we based ours on used an arduino Nano Every, but seeing as ours broke we switched to an arduino UNO*

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


## The Circuit

### Circuit Bill of Materials

You will need the following: 
    1x Arduino UNO Board - The central microcontroller board for the project.
    2x 10k Ohm Resistors (R1 & R2) - Two resistors forming a voltage divider to create a 2.5V DC offset.
    1x 33 Ohm Resistor (R3) - The burden resistor connected across the CT terminals.
    1x 1k Ohm Resistor (R4) - A current-limiting resistor to protect the ADC pin.
    1x 1uF Capacitor - Provides a low impedance bypass to the ground.
    1x Current Transformer (CT) - The primary sensor for the project, with a built-in diode for protection and safety.
    1x Standard Microphone Jack - Used to connect the CT to the Arduino's analog input A1.
    1x Adafruit 1.14" 240x135 Color TFT Breakout LCD Display - This will be used to display the measurements or output from the Arduino UNO.
    Jumper Wires/Connectors - To make all the necessary connections on the breadboard or PCB.
    1x Breadboard - To build out the prototype circuit.

### How the circuit works

The circuit itself is actually quite simple. The two 10k Ohm resistors, R1 & R2, form a voltage divider, this halves the 5V supply voltage provided by the Arduino’s 5V pin to 2.5V. This creates the DC offset for the Current Transformer, which is connected between the centre of the voltage divider and the analogue input A1 using a standard microphone jack.

The 33 Ohm Burden resistor R3 is connected across the CT terminals, and a 1uF capacitor provides a low impedance by-pass to the ground. The 1k Ohm current limiting resistor R4 protects the ADC pin.

All the other connections are for the e-Paper display, which is detailed next.

Warning: Never install the CT with the power on. Always make sure the burden resistor is connected before turning on the power. The CT recommended for this project has a diode for protection and safety built into the device.

![Circuit diagram layout](https://github.com/ChylkemaMDEF/MicroChallenge-2-Energy-Bot/assets/147057296/18aa0ee7-1e1b-4534-b882-4419352a31e5)

### The Code you'll need
The code we used for this project was adapted from [OkDo's Github Repository](https://github.com/LetsOKdo/arduino-power-meter/tree/main/epd2in9-demo) and modified to adapt to the adafruit mini oled screen we've used. you can download it from this Github repository in the code file section!

The way this code works is that it measures the voltage across the burden resistor by rapidly sampling the ADC to digitise the AC signal by filtering out the DC offset and calculating the RMS current in the secondary coil. This is then scaled to the RMS current in the primary coil.

A fixed value is used for the primary RMS voltage so the Real Power can be calculated along with the cost per kWh. This is a simplified approach but is easier to understand and code, but it works really well. We got well within 2% of our electricity company’s smart meter readings.

Important values are configured at the top of the listing; some of them can be adjusted to obtain more accurate readings. Details of calibrating these are in the next section.

The current ratio is set according to the number of turns in the CT’s secondary coil divided by the value of the burden resistor:

        const float current_ratio =  2000.0 / 33.0;

**Note: In C/C++, it is important to include decimal places for floating point numbers to indicate to the compiler; otherwise, you can get integer arithmetic which will give very different results!**

This is the DC bias set by the resistor divider circuit – both resistors should be about the same value, so it should be set to 512.

        int16_t adc_bias = 512;

The next macro sets the value for the Arduino supply voltage – this is used in converting the ADC reading, which is an integer into a voltage – nominally, it is 5V but can be adjusted.

        #define ARDUINO_V 4.8

Your electricity cost per kWh is set in this macro – ours is in pence, and it is multiplied by the power figure to obtain the cost shown on the display:

        #define COST_PER_KWHR 28.5

The final value of importance is the mains RMS voltage – this varies depending on your location – ours is about 240V:

        #define MAINS_V_RMS  240.0

The low pass filter function removes the DC bias from the AC signal. We put it in its own file so we could test it – lowpass.h & lowpass.cpp

It takes two parameters, a pointer to the bias variable and the ADC reading, which will be a value between 0 and 1023. The return value is an integer with the DC offset removed or filtered out. It will be positive if the raw reading is above 512, and negative if it is below. It needs to be very fast so that it can be called multiple times to sample the signal quickly enough.

Note: The data types and use of integer division are necessary to ensure the correct return.
        
        int16_t intLowPass(int16_t* bias, int16_t raw) {
          *bias = (*bias + ((raw - *bias) / 1024)); // int division!
          return raw - *bias;
        }

The next section in main() is where the ADC is sampled. Each reading from the filtered output is squared to remove any negative values and accumulated in a 32-bit wide variable which is large enough to hold all the samples.

         int32_t adc_sum_sqr = 0;
          for (int n = 0; n < NUM_OF_SAMPLES; n++)
          {
            int16_t adc_raw = analogRead(ADC_PIN);
            int16_t adc_filtered = intLowPass(&adc_bias, adc_raw);
            adc_sum_sqr += adc_filtered * adc_filtered;
          }

If you take the square root of the average reading and scale it by the Arduino supply voltage, you get the RMS voltage across the burden resistor. This is proportional to the primary current.

         double vrms = sqrt(adc_sum_sqr / NUM_OF_SAMPLES) * ARDUINO_V / 1024.0;

Multiply the burden voltage by the current ratio to get the primary RMS current:

         double Irms = vrms * current_ratio;

Multiply primary RMS current by the primary RMS voltage, and we have the power in Watts:

         double active_power = Irms * MAINS_V_RMS;

From this, the cost per kWh can be calculated and rounded for the display:

         double rnd_cost = round(active_power * COST_PER_KWHR / 1000.0);

All the rest of the code deals with managing and displaying the results on the EPD. Values need to be converted to strings for display purposes using the val_to_str() function.


# The Outcomes
## Dan Working and Generating Images
The way Dan works currently is that he takes a variety of inputs coming in through telegram and holds a conversation with the user. Next to this he is also constantly taking input from the plug and logging this into a google sheets. This database allows for him to get a better understanding of the users past behavior and give specific tips based on the persons personal usage. There are still a few bugs but that is for us to work out in the future. Below a video is shown in which you can see the interaction that one has with Dan.

_Outputted Stickers_

As you can see in the video when you ask for energy saving tips it also automatically sends a generated image for a sticker that you can use. For this we then decided to make a physical sticker that people could take and stick to dfferent appliances in a way to raise awareness and potentially in the future also be specific to their own usage. This was just a fun addition we created however for the functionaloty of the system one could keep them as a digital sticker or omit it to save on the energy usage that is needed to run the machine, taking into consideration the use of an AI image generator.  

## The Current state of Energy Measurer

At the moment we have a functioning energy monitor that we have built with easy to source components from a local electronics store. At the moment there is a slight issue with the calculation of the ampere and voltage of the measurements but this is most likely due to the type of wire we are trying to measure over. As a professor mentioned to us it is not possible to use current transformers over geenral appliance wires as they contain three different wires running through it not just one that you need. In turn this means our monitoring device can only be used as we designed in breaker boxes. This is fine as you still do not need to cut or open wires just clip and it is ready to go.
![Ontwerp zonder titel](https://github.com/ChylkemaMDEF/MicroChallenge-2-Energy-Bot/assets/147051108/eb4e8ff9-9d79-4751-a431-341cff0a1fed)


# Reflecting and Moving Forward

This microchallenge has been a lot of fun, we've made significant progress in our research into measuring and understanding energy consumption, as well as how we can combine this information with big data technologies like AI in a collaborative and conversational way. 

We made even more progress in understanding our skills in coding and basic programming using tools like Node-Red, coding with Javascript and Arduino as well as understanding how to adapt existing state of the art technologies through different API calls.

It was nice this time around do a bit of hardware development, even if it was just a basic circuit to understand the real world aspects of our research, which was a welcome change to just working on software as we did in the previous microchallenge.

We can definitely feel ourselves adapting as designers, turning into hybrid designers from pure product designers we were before, this an exciting area for both of us as we've been able to explore a range of interests we've had that that we might otherwise not have been able to engage with as much in the past.

Moving forward we'd like to continue working on this energy monitor prototype, developing the circuit further to use a different microcontroller with an integrated ESP332 moudule, which would allow us to consolidate hardware into a mich smaller package, as well as publish the recieved energy information to our Node-Red Dashboard and our friendly energybot Dan. 

Building on this we'd like to create a custom PCB that integrates all the individual components we've used onto one board, and do a bit of old fanished product design to create an appealing and usable casing that would faciliate an intuitive user experience and actually look like a consumer facing product.

We plan to develop a few prototypes that we could send to some volunteer Alpha testers, where we could then engage with our community through user led design feedback to better improve both Dan the energy bot and our energy monitor, to be able to investigate further our research idea of reducing consumption without lowering quality of life.

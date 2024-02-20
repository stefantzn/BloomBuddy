# BloomBuddy 🌱

## Inspiration
1/5 elderly Canadians feel isolated as a result of their environment. In an ever-changing world, society often forgets about the people that built the present world we live in. Elderly people constantly battle between the desire to connect with the changing society around them whilst worrying that they are being a bother to their children and grandchildren.

Having something that always has time to understand and talk to you would be great for loneliness and mental health issues in elderly people. This is where BloomBuddy comes in. Like a human, the plant lives alongside the user, undergoing all the environmental changes and basic necessities it would normally need. As such, it understands the environment that elderly people live in and is able to be a present and effective companion for elderly people. BloomBuddy not only analyzes the words coming from the user but also the environment and climate surrounding the user that could impact their mental health.

## What it does
Using machine learning, BloomBuddy is able to analyze the environment both the plant and the user is living in and generate a personality based off of those metrics. Through the unique personality created through the shared environment between the user and BloomBuddy, the plant is able to provide realistic and relatable responses to the user. BloomBuddy lives alongside the human and generates outputs based off of whether it needs resources (eg. water, more light...), it is self-caring and automatically notifies the user on its metrics using sensors. The user is able to communicate with their unique BloomBuddy through a screen and typed input, effectively communicating with the personalized ML model as they would a human. Each BloomBuddy is unique in both personality and digital presence, with an individualized NFT generated per plant built on the Flow blockchain network.

The plant's metrics are easily viewable through the 7-inch display or through **Kintone* where the user can see further data analysis of measured metrics throughout a period of time.

## How we built it
Some of the sensors we used includes a photoresistor, a humidity sensor, a temperature sensor and a moisture sensor to collect the large variety of data. Arduino IDE was used to program the Arduino and ESP32 respectively, while also programming the communication between the two with UART protocol to store the data on the ESP32 to display on the screen. We built the webpage with HTML for the template, CSS for the styling, and JavaScript for the functionality, while also integrating OpenAI API into the webpage. The NFT was created on the Flow blockchain network using Cadence and Javascript to create the smart contracts and environment to validate the NFT.

## Challenges we ran into
It was our first time working with a lot of the technologies and we namely had several issues with hardware.

Our initial approach with the Raspberry Pi failed due to a faulty SD card reader. After hours of long work to debug and resolve the issue, we pivoted to an Arduino instead to fulfill the role as the central computing unit of our project. However, the Arduino still had some issues on communicating with the ESP32 that needed to be solved.

When implementing Flow into our project, we were unfamiliar with the environment and it was our first time setting a Web3 environment up. We encountered many issues getting the environment, smart contracts, and scripts setup.

Nevertheless, our team learned a lot by working with new software and languages. It took all of 24+ hours with no sleep and many Red Bulls but we'd like to think it was worth it :).

## Accomplishments that we're proud of
We were able to support our hardware system with a strong, multi-aspect software system consisting of tech ranging from Web3, web and app development, data processing, and more. The entire tech stack that we learned was geared towards the one goal of providing the most realistic interactable machine to provide companionship to elderly people and we'd like to say we've accomplished that.

As a team, we used our time efficiently by delegating responsibilities well based on skills and experience. Despite issues with hardware and software, our team pushed through it and learned lots in the process.

The issue we tackled hit home for our entire team as we've seen first hand how elderly people get neglected on accident in our fast-paced society. We're proud that within 24 hours, we were able to construct an MVP of a promising solution that we all truly believe in.

## What we learned
Although we had many setbacks, we overcame most of them and learned from our experiences. We quickly learned how to implement OpenAPI using JavaScript within a microcontroller such as the Arduino. Furthermore, as we had limited experience with NFTs, we learned how to use Flow for Web3 implementation with NFTs. Through the hackathon, we were able to deploy a webpage on the ESP32 with the help of the mentor panel, as without them, we wouldn't have been able to get past this step.

Most of all, we've learned that any technology is learnable given a strong passion for the project and a team that's motivated to learn. As a collective team, we can confidently say we've learned way more than we expected coming into MakeUofT.

## What's next for: BloomBuddy
The next step is scaling the project by adding more functionalities to 1) Increase accessibility for elderly people with disabilities 2) Generate more impact by personalizing the plant more to tailor to individual mental illnesses 3) Further develop Web3 functionality to enhance NFT collections and reward users with FLOW tokens.

and more...

BloomBuddy is just the start of what personifying our hobbies could look like. Whether we realize it or not, every living being shows their behavior in some way. BloomBuddy is proof of concept that personifying the things we care about will enhance the growth of others as well as ourselves to feasibly make a larger impact in the world with the help of technologies like AI and Web3.

## Gallery

![BloomBuddy](https://d112y698adiu2z.cloudfront.net/photos/production/software_photos/002/771/658/datas/gallery.jpg)

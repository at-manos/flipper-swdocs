---
sidebar_position: 6
---

# Software Diagram

Before getting into any programming, I think it's important to get a quick glance at the terms you'll be encountering.



<!-- ## s -->

![Flipper Software Diagram](/img/flipper_sw.png)
- Services
  - Not seen by the end-user.
  - Programs and headers to assist in the process of writing applications
  - Provides interface with common features, such as storage, notifications, gui, etc.
  - These will be explored in more depth in another chapter.
- Applications
  - Seen by the user
  - Includes "plugins" as well.
  <!-- - change dis -->
  - Examples: Wav player, infrared, almost everything on the ![Ok](/img/buttons/ok.svg) menu 
- Furi
  - Originally standing for "Flipper Universal Registry Implementation", but has lost its meaning.
    - Now "officially" just a shortening of フリッパー, <i>**furi**ppa</i>, as per Aleksandr Kutuzov.
  - Responsible for OS and HAL abstraction layers. Also extra primitives for concurrent programming, etc



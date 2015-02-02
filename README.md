# ChemistsFun

Simple game concept for U of A hackathon. This was developed in 24 hours so I apoligize for the code quality, it was rather rushed.

Utilized a variation of Box2d called Liquidfun which is an open source physics engine written in C++. The end result of the application is a simple 1 level demo running as a windows 8 app. It shows the basic fluid capabilities of liquidfun, namely there are emitters that countinously drop fluid the 'player' (a rectangle) must move through, a platform that the fluid will raise and a set of jets the player can 'hover' over to get to another section.

Some postmortum stuff:

What worked:

Liquidfun worked amazing with little effort. It took a while to figure out how to use it but once the basics were setup everything just fell into place.

Direct2D was an effective way to get some quick and easy rendering running. It was performant enough to show a single screen with a large number of fluid particles. It did start to slow down once we had a couple thousand particles on screen but that is to be expected.

Demo - The demo went great. We had a few basic building blocks that were used to construct an excellent demo level. The demo was composed of only a handful of static blocks, some fluids, some emitters, some jets and a floating block. 

What didn't work

Preperation - Planned to do a windows 8 app but not all developers had a windows 8 dev environment setup. This was not discovered until a couple of hours into the project after all dependencies and project setup had already been completed. We decided to continue with what we had but this limited one member of the team severly.

Memory Managment - A poor initial understanding of how Liquidfun handled memory managment caused a few crashs. Basically the pointers that Liquidfun provides are non-owning, but I thought they were owning and wrapped them in smart pointers which caused crashes when the physics system was unloaded. Additionally cleanup of the simulator was not handled correctly which caused the simulation to keep running after the memory had been cleaned up. Simple issues to resolve (as their source and implications are known) but they were not resolved due to the time constraints. Instead only 1 level was demo'd so no cleanup was ever needed.

Scope - We planned a great deal more than we were capable of. The original design called for multiple interacting fluid types. We barely had time to get a single fluid and some basic interaction working.

Sleep deprivation - Progress pretty much tanked early morning as we all were very tired.


Overall Result:

Project turned out surprisingly well. We won the honorary mention for software project and the end result was actually complete and presentable as a concept / prototype. The project is more so a game design sandbox for testing out a couple of ideas of fluid based platforming mechanics. The concept has potential to be expanded.

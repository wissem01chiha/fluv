

The Runtime Monitor is a component part of the [Watchdog Module](Watchdog%20Module) that
is responsible for monitoring the execution time of a component or a set of components, 
depending on the configuration.

the runtime monitor should track the execution time of components and alert if they exceed predefined thresholds.
the runtime monitor should be configurable to define what constitutes a threshold breach.
the runtime monitor can be totally enabled or disabled in the engine configuration.
the runtime monitor when enabled can be enabled for some components and disabled for others.
it should provide alerts or notifications when thresholds are exceeded.
it should allow for multiple components to be monitored simultaneously.

> [!NOTE]
> a single component can be used many times in the graph model, and thus, many
> instances of the same component can be executed in the engine, parallelly or
> sequentially, depending on the engine configuration.

The runtime monitor triggers an event in the following cases:
- A single instance component surpasses the maximum allocated time for execution, this parameter is preconfigured in the component configuration at build time and cannot be changed at runtime.
- The averaged execution time of a component surpasses the maximum allocated time, this is in timeout aggregation mode.
this average is computed over a number of execution instances of the same component in all the computation model
- The combined execution time of all instances of a component surpasses the maximum allocated time.

Functional Specifications:
What happens if this cases occur?
The RM sends an event to the Engine event module , they this
The Eem dispatches the call to Dem and the Fsm to handl it as a failsoft and keep engine running
What interface services it provide ?


[link](https://mianshi.idocdown.com/en/app/articles/blogs/detail/1821#google_vignette)
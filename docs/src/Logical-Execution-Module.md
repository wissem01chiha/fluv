

This package manages the logical execution timing for components, giving an
abstraction over physical timing mechanisms (each component has a logical
execution time and a physical execution time).

The LET component allows control of execution time of components in strict
control loops. Components can have different physical runtime execution times,
but this is not allowed in some systems; deterministic execution shall be
fulfilled. This component is only configured when the engine is configured to
run in scheduled execution mode; for other engine models it is, by design,
ignored.

The logical execution time is a key concept in ensuring that components behave
deterministically, even when their physical execution times may vary. This is
particularly important in real-time systems, where meeting deadlines is critical.


ZET programs are reactive, i.e., always react to input with some output,

Note the Logical Execution Timer is only enabled in the timer-triggered execution mode, and it is disabled in the event-triggered execution mode.(not supported)

        Dataflow/Application definition
                    │
                    ▼
             Logical schedule
                    │
          ┌─────────┴─────────┐
          │                   │
      Component A         Component B
          │                   │
          ▼                   ▼
      LET runtime         LET runtime
          │                   │
          └─────────┬─────────┘
                    ▼
           Physical scheduler
                    │
                    ▼
               CPU / cores



## Overrun Execution Manager

In the context of the Logical Execution Module, an overrun occurs when a component's physical execution time exceeds its logical execution time. This can lead to missed deadlines and unpredictable behavior in real-time systems.

so what the engine should do when an overrun has been detected (which is gotten by the Physical Runtime Monitor)

when an overrun is detected, the Overrun Execution Manager (OEM) takes the following actions:

- cretaes an evnet to the Diagnostic Event Manager (DEM) to log the overrun event and notify the system of the timing violation.
- if 
Policy D: Fail the graph

For strict real-time operation,  the engine stop immediately if it is configurated to  fail the entire execution graph when an overrun is detected. This ensures that the system does not continue operating under potentially invalid assumptions about timing and execution.

# MultiRate Transition Manager

when the engine is configured to run in time-triggered mode, a common problem arises which is between fast and slow
running components, leading to undefined transfer behavior of dataflow , so a dedecieted communication manager is need to handle these policies


1. Fast producer → slow consumer



## Initialization Manager


## Data Integrity In Mixed Execution Mode

The Initialization Manager is responsible for setting up the initial state of the system and its components. This includes configuring the logical execution times, physical execution times, and any other parameters necessary for the components to function correctly within the defined execution model.
An event-triggered component observes the latest committed producer value whose logical publication timestamp is less than or equal to the event's logical timestamp

References:
- [Giotto: A Time-Triggered Language for Embedded Programming](https://ckirsch.github.io/publications/journals/ProcIEEE03-Giotto.pdf)
- [ARTS: A Real-Time Scheduling Framework for Time-Triggered Systems](https://cs.uni-salzburg.at/~anas/papers/ARTS-chapter.pdf)
- [Real-Time Systems: Scheduling, Analysis, and Verification](https://link.springer.com/book/10.1007/978-3-319-99966-0)
- [Logical Execution Time: A New Paradigm for Real-Time Systems](https://ieeexplore.ieee.org/document/8761234)
- [Rate Transition Blocks Explained](https://ethz.ch/content/dam/ethz/special-interest/mavt/dynamic-systems-n-control/idsc-dam/Lectures/Embedded-Control-Systems/AdditionalMaterial/Miscellaneous/Rate_Transition_Blocks_Explained.pdf)
- [Handling Rate Transitions in Simulink](https://www.mathworks.com/help/simulink/ug/handle-rate-transitions.html)
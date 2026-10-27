Component testing in a flow-based paradigm is much easier: it only requires creating the appropriate input test file and running the component against it. No direct API calls are needed. Therefore, when internal APIs change, the tests remain valid and do not need to be updated. For example, the same tests can be rerun after changing a single line of code, saving considerable time and effort compared with refactoring tests after changes to the traditional public API.

FBB provides basic infrastructure for defining and maintaining flow-based unit and regression tests.

## Testing a single component

To test a single component, create a test harness that runs it in an isolated environment and wraps it with the required input/output helpers. FHar is the relevant submodule.

## Testing multiple components

### Test manager

The flow test manager is responsible for managing test cases and input and output data for component tests. It can:

- Run a selected set of tests against a selected set of components.
- Report test results.

### Composite nodes and test aggregation

Testing composite nodes or components is challenging because of their nested, hierarchical structure. A submodule of FBB aggregates the separate input test data for each individual node or component into a single test data file. This file contains all the subtest data, mapped to the corresponding nodes. When the file is passed to test runners, they expand it until they reach the individual unit test data. This feature makes it possible to merge different developers' unit test inputs into a global set and feed it into the graph.

However, each component can have multiple test cases, so aggregating all possible combinations can become a problem. For example, if a composite component has three subcomponents or nodes, each with $n$ test cases, combining them creates $n \times n \times n$ test cases. The number can grow rapidly: adding a unit test case for one component increases the number of global system tests by a factor of $n^2$.

Each combination is called a test set.

## Built-in fuzz testing features

Because of the design of flow-based applications, fuzzing is much simpler. FFuzz is FBB's built-in fuzzer module, responsible for launching fuzzers supported by backends such as:

- Clang LibFuzzer
- AFL
- ...

FBB has a built-in fuzzing engine that generates controlled input data and feeds it to the [source nodes]() of the network. Any crashes in component nodes are collected by the diagnostic event manager and reported.

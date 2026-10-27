![GitHub License](https://img.shields.io/github/license/wissem01chiha/fbb)

fluv is a set of optimized runtime components/libraries and various development tools written mainly in modern C++, with multiple language bindings that let you write data intensive applications in flow-based paradigms (see below for more info).

fluv is designed with performance in mind, targeting large-scale distributed complex dataflow execution graphs.

Due to the architectural design of flow-based applications, which rely on separate node/components processing data tokens/information packets, the parallelism of such programs is significant; thus, the fluv core runtime is built around multithreading and [SIMD](https://en.wikipedia.org/wiki/Single_instruction,_multiple_data) features of modern processor units.

Writing flow-based programs often requires rethinking system design. Instead of direct callbacks, which create strong coupling between components (for example, changing a class's public API may require updating all dependent code and tests), standardizing how black-box nodes communicate through messages and callback signatures reduces coupling. Unit tests remain stable while internals change. Adding or removing a node affects program output only; no changes are required to nodes' private or public APIs.

In computer programming, flow-based programming is a programming paradigm that defines applications as networks of "black box" processes, which exchange data across predefined connections by message passing, where the connections are specified externally to the processes. These black box processes can be reconnected endlessly to form different applications without having to be changed internally. FBP is thus naturally component-oriented.

FBP is a particular form of dataflow programming based on bounded buffers, information packets with defined lifetimes, named ports, and separate definition of connections.

One interesting aspect of this implementation is that it supports scripting languages, so large parts of your networks can be written in a scripting language if desired.

>[!CAUTION]
> Fbb brings flow-based software architecture to conventional software design without requiring developers to adopt a new programming language or read a long documented API. Components are entirely written using common imperative programming languages, while Fbb provides the component model and runtime layer needed to build, run, and test them together without a lot of hassle.


> [!NOTE]
> Although the project started as a fork of [jpaulmorrison](https://jpaulm.github.io/fbp/)'s work, it's now a completely different software, with a different license; however, a homage to jpaulmorrison is included in the copyright notices.

- [Getting-Started](Getting-Started)
- [Developer Notes](Developer-Notes)
- [Design Notes](Design-Notes)
- [Resources](Resources)
- [FAQ](FAQ)


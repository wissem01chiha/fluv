# Contributing Guide

Absolutely. Here's a reusable naming convention document that you can share with other agents, LLMs, or developers.

Software Architecture Naming & Abbreviation Convention

Version: 1.0
 Purpose: Define a consistent abbreviation scheme for architecture diagrams, component names, header files, class names, namespaces, and identifiers.

Core Principles
Use recognizable abbreviations.
Remove non-essential vowels.
Preserve industry-standard abbreviations when they exist.
Concatenate abbreviated words without separators.
Use lowercase for all generated abbreviations.
Keep abbreviations stable across the entire codebase.
Prefer readability over maximum shortening.
Standard Dictionary
Systems & Components
Full Term	AbbreviationInformation	info
Packet	pkt
Component	cmpnt
System	sys
Module	mdl
Plugin	plgn
Engine	eng
Unit	unit
Service	svc
Framework	frmwrk
Management
Full Term	AbbreviationManager	mgr
Management	mgmt
Monitor	mntr
Controller	ctrlr
Scheduler	schd
Handler	hndlr
Events
Full Term	AbbreviationEvent	evnt
Trigger	trg
Dispatcher	dsptchr
Gateway	gtwy
Store	str
Source	src
Data Processing
Full Term	AbbreviationData	dta
Processing	prc
Provider	prvdr
Request	rqst
Response	rsp
Cache	cch
Chunker	chnkr
Stream	strm
Networking
Full Term	AbbreviationNetwork	ntwk
Topology	topo
Node	nd
Transmit	tx
Receive	rx
Protocol	prtcl
Reliability & Runtime
Full Term	AbbreviationFail Safe	flsf
Timeout	tmout
Heartbeat	hrtbt
Diagnostic	diag
Watchdog	wtchdg
Activation	actv
Execution	exec
Enable	enbl
Resources
Full Term	AbbreviationResource	rsc
Memory	mem
Configuration	cfg
Token	tkn
Registry	rgstr
Repository	repo
Composition Rules
Rule 1: Multi-word Names

Combine abbreviated words directly.

Examples:

Information Packet
-> infopkt

Event Store
-> evntstr

Backpressure Manager
-> bkprsmgr

Resource Manager
-> rscmgr

Event Management System
-> evntmgmtsys

Rule 2: System Names

Pattern:

<function><sys>


Examples:

Event Source System
-> evntsrcsys

Input Cache System
-> inpcchsys

Engine Logging System
-> englogsys

Plugin System
-> plgnsys

Rule 3: Manager Names

Pattern:

<domain><mgr>


Examples:

Component Manager
-> cmpntmgr

Module Manager
-> mdlmgr

Activation Manager
-> actvmgr

Resource Manager
-> rscmgr

Rule 4: Engine Names

Pattern:

<purpose><eng>


Examples:

Data Chunker Engine
-> dtachnkreng

Execution Engine
-> execeng

Validation Engine
-> valeng

File Naming Convention
Header Files
evntmgmtsys.hpp
cmpntmgr.hpp
rscmgr.hpp
evntdsptchr.hpp
dtachnkreng.hpp

Source Files
evntmgmtsys.cpp
cmpntmgr.cpp
rscmgr.cpp
evntdsptchr.cpp
dtachnkreng.cpp

Class Naming Convention

Use PascalCase while preserving abbreviations.

Examples:

class EvntMgmtSys;
class CmpntMgr;
class RscMgr;
class EvntDsptchr;
class DtaChnkrEng;

Namespace Convention
namespace evntmgmt
{
}

namespace cmpnt
{
}

namespace rsc
{
}

Examples From Current Architecture
Full Name	AbbreviationEvent Management System	evntmgmtsys
Event Source System	evntsrcsys
Event Gateway	evntgtwy
Event Dispatcher	evntdsptchr
Event Store	evntstr
Node Watchdog	ndwtchdg
Data Processing System	dtaprcsys
Data Chunker Engine	dtachnkreng
Engine Logging System	englogsys
Token Store	tknstr
Resource Manager	rscmgr
Data Source System	dtasrcsys
Data Request Handler	dtarqsthndlr
Data Provider	dtaprvdr
Input Cache System	inpcchsys
Output System	outsys
Engine Fail Safe System	engflsfsys
Execution Fail Safe System	execflsfsys
Input System Fail Safe	inpsysflsf
Diagnostic Event System	diagevntsys
Scheduler Manager	schdmgr
Event Trigger Manager	evnttrgmgr
Activation Manager	actvmgr
Component Manager	cmpntmgr
Module Manager	mdlmgr
Plugin System	plgnsys
Component System	cmpntsys
Agent Instruction

When generating a new abbreviation:

Check if the word exists in the standard dictionary.
Reuse the established abbreviation.
If no mapping exists:
Remove vowels except when needed for readability.
Keep leading consonants intact.
Prefer commonly used software abbreviations.
Concatenate abbreviated words without separators.
Never create multiple abbreviations for the same term.

Example:

Configuration Event Manager

Configuration -> cfg
Event -> evnt
Manager -> mgr

Result:
cfgevntmgr


This document can serve as the single source of truth for naming across diagrams, code, headers, classes, namespaces, and future architecture work.

Mixed Java, Python, and C/C++ Components
There are two ways, and real systems usually use both:

In-process: every language loads into one process and calls a shared C ABI through bindings (FFI).
Out-of-process: each language runs in its own process, and processes exchange tokens over IPC (shared memory, sockets, or a broker).
In both cases the C ABI and the fixed 64-byte token are the common contract. Every language only needs to read and write the same 64 bytes.

How Existing Systems Do It
System	Approach
PyFlink	Java runtime launches separate Python worker processes and streams data to them over gRPC (Apache Beam Fn API)
PySpark	Py4J sockets for control, Apache Arrow for bulk data
TensorFlow / PyTorch	C/C++ core with in-process Python bindings (pybind11)
ROS 2	C core (rcl) with thin per-language bindings, plus DDS between processes
Kafka ecosystem	Out-of-process only: every language has a client, and the broker is the shared medium
Option 1: In-Process (C ABI Hub)
Language	Binding technology
C++	Direct, with extern "C"
Python	ctypes, cffi, pybind11, or embedding CPython with Py_Initialize
Java	JNI, JNA, or Panama FFM (java.lang.foreign, Java 22+); the C runtime can embed the JVM with JNI_CreateJavaVM
Go	cgo
Lua	Lua C API (embedded)
The token is mapped identically in each language.

Python:

Java (Panama):

Pros: fastest path, with zero-copy and a single deployment.
Cons: a crash in any language kills the whole process. The JVM and CPython each bring their own GC, threads, and the Python GIL, and running two runtimes in one process is hard to debug.
Option 2: Out-of-Process (Component Hosts)
Each language gets one small component host process. The host loads that language's components, speaks the fluv wire protocol, and exposes the same read/write API locally. To the engine, a remote node is just a node whose ports are backed by a transport.

Transport	When to use it
Shared-memory ring buffer of 64 B slots	Same machine, highest throughput (fixed-width tokens make this simple)
nng / ZeroMQ (IPC or TCP)	Simple and cross-platform; Java has JeroMQ and Python has pynng/pyzmq
gRPC + Protobuf	Control plane, cross-machine, strongly typed
Kafka	Decoupled, persistent, cross-team
Apache Arrow (Flight)	Bulk columnar batches instead of single tokens
Pros: fault isolation (a Java crash doesn't kill the engine), independent deployment, and a prebuilt .jar can be used unchanged behind a thin host.
Cons: serialization and context-switch overhead, plus more processes to supervise (a natural job for your Heartbeat and Watchdog).
Recommended Design for fluv
Component language	Mode
C / C++	In-process, native
Lua	In-process, embedded
Python	Out-of-process host by default; in-process (cffi) as an option for trusted, hot-path nodes
Java (compiled binaries)	Out-of-process Java host that loads the jars and talks over shm or nng
Make the choice per component in the composition rather than in code:

What fluv-weave Generates
Per language: typed port wrappers (readA(), writeSum()) over the same port indexes.
The wire layer: a token codec with explicit little-endian layout, plus a schema hash checked during the handshake.
The composition: which instances run in which host, and the transport used for each arc that crosses a process boundary.
Key principle: one token layout, one port-index contract, and one schema hash. Whether a node runs in the same process or another, and in which language, is a deployment decision, not a code change.
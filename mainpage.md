# Cotila: a compile-time linear algebra system for C++

Copyright 2018 Caleb Zulawski

## Overview

Cotila (<b>co</b>mpile-<b>ti</b>me <b>l</b>inear <b>a</b>lgebra) provides a set of linear algebra functions in C++ intended for use during compile time. 
All functions available in Cotila are <b>constexpr</b>, meaning they can be used at compile-time to generate constants and lookup tables in a type-safe, transparent manner.

## Installation

Cotila is a header-only library.  Simply point your compiler to include the `include/` directory.

Code must be compiled with at least C++17 support to use Cotila.

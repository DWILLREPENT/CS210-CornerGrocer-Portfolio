# CS210-CornerGrocer-Portfolio

## Project Summary

This project is a grocery tracking program written in C++ that reads a list of purchased items from an input file and tracks how frequently each item appears. It solves the problem of organizing and analyzing purchase data without manual counting, outputting item frequencies in both text and histogram format.

## What I Did Well

I organized the program using a class structure that kept the data management logic separate from the display logic. This made the code easier to follow and debug. I also made sure the file handling was clean and that the program could gracefully handle missing input.

## Where I Could Enhance the Code

Input validation could be stronger. Right now if the file is missing or malformed, the experience isn't great. I could also add a sorting feature so the histogram displays items from most to least frequent, which would make the output more useful at a glance. Using a more efficient data structure could also improve performance at scale.

## Most Challenging Part

Working with maps in C++ and making sure I was iterating through them correctly was the biggest challenge early on. I worked through it using the course materials and cppreference.com, which I'm adding to my regular toolkit going forward.

## Transferable Skills

File I/O, map data structures, and class design are all skills that transfer directly to future C++ work and audio DSP projects where you're constantly managing data streams and structured output.

## Maintainability and Readability

I used clear variable names, commented key sections, and kept functions focused on single responsibilities so future edits wouldn't require relearning the whole program.

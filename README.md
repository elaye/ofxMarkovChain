ofxMarkovChain
=======

![MarkovChain](ofxaddons_thumbnail.png)

Introduction
------------

This is a simple openFrameworks addon for generating random states using a Markov chain. The transition matrix can be set programmatically or with a text file.

Usage
-----

Create a Markov chain and load a transition matrix like this:

	MarkovChain markov;
    markov.load("transitionMatrix.txt");

Update the state of the Markov chain:

	markov.update();

You can get the state of the Markov chain like this:

	markov.getState();

It will return an `int` representing the state of the Markov chain, starting at 0.

You can draw the Markov chain with the `draw()` method.

Examples
--------

The example `example-rainfall` depends on the ofxGui addon to work.
The example `example-random_walker` has no dependency (except ofxMarkovChain of course).

<div style="text-align:center;">
	<img src="random_walker.png" alt="Random walker">
	<em>Random walker example</em>
</div>


Compatibility
-------------
This addon was tested with Linux and openFrameworks v0.8.3

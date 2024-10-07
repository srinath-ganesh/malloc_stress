# CS463: Getting to know Malloc

## Preliminaries: The Scientific Process

What we are doing in this class as a whole may be better described as engineering than science. After all, we are only studying the effective and efficient use of man-made artifacts. That said, the computer is sufficiently complex that the scientific process provides a good workflow. For your reference, here is a brief review of the scientific method as applied to system performance.

- **Observation / Question Formulation**  
  We may observe that two apparently similar programs perform differently, say depending on whether a variable is allocated on the stack or on the heap. We may question why.

- **Falsifiable Hypothesis**  
  We may come up with one or more explanations for our observations, or hypotheses. For example, "Stack memory accesses are faster than heap memory accesses." The hypothesis doesn't have to be good, but it must be falsifiable: the hypothesis must produce predictions, that can be shown through repeatable experiment to be true or false.

  Thus, "variables with names starting with the letter q are quicker," is a valid, falsifiable hypothesis. It predicts that the access time of a variable named "qVar" will on average be lower than a variable named "sVar".

- **Experiment to Validate / Falsify Hypothesis**  

  A carefully designed experiment can then be used to test this prediction. If the experiments do not confirm the predictions, we have either falsified the hypothesis, or performed an inaccurate experiment.

Note that depending on the experiment, it can be quite difficult to convince yourself that the experiment itself is accurate. A combination of careful experimental design, and using multiple predictions and tests to validate the same hypothesis can both help build confidence in a hypothesis.

Generally, proving a hypothesis to be true is virtually impossible. However, if the hypothesis produces accurate, and falsifiable, predictions then it is a good hypothesis. At some point, you might even start calling it a theory.

## mstress - stressing out malloc

The provided program `mstress` makes several `malloc()` allocations, then frees them. 
The program takes three arguments, `-n <count>`, `-s <size>`, `-i <iterations>` and a flag `-r` to reverse the order in which chunks are freed.
Here, the `-n` says how many chunks to allocate, and `-i` says how many times to repeat the entire experiment.
The program outputs the number of CPU cycles taken for each individual operation. 

### task 1: compute mean time to allocate and free

Without changing the program, devise a script to compute the mean time taken to allocate a chunk, and the mean time to free a chunk.
The best tool for this job is `awk`. If you're not already familiar with it, take some time to write a few awk programs,
including this one. It's an excellent tool to have in your toolbox. 

### task 2: measure mean time for varying sizes

Again without modifying the program, write a small script to measure the mean time taken to allocate a chunk of memory, varying 
the size of the chunk from 8 bytes to 10000 bytes. Use `-n 1000` or higher. 

### task 3: plot the time to allocate and free

Using `gnuplot`, plot the data from above, with size on the x axis, and time taken on the Y axis. Plot the time to allocate,
free as well as free with the -r flag.

### task 4: analyze the experimental results

Answer the following questions. For each question, come up with a hypothesis, make a prediction using the hypothesis, *then* test it.

 * In the plot, allocation takes an increasing amount of time up to chunk sizes of about 4000 bytes. At that point, it takes 
a fixed amount of time. What explains the initial increase, and why does it stop increasing?
 * Freeing with `-r` is much slower than without `-r`. What explains this behavior? 
 * If you look at the individual allocation times, rather than the mean, small allocations show very large variance. What's happening there?
 * Freeing does not show the same behavior. Does anything stick out about the individual free performance?
 * With `-r` time taken to free an individual chunk changes. What explains the variance? 
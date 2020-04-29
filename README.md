## CS 5201 Final Project
Read the directions on the [course website](https://jberm6.git-pages.mst.edu/essman/homework/hw7_final/)

### Image Conversion Script
As part of your testing, you may want to use your own silhouettes.  
I have provided you with a script, `image_to_ascii.py`, that you can use
to convert your own images into the format your program is expected to process.
You can use it as follows:
`python3 image_to_ascii.py input.jpg output.txt 100`

This will import a file named `input.jpg` and write the resulting ASCII to
`output.txt`.  The `100` refers to the max size of the matrix that the output
file would require your program to solve.  If the input image would result
in a matrix larger than this threshold, it will be scaled down appropriately.

This script requires the NumPy and PIL Python libraries, and is compatible
with JPEG images only.

### Run Script
I have included a script, `run.sh`, that should be used to actually run your program,
such that one can run `./run.sh image.jpg image_data.csv 100 0`, in which the first argument is
the name of the silhouette file, the second is the name of the desired output file,
the third argument is the max matrix size as described above, and the fourth argument is the
solution you wish to run..  Feel free to modify it as you see fit, as long as its current
behavior remains intact.

Sample images you can use with this script are available in the `images/` directory.
